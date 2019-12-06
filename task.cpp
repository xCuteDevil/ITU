#include "task.h"
#include <iostream>
#include <sstream>
#include <QTimer>
#include <QMessageBox>
#include "mainwindow.h"


Task::Task(QDateTime date_time,int task_type, int time_type)
{
    this->date_time = date_time;
    this->task_type = task_type;
    this->time_type = time_type;
    this->Activate();
}


void Task::Execute() {
    QMessageBox msg;
    msg.setText("Hello");
    msg.exec();

}

void Task::Activate() {
    QTimer::singleShot(2000, &Execute);
}

bool operator()(const Task *a, const Task *b)  {

}
