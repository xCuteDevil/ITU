#include "tasksorter.h"

TaskSorter::TaskSorter()
{

}

void TaskSorter::AddObj(Task * new_obj){
    this->objs.push_back(new_obj);
}

std::vector< Task *> TaskSorter::SortTasksByDate(){
   std::vector< Task *> tmp = objs;
   sort(tmp.begin(), tmp.end());
   return tmp;
}
