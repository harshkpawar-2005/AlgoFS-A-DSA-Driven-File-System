// File: include/FolderListNode.h
#pragma once

// We can now safely include FolderNode.h
#include "FolderNode.h"

class FolderListNode {
public:
    FolderNode* folder;     // A pointer to the actual subfolder
    FolderListNode* next;   // Pointer to the next *link* in the subfolder list

    // Constructor
    FolderListNode(FolderNode* subFolder) {
        folder = subFolder;
        next = nullptr;
    }
};