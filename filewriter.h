#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <string>
#include "task.h"


class FileWriter
{
public:
    FileWriter();
    void WriteToFile(std::vector<Task *> *tasks);
    void InitFromFile(std::vector<Task *> *tasks);
    void CreateTask(std::vector<Task *> *tasks, QString line);
};

#endif // FILEWRITER_H
