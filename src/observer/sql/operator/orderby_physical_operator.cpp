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

  if (parent_tuple_ != nullptr) {
    children_[0]->set_parent_tuple(get_parent_tuple());
  }

  emitted_ = false;
  return RC::SUCCESS;
}

RC OrderbyPhysicalOperator::next()
{
  if (!emitted_) {
    RC rc = RC::SUCCESS;
    emitted_ = true;
    rows_.clear();
    std::vector<TupleCellSpec *> speces;
    for (const Field &order : orders_) {
      speces.push_back(new TupleCellSpec(order.table_name(), order.field_name()));
    }
    for (const Field &field : fields_) {
      speces.push_back(new TupleCellSpec(field.table_name(), field.field_name()));
    }
    tuple_.set_speces(speces);

    std::vector<int> order_position;
    std::vector<int> field_position;
    bool got_position = false;

    PhysicalOperator *oper = children_.front().get();
    while (RC::SUCCESS == (rc = oper->next())) {
      Tuple *tuple = oper->current_tuple();
      if (nullptr == tuple) {
        rc = RC::INTERNAL;
        LOG_WARN("failed to get tuple from operator");
        break;
      }

      if (!got_position) {
        order_position.resize(orders_.size());
        for (int i = 0; i < int(orders_.size()); ++i) {
          rc = tuple->find_cell(TupleCellSpec(orders_[i].table_name(), orders_[i].field_name()), order_position[i]);
          if (rc != RC::SUCCESS) {
            return rc;
            break;
          }
        }
        field_position.resize(fields_.size());
        for (int i = 0; i < int(fields_.size()); ++i) {
          rc = tuple->find_cell(TupleCellSpec(fields_[i].table_name(), fields_[i].field_name()), field_position[i]);
          if (rc != RC::SUCCESS) {
            return rc;
            break;
          }
        }
        got_position = true;
      }

      // get a row
      std::vector<Value> row;
      row.reserve(orders_.size() + fields_.size());
      for (int i = 0; i < int(orders_.size()); ++i) {
        Value cell;
        rc = tuple->cell_at(order_position[i], cell);
        if (rc != RC::SUCCESS) {
          return rc;
          break;
        }
        row.push_back(std::move(cell));
      }

      for (int i = 0; i < int(fields_.size()); ++i) {
        Value cell;
        rc = tuple->cell_at(field_position[i], cell);
        if (rc != RC::SUCCESS) {
          return rc;
          break;
        }
        row.push_back(std::move(cell));
      }

      rows_.push_back(std::move(row));
    }

    int   order_size = orders_.size();
    auto &asc        = asc_;
    auto  cmp        = [&order_size, &asc](const std::vector<Value> &a, const std::vector<Value> &b) {
      for (int i = 0; i < order_size; ++i) {
        if (a[i].attr_type() == NULLS || b[i].attr_type() == NULLS) {
          if (a[i].attr_type() != b[i].attr_type()) {
            if (a[i].attr_type() == NULLS) {
              return bool(asc[i]);
            } else {
              return !bool(asc[i]);
            }
          }
        }
        int cmp_ret = a[i].compare(b[i]);
        if (cmp_ret == 0) {
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
  }

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
