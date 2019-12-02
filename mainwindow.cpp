#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
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
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(1000);
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(DeleteItem()));

    //QTableWidgetItem *item=new QTableWidgetItem ("blaa");
    //ui->tableWidget->setItem(1, 1, item);
    //ui->listWidget_2->addItem("laus");
    //ui->listWidget_2->addItem("laus");
    //ui->listWidget_2->addItem("laus");
    //ui->tableWidget->rowCount()-1
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

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

void MainWindow::EnableItem()
{
    int selected = ui->tableWidget->currentRow();
    ui->tableWidget->setEnabled(selected);
}
