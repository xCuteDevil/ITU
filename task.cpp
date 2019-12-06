#include "task.h"
#include <iostream>
#include "mainwindow.h"

Task::Task(QDateTime date_time,int task_type, int time_type)
{
    this->date_time = date_time;
    this->task_type = task_type;
    this->time_type = time_type;
}
