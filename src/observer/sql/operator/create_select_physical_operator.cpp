#include "create_select_physical_operator.h"
#include "sql/stmt/create_table_stmt.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"
#include "storage/db/db.h"

RC CreateSelectPhysicalOperator::open(Trx *trx)
{
  if (children_.size() != 1) {
    LOG_ERROR("create-select: not 1 child operator");
    return RC::INTERNAL;
  }

  RC rc = children_[0]->open(trx);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  const int attribute_count = static_cast<int>(create_table_stmt_->attr_infos().size());
  const char *table_name = create_table_stmt_->table_name().c_str();
  rc = db_->create_table(table_name, attribute_count, create_table_stmt_->attr_infos().data());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("fail to create table");
    return rc;
  }

  table_ = db_->find_table(table_name);
  trx_ = trx;
  return rc;
}

RC CreateSelectPhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  while ((rc = children_[0]->next()) == RC::SUCCESS) {
    // get next from select
    if (rc != RC::SUCCESS && rc != RC::RECORD_EOF) {
      // drop table if fail
      db_->drop_table(table_->table_meta().name());
      table_ = nullptr;
      return RC::INTERNAL;
    }
    if (rc == RC::RECORD_EOF) {
      return rc;
    }

    // get vector
    Tuple             *tuple = children_[0]->current_tuple();
    std::vector<Value> values;
    int                cell_num = tuple->cell_num();
    values.resize(cell_num);
    for (int i = 0; i < cell_num; ++i) {
      rc = tuple->cell_at(i, values[i]);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }

    // make record and insert it
    Record record;
    rc = table_->make_record(static_cast<int>(values.size()), values.data(), record);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("failed to make record. rc=%s", strrc(rc));
      return rc;
    }
    rc = trx_->insert_record(table_, record);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to insert record by transaction. rc=%s", strrc(rc));
      return rc;
    }
  }
  return rc;
}

RC CreateSelectPhysicalOperator::close()
{
  return children_[0]->close();
}