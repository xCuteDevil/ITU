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
    this->Activate(task_type, is_active);
}


void Task::Execute(int task_type, bool is_active) {
    if (!is_active) {
        return;
    }
    QMessageBox msg;
    std::string str = "";
    switch(task_type) {
        case 0:
            str = "Going to sleep";
            break;
        case 1:
            str = "Waking up";
            break;
        case 2:
            str = "Shutting down";
            break;
        case 3:
            str = "Restarting";
            break;
    }

    msg.setText(QString::fromStdString(str));
    msg.exec();

}

void Task::Activate(int task_type, bool is_active) {
    is_active = true;
    int how_long = QDateTime::currentDateTime().secsTo(date_time) * 1000;
    QTimer::singleShot(how_long, [task_type, is_active]() {Execute(task_type, is_active);});
}

std::string Task::GetInfo(){
    QString dt = date_time.toString("dd.MM.yyyy hh:mm");
    std::string str = "";
    str.append(dt.toStdString());
    str.append(" ");
    str.append(std::to_string(task_type));
    str.append(" ");
    str.append(std::to_string(time_type));
    str.append("\n");

    return str;

}

