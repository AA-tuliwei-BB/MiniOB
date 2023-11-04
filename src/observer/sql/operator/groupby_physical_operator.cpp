#include "sql/operator/groupby_physical_operator.h"
#include "groupby_physical_operator.h"

RC GroupbyPhysicalOperator::open(Trx *trx)
{
  if (children_.size() != 1) {
    LOG_ERROR("group by operator don't have exactly 1 childs");
    return RC::INTERNAL;
  }

  auto child = children_[0].get();
  RC rc = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("group-by: fail to open child operator");
    return rc;
  }

  last_values.resize(fields_.size());
  start_ = false;
  end_ = false;
  return rc;
}

RC GroupbyPhysicalOperator::next()
{
  if (end_) {
    return RC::RECORD_EOF;
  }
  RC rc = RC::SUCCESS;
  auto child = children_[0].get();
  if (!start_) {
    start_ = true;
    rc = child->next();
    if (rc != RC::SUCCESS) {
      if (rc == RC::RECORD_EOF) {
        end_ = true;
      }
      return rc;
    }
    reset();
    rc = add(child->current_tuple());
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }

  while ((rc = child->next()) == RC::SUCCESS) {
    bool is_same;
    rc = check_same(child->current_tuple(), is_same);
    if (is_same) {
      rc = add(child->current_tuple());
      if (rc != RC::SUCCESS) {
        return rc;
      }

    } else {
      bool passed;
      rc = filter(passed);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      if (passed) {
        // 先懒得检测错误了
        get_tuple();
        reset();
        add(child->current_tuple());
        return RC::SUCCESS;
      } else {
        reset();
        add(child->current_tuple());
      }
    }
  }

  if (rc != RC::RECORD_EOF) {
    return rc;
  } else {
    end_ = true;
    bool passed;
    rc = filter(passed);
    if (passed) {
      get_tuple();
      return RC::SUCCESS;
    } else {
      return RC::RECORD_EOF;
    }
  }
  return rc;
}

RC GroupbyPhysicalOperator::close()
{
  return children_[0]->close();
}

void GroupbyPhysicalOperator::reset()
{
  for (auto expr : exprs_) {
    expr->reset();
  }
  for (auto expr : left_) {
    expr->reset();
  }
  for (auto expr : right_) {
    expr->reset();
  }
}

RC GroupbyPhysicalOperator::add(Tuple *tuple)
{
  RC rc = RC::SUCCESS;
  for (auto expr : exprs_) {
    if ((rc = expr->add_value(*tuple)) != RC::SUCCESS) {
      return rc;
    }
  }
  for (auto expr : left_) {
    if ((rc = expr->add_value(*tuple)) != RC::SUCCESS) {
      return rc;
    }
  }
  for (auto expr : right_) {
    if ((rc = expr->add_value(*tuple)) != RC::SUCCESS) {
      return rc;
    }
  }

  int field_num = fields_.size();
  for (int i = 0; i < field_num; ++i) {
    rc = tuple->find_cell(TupleCellSpec(fields_[i].table()->name(), fields_[i].field_name()), last_values[i]);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }
  return rc;
}

RC GroupbyPhysicalOperator::check_same(Tuple *tuple, bool &result)
{
  RC rc = RC::SUCCESS;
  int field_num = fields_.size();
  for (int i = 0; i < field_num; ++i) {
    Value value;
    rc = tuple->find_cell(TupleCellSpec(fields_[i].table()->name(), fields_[i].field_name()), value);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    if (value.compare(last_values[i]) != 0) {
      result = false;
      break;
    }
  }
  result = true;
  return rc;
}

RC GroupbyPhysicalOperator::filter(bool &result)
{
  RC rc = RC::SUCCESS;
  result = true;
  int condition_num = left_.size();
  for (int i = 0; i < condition_num; ++i) {
    Value left_value, right_value;
    rc = left_[i]->get_value(left_value);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    rc = right_[i]->get_value(right_value);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    bool comp_result;
    rc = ComparisonExpr::compare_value_static(left_value, right_value, opts_[i], comp_result);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    if (comp_result == false) {
      result = false;
      return RC::SUCCESS;
    }
  }
  return RC::SUCCESS;
}

RC GroupbyPhysicalOperator::get_tuple()
{
  RC rc = RC::SUCCESS;
  std::vector<Value> values;
  int expr_num = exprs_.size();
  values.resize(expr_num);
  for (int i = 0; i < expr_num; ++i) {
    rc = exprs_[i]->get_value(values[i]);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }
  tuple_.set_cells(values);
  return rc;
}

Tuple *GroupbyPhysicalOperator::current_tuple() { return &tuple_; }

//   std::vector<Field> fields_;
//   std::vector<AggrFuncExpr *> exprs_;
//   std::vector<AggrFuncExpr *> left_;
//   std::vector<AggrFuncExpr *> right_;
//   std::vector<CompOp> opts_;

//   ValueListTuple tuple_;
//   std::vector<Value> last_values;
//   bool start = false;
//   bool end = false;