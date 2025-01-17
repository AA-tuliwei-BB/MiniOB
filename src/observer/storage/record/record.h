/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/5/4.
//

#pragma once

#include <stddef.h>
#include <vector>
#include <limits>
#include <sstream>

#include "common/rc.h"
#include "common/types.h"
#include "common/log/log.h"
#include "storage/index/index_meta.h"
#include "storage/field/field_meta.h"

class Field;

/**
 * @brief 标识一个记录的位置
 * 一个记录是放在某个文件的某个页面的某个槽位。这里不记录文件信息，记录页面和槽位信息
 */
struct RID
{
  PageNum page_num;  // record's page number
  // SlotNum slot_num;  // record's slot number
  OffsetNum offset; // offset in the page

  RID() = default;
  RID(const PageNum _page_num, const OffsetNum _offset) : page_num(_page_num), offset(_offset) {}

  const std::string to_string() const
  {
    std::stringstream ss;
    ss << "PageNum:" << page_num << ", Offset:" << offset;
    return ss.str();
  }

  bool operator<(const RID &other) const {
    if (page_num == other.page_num) {
      return offset < other.offset;
    } else {
      return page_num < other.page_num;
    }
  }

  bool operator==(const RID &other) const { return page_num == other.page_num && offset == other.offset; }

  bool operator!=(const RID &other) const { return !(*this == other); }

  static int compare(const RID *rid1, const RID *rid2)
  {
    int page_diff = rid1->page_num - rid2->page_num;
    if (page_diff != 0) {
      return page_diff;
    } else {
      return rid1->offset - rid2->offset ;
    }
  }

  /**
   * 返回一个不可能出现的最小的RID
   * 虽然page num 0和offset 0都是合法的，但是page num 0通常用于存放meta数据，所以对数据部分来说都是
   * 不合法的. 这里在bplus tree中查找时会用到。
   */
  static RID *min()
  {
    static RID rid{0, 0};
    return &rid;
  }

  /**
   * @brief 返回一个“最大的”RID
   * 我们假设page num和offset都不会使用对应数值类型的最大值
   */
  static RID *max()
  {
    static RID rid{std::numeric_limits<PageNum>::max(), std::numeric_limits<OffsetNum>::max()};
    return &rid;
  }
};

/**
 * @brief 表示一个记录
 * 当前的记录都是连续存放的空间（内存或磁盘上）。
 * 为了提高访问的效率，record通常直接记录指向页面上的内存，但是需要保证访问这种数据时，拿着锁资源。
 * 为了方便，也提供了复制内存的方法。可以参考set_data_owner
 */
class Record
{
public:
  Record() = default;
  ~Record()
  {
    clear_data();
  }

  Record(const Record &other)
  {
    rid_     = other.rid_;
    data_    = other.data_;
    len_     = other.len_;
    owner_   = other.owner_;
    null_    = other.null_;
    offset_  = other.offset_;

    if (other.owner_) {
      char *tmp = (char *)malloc(other.len_);
      ASSERT(nullptr != tmp, "failed to allocate memory. size=%d", other.len_);
      memcpy(tmp, other.data_, other.len_);
      data_ = tmp;
    }
  }

  Record &operator=(const Record &other)
  {
    if (this == &other) {
      return *this;
    }

    this->~Record();
    new (this) Record(other);
    return *this;
  }

  void clear_data()
  {
    if (owner_ && data_ != nullptr) {
      free(data_);
      owner_ = false;
      data_ = nullptr;
    }
  }

  void set_data(char *data, int len = 0)
  {
    this->data_ = data;
    this->len_  = len;
  }
  void set_data_owner(char *data, int len)
  {
    ASSERT(len != 0, "the len of data should not be 0");
    if (owner_ && data_ != nullptr) {
      free(data_);
      data_ = nullptr;
    }

    this->data_  = data;
    this->len_   = len;
    this->owner_ = true;
  }

  bool is_null(int field_id) const
  {
    return null_[field_id];
  }

  char *get_field_data(int field_id)
  {
    return data_ + offset_[field_id];
  }

  const char *get_field_data(int field_id) const
  {
    return data_ + offset_[field_id];
  }

  const std::vector<int> & offset() const { return offset_; }
  const std::vector<bool> & null() const { return null_; }

  std::vector<int> & offset() { return offset_; }
  std::vector<bool> & null() { return null_; }

  char       *data() { return this->data_; }
  const char *data() const { return this->data_; }
  int         len() const { return this->len_; }
  int         size() const { return *--offset_.end(); }

  void set_rid(const RID &rid) { this->rid_ = rid; }
  void set_rid(const PageNum page_num, const OffsetNum offset)
  {
    this->rid_.page_num = page_num;
    this->rid_.offset = offset;
  }
  RID       &rid() { return rid_; }
  const RID &rid() const { return rid_; }

private:
  RID rid_;

  char        *data_    = nullptr;
  int          len_     = 0;      /// 如果不是record自己来管理内存，这个字段可能是无效的
  bool         owner_   = false;  /// 表示当前是否由record来管理内存
  std::vector<bool> null_;             /// 字段是否为空
  std::vector<int>  offset_;           /// 字段偏移量，最后一个为边界
};
