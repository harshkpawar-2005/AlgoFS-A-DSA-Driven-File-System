// File: include/BatchTask.h
#pragma once

#include <string>

using namespace std;

class BatchTask {
public:
    string command;     // "addFile" or "createFolder"
    string parentPath;
    string itemName;
    string content;     // Only used for "addFile"

    // Constructor for creating a folder
    BatchTask(string cmd, string path, string name) {
        command = cmd;
        parentPath = path;
        itemName = name;
        content = ""; // Not needed for a folder
    }

    // Constructor for creating a file
    BatchTask(string cmd, string path, string name, string c) {
        command = cmd;
        parentPath = path;
        itemName = name;
        content = c;
    }
};