// File: include/Sorting.h
#pragma once

#include "FileNode.h"
#include "FolderListNode.h"
#include <string>

using namespace std;

class Sorting {
private:
    // --- File Sort Helpers ---
    static FileNode* getFileMiddle(FileNode* head);
    static FileNode* sortedFileMerge(FileNode* a, FileNode* b, string criteria, bool isAscending);
    static bool compareFiles(FileNode* a, FileNode* b, string criteria, bool isAscending);

    // --- Folder Sort Helpers ---
    static FolderListNode* getFolderMiddle(FolderListNode* head);
    static FolderListNode* sortedFolderMerge(FolderListNode* a, FolderListNode* b, string criteria, bool isAscending);
    static bool compareFolders(FolderListNode* a, FolderListNode* b, string criteria, bool isAscending);

public:
    /**
     * @brief Main function to sort a linked list of FileNodes.
     * @param head The head of the file list.
     * @param criteria "name", "size", or "date".
     * @param isAscending True for A-Z, 0-9. False for Z-A, 9-0.
     * 
     * 
     * 
     * @return A pointer to the *new* head of the sorted list.
     */
    static FileNode* sortFiles(FileNode* head, string criteria, bool isAscending);

    /**
     * @brief Main function to sort a linked list of FolderListNodes.
     * @param head The head of the subfolder list.
     * @param criteria "name" or "date".
     * @param isAscending True for A-Z, Old-New. False for Z-A, New-Old.
     * @return A pointer to the *new* head of the sorted list.
     */
    static FolderListNode* sortSubfolders(FolderListNode* head, string criteria, bool isAscending);
};