// File: src/Sorting.cpp

#include "Sorting.h"

// --- 1. FILE SORTING IMPLEMENTATION ---

bool Sorting::compareFiles(FileNode* a, FileNode* b, string criteria, bool isAscending) {
    bool result = false;
    if (criteria == "name") {
        result = a->fileName < b->fileName;
    } else if (criteria == "size") {
        result = a->fileSize < b->fileSize;
    } else if (criteria == "date") {
        result = a->creationDate < b->creationDate;
    }
    return isAscending ? result : !result;
}

FileNode* Sorting::sortedFileMerge(FileNode* a, FileNode* b, string criteria, bool isAscending) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;

    FileNode* result = nullptr;
    if (compareFiles(a, b, criteria, isAscending)) {
        result = a;
        result->next = sortedFileMerge(a->next, b, criteria, isAscending);
    } else {
        result = b;
        result->next = sortedFileMerge(a, b->next, criteria, isAscending);
    }
    return result;
}

FileNode* Sorting::getFileMiddle(FileNode* head) {
    if (head == nullptr) return head;
    FileNode* slow = head;
    FileNode* fast = head->next;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

FileNode* Sorting::sortFiles(FileNode* head, string criteria, bool isAscending) {
    if (head == nullptr || head->next == nullptr) {
        return head; // Base case: list is 0 or 1 item
    }

    // 1. Find middle
    FileNode* middle = getFileMiddle(head);
    FileNode* nextOfMiddle = middle->next;

    // 2. Split the list in two
    middle->next = nullptr;

    // 3. Recursively sort both halves
    FileNode* left = sortFiles(head, criteria, isAscending);
    FileNode* right = sortFiles(nextOfMiddle, criteria, isAscending);

    // 4. Merge the sorted halves
    FileNode* sortedList = sortedFileMerge(left, right, criteria, isAscending);
    return sortedList;
}

// --- 2. FOLDER SORTING IMPLEMENTATION ---

bool Sorting::compareFolders(FolderListNode* a, FolderListNode* b, string criteria, bool isAscending) {
    bool result = false;
    if (criteria == "name") {
        result = a->folder->folderName < b->folder->folderName;
    } else if (criteria == "date") {
        result = a->folder->creationDate < b->folder->creationDate;
    }
    return isAscending ? result : !result;
}

FolderListNode* Sorting::sortedFolderMerge(FolderListNode* a, FolderListNode* b, string criteria, bool isAscending) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;

    FolderListNode* result = nullptr;
    if (compareFolders(a, b, criteria, isAscending)) {
        result = a;
        result->next = sortedFolderMerge(a->next, b, criteria, isAscending);
    } else {
        result = b;
        result->next = sortedFolderMerge(a, b->next, criteria, isAscending);
    }
    return result;
}

FolderListNode* Sorting::getFolderMiddle(FolderListNode* head) {
    if (head == nullptr) return head;
    FolderListNode* slow = head;
    FolderListNode* fast = head->next;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

FolderListNode* Sorting::sortSubfolders(FolderListNode* head, string criteria, bool isAscending) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    // 1. Find middle
    FolderListNode* middle = getFolderMiddle(head);
    FolderListNode* nextOfMiddle = middle->next;

    // 2. Split the list
    middle->next = nullptr;

    // 3. Recursively sort
    FolderListNode* left = sortSubfolders(head, criteria, isAscending);
    FolderListNode* right = sortSubfolders(nextOfMiddle, criteria, isAscending);

    // 4. Merge
    FolderListNode* sortedList = sortedFolderMerge(left, right, criteria, isAscending);
    return sortedList;
}