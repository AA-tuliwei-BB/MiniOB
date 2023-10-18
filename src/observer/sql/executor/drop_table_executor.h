
#pragma once

#include "common/rc.h"

class SQLStageEvent;

/**
 * @brief 丢弃表的执行器
 * @ingroup Executor
 */
class DropTableExecutor
{
public:
  DropTableExecutor() = default;
  virtual ~DropTableExecutor() = default;

  RC execute(SQLStageEvent *sql_event);
};