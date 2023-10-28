/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Meiyi & Longda on 2021/4/13.
//
#include "storage/record/record_manager.h"
#include "common/log/log.h"
#include "common/lang/bitmap.h"
#include "storage/common/condition_filter.h"
#include "storage/trx/trx.h"
#include "record_manager.h"

using namespace common;

static constexpr int PAGE_HEADER_SIZE = (sizeof(PageHeader));

/**
 * @brief 8字节对齐
 * 注: ceiling(a / b) = floor((a + b - 1) / b)
 * 
 * @param size 待对齐的字节数
 */
int align8(int size) { return (size + 7) / 8 * 8; }

/**
 * @brief 计算指定大小的页面，可以容纳多少个记录
 *
 * @param page_size   页面的大小
 * @param record_size 记录的大小
 */
int page_record_capacity(int page_size, int record_size)
{
  // (record_capacity * record_size) + record_capacity/8 + 1 <= (page_size - fix_size)
  // ==> record_capacity = ((page_size - fix_size) - 1) / (record_size + 0.125)
  return (int)((page_size - PAGE_HEADER_SIZE - 1) / (record_size + 0.125));
}

/**
 * @brief bitmap 记录了某个位置是否有有效的记录数据，这里给定记录个数时需要多少字节来存放bitmap数据
 * 注: ceiling(a / b) = floor((a + b - 1) / b)
 *
 * @param record_capacity 想要存放多少记录
 */
int page_bitmap_size(int record_capacity) { return (record_capacity + 7) / 8; }



///////////////////////////////////////////////////////////////////

int ExtraRecord::data_start_offset() const { return align8(length.size() * sizeof(int) + 1 + (null.size() + 7) / 8); }

RC ExtraRecord::from_record(const Record &record, const TableMeta &table_meta)
{
  length.clear();
  null.clear();
  int field_count = table_meta.field_metas()->size();
  if (field_count != record.null().size()) {
    return RC::INTERNAL;
  }
  data     = record.data();
  data_len = record.len();

  const std::vector<FieldMeta> &field_metas = *table_meta.field_metas();
  for (int i = 0; i < field_count; ++i) {
    // 变长，添加变长字段长度
    if (field_metas[i].type() == TEXTS) {
      length.push_back(record.offset()[i + 1] - record.offset()[i]);
    }
    // 可空，添加是否为空
    if (field_metas[i].nullable()) {
      null.push_back(record.is_null(i));
    }
  }
  length_size = length.size();
  null_size   = null.size();

  // 溢出
  int max_size = BP_PAGE_DATA_SIZE - sizeof(PageHeader) - 4;
  if (data_start_offset() + data_len > max_size) {
    len = data_start_offset() + sizeof(RID);
    int data_max_size = max_size - sizeof(RID);
    for (int i = 0; i < data_len; i += data_max_size) {
      overflow_data.push_back(OverFlowData(std::min(data_len - i, data_max_size), data + i));
    }
    overflow_flag = true;
  } else {
    len = data_start_offset() + data_len;
  }
  return RC::SUCCESS;
}

RC ExtraRecord::to_record(DiskBufferPool *disk_buffer_pool_, const TableMeta *table_meta_, bool readonly, Record *rec)
{
  // 获取record的数据
  if (!overflow_flag) {
    // 未溢出
    rec->clear_data();
    // 此时extra.data指向frame中的某个位置，原始位置不是const的，因此可以进行转化
    rec->set_data(const_cast<char *>(data));
  } else {

    // 对于溢出的数据，只能使用只读操作，否则报错
    // 但由于delete操作会让迭代器readonly为false（为什么啊），此处暂时废弃
    //if (!readonly) {
    //  return RC::INTERNAL;
    //}
    char *rec_data = (char *)malloc(data_len);
    rec->set_data_owner(rec_data, data_len);
    char *current_positon = rec_data;
    RID next = overflow_data[0].rid;
    overflow_data.clear();

    while (next != *RID::min()) {
      OverFlowData overflowdata;
      // 需要使用新的 page_handler
      RecordPageHandler data_page_handler;
      RC ret = data_page_handler.init(*disk_buffer_pool_, next.page_num, table_meta_, readonly);
      if (OB_FAIL(ret)) {
        LOG_ERROR("Failed to init record page handler.page number=%d", next.page_num);
        return ret;
      }

      data_page_handler.get_data(&next, &overflowdata);
      memcpy(current_positon, overflowdata.data, overflowdata.len);
      current_positon += overflowdata.len;
      next = overflowdata.next;
      overflow_data.push_back(overflowdata);
      data_page_handler.cleanup();
    }
  }

  // 获取到了record的数据，处理record的其他参数
  rec->rid() = rid;
  rec->null().clear();
  rec->offset().clear();
  int null_p = 0, offset_p = 0, current_offset = 0;
  rec->offset().push_back(current_offset);
  for (auto &field : *table_meta_->field_metas()) {
    if (field.nullable()) {
      rec->null().push_back(null[null_p++]);
    } else {
      rec->null().push_back(false);
    }
    int field_size = field.len() != 0 ? field.len() : length[offset_p++];
    current_offset += field_size;
    rec->offset().push_back(current_offset);
  }
  return RC::SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////
RecordPageIterator::RecordPageIterator() {}
RecordPageIterator::~RecordPageIterator() {}

void RecordPageIterator::init(RecordPageHandler &record_page_handler, int32_t start_num /*=1*/)
{
  record_page_handler_ = &record_page_handler;
  page_num_            = record_page_handler.get_page_num();
  record_num_          = record_page_handler.page_header_->number;
  next_num_            = record_page_handler.get_list_next(start_num);
}

bool RecordPageIterator::has_next() { return next_num_ <= record_num_ && next_num_ > 0; }

RC RecordPageIterator::next(ExtraRecord &record)
{
  if (!has_next()) {
    return RC::RECORD_EOF;
  }
  int32_t offset = *record_page_handler_->get_list(next_num_);
  RID rid(record_page_handler_->get_page_num(), offset);
  record_page_handler_->get_record(&rid, &record);
  next_num_ = record_page_handler_->get_list_next(next_num_ + 1);
  return RC::SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////

RecordPageHandler::~RecordPageHandler() { cleanup(); }

RC RecordPageHandler::init(DiskBufferPool &buffer_pool, PageNum page_num, const TableMeta *table_meta, bool readonly)
{
  if (disk_buffer_pool_ != nullptr) {
    LOG_WARN("Disk buffer pool has been opened for page_num %d.", page_num);
    return RC::RECORD_OPENNED;
  }

  RC ret = RC::SUCCESS;
  if ((ret = buffer_pool.get_this_page(page_num, &frame_)) != RC::SUCCESS) {
    LOG_ERROR("Failed to get page handle from disk buffer pool. ret=%d:%s", ret, strrc(ret));
    return ret;
  }

  char *data = frame_->data();

  if (readonly) {
    frame_->read_latch();
  } else {
    frame_->write_latch();
  }
  disk_buffer_pool_ = &buffer_pool;
  readonly_         = readonly;
  page_header_      = (PageHeader *)(data);
  table_meta_       = table_meta;

  LOG_TRACE("Successfully init page_num %d.", page_num);
  return ret;
}

RC RecordPageHandler::recover_init(DiskBufferPool &buffer_pool, PageNum page_num)
{
  if (disk_buffer_pool_ != nullptr) {
    LOG_WARN("Disk buffer pool has been opened for page_num %d.", page_num);
    return RC::RECORD_OPENNED;
  }

  RC ret = RC::SUCCESS;
  if ((ret = buffer_pool.get_this_page(page_num, &frame_)) != RC::SUCCESS) {
    LOG_ERROR("Failed to get page handle from disk buffer pool. ret=%d:%s", ret, strrc(ret));
    return ret;
  }

  char *data = frame_->data();

  frame_->write_latch();
  disk_buffer_pool_ = &buffer_pool;
  readonly_         = false;
  page_header_      = (PageHeader *)(data);

  buffer_pool.recover_page(page_num);

  LOG_TRACE("Successfully init page_num %d.", page_num);
  return ret;
}

RC RecordPageHandler::init_empty_page(DiskBufferPool &buffer_pool, PageNum page_num, const TableMeta *table_meta)
{
  RC ret = init(buffer_pool, page_num, table_meta, false /*readonly*/);
  if (ret != RC::SUCCESS) {
    LOG_ERROR("Failed to init empty page page_num:record_size %d:%d.", page_num);
    return ret;
  }

  page_header_->number = 0;
  page_header_->tail   = PAGE_HEADER_SIZE;

  if ((ret = buffer_pool.flush_page(*frame_)) != RC::SUCCESS) {
    LOG_ERROR("Failed to flush page header %d:%d.", buffer_pool.file_desc(), page_num);
    return ret;
  }

  return RC::SUCCESS;
}

RC RecordPageHandler::cleanup()
{
  if (disk_buffer_pool_ != nullptr) {
    if (readonly_) {
      frame_->read_unlatch();
    } else {
      frame_->write_unlatch();
    }
    disk_buffer_pool_->unpin_page(frame_);
    disk_buffer_pool_ = nullptr;
  }

  return RC::SUCCESS;
}

RC RecordPageHandler::insert_record(const ExtraRecord &record, RID *rid)
{
  ASSERT(readonly_ == false, "cannot insert record into page while the page is readonly");

  int available_size = BP_PAGE_DATA_SIZE - page_header_->tail - page_header_->number * 4;
  if (available_size < record.len + 4) {
    LOG_WARN("Page is full, page_num %d:%d.", disk_buffer_pool_->file_desc(), frame_->page_num());
    return RC::RECORD_NOMEM;
  }

  page_header_->number++;
  int32_t offset = page_header_->tail;
  page_header_->tail += record.len;
  *get_list(page_header_->number) = offset;

  char *record_data = get_record_data(offset);
  //写入length
  for (int i = 0; i < record.length_size; ++i) {
    *reinterpret_cast<int *>(record_data) = record.length[i];
    record_data += 4;
  }
  *reinterpret_cast<bool *>(record_data) = record.overflow_flag;
  record_data++;

  int bitmap_size = (record.null_size + 7) / 8;
  Bitmap bitmap(record_data, bitmap_size);
  for (int i = 0; i < record.null_size; ++i) {
    if (record.null[i]) {
      bitmap.set_bit(i);
    } else {
      bitmap.clear_bit(i);
    }
  }

  record_data = get_record_data(offset) + record.data_start_offset();
  if (!record.overflow_flag) {
    memcpy(record_data, record.data, record.data_len);
  } else {
    ASSERT(record.overflow_data.size() != 0, "Null OverflowData");
    *reinterpret_cast<RID *>(record_data) = record.overflow_data.begin()->rid;
  }

  frame_->mark_dirty();

  if (rid) {
    rid->page_num = get_page_num();
    rid->offset = offset;
  }

  // LOG_TRACE("Insert record. rid page_num=%d, slot num=%d", get_page_num(), index);
  return RC::SUCCESS;
}

RC RecordPageHandler::insert_data(const OverFlowData &data, RID *rid, RID* next/*=nullptr*/)
{
  ASSERT(readonly_ == false, "cannot insert record into page while the page is readonly");

  int available_size = BP_PAGE_DATA_SIZE - page_header_->tail - page_header_->number * 4;
  if (available_size < data.len + sizeof(RID) + 4) {
    LOG_WARN("Page is full, page_num %d:%d.", disk_buffer_pool_->file_desc(), frame_->page_num());
    return RC::RECORD_NOMEM;
  }

  int32_t offset = page_header_->tail;
  page_header_->tail += data.len + sizeof(RID) + 4;
  char *record_data = get_record_data(offset);

  // 写入next
  if (next != nullptr) {
    *reinterpret_cast<RID *>(record_data) = *next;
  } else {
    *reinterpret_cast<RID *>(record_data) = *RID::min();
  }
  //写入length
  *reinterpret_cast<int32_t*>(record_data + sizeof(RID)) = data.len;
  memcpy(record_data + sizeof(RID) + 4, data.data, data.len);

  frame_->mark_dirty();

  if (rid != nullptr) {
    rid->page_num = get_page_num();
    rid->offset = offset;
  }

  // LOG_TRACE("Insert record. rid page_num=%d, slot num=%d", get_page_num(), index);
  return RC::SUCCESS;
}

RC RecordPageHandler::recover_insert_record(const ExtraRecord &record, const RID &rid)
{
  ASSERT(readonly_ == false, "cannot insert record into page while the page is readonly");

  int available_size = BP_PAGE_DATA_SIZE - page_header_->tail - page_header_->number * 4;
  if (available_size < record.len + 4) {
    LOG_WARN("Page is full, page_num %d:%d.", disk_buffer_pool_->file_desc(), frame_->page_num());
    return RC::RECORD_NOMEM;
  }

  page_header_->number++;
  int32_t offset = rid.offset;
  page_header_->tail = std::max(page_header_->tail, offset + record.len);

  char *record_data = get_record_data(offset);
  //写入length
  for (int i = 0; i < record.length_size; ++i) {
    *reinterpret_cast<int *>(record_data) = record.length[i];
    record_data += 4;
  }
  *reinterpret_cast<bool *>(record_data) = record.overflow_flag;
  record_data++;

  int bitmap_size = (record.null_size + 7) / 8;
  Bitmap bitmap(record_data, bitmap_size);
  for (int i = 0; i < record.null_size; ++i) {
    if (record.null[i]) {
      bitmap.set_bit(i);
    } else {
      bitmap.clear_bit(i);
    }
  }

  record_data = get_record_data(offset) + record.data_start_offset();
  if (!record.overflow_flag) {
    memcpy(record_data, record.data, record.data_len);
  } else {
    ASSERT(record.overflow_data.size() != 0, "Null OverflowData");
    *reinterpret_cast<RID *>(record_data) = record.overflow_data.begin()->rid;
  }

  frame_->mark_dirty();

  // LOG_TRACE("Insert record. rid page_num=%d, slot num=%d", get_page_num(), index);
  return RC::SUCCESS;
}

RC RecordPageHandler::delete_record(const RID *rid)
{
  ASSERT(readonly_ == false, "cannot delete record from page while the page is readonly");
  for (int i = 0; i < page_header_->number; ++i) {
    int32_t *offset = get_list(i);
    if (*offset == rid->offset) {
      *offset = 0;
      return RC::SUCCESS;
    }
  }
  return RC::RECORD_NOT_EXIST;
}

RC RecordPageHandler::get_record(const RID *rid, ExtraRecord *rec)
{
  if (rec == nullptr) {
    return RC::INVALID_ARGUMENT;
  }
  rec->rid = *rid;
  int offset = rid->offset;
  char *record_data = get_record_data(offset);
  rec->length_size = table_meta_->variable_length_count();
  rec->null_size   = table_meta_->nullable_count();
  rec->length.resize(rec->length_size);
  rec->null.resize(rec->null_size);

  for (int i = 0; i < rec->length_size; ++i) {
    rec->length[i] = *(reinterpret_cast<int32_t *>(record_data));
    record_data += 4;
  }
  rec->overflow_flag = *(reinterpret_cast<bool *>(record_data));
  ++record_data;

  Bitmap bitmap(record_data, (rec->null_size + 7) / 8);
  for (int i = 0; i < rec->null_size; ++i) {
    rec->null[i] = bitmap.get_bit(i);
  }

  record_data = get_record_data(offset) + rec->data_start_offset();
  // 溢出
  if (rec->overflow_flag) {
    OverFlowData next;
    next.rid = *(reinterpret_cast<RID *>(record_data));
    rec->overflow_data.push_back(next);
  } else {
    // 未溢出
    int now = 0; // 目前是第几个可变长字段
    rec->data = record_data;
    rec->data_len = 0;
    for (const FieldMeta &field : *table_meta_->field_metas()) {
      if (field.len() == 0) {
        rec->data_len += rec->length[now];
        ++now;
      } else {
        rec->data_len += field.len();
      }
    }
  }
  return RC::SUCCESS;
}

RC RecordPageHandler::get_data(const RID *rid, OverFlowData *data)
{
  if (data == nullptr) {
    return RC::INVALID_ARGUMENT;
  }
  int offset = rid->offset;
  char *record_data = get_record_data(offset);

  data->rid  = *rid;
  data->next = *(reinterpret_cast<RID *>(record_data));
  data->len  = *(reinterpret_cast<int *>(record_data + sizeof(RID)));
  data->data = record_data + sizeof(RID) + sizeof(data->len);
  return RC::SUCCESS;
}

void RecordPageHandler::make_dirty() { frame_->mark_dirty(); }

PageNum RecordPageHandler::get_page_num() const
{
  if (nullptr == page_header_) {
    return (PageNum)(-1);
  }
  return frame_->page_num();
}

int32_t RecordPageHandler::free_space() const
{
  return BP_PAGE_DATA_SIZE - page_header_->tail - page_header_->number * sizeof(int);
}

int32_t *RecordPageHandler::get_list() { return reinterpret_cast<int32_t *>(frame_->data() + BP_PAGE_DATA_SIZE); }

int32_t* RecordPageHandler::get_list(int32_t pos)
{
  if (pos > page_header_->number || pos <= 0) {
    return nullptr;;
  } else {
    return get_list() - pos;
  }
}

int32_t RecordPageHandler::get_list_next(int32_t current)
{
  int32_t *list_ = get_list();
  while (current <= page_header_->number && *(list_ - current) == 0) {
    ++current;
  }
  return current;
}

bool RecordPageHandler::is_full()
{
  return table_meta_->min_size() + 4 > BP_PAGE_DATA_SIZE - page_header_->tail;
}

////////////////////////////////////////////////////////////////////////////////

RecordFileHandler::~RecordFileHandler() { this->close(); }

RC RecordFileHandler::init(DiskBufferPool *buffer_pool, const TableMeta *table_meta)
{
  if (disk_buffer_pool_ != nullptr) {
    LOG_ERROR("record file handler has been openned.");
    return RC::RECORD_OPENNED;
  }

  disk_buffer_pool_ = buffer_pool;
  table_meta_       = table_meta;

  RC rc = init_free_pages();

  LOG_INFO("open record file handle done. rc=%s", strrc(rc));
  return RC::SUCCESS;
}

void RecordFileHandler::close()
{
  if (disk_buffer_pool_ != nullptr) {
    free_pages_.clear();
    disk_buffer_pool_ = nullptr;
  }
}

RC RecordFileHandler::update_record_field(const RID &rid, const FieldMeta *field, std::function<void(char *)> updater)
{
  // 判断是不是可变的，如果是，终止
  if (field->len() == 0) {
    return RC::INTERNAL;
  }
  // 获取rid对应的ExtraRecord
  RecordPageHandler page_handler;
  page_handler.init(*disk_buffer_pool_, rid.page_num, table_meta_, false);
  ExtraRecord extra;
  page_handler.get_record(&rid, &extra);
  
  // 计算字段对应的偏移
  int offset = 0;
  int length_pos = 0;
  bool found = false;
  for (auto &field_it : *table_meta_->field_metas()) {
    // 找到该字段
    if (field_it.name() == field->name()) {
      found = true;
      break;
    }
    if (field_it.len() == 0) {
      offset += extra.length[length_pos++];
    } else {
      offset += field_it.len();
    }
  }
  if (!found) {
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  char *field_data;
  // 从ExtraRecord中找到偏移
  if (extra.overflow_flag) {
    // extra 是溢出的，从溢出数据中找
    RID          data_rid = extra.overflow_data[0].rid;
    OverFlowData overflow_data;
    while (true)
    {
      page_handler.cleanup();
      RC rc = page_handler.init(*disk_buffer_pool_, data_rid.page_num, table_meta_, false);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      rc = page_handler.get_data(&data_rid, &overflow_data);
      if (offset < overflow_data.len) {
        field_data = const_cast<char *>(overflow_data.data) + offset;
        break;
      } else {
        offset -= overflow_data.len;
        data_rid = overflow_data.next;
      }
    }
  } else {
    // 未溢出，直接找
    field_data = const_cast<char *>(extra.data) + offset;
  }

  // 执行updater
  updater(field_data);
  page_handler.make_dirty();
  return RC();
}

RC RecordFileHandler::init_free_pages()
{
  // 遍历当前文件上所有页面，找到没有满的页面
  // 这个效率很低，会降低启动速度
  // NOTE: 由于是初始化时的动作，所以不需要加锁控制并发

  RC rc = RC::SUCCESS;

  BufferPoolIterator bp_iterator;
  bp_iterator.init(*disk_buffer_pool_);
  RecordPageHandler record_page_handler;
  PageNum           current_page_num = 0;

  while (bp_iterator.has_next()) {
    current_page_num = bp_iterator.next();

    rc = record_page_handler.init(*disk_buffer_pool_, current_page_num, table_meta_, true /*readonly*/);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to init record page handler. page num=%d, rc=%d:%s", current_page_num, rc, strrc(rc));
      return rc;
    }

    if (!record_page_handler.is_full()) {
      free_pages_.insert(current_page_num);
    }
    record_page_handler.cleanup();
  }
  LOG_INFO("record file handler init free pages done. free page num=%d, rc=%s", free_pages_.size(), strrc(rc));
  return rc;
}

RC RecordFileHandler::get_new_page(RecordPageHandler &record_page_handler, PageNum &current_page_num)
{
    RC ret = RC::SUCCESS;
    Frame *frame = nullptr;
    if ((ret = disk_buffer_pool_->allocate_page(&frame)) != RC::SUCCESS) {
      LOG_ERROR("Failed to allocate page while inserting record. ret:%d", ret);
      return ret;
    }

    current_page_num = frame->page_num();

    ret = record_page_handler.init_empty_page(*disk_buffer_pool_, current_page_num, table_meta_);
    if (ret != RC::SUCCESS) {
      frame->unpin();
      LOG_ERROR("Failed to init empty page. ret:%d", ret);
      // this is for allocate_page
      return ret;
    }

    // frame 在allocate_page的时候，是有一个pin的，在init_empty_page时又会增加一个，所以这里手动释放一个
    frame->unpin();

    // 这里的加锁顺序看起来与上面是相反的，但是不会出现死锁
    // 上面的逻辑是先加lock锁，然后加页面写锁，这里是先加上
    // 了页面写锁，然后加lock的锁，但是不会引起死锁。
    // 为什么？
    // 显然，这里的锁的页面不在free_pages中，故不会被上面访问，即不会被锁住
    // 因此，不会出现死锁
    lock_.lock();
    free_pages_.insert(current_page_num);
    lock_.unlock();
    return ret;
}

RC RecordFileHandler::insert_record(const Record &record, RID *rid)
{
  RC ret = RC::SUCCESS;

  RecordPageHandler record_page_handler;
  bool              page_found       = false;
  PageNum           current_page_num = 0;
  ExtraRecord       extra;

  if ((ret = extra.from_record(record, *table_meta_)) != RC::SUCCESS) {
    LOG_ERROR("failed to get extra_record");
    return ret;
  }

  // 当前要访问free_pages对象，所以需要加锁。在非并发编译模式下，不需要考虑这个锁
  lock_.lock();

  // 找到能放下ExtraRecord的页面
  for (auto it : free_pages_) {
    current_page_num = it;

    ret = record_page_handler.init(*disk_buffer_pool_, current_page_num, table_meta_, false /*readonly*/);
    if (ret != RC::SUCCESS) {
      lock_.unlock();
      LOG_WARN("failed to init record page handler. page num=%d, rc=%d:%s", current_page_num, ret, strrc(ret));
      return ret;
    }

    if (record_page_handler.free_space() >= extra.len) {
      page_found = true;
      break;
    } else if (record_page_handler.is_full()) {
      free_pages_.erase(free_pages_.begin());
    }
    record_page_handler.cleanup();
  }
  lock_.unlock();  // 如果找到了一个有效的页面，那么此时已经拿到了页面的写锁

  // 如果溢出，为每个溢出部分单独分配一个新的页面
  if (extra.overflow_flag) {
    RID next_rid = *RID::min();
    for (auto it = extra.overflow_data.rbegin(); it != extra.overflow_data.rend(); ++it) {
      ret = get_new_page(record_page_handler, current_page_num);
      if (ret != RC::SUCCESS) {
        // 先不考虑回收的问题
        return ret;
      }
      RID rid;
      record_page_handler.insert_data(*it, &rid, &next_rid);
      record_page_handler.cleanup();
      next_rid = rid;
    }
    // insert_record会从over_flow_data[0]中读取next的位置
    // 有点抽象，有空可以优化一下
    extra.overflow_data[0].rid = next_rid;
  }

  // 找不到就分配一个新的页面
  if (!page_found) {
    ret = get_new_page(record_page_handler, current_page_num);
    if (ret != RC::SUCCESS) {
      return ret;
    }
  }
  // record_page_handler 析构时会 cleanup
  return record_page_handler.insert_record(extra, rid);
}

/* MYTODO 暂时封存，要用再写
RC RecordFileHandler::recover_insert_record(const Record &record, int record_size, const RID &rid)
{
  RC ret = RC::SUCCESS;

  RecordPageHandler record_page_handler;

  ret = record_page_handler.recover_init(*disk_buffer_pool_, rid.page_num);
  if (ret != RC::SUCCESS) {
    LOG_WARN("failed to init record page handler. page num=%d, rc=%s", rid.page_num, strrc(ret));
    return ret;
  }

  return record_page_handler.recover_insert_record(data, rid);
}
*/

RC RecordFileHandler::delete_record(const RID *rid)
{
  RC rc = RC::SUCCESS;

  RecordPageHandler page_handler;
  if ((rc = page_handler.init(*disk_buffer_pool_, rid->page_num, table_meta_, false /*readonly*/)) != RC::SUCCESS) {
    LOG_ERROR("Failed to init record page handler.page number=%d. rc=%s", rid->page_num, strrc(rc));
    return rc;
  }

  rc = page_handler.delete_record(rid);
  // 📢 这里注意要清理掉资源，否则会与insert_record中的加锁顺序冲突而可能出现死锁
  // delete record的加锁逻辑是拿到页面锁，删除指定记录，然后加上和释放record manager锁
  // insert record是加上 record manager锁，然后拿到指定页面锁再释放record manager锁
  page_handler.cleanup();
  if (OB_SUCC(rc)) {
    // 因为这里已经释放了页面锁，并发时，其它线程可能又把该页面填满了，那就不应该再放入 free_pages_
    // 中。但是这里可以不关心，因为在查找空闲页面时，会自动过滤掉已经满的页面
    lock_.lock();
    free_pages_.insert(rid->page_num);
    LOG_TRACE("add free page %d to free page list", rid->page_num);
    lock_.unlock();
  }
  return rc;
}

RC RecordFileHandler::get_record(RecordPageHandler &page_handler, const RID *rid, bool readonly, Record *rec)
{
  if (nullptr == rid || nullptr == rec) {
    LOG_ERROR("Invalid rid %p or rec %p, one of them is null.", rid, rec);
    return RC::INVALID_ARGUMENT;
  }

  RC ret = page_handler.init(*disk_buffer_pool_, rid->page_num, table_meta_, readonly);
  if (OB_FAIL(ret)) {
    LOG_ERROR("Failed to init record page handler.page number=%d", rid->page_num);
    return ret;
  }

  rec->set_rid(*rid);

  // 读取 ExtraRecord
  ExtraRecord extra;
  page_handler.get_record(rid, &extra);
  return extra.to_record(disk_buffer_pool_, table_meta_, readonly, rec);
}

RC RecordFileHandler::visit_record(const RID &rid, bool readonly, std::function<void(Record &)> visitor)
{
  RecordPageHandler page_handler;
  Record record;
  RC rc = get_record(page_handler, &rid, readonly, &record);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to get record. rid=%s, rc=%s", rid.to_string().c_str(), strrc(rc));
    return rc;
  }

  visitor(record);
  return rc;
}

////////////////////////////////////////////////////////////////////////////////

RecordFileScanner::~RecordFileScanner() { close_scan(); }

RC RecordFileScanner::open_scan(
    Table *table, DiskBufferPool &buffer_pool, Trx *trx, bool readonly, ConditionFilter *condition_filter)
{
  close_scan();

  table_            = table;
  disk_buffer_pool_ = &buffer_pool;
  trx_              = trx;
  // MYTODO 需要并发时处理
  //readonly_         = readonly;
  readonly_ = true;

  RC rc = bp_iterator_.init(buffer_pool);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to init bp iterator. rc=%d:%s", rc, strrc(rc));
    return rc;
  }
  condition_filter_ = condition_filter;

  rc = fetch_next_record();
  if (rc == RC::RECORD_EOF) {
    rc = RC::SUCCESS;
  }
  return rc;
}

/**
 * @brief 从当前位置开始找到下一条有效的记录
 *
 * 如果当前页面还有记录没有访问，就遍历当前的页面。
 * 当前页面遍历完了，就遍历下一个页面，然后找到有效的记录
 */
RC RecordFileScanner::fetch_next_record()
{
  RC rc = RC::SUCCESS;
  if (record_page_iterator_.is_valid()) {
    // 当前页面还是有效的，尝试看一下是否有有效记录
    rc = fetch_next_record_in_page();
    if (rc == RC::SUCCESS || rc != RC::RECORD_EOF) {
      // 有有效记录：RC::SUCCESS
      // 或者出现了错误，rc != (RC::SUCCESS or RC::RECORD_EOF)
      // RECORD_EOF 表示当前页面已经遍历完了
      return rc;
    }
  }

  // 上个页面遍历完了，或者还没有开始遍历某个页面，那么就从一个新的页面开始遍历查找
  while (bp_iterator_.has_next()) {
    PageNum page_num = bp_iterator_.next();
    record_page_handler_.cleanup();
    rc = record_page_handler_.init(*disk_buffer_pool_, page_num, &table_->table_meta(), readonly_);
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to init record page handler. page_num=%d, rc=%s", page_num, strrc(rc));
      return rc;
    }

    record_page_iterator_.init(record_page_handler_);
    rc = fetch_next_record_in_page();
    if (rc == RC::SUCCESS || rc != RC::RECORD_EOF) {
      // 有有效记录：RC::SUCCESS
      // 或者出现了错误，rc != (RC::SUCCESS or RC::RECORD_EOF)
      // RECORD_EOF 表示当前页面已经遍历完了
      return rc;
    }
  }

  // 所有的页面都遍历完了，没有数据了
  next_record_.rid().offset = -1;
  record_page_handler_.cleanup();
  return RC::RECORD_EOF;
}

/**
 * @brief 遍历当前页面，尝试找到一条有效的记录
 */
RC RecordFileScanner::fetch_next_record_in_page()
{
  RC rc = RC::SUCCESS;
  while (record_page_iterator_.has_next()) {
    rc = record_page_iterator_.next(next_extra_record_);
    if (rc != RC::SUCCESS) {
      const auto page_num = record_page_handler_.get_page_num();
      LOG_TRACE("failed to get next record from page. page_num=%d, rc=%s", page_num, strrc(rc));
      return rc;
    }

    next_extra_record_.to_record(disk_buffer_pool_, &table_->table_meta(), readonly_, &next_record_);

    // 如果有过滤条件，就用过滤条件过滤一下  (现在是没有的
    if (condition_filter_ != nullptr && !condition_filter_->filter(next_record_)) {
      continue;
    }

    // 如果是某个事务上遍历数据，还要看看事务访问是否有冲突
    if (trx_ == nullptr) {
      return rc;
    }

    // 让当前事务探测一下是否访问冲突，或者需要加锁、等锁等操作，由事务自己决定
    rc = trx_->visit_record(table_, next_record_, readonly_);
    if (rc == RC::RECORD_INVISIBLE) {
      // 可以参考MvccTrx，表示当前记录不可见
      // 这种模式仅在 readonly 事务下是有效的
      continue;
    }
    return rc;
  }

  next_record_.rid().offset = -1;
  return RC::RECORD_EOF;
}

RC RecordFileScanner::close_scan()
{
  if (disk_buffer_pool_ != nullptr) {
    disk_buffer_pool_ = nullptr;
  }

  if (condition_filter_ != nullptr) {
    condition_filter_ = nullptr;
  }

  record_page_handler_.cleanup();

  return RC::SUCCESS;
}

bool RecordFileScanner::has_next() { return next_record_.rid().offset != -1; }

RC RecordFileScanner::next(Record &record)
{
  record = next_record_;

  RC rc = fetch_next_record();
  if (rc == RC::RECORD_EOF) {
    rc = RC::SUCCESS;
  }
  return rc;
}
