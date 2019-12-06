#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include <list>
#include "task.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::list<Task *> task_list;

private slots:

    void showTime();

    void DeleteItem();

    void DisableItem();

    void EnableItem();

    void RunTask();

    QDate getDay(int selectedDay);

    void ShowTasks();


private:

    Ui::MainWindow *ui;
    QButtonGroup *RadioGroup;
    QButtonGroup *RadioGroup2;

};
#endif // MAINWINDOW_H
