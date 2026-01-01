// File: src/TaskQueue.cpp

#include "TaskQueue.h"

// Adds a new task to the back of the queue
void TaskQueue::addTask(BatchTask task) {
    taskQueue.push(task);
}

// Gets and removes the next task from the front
BatchTask TaskQueue::getNextTask() {
    // Get the task from the front
    BatchTask nextTask = taskQueue.front();
    // Remove it from the queue
    taskQueue.pop();
    // Return the task
    return nextTask;
}

// Checks if the queue is empty
bool TaskQueue::isEmpty() {
    return taskQueue.empty();
}