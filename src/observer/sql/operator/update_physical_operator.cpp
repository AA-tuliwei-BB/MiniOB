#include "sql/operator/update_physical_operator.h"
#include "storage/trx/trx.h"

RC UpdatePhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  std::unique_ptr<PhysicalOperator> &child = children_[0];
  RC rc = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  // get value of sub select
  int current_sub_select = 1;
  for (Value &value : values_) {
    if (value.attr_type() == UNDEFINED) {
      if (current_sub_select >= children_.size()) {
        LOG_ERROR("Update: Value undefined but can't get a sub select!");
        return RC::INTERNAL;
      }
      std::unique_ptr<PhysicalOperator> &sub_select = children_[current_sub_select++];
      RC rc = sub_select->open(trx);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("Update: failed to open sub select!");
        return rc;
      }
      rc = sub_select->next();
      if (rc != RC::SUCCESS) {
        LOG_ERROR("Update: failed to get next of sub select!");
        return rc;
      }
      rc = sub_select->current_tuple()->cell_at(0, value);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("Update: failed to get cell of sub select!");
        return rc;
      }
      rc = sub_select->close();
      if (rc != RC::SUCCESS) {
        LOG_ERROR("Update: failed to close sub select!");
        return rc;
      }
    }
  }

  trx_ = trx;

  return RC::SUCCESS;
}

RC UpdatePhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    return RC::RECORD_EOF;
  }

  PhysicalOperator *child = children_[0].get();
  while (RC::SUCCESS == (rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    RID rid = row_tuple->record().rid();
    if (!visited[rid]) {
      rc = trx_->update_record(table_, rid, this->fields_, this->values_);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to update record: %s", strrc(rc));
        return rc;
      }
      visited[rid] = true;
    }
  }

  return RC::RECORD_EOF;
}

RC UpdatePhysicalOperator::close()
{
  visited.clear();
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}