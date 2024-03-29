#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "task.h"
#include "tasksorter.h"
#include "filewriter.h"
#include <iostream>
#include <string>
#include <sstream>
#include <QTimer>
#include <QTime>
#include <QString>
#include <QDateTime>
#include <QMessageBox>
#include <QDebug>
#include <QtCore>
#include <QtGui>

class MyClass {       // The class
  public:             // Access specifier
    int myNum;        // Attribute (int variable)
    QString myString;  // Attribute (string variable)
};

/*
 *  Main window of the application
 */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->dateEdit->setDate(QDate::currentDate());
    ui->timeEdit->setTime(QTime::currentTime());

    RadioGroup = new QButtonGroup();
    RadioGroup->addButton(ui->sleepRadio, 0);
    RadioGroup->addButton(ui->wakeRadio, 1);
    RadioGroup->addButton(ui->shutdownRadio, 2);
    RadioGroup->addButton(ui->restartRadio, 3);

    RadioGroup2 = new QButtonGroup();
    RadioGroup2->addButton(ui->weeklyRadio, 10);
    RadioGroup2->addButton(ui->dailyRadio, 11);
    RadioGroup2->addButton(ui->specifyRadio, 12);


    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(1000);
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(DeleteItem()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(RunTask()));
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(ShowTasks()));
    //connect(, SIGNAL(foo()), )

    //QTableWidgetItem *item=new QTableWidgetItem ("blaa");
    //ui->tableWidget->setItem(1, 1, item);
    //ui->listWidget_2->addItem("laus");
    //ui->listWidget_2->addItem("laus");
    //ui->listWidget_2->addItem("laus");
    //ui->tableWidget->rowCount()-1
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    FileWriter f;
    f.InitFromFile(&task_list);
    ShowTasks();

}


MainWindow::~MainWindow()
{
    delete ui;
}

/*
 *  Showing current time in application
 */
void MainWindow::showTime()
{
    QDateTime time=QDateTime::currentDateTime();
    QString time_text=time.toString("hh:mm:ss d.MM.yyyy");
    ui->label_2->setText(time_text);
}

/*
 *  Removes selected task from application
 */
void MainWindow::DeleteItem()
{
    int selected = ui->tableWidget->currentRow();
    task_list.at(selected)->is_active = false;
    task_list.erase(task_list.begin() + selected);
    ShowTasks();
    FileWriter f;
    f.WriteToFile(&task_list);
}

/*
 *  Called after saving new task, task is created, saved into task vector.
 *  If task is created with time past current date and time, task is not created
 *  and user is notified with pop-up window
 */
void MainWindow::RunTask() {


    int taskType = RadioGroup->checkedId();
    int timeType = RadioGroup2->checkedId();
    QDateTime date_time; //hlavni
    QDate day;
    QTime selected_time;
    int selectedDay;
    Task *task;

    switch (timeType) {

    case 10: //weekly

        selected_time = ui->timeEdit->time();
        date_time.setTime(selected_time);

        selectedDay = ui->selectedDay->currentIndex();
        day = getDay(selectedDay);
        date_time.setDate(day);

        break;
    case 11: //daily

        selected_time = ui->timeEdit->time();
        date_time.setTime(selected_time);

        day = QDate::currentDate();
        if (QTime::currentTime() > selected_time) {
            day = day.addDays(1);
        }
        date_time.setDate(day);

        break;
    case 12: //specific time

        selected_time = ui->timeEdit->time();
        date_time.setTime(selected_time);

        day = ui->dateEdit->date();
        date_time.setDate(day);

        break;

    }
    if (date_time.date() <= QDate::currentDate() && date_time.time() < QTime::currentTime()) {
        QMessageBox::information(
        this,
        tr("ShutdownScheduler"),
        tr("Zadané datum není platné")
        );

    }
    else {
        task = new Task(date_time, taskType, timeType);
        task_list.push_back(task);

        ShowTasks();
        FileWriter f;
        f.WriteToFile(&task_list);

        QMessageBox::information(
        this,
        tr("ShutdownScheduler"),
        tr("Úkol byl spuštěn")
        );
    }
}

/*
 *  Getting nearest date of new weekly task
 */
QDate MainWindow::getDay(int selectedDay) {

    QDate today = QDate::currentDate();
    QDate task_day;
    int today_index = today.dayOfWeek();
    int how_many_days;

    if (selectedDay == 0) {
        selectedDay = 7;
    }

    how_many_days = selectedDay - today_index;
    //Thur (4) - Sun (7) = - 3
    //Fri (5) - Tue (2) = 3
    //Fri (5) - Fri (5) = 0

    if (how_many_days < 0) {
        how_many_days += 7;
    }

    task_day = today.addDays(how_many_days);
    return task_day;
}

/*
 *  Recreates tablewidget in application with current tasks saved in task_vector
 */
void MainWindow::ShowTasks() {


    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);

    unsigned long size = task_list.size();

    for (unsigned long i = 0; i < size; i++) {
        if (!(task_list.at(i)->is_active)) {
            task_list.erase(task_list.begin() + i);
        }
    }

    for (unsigned long row = 0; row < size; row++) {

        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        for( int column = 0; column < 4; column++ )
        {

            if(column == 0) {
                QString typ;
                switch(task_list.at(row)->task_type) {
                    case 0:
                        typ = "Sleep";
                        break;
                    case 1:
                        typ = "Wake up";
                        break;
                    case 2:
                        typ = "Shut-down";
                        break;
                    case 3:
                        typ = "Restart";
                        break;
                }

                QVariant data(typ);
                // allocate the widget item
                QTableWidgetItem * poItem = new QTableWidgetItem();
                poItem->setData( Qt::DisplayRole, data );

                // insert into the table
                ui->tableWidget->setItem(row, column, poItem );
            }
            else if (column == 1) {
                QVariant data(task_list.at(row)->date_time.time());
                // allocate the widget item
                QTableWidgetItem * poItem = new QTableWidgetItem();
                poItem->setData( Qt::DisplayRole, data );

                // insert into the table
                //ui->tableWidget->insertRow(ui->tableWidget->rowCount());
                ui->tableWidget->setItem(row, column, poItem );
            }
            else if (column == 2) {
                QVariant data(task_list.at(row)->date_time.date());
                // allocate the widget item
                QTableWidgetItem * poItem = new QTableWidgetItem();
                poItem->setData( Qt::DisplayRole, data );

                // insert into the table
                //ui->tableWidget->insertRow(ui->tableWidget->rowCount());
                ui->tableWidget->setItem(row, column, poItem );
            }
            else {

                QString typ;

                switch(task_list.at(row)->time_type) {
                    case 10:
                        typ = "Weekly";
                        break;
                    case 11:
                        typ = "Daily";
                        break;
                    case 12:
                        typ = "Specified time";
                        break;
                }

                QVariant data(typ);
                // allocate the widget item
                QTableWidgetItem * poItem = new QTableWidgetItem();
                poItem->setData( Qt::DisplayRole, data );

                // insert into the table
                //ui->tableWidget->insertRow(ui->tableWidget->rowCount());
                ui->tableWidget->setItem(row, column, poItem );
            }

        }

    }

}
