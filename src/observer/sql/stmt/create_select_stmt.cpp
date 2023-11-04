#include "create_select_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/create_table_stmt.h"

RC CreateSelectStmt::create(Db *db, const CreateSelectSqlNode &create_table, Stmt *&stmt) {     
    Stmt* tmp;
    RC rc;
    rc = SelectStmt::create(db, create_table.select_node->selection, tmp);
    if(rc != RC::SUCCESS) {
        LOG_WARN("fail to create select stmt in create-select command");
        return rc;
    }
    SelectStmt* sub_select = static_cast<SelectStmt*>(tmp);
    std::vector<AttrInfoSqlNode> infos;
    CreateTableStmt* create_table_stmt;
    if(create_table.attr_infos.empty()) {
        for(int i = 0; i < sub_select->alias().size(); ++i) {
            AttrInfoSqlNode info;
            info.name = sub_select->alias()[i];
            info.type = sub_select->expression()[i]->value_type();
            int len = 0;
            bool nullable = false;
            for (int j = i == 0 ? 0 : sub_select->query_fields_size()[i-1]; j < sub_select->query_fields_size()[i]; ++j) {
                len = std::max(len, sub_select->query_fields()[j].meta()->len());
                nullable |= sub_select->query_fields()[j].meta()->nullable();
            }
            info.length = len;
            info.nullable = nullable;
            infos.push_back(info);
        }
        create_table_stmt = new CreateTableStmt(create_table.relation_name, infos);
    } else {
        create_table_stmt = new CreateTableStmt(create_table.relation_name, create_table.attr_infos);
    }

    CreateSelectStmt* result = new CreateSelectStmt(db, create_table_stmt, sub_select);
    stmt = static_cast<Stmt*>(result);

    return rc; 
}