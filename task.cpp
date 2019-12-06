#include "task.h"
#include <iostream>
#include "mainwindow.h"

Task::Task(QDateTime date_time,int type)
{
    this->date_time = date_time;
    this->type = type;
}
