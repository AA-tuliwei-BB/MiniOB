#include "aggrfunc_physical_operator.h"
#include "storage/trx/trx.h"

RC AggrFuncPhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  std::unique_ptr<PhysicalOperator> &child = children_[0];
  RC                                 rc    = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  if (parent_tuple_ != nullptr) {
    child->set_parent_tuple(get_parent_tuple());
  }

  trx_ = trx;
  return RC::SUCCESS;
}

RC AggrFuncPhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  if (emitted_) {
    rc = RC::RECORD_EOF;
    return rc;
  }
  emitted_ = true;

  if (children_.empty()) {
    return RC::INTERNAL;
  }

  PhysicalOperator *child = children_[0].get();
  while (RC::SUCCESS == (rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    int expr_size = static_cast<int>(aggr_list_.size());
    for (int i = 0; i < expr_size; ++i) {
      AggrFuncExpr *expr = aggr_list_[i];
      rc = expr->add_value(*row_tuple);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to add value: %s", strrc(rc));
        return rc;
      }
    }
  }
  for (auto &it : aggr_list_) {
    it->finish();
  }
  
  int cell_num = tuple_.cell_num();
  for (int i = 0; i < cell_num; i++) {
    Value value;
    rc = tuple_.cell_at(i, value);
    if (OB_FAIL(rc)) {
      return rc;
    }
  }
  return RC::SUCCESS;
}

RC AggrFuncPhysicalOperator::close()
{
  if (!children_.empty()) {
    children_[0]->close();
  }
  emitted_ = false;
  return RC::SUCCESS;
}