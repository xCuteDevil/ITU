#ifndef TASK_H
#define TASK_H

#include <QTime>


class Task {

public:

    enum TaskType {
        sleep = 0,
        wake_up = 1,
        shutdown = 2,
        restart = 3
    };

    Task(QDateTime date_time, int type);
    int type;
    QDateTime date_time;

};

#endif // TASK_H
