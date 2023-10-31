#include "orderby_physical_operator.h"

OrderbyPhysicalOperator::OrderbyPhysicalOperator(
    std::vector<Field> &&fields, std::vector<Field> &&orders, std::vector<bool> &&asc)
    : fields_(std::move(fields)), orders_(std::move(orders)), asc_(std::move(asc))
{}

RC OrderbyPhysicalOperator::open(Trx *trx)
{
  if (children_.size() != 1) {
    LOG_WARN("order operator must has one child");
    return RC::INTERNAL;
  }

  RC rc = children_[0]->open(trx);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  std::vector<TupleCellSpec *> speces;
  for (const Field &order : orders_) {
    speces.push_back(new TupleCellSpec(order.table_name(), order.field_name()));
  }
  for (const Field &field : fields_) {
    bool in_order = false;
    for (const Field &order : orders_) {
      if (0 == strcmp(order.table_name(), field.table_name()) && 0 == strcmp(order.field_name(), field.field_name())) {
        in_order = true;
        break;
      }
    }
    if (!in_order) {
      speces.push_back(new TupleCellSpec(field.table_name(), field.field_name()));
    }
  }
  tuple_.set_speces(speces);

  PhysicalOperator *oper = children_.front().get();
  while (RC::SUCCESS == (rc = oper->next())) {
    Tuple *tuple = oper->current_tuple();
    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get tuple from operator");
      break;
    }

    // get a row
    std::vector<Value> row;
    for (const Field &order : orders_) {
      Value cell;
      rc = tuple->find_cell(TupleCellSpec(order.table_name(), order.field_name()), cell);
      if (rc != RC::SUCCESS) {
        return rc;
        break;
      }
      row.push_back(cell);
    }

    for (const Field &field : fields_) {
      bool in_order = false;
      for (const Field &order : orders_) {
        if (0 == strcmp(order.table_name(), field.table_name()) &&
            0 == strcmp(order.field_name(), field.field_name())) {
          in_order = true;
          break;
        }
      }
      if (in_order) {
        continue;
      }
      Value cell;
      rc = tuple->find_cell(TupleCellSpec(field.table_name(), field.field_name()), cell);
      if (rc != RC::SUCCESS) {
        return rc;
        break;
      }
      row.push_back(cell);
    }

    rows_.push_back(row);
  }

  int order_size = orders_.size();
  auto &asc        = asc_;
  auto cmp = [&order_size, &asc](const std::vector<Value> &a, const std::vector<Value>&b) {
    for (int i = 0; i < order_size; ++i) {
      if (a[i].attr_type() == NULLS || b[i].attr_type() == NULLS) {
        if (a[i].attr_type() != b[i].attr_type()) {
          if (a[i].attr_type() == NULLS) {
            return true;
          } else {
            return false;
          }
        }
      }
      int cmp_ret = a[i].compare(b[i]);
      if(cmp_ret == 0) {
        continue;
      } else {
        if (asc[i]) {
          return cmp_ret < 0;
        } else {
          return cmp_ret > 0;
        }
      }
    }
    return false;
  };
  sort(rows_.begin(), rows_.end(), cmp);
  current_row_ = 0;

  return RC::SUCCESS;
}

RC OrderbyPhysicalOperator::next()
{
  if (current_row_ == rows_.size()) {
    return RC::RECORD_EOF;
  }
  tuple_.set_cells(rows_[current_row_]);
  ++current_row_;
  return RC::SUCCESS;
}

RC OrderbyPhysicalOperator::close()
{
  RC rc = children_[0]->close();
  if (rc != RC::SUCCESS) {
    return rc;
  }
  return RC::SUCCESS;
}

Tuple *OrderbyPhysicalOperator::current_tuple()
{
  return &tuple_;
}
