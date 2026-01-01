// File: src/main.cpp

#include <iostream>
#include <string>
#include "FileSystem.h" // Include our main FileSystem class
#include "TaskQueue.h"
#include "SearchResult.h" // <-- ADDED THIS

using namespace std;

// This function clears the input buffer
// We need this after using 'cin >>' before 'getline'
void clearInputBuffer() {
    cin.clear(); // Clear any error flags
    cin.ignore(10000, '\n'); // Ignore remaining characters
}

void showMainMenu() {
    cout << "\n=========================================" << endl;
    cout << " AlgoFS : A DSA Driven File System" << endl;
    cout << "=========================================\n" << endl;
    cout << "1. Display Structure" << endl;
    cout << "2. Create Item (File/Folder)" << endl;
    cout << "3. Delete Item (File/Folder)" << endl;
    cout << "4. Search Item (File/Folder)" << endl;
    cout << "5. View File Content" << endl;
    cout << "6. Edit File Content" << endl;
    cout << "7. Add to Batch Queue" << endl;
    cout << "8. Process Batch Queue" << endl;
    cout << "9. Sort Items in Folder" << endl;
    cout << "10. Fast File Operations (Search, View, Edit)" << endl;
    cout << "11. Quit" << endl; // <-- FIXED MENU
    cout << "Please enter your choice: ";
}

int main() {
    FileSystem myFileSystem;
    TaskQueue myTaskQueue;

    // --- BOOTSTRAP PHASE ---
    if (myFileSystem.getRoot() == nullptr) {
        cout << "=========================================" << endl;
        cout << " Welcome to AlgoFS!" << endl;
        cout << "=========================================" << endl;
        cout << "System is empty. You must create a root folder." << endl;
        
        string rootName;
        cout << "Please enter a name for your root folder: ";
        getline(cin, rootName);

        if (rootName.empty()) rootName = "root";
        
        myFileSystem.createRootFolder(rootName);
    }

    // --- MAIN MENU LOOP ---
    int choice = 0;
    while (choice != 11) { // <-- FIXED QUIT NUMBER
        showMainMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            clearInputBuffer();
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }
        
        clearInputBuffer(); 

        // Variables needed for our switch cases
        string path, name, content, flag;
        int typeChoice;
        string criteria, type;
        bool isAscending;

        switch (choice) {
            case 1:
                myFileSystem.displayStructure();
                break;
            
            case 2: // Create Item
                cout << "What do you want to create?\n 1. Folder\n 2. File\nChoice: ";
                cin >> typeChoice;
                clearInputBuffer();

                if (typeChoice == 1) {
                    cout << "Enter parent path (e.g., /MyPC): ";
                    getline(cin, path);
                    cout << "Enter new folder name: ";
                    getline(cin, name);
                    myFileSystem.createFolder(path, name);
                } else if (typeChoice == 2) {
                    cout << "Enter path to folder (e.g., /MyPC/Docs): ";
                    getline(cin, path);
                    cout << "Enter new file name: ";
                    getline(cin, name);
                    cout << "Enter file content (type '~' on a new line to save):" << endl;
                    
                    content = "";
                    string line;
                    while (getline(cin, line)) {
                        if (line == "~") break;
                        content += line + "\n";
                    }
                    if (!content.empty()) content.pop_back();
                    
                    myFileSystem.addFile(path, name, content);
                } else {
                    cout << "Invalid choice." << endl;
                }
                break;
            
            case 3: // Delete Item
                cout << "What do you want to delete?\n 1. Folder\n 2. File\nChoice: ";
                cin >> typeChoice;
                clearInputBuffer();

                if (typeChoice == 1) {
                    flag = "folder";
                    cout << "Enter full path to folder (e.g., /MyPC/Docs): ";
                    getline(cin, path);
                } else if (typeChoice == 2) {
                    flag = "file";
                    cout << "Enter full path to file (e.g., /MyPC/Docs/report.txt): ";
                    getline(cin, path);
                } else {
                    cout << "Invalid choice." << endl;
                    break;
                }
                
                myFileSystem.deleteItem(path, flag);
                break;

            case 4: // Search Item (Slow)
                cout << "What do you want to search for?\n 1. Folder\n 2. File\nChoice: ";
                cin >> typeChoice;
                clearInputBuffer();

                if (typeChoice == 1) {
                    flag = "folder";
                    cout << "Enter name of folder to search for: ";
                } else if (typeChoice == 2) {
                    flag = "file";
                    cout << "Enter name of file to search for: ";
                } else {
                    cout << "Invalid choice." << endl;
                    break;
                }
                
                getline(cin, name);
                myFileSystem.searchItem(name, flag);
                break;

            case 5: // View File Content (Slow)
                cout << "Enter full path to file (e.g., /MyPC/Docs/report.txt): ";
                getline(cin, path);
                myFileSystem.viewFileContent(path);
                break;

            case 6: // Edit File Content (Slow)
                cout << "Enter full path to file (e.g., /MyPC/Docs/report.txt): ";
                getline(cin, path);
                myFileSystem.editFileContent(path);
                break;
            
            case 7: // Add to Batch
                cout << "\n--- Batch Task Mode ---" << endl;
                while (true) {
                    cout << "\nWhat do you want to add to the batch?\n 1. Folder\n 2. File\n 3. Stop (Return to Main Menu)\nChoice: ";
                    cin >> typeChoice;
                    clearInputBuffer();

                    if (typeChoice == 1) {
                        cout << "  Enter parent path (e.g., /MyPC): ";
                        getline(cin, path);
                        cout << "  Enter new folder name: ";
                        getline(cin, name);
                        myTaskQueue.addTask(BatchTask("createFolder", path, name));
                        cout << "  Success: 'Create Folder' task added to batch." << endl;

                    } else if (typeChoice == 2) {
                        cout << "  Enter path to folder (e.g., /MyPC/Docs): ";
                        getline(cin, path);
                        cout << "  Enter new file name: ";
                        getline(cin, name);
                        cout << "  Enter file content (type '~' on a new line to save):" << endl;
                        content = "";
                        string line;
                        while (getline(cin, line)) {
                            if (line == "~") break;
                            content += line + "\n";
                        }
                        if (!content.empty()) content.pop_back();
                        
                        myTaskQueue.addTask(BatchTask("addFile", path, name, content));
                        cout << "  Success: 'Add File' task added to batch." << endl;
                    
                    } else if (typeChoice == 3) {
                        cout << "Exiting batch mode. Returning to main menu." << endl;
                        break; 
                    
                    } else {
                        cout << "Invalid choice. Please enter 1, 2, or 3." << endl;
                    }
                }
                break; 
            
            case 8: // Process Batch
                cout << "\nProcessing batch queue..." << endl;
                if (myTaskQueue.isEmpty()) {
                    cout << "Queue is empty. Nothing to process." << endl;
                    break;
                }
                while (!myTaskQueue.isEmpty()) {
                    BatchTask nextTask = myTaskQueue.getNextTask();
                    if (nextTask.command == "createFolder") {
                        cout << "  - Executing: Create Folder '" << nextTask.itemName << "'..." << endl;
                        myFileSystem.createFolder(nextTask.parentPath, nextTask.itemName);
                    } else if (nextTask.command == "addFile") {
                        cout << "  - Executing: Add File '" << nextTask.itemName << "'..." << endl;
                        myFileSystem.addFile(nextTask.parentPath, nextTask.itemName, nextTask.content);
                    }
                }
                cout << "Batch processing complete." << endl;
                break;

            case 9: // Sort Items in Folder
                cout << "Enter full path to folder (e.g., /MyPC/Docs): ";
                getline(cin, path);

                cout << "What do you want to sort?\n 1. Files\n 2. Subfolders\nChoice: ";
                cin >> typeChoice;
                clearInputBuffer();

                if (typeChoice == 1) {
                    type = "file";
                    cout << "Sort by:\n 1. Name\n 2. Date\n 3. Size\nChoice: ";
                    cin >> typeChoice;
                    clearInputBuffer();
                    if (typeChoice == 1) criteria = "name"; 
                    else if (typeChoice == 2) criteria = "date";
                    else if (typeChoice == 3) criteria = "size";
                    else { cout << "Invalid choice." << endl; break; }
                
                } else if (typeChoice == 2) {
                    type = "folder";
                    cout << "Sort by:\n 1. Name\n 2. Date\nChoice: ";
                    cin >> typeChoice;
                    clearInputBuffer();
                    if (typeChoice == 1) criteria = "name";
                    else if (typeChoice == 2) criteria = "date";
                    else { cout << "Invalid choice." << endl; break; }

                } else {
                    cout << "Invalid choice." << endl;
                    break;
                }

                cout << "Order:\n 1. Ascending\n 2. Descending\nChoice: ";
                cin >> typeChoice;
                clearInputBuffer();
                isAscending = (typeChoice == 1);

                myFileSystem.sortItemsInFolder(path, type, criteria, isAscending);
                break;

            

            case 10: { // <-- FIXED (added brace)
                cout << "Enter file name to find instantly: ";
                getline(cin, name);

                vector<SearchResult> results;
                results = myFileSystem.findFast(name); 

                if (results.empty()) {
                    cout << "No files found with that name." << endl;
                    break;
                }

                cout << "\n--- Fast Search Results ---" << endl;
                cout << "Found " << results.size() << " file(s):" << endl;
                for (size_t i = 0; i < results.size(); ++i) {
                    cout << "  " << (i + 1) << ". " << results[i].path << endl;
                }


                while(true){
                    cout << "\nEnter character to (v)iew, (e)dit, or (n) to cancel: ";
                    char op;
                    cin >> op;
                    
                    if (op == 'n' || op == 'N') {
                        cin.ignore(10000, '\n');
                        break;
                    }

                    cout << "Enter the file number (e.g., 1): ";
                    int fileNum;
                    cin >> fileNum;
                    cin.ignore(10000, '\n');

                    if (cin.fail() || fileNum < 1 || fileNum > (int)results.size()) {
                        cout << "Invalid number." << endl;
                        break;
                    }

                    SearchResult selected = results[fileNum - 1];

                    if (op == 'v' || op == 'V') {
                        // --- O(1) VIEW ---
                        cout << "\n--- Content of " << selected.nodePtr->fileName << " ---" << endl;
                        cout << selected.nodePtr->fileContent << endl;
                        cout << "--- End of Content ---" << endl;
                    
                    } else if (op == 'e' || op == 'E') {
                        // --- O(1) EDIT ---
                        // <-- FIXED (calling the new 'fastEdit' function)
                        myFileSystem.fastEdit(selected.nodePtr);
                    
                    } else {
                        cout << "Invalid operation." << endl;
                    }
                }
                break;

            } // <-- FIXED (added brace)

            case 11 : // <-- FIXED QUIT NUMBER
                cout << "Exiting. All data will be lost. Goodbye!" << endl;
                break;
            
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    return 0;
}