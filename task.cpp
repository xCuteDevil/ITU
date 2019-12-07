#include "task.h"
#include <iostream>
#include <sstream>
#include <QTimer>
#include <QMessageBox>
#include "mainwindow.h"

/*
 *  Class Task creates Task and hold its date, time, type of task and type of time information
 */
Task::Task(QDateTime date_time,int task_type, int time_type)
{
    this->date_time = date_time;
    this->task_type = task_type;
    this->time_type = time_type;
    this->Activate(task_type);
}

/*
 *  Called after timer of current task ends
 */
void Task::Execute(int task_type, Task *task) {
    if (!task->is_active) {
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

    task->is_active = false;
    msg.setText(QString::fromStdString(str));
    msg.exec();

}

/*
 *  Activating the task, setting timer to specific duration
 */
void Task::Activate(int task_type) {
    is_active = true;
    int how_long = QDateTime::currentDateTime().secsTo(date_time) * 1000;
    QTimer::singleShot(how_long, [task_type, this]() {Execute(task_type, this);});
}
/*
 *  Creates text representation of task (for saving into file)
 */
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

