// File: include/FileNode.h
#pragma once

#include <string>
#include <ctime>

using namespace std;

class FileNode {
public:
    string fileName;
    string fileContent;
    time_t creationDate;
    size_t fileSize;

    FileNode* next; // Pointer to the next FileNode in the list

    // Constructor
    FileNode(string name, string content = "") {
        fileName = name;
        fileContent = content;
        creationDate = time(nullptr);
        fileSize = fileContent.length();
        next = nullptr;
    }
};