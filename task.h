#ifndef TASK_H
#define TASK_H

#include <QTime>
#include <QObject>
#include <string>

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
    void Activate(int task_type, bool is_active);
    void Deactivate();
    static void Execute(int task_type, bool is_active);
    std::string GetInfo();
    int task_type;
    int time_type;
    QDateTime date_time;
    bool is_active = false;

public slots:

};

#endif // TASK_H
