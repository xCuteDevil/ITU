#include "filewriter.h"
#include "fstream"
#include <QFile>
#include <QTextStream>
#include <string>

/*
 *  FileWriter serves as class for writing tasks to file after creation
 *  and reading tasks from file after running the application
 *
 */
FileWriter::FileWriter()
{

}
/*
 *  Reads all actual tasks and writes them into file tasks.txt
 */
void FileWriter::WriteToFile(std::vector<Task *> *tasks) {
    QString fn = "tasks.txt";
    QFile file(fn);

    if(file.open(QIODevice::ReadWrite|QFile::Truncate)) {
        QTextStream ts(&file);
        for(int i = 0; i < tasks->size(); i++) {
            ts << QString::fromStdString(tasks->at(i)->GetInfo());
        }

    }
}

/*
 *  Reads all tasks from file tasks.txt, creates them, appends them to task vector and activate each one
 */
void FileWriter::InitFromFile(std::vector<Task *> *tasks) {
    QString fn = "tasks.txt";
    QFile file(fn);

    if(file.open(QIODevice::ReadOnly)) {
        QTextStream ts(&file);
        while(!ts.atEnd()) {
            QString line = ts.readLine();
            CreateTask(tasks, line);

        }
    }
}

/*
 *  Parsing text file and handling task creation
 */
void FileWriter::CreateTask(std::vector<Task *> *tasks, QString line) {
    std::string str = line.toStdString();
    std::string day = str.substr(0,2);
    std::string month = str.substr(3,2);
    std::string year = str.substr(6,4);
    std::string timestr = str.substr(11,5);
    //std::string minutes = str.substr(14,2);
    std::string taskType = str.substr(17,1);
    std::string timeType = str.substr(19,2);
    QString time_q = QString::fromStdString(timestr);

    QDateTime dt;
    QDate date;
    QTime time;

    date.setDate(std::stoi(year), std::stoi(month), std::stoi(day));
    time = time.fromString(time_q, "hh:mm");
    dt.setDate(date);
    dt.setTime(time);
    if (date <= QDate::currentDate() && time < QTime::currentTime()) {
        return;
    }
    Task *task;
    task = new Task(dt, std::stoi(taskType), std::stoi(timeType));
    tasks->push_back(task);

}
