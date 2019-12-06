#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "task.h"
#include <iostream>
#include <string>
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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

    //QTableWidgetItem *item=new QTableWidgetItem ("blaa");
    //ui->tableWidget->setItem(1, 1, item);
    //ui->listWidget_2->addItem("laus");
    //ui->listWidget_2->addItem("laus");
    //ui->listWidget_2->addItem("laus");
    //ui->tableWidget->rowCount()-1
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

/*
    for( int row = 0; row < 5; row++ )
    {
        for( int column = 0; column < 3; column++ )
        {
            QVariant oVariant("ahoj");

            // allocate the widget item
            QTableWidgetItem * poItem = new QTableWidgetItem();
            poItem->setData( Qt::DisplayRole, oVariant );

            // insert into the table
            ui->tableWidget->setItem( row, column, poItem );
        }
    }
*/

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showTime()
{
    QDateTime time=QDateTime::currentDateTime();
    QString time_text=time.toString("hh:mm:ss d.MM.yyyy");
    ui->label_2->setText(time_text);
}

void MainWindow::DeleteItem()
{
    /* Method removes selected TableWidget item */
    int selected = ui->tableWidget->currentRow();
    ui->tableWidget->removeRow(selected);
}

void MainWindow::DisableItem()
{
    int selected = ui->tableWidget->currentRow();
    ui->tableWidget->setDisabled(selected);
    QTableWidgetItem *a = ui->tableWidget->takeItem(selected, 0);
    a->setTextColor(QColor(255,0,0));

}

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

        task = new Task(date_time, taskType, timeType);
        task_list.push_back(task);

        break;
    case 11: //daily

        break;
    case 12: //specific time
        break;

    }

    this->ShowTasks();
    QMessageBox::information(
    this,
    tr("ShutdownScheduler"),
    tr("Úkol byl spuštěn")
    );

}

void MainWindow::EnableItem()
{
    int selected = ui->tableWidget->currentRow();
    ui->tableWidget->setEnabled(selected);
}

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

void MainWindow::ShowTasks() {


    ui->tableWidget->clear();

    for (unsigned long row = 0; row < task_list.size(); row++) {

        Task *tmp_task = task_list.front();

        for( int column = 0; column < 4; column++ )
        {

            if(column == 0) {
                QString typ;
                switch(tmp_task->task_type) {
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
                QVariant data(tmp_task->date_time.time());
                // allocate the widget item
                QTableWidgetItem * poItem = new QTableWidgetItem();
                poItem->setData( Qt::DisplayRole, data );

                // insert into the table
                ui->tableWidget->setItem(row, column, poItem );
            }
            else if (column == 2) {
                QVariant data(tmp_task->date_time.date());
                // allocate the widget item
                QTableWidgetItem * poItem = new QTableWidgetItem();
                poItem->setData( Qt::DisplayRole, data );

                // insert into the table
                ui->tableWidget->setItem(row, column, poItem );
            }
            else {

                QString typ;

                switch(tmp_task->time_type) {
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
                ui->tableWidget->setItem(row, column, poItem );

            }

        }

        tmp_list.push_back(task_list.front());
        task_list.pop_front();
    }

    for (int i = 0; i < tmp_list.size(); i++) {
        task_list.push_back(tmp_list.front());
        tmp_list.pop_front();
    }
}
