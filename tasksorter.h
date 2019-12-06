#ifndef TASKSORTER_H
#define TASKSORTER_H

#include <vector>
#include <algorithm>
#include "task.h"


class TaskSorter
{
public:
    TaskSorter();
    std::vector< Task *> objs;
    std::vector< Task *> SortTasksByDate();
    void AddObj( Task * new_obj );
    bool operator()(const Task *a, const Task *b);
};

#endif // TASKSORTER_H
