#ifndef TASK_H
#define TASK_H

#include <QTime>
#include <QObject>

class Task : public QObject{

public:

    enum TaskType {
        sleep = 0,
        wake_up = 1,
        shutdown = 2,
        restart = 3
    };

    enum TimeType {
        weekly = 10,
        daily = 11,
        specify = 12
    };

    Task(QDateTime date_time, int task_type, int time_type);
    void Activate();
    void Deactivate();
    static void Execute();
    int task_type;
    int time_type;
    QDateTime date_time;

public slots:

};

#endif // TASK_H
