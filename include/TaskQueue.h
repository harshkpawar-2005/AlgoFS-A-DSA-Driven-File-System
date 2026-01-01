// File: include/TaskQueue.h
#pragma once

#include <queue>
#include "BatchTask.h"

using namespace std;

class TaskQueue {
private:
    std::queue<BatchTask> taskQueue;

public:
    // Adds a new task to the back of the queue
    void addTask(BatchTask task);

    // Gets the next task from the front of the queue
    BatchTask getNextTask();

    // Checks if the queue is empty
    bool isEmpty();
};