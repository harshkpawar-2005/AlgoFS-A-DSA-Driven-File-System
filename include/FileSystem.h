// File: include/FileSystem.h
#pragma once

#include <string>
#include <vector>
#include "SearchResult.h"
#include "SearchIndex.h"
#include "FolderNode.h" // Needs to know what a FolderNode is

using namespace std;

class FileSystem {
public:
    // Constructor (the "startup" function)
    FileSystem();

    // A "getter" so main.cpp can check if the root is null
    FolderNode* getRoot(); 


    void createRootFolder(string name);
    void displayStructure();

    void createFolder(string parentPath, string newFolderName);
    void addFile(string parentPath, string newFileName, string content);
    void deleteItem(string path, string flag);

    void editFileContent(string path);
    void viewFileContent(string path);
    void searchItem(string name, string flag);

    void sortItemsInFolder(string path, string type, string criteria, bool isAscending);


    // This is the new "passthrough" for main.cpp to call
    vector<SearchResult> findFast(string name);
    void fastEdit(FileNode* nodeToEdit);

private:
    // The single pointer to the entire folder tree
    FolderNode* root;
SearchIndex mySearchIndex;
    void displayRecursive(FolderNode* currentNode, string indent);

    FileNode* findFileNode(string path);
    FolderNode* findFolderNode(string path);
    void recursiveDelete(FolderNode* node);

   void searchRecursive(FolderNode* node, string name, string flag,
                         string currentPath, vector<SearchResult>& foundItems);
};