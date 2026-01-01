# AlgoFS – A DSA Driven In-Memory File System

## 📌 Project Overview
AlgoFS is a **console-based C++ application** that simulates a complete file system **entirely in memory**.  
The project is designed as a **portfolio and interview project** to demonstrate strong understanding of **Data Structures and Algorithms** by applying them to a real-world system.

This is **not** an OS-level file system. No data is written to disk — all operations happen in memory.

---

## 🎯 Key Idea: Time–Space Tradeoff
AlgoFS uses **extra memory for indexing** to achieve **very fast file search and access**.

- Extra memory → Hash Map index
- Benefit → **O(1)** file search and direct access
- Tradeoff → Slightly higher space usage

This clearly demonstrates a **time–space tradeoff**, a common system design principle.

---

## 🌳 Core Architecture
- The file system is represented as a **tree**
- Each folder is a node in the tree
- Linked lists are used to store:
  - Files inside a folder
  - Subfolders inside a folder

---

## 🚀 Features & Data Structures

| Feature | Data Structure / Algorithm |
|-------|----------------------------|
| Folder hierarchy | Tree + Linked Lists |
| Display structure | Recursive DFS (Pre-order) |
| Delete folder | Recursive DFS (Post-order) |
| Delete file | Linked List unlinking |
| Fast file search | Hash Map (O(1)) |
| Sorting files/folders | Merge Sort on Linked Lists |
| Batch operations | Queue (FIFO) |
| Path resolution | String parsing + traversal |

---

## 🔍 Fast Search Index (Important Feature)
- A **Hash Map** maps file names to a list of:
  - Full file path
  - Direct `FileNode*` pointer
- This allows:
  - Instant file lookup
  - Direct view/edit without re-traversing the folder tree
- Index is safely updated during:
  - File creation
  - File deletion

---

## 🗑️ Delete Operation (Key Highlight)
- **File deletion**:
  - Unlink from file linked list
  - Remove entry from search index
  - Free memory
- **Folder deletion**:
  - Uses **post-order DFS**
  - Deletes all files first
  - Then deletes all subfolders recursively
  - Finally deletes the folder itself
- This ensures:
  - No memory leaks
  - No dangling pointers

---

## ⚙️ How to Build and Run

### Compile
```bash
g++ main.cpp FileSystem.cpp SearchIndex.cpp Sorting.cpp TaskQueue.cpp -o AlgoFS

##Run 
./bin/algofs