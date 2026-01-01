// File: src/FileSystem.cpp

#include "FileSystem.h" // Include the header "blueprint"
#include "FolderListNode.h"
#include "Sorting.h"
#include <iostream>

#include <sstream> // For string splitting
#include <vector>  // For string splitting

// Constructor implementation
FileSystem::FileSystem() {
    // This is the starting point. The system is empty.
    root = nullptr;
}

// Getter implementation
FolderNode* FileSystem::getRoot() {
    return root;
}


/**
 * @brief Implementation of createRootFolder.
 */
void FileSystem::createRootFolder(string name) {
    // We only create the root if it doesn't already exist
    if (root == nullptr) {
        // 'new' allocates memory for a new FolderNode
        // The constructor for FolderNode runs, setting its members
        root = new FolderNode(name);
        cout << "Success: Root folder '" << name << "' created." << endl;
    } else {
        cout << "Error: Root folder already exists." << endl;
    }
}

/**
 * @brief Public wrapper for displayStructure.
 * This provides a clean interface for main.cpp.
 */
void FileSystem::displayStructure() {
    // If the root is null, there's nothing to show
    if (root == nullptr) {
        cout << "File system is empty. No root folder found." << endl;
        return;
    }
    // Start the recursive call from the root with no indentation
    displayRecursive(root, "");
}

void FileSystem::displayRecursive(FolderNode* currentNode, string indent) {
    // 1. PROCESS SELF (The Folder)
    cout << indent << currentNode->folderName << "/" << endl;

    // 2. PROCESS FILES
    // Loop through the file linked list
    string fileIndent = indent + "  ";
    FileNode* currentFile = currentNode->fileListHead;
    while (currentFile != nullptr) {
        cout << fileIndent << "- " << currentFile->fileName << endl;
        currentFile = currentFile->next;
    }

    // 3. PROCESS CHILDREN (The Subfolders)
    // Loop through the subfolder linked list
    FolderListNode* currentLink = currentNode->subfolderListHead;
    while (currentLink != nullptr) {
        
        // Get the actual folder from the link
        FolderNode* subfolder = currentLink->folder;

        // Recursively call this function for the child
        displayRecursive(subfolder, indent + "  ");

        // Move to the next link in the list
        currentLink = currentLink->next;
    }
}


// --- PHASE 3: NEW IMPLEMENTATIONS ---

/**
 * @brief Splits a path string (e.g., "/MyPC/Docs") into parts (["MyPC", "Docs"]).
 * This is a helper for findFolderNode.
 */
vector<string> splitPath(string path) {
    vector<string> parts;
    string part;
    stringstream ss(path);
    // Split by the '/' delimiter
    while (getline(ss, part, '/')) {
        if (!part.empty()) { // Ignore empty strings
            parts.push_back(part);
        }
    }
    return parts;
}

/**
 * @brief Implementation of the findFolderNode helper function.
 */
FolderNode* FileSystem::findFolderNode(string path) {
    if (root == nullptr) return nullptr;

    vector<string> parts = splitPath(path);
    
    // Check if the path is just the root
    if (path == "/" + root->folderName) {
        return root;
    }
    // Handle case where user just types "/"
    if (path == "/" && root != nullptr) {
        return root;
    }

    // Start our search from the root
    FolderNode* currentNode = root;

    // We must match the root name first
    if (parts.empty() || parts[0] != currentNode->folderName) {
        return nullptr; // Path doesn't start with the root
    }

    // Loop through the path parts, starting from the second one (index 1)
    for (size_t i = 1; i < parts.size(); ++i) {
        string targetName = parts[i];
        
        // Start searching this folder's subfolder list
        FolderListNode* link = currentNode->subfolderListHead;
        
        FolderNode* foundNode = nullptr;
        while (link != nullptr) {
            if (link->folder->folderName == targetName) {
                foundNode = link->folder;
                break; // Found the next part of the path
            }
            link = link->next; // Check the next link
        }

        if (foundNode == nullptr) {
            // We looped all links and found nothing
            return nullptr; // Path is invalid
        }
        
        // We found it, so it becomes the new currentNode for the next loop
        currentNode = foundNode;
    }

    // After the loop, currentNode is the folder we were looking for
    return currentNode;
}


/**
 * @brief Implementation of createFolder.
 */
void FileSystem::createFolder(string parentPath, string newFolderName) {
    // 1. Find the parent folder
    FolderNode* parent = findFolderNode(parentPath);

    if (parent == nullptr) {
        cout << "Error: The path '" << parentPath << "' does not exist." << endl;
        return;
    }

    // 2. TODO: Check for duplicate names (we'll add this later)
    // ...

    // 3. Create the new folder and the link for it
    FolderNode* newFolder = new FolderNode(newFolderName);
    FolderListNode* newLink = new FolderListNode(newFolder);

    // 4. Add the new link to the *head* of the parent's subfolder list
    newLink->next = parent->subfolderListHead;
    parent->subfolderListHead = newLink;
    
    cout << "Success: Folder '" << newFolderName << "' created in '" << parentPath << "'." << endl;
}

/**
 * @brief Implementation of addFile.
 */
void FileSystem::addFile(string parentPath, string newFileName, string content) {
    // 1. Find the parent folder
    FolderNode* parent = findFolderNode(parentPath);
    
    if (parent == nullptr) {
        cout << "Error: The path '" << parentPath << "' does not exist." << endl;
        return;
    }

    // 2. TODO: Check for duplicate names
    // ...

    // 3. Create the new file
    FileNode* newFile = new FileNode(newFileName, content);

    // 4. Add the new file to the *head* of the parent's file list
    newFile->next = parent->fileListHead;
    parent->fileListHead = newFile;

    string fullPath = parentPath + "/" + newFileName;
    mySearchIndex.add(fullPath, newFile);   

    cout << "Success: File '" << newFileName << "' added to '" << parentPath << "'." << endl;
}

/**
 * @brief The main public delete function.
 */
void FileSystem::deleteItem(string path, string flag) {
    // --- ADD THIS SAFETY CHECK ---
    if (path == "/" + root->folderName || path == "/") {
        cout << "Error: Cannot delete the root folder." << endl;
        return;
    }
    // ---
    // 1. Find the parent path and item name
    size_t lastSlash = path.find_last_of('/');
    if (lastSlash == string::npos) {
        cout << "Error: Invalid path. Must be absolute." << endl;
        return;
    }
    
    string parentPath = path.substr(0, lastSlash);
    string itemName = path.substr(lastSlash + 1);

    // Handle root folder path (e.g., "/MyPC"...(e.g., "/file.txt").)
    if (parentPath.empty()) {
        parentPath = "/";
    }

    // 2. Find the parent folder
    FolderNode* parent = findFolderNode(parentPath);
    if (parent == nullptr) {
        cout << "Error: Parent folder at '" << parentPath << "' not found." << endl;
        return;
    }

    // 3. Handle based on user's intent
    if (flag == "file") {
        // --- Delete File Logic ---
        FileNode* current = parent->fileListHead;
        FileNode* prev = nullptr;

        while (current != nullptr && current->fileName != itemName) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Error: File '" << itemName << "' not found in '" << parentPath << "'." << endl;
            return;
        }

        // remove entry from map
        mySearchIndex.remove(current);


        // Unlink the file from the list
        if (prev == nullptr) { // It's the head of the list
            parent->fileListHead = current->next;
        } else { // It's somewhere in the middle
            prev->next = current->next;
        }

        // TODO: Remove from Hash Map index
        
        delete current; // Free the memory
        cout << "Success: File '" << itemName << "' deleted." << endl;

    } else if (flag == "folder") {
        // --- Delete Folder Logic ---
        FolderListNode* currentLink = parent->subfolderListHead;
        FolderListNode* prevLink = nullptr;

        while (currentLink != nullptr && currentLink->folder->folderName != itemName) {
            prevLink = currentLink;
            currentLink = currentLink->next;
        }

        if (currentLink == nullptr) {
            cout << "Error: Folder '" << itemName << "' not found in '" << parentPath << "'." << endl;
            return;
        }

        // Unlink the folder *from the parent's list*
        if (prevLink == nullptr) { // It's the head of the list
            parent->subfolderListHead = currentLink->next;
        } else { // It's in the middle
            prevLink->next = currentLink->next;
        }
        
        // Get the pointer to the folder we're about to kill
        FolderNode* folderToKill = currentLink->folder;
        
        // Free the *link* node itself
        delete currentLink;

        // NOW, recursively delete the folder and all its contents
        recursiveDelete(folderToKill);
        
        cout << "Success: Folder '" << itemName << "' and all its contents deleted." << endl;
    }
}

/**
 * @brief Implementation of the recursive delete helper.
 * This is a Post-order Traversal.
 */
void FileSystem::recursiveDelete(FolderNode* node) {
    // 1. Delete all files in this folder
    FileNode* currentFile = node->fileListHead;
    while (currentFile != nullptr) {
        FileNode* nextFile = currentFile->next;
        // TODO: Remove file from Hash Map index
        mySearchIndex.remove(currentFile);

        delete currentFile;
        currentFile = nextFile;
    }
    // ✔ Then frees the ENTIRE heap block of the object

// Meaning:
// fileName, fileContent, creationDate, fileSize, next
// → all disappear because the entire object memory is released.

// NOT because destructor deletes them…
// but because delete frees the whole object’s memory.

    // 2. Recursively delete all subfolders
    FolderListNode* currentLink = node->subfolderListHead;
    while (currentLink != nullptr) {
        FolderListNode* nextLink = currentLink->next;
        
        // Recurse on the child folder *first*
        recursiveDelete(currentLink->folder);
        
        // Delete the link node
        delete currentLink;
        currentLink = nextLink;
    }

    // 3. Delete the folder itself (after all children are gone)
    delete node;
}


// --- PHASE 4: NEW IMPLEMENTATIONS ---

/**
 * @brief Private helper to find a FileNode* from a full path.
 */
FileNode* FileSystem::findFileNode(string path) {
    // 1. Parse the path to find the parent path and file name
    size_t lastSlash = path.find_last_of('/');
    if (lastSlash == string::npos) {
        return nullptr; // Invalid path
    }
    
    string parentPath = path.substr(0, lastSlash);
    string fileName = path.substr(lastSlash + 1);

    // Handle root file (e.g., "/file.txt" or "/MyPC/file.txt")
    if (parentPath.empty()) {
        parentPath = "/" + root->folderName;
    }

    // 2. Find the parent folder
    FolderNode* parent = findFolderNode(parentPath);
    if (parent == nullptr) {
        return nullptr; // Parent folder not found
    }

    // 3. Find the file in the parent's linked list
    FileNode* file = parent->fileListHead;
    while (file != nullptr) {
        if (file->fileName == fileName) {
            return file; // Found the file
        }
        file = file->next;
    }

    return nullptr; // File not found
}

/**
 * @brief Public function to view a file's content.
 */
void FileSystem::viewFileContent(string path) {
    FileNode* file = findFileNode(path);

    if (file == nullptr) {
        cout << "Error: File not found at '" << path << "'." << endl;
    } else {
        cout << "\n--- Content of " << file->fileName << " ---" << endl;
        cout << file->fileContent << endl;
        cout << "--- End of Content ---" << endl;
    }
}


/**
 * @brief Public function to edit a file's content.
 */
void FileSystem::editFileContent(string path) {
    FileNode* file = findFileNode(path);

    if (file == nullptr) {
        cout << "Error: File not found at '" << path << "'." << endl;
        return;
    }

    fastEdit(file);
}

/**
 * @brief Recursive helper for the new, smarter slow search.
 */
void FileSystem::searchRecursive(FolderNode* node, string name, string flag,
                                 string currentPath, vector<SearchResult>& foundItems) {
    
    if (flag == "file") {
        FileNode* file = node->fileListHead;
        while (file != nullptr) {
            if (file->fileName == name) {
                // We found a file. Create a SearchResult and add it.
                string path = currentPath + "/" + file->fileName;
                foundItems.push_back(SearchResult(path, file)); // <-- NEW
            }
            file = file->next;
        }
    } else if (flag == "folder") {
        // (This logic is unchanged, as we don't store pointers to folders)
        FolderListNode* link = node->subfolderListHead;
        while (link != nullptr) {
            if (link->folder->folderName == name) {
                // We're just storing the path, not a pointer
                foundItems.push_back(SearchResult(currentPath + "/" + link->folder->folderName, nullptr)); // <-- NEW
            }
            link = link->next;
        }
    }

    // 3. Always recurse into subfolders to search deeper
    FolderListNode* link = node->subfolderListHead;
    while (link != nullptr) {
        searchRecursive(link->folder, name, flag,
                        currentPath + "/" + link->folder->folderName,
                        foundItems);
        link = link->next;
    }
}

/**
 * @brief 3. MODIFIED Public wrapper.
 * Now it's much smarter and prints content instantly.
 */
/**
 * @brief Public wrapper for the new slow search function.
 */
/**
 * @brief Public wrapper for the new slow search function.
 */
void FileSystem::searchItem(string name, string flag) {
    if (root == nullptr) {
        cout << "File system is empty." << endl;
        return;
    }

    // This vector now holds our powerful SearchResult objects
    vector<SearchResult> foundItems;
    string rootPath = "/" + root->folderName;

    if (flag == "folder" && root->folderName == name) {
        foundItems.push_back(SearchResult(rootPath, nullptr));
    }

    // Start the recursive search *inside* the root
    searchRecursive(root, name, flag, rootPath, foundItems);

    // --- Display Results ---
    cout << "\n--- Search Results for '" << name << "' ---" << endl;
    
    if (foundItems.empty()) {
        cout << "No " << flag << "s found." << endl;
        return;
    }

    cout << "Found " << foundItems.size() << " " << flag << "(s):" << endl;
    for (size_t i = 0; i < foundItems.size(); ++i) {
        // Print the path from the struct
        cout << "  " << (i + 1) << ". " << foundItems[i].path << endl;
    }

    // --- Prompt to Print Content (only for files) ---
    if (flag == "file") {
        
        // --- 1. ASK (y/n) FIRST ---
        cout << "\nDo you want to print the content of a file? (y/n): ";
        char choice;
        cin >> choice;
        cin.ignore(10000, '\n'); // Clear buffer

        if (choice != 'y' && choice != 'Y') {
            return; // User said no, so just return
        }

        // --- 2. ENTER THE "KEEP-ASKING" LOOP ---
        while (true) {
            cout << "\nEnter file number to print (e.g., 1), or 'n' to stop: ";
            
            string input;
            cin >> input;
            cin.ignore(10000, '\n'); // Clear buffer

            if (input == "n" || input == "N") {
                break; // Exit loop
            }

            // 3. TRY TO CONVERT INPUT TO A NUMBER
            int fileNum = 0;
            try {
                fileNum = stoi(input); // stoi = "string to integer"
            } catch (...) {
                cout << "Invalid input. Please enter a number or 'n'." << endl;
                continue;
            }

            // 4. CHECK IF NUMBER IS VALID
            if (fileNum < 1 || fileNum > (int)foundItems.size()) {
                cout << "Invalid number. Please enter a number from the list." << endl;
                continue; 
            }

            // 5. PRINT THE CONTENT (O(1) ACCESS)
            FileNode* fileToPrint = foundItems[fileNum - 1].nodePtr;

            cout << "\n--- Content of " << fileToPrint->fileName << " ---" << endl;
            cout << fileToPrint->fileContent << endl;
            cout << "--- End of Content ---" << endl;
        }
    }
}


// --- PHASE 5: NEW IMPLEMENTATION ---

void FileSystem::sortItemsInFolder(string path, string type, string criteria, bool isAscending) {
    // 1. Find the folder to sort
    FolderNode* folderToSort = findFolderNode(path);

    if (folderToSort == nullptr) {
        cout << "Error: Folder at path '" << path << "' not found." << endl;
        return;
    }

    if (type == "file") {
        if (criteria != "name" && criteria != "size" && criteria != "date") {
            cout << "Error: Invalid criteria for sorting files." << endl;
            return;
        }
        
        // 2. Call the specialist to sort the file list
        FileNode* newHead = Sorting::sortFiles(folderToSort->fileListHead, criteria, isAscending);
        
        // 3. Re-attach the new, sorted list
        folderToSort->fileListHead = newHead;

        cout << "Success: Files in '" << path << "' sorted by " << criteria << "." << endl;

    } else if (type == "folder") {
        if (criteria != "name" && criteria != "date") {
            cout << "Error: Invalid criteria for sorting folders (only 'name' or 'date')." << endl;
            return;
        }

        // 2. Call the specialist to sort the subfolder list
        FolderListNode* newHead = Sorting::sortSubfolders(folderToSort->subfolderListHead, criteria, isAscending);
        
        // 3. Re-attach the new, sorted list
        folderToSort->subfolderListHead = newHead;

        cout << "Success: Subfolders in '" << path << "' sorted by " << criteria << "." << endl;
    }
}


// PHASE 6

vector<SearchResult> FileSystem::findFast(string name) {
    return mySearchIndex.find(name);
}


void FileSystem::fastEdit(FileNode* nodeToEdit) {
    if (nodeToEdit == nullptr) {
        cout << "Error: Cannot edit a null file." << endl;
        return;
    }


    cout << "--- Current Content ---" << endl;
    cout << nodeToEdit->fileContent << endl;
    cout << "-----------------------" << endl;
    cout << "Enter new content (type '~' on a new line to save):" << endl;

    string newContent = "";
    string line;
    while (getline(cin, line)) {
        if (line == "~") break;
        newContent += line + "\n";
    }
    if (!newContent.empty()) newContent.pop_back();
    
    // Directly update the node's data
    nodeToEdit->fileContent = newContent;
    nodeToEdit->fileSize = newContent.length(); 

    cout << "Success: File '" << nodeToEdit->fileName << "' updated." << endl;
}