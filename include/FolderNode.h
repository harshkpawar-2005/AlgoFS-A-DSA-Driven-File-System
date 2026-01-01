// File: include/FolderNode.h
#pragma once

#include <string>
#include <ctime>
#include "FileNode.h" // A folder needs to know what a FileNode is

using namespace std;

// Forward-declare the helper class to break the circular include
class FolderListNode;

class FolderNode {
public:
    string folderName;
    time_t creationDate;
    // --- Head Pointers ---
    
    // 1. Head of the linked list for all files
    FileNode* fileListHead;

    // 2. Head of the linked list for all subfolders
    FolderListNode* subfolderListHead;

    // Constructor
    FolderNode(string name) {
        folderName = name;
        creationDate = time(nullptr);
        fileListHead = nullptr;
        subfolderListHead = nullptr;
    }
};