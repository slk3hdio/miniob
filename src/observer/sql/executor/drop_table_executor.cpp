/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "sql/executor/drop_table_executor.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "session/session.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/drop_table_stmt.h"
#include "storage/db/db.h"

using namespace std;

RC DropTableExecutor::execute(SQLStageEvent *sql_event)
{
  RC             rc              = RC::SUCCESS;
  Stmt          *stmt            = sql_event->stmt();
  DropTableStmt *drop_table_stmt = static_cast<DropTableStmt *>(stmt);
  const string  &table_name      = drop_table_stmt->table_name();

  ASSERT(stmt->type() == StmtType::DROP_TABLE,
      "drop table executor can not run this command: %d",
      static_cast<int>(stmt->type()));

  Db *db = sql_event->session_event()->session()->get_current_db();
  rc = db->drop_table(table_name.c_str());
  return rc;
}