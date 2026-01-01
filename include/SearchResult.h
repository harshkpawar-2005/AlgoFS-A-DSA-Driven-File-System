// File: include/SearchResult.h
#pragma once

#include <string>
#include "FileNode.h" // Needs to know what a FileNode is

using namespace std;

/**
 * @class SearchResult
 * @brief A shared class that holds a direct pointer to a file
 * and its full path string. This is used by BOTH the
 * slow recursive search and the fast hash map index.
 */
class SearchResult {
public: // <-- Must add this for a class
    string path;
    FileNode* nodePtr; // The direct pointer for O(1) access

    // Constructor to make it easy to create
    SearchResult(string p, FileNode* ptr) {
        path = p;
        nodePtr = ptr;
    }
};