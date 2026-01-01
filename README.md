# AlgoFS – A DSA Driven In-Memory File System

## 📌 Project Overview
AlgoFS is a **console-based C++ application** that simulates a complete file system **entirely in memory**.  
The project is designed as a **portfolio-level and interview-oriented project** to demonstrate strong understanding of **Data Structures and Algorithms (DSA)** by applying them to a real-world system.

> ⚠️ This is **not** an OS-level file system. No data is written to disk — all operations happen **only in memory**.

---

## 🎯 Key Concept: Time–Space Tradeoff
AlgoFS intentionally uses **extra memory for indexing** to achieve **very fast file search and access**.

- Extra memory → **Hash Map index**
- Benefit → **O(1)** average-case file search
- Tradeoff → Slightly higher space usage

This clearly demonstrates the **time–space tradeoff**, a fundamental concept in system design and DSA.

---

## 🌳 Core Architecture
- The file system is represented as a **Tree**
- Each **folder** is a tree node
- Each folder maintains:
  - A **Linked List** of files
  - A **Linked List** of subfolders

```
Root
 ├── Folder_A
 │    ├── file1.txt
 │    └── file2.txt
 └── Folder_B
      └── Folder_C
           └── file3.txt
```

---

## 🚀 Features & Data Structures

| Feature | Data Structure / Algorithm |
|------|----------------------------|
| Folder hierarchy | Tree + Linked Lists |
| Display structure | Recursive DFS (Pre-order) |
| Delete folder | Recursive DFS (Post-order) |
| Delete file | Linked List unlinking |
| Fast file search | Hash Map (O(1)) |
| Sorting files/folders | Merge Sort on Linked Lists |
| Batch operations | Queue (FIFO) |
| Path resolution | String parsing + traversal |

---

## 🔍 Fast Search Index (Key Highlight)
AlgoFS maintains a **global search index** using a **Hash Map**.

- **Key** → File name
- **Value** → List of:
  - Full file path
  - Direct `FileNode*` pointer

### Benefits
- Instant file lookup (**O(1)** average)
- Direct file access without re-traversing the folder tree
- Efficient view/edit/delete operations

### Index Safety
The index is **always synchronized** during:
- File creation
- File deletion
- Folder deletion (recursive cleanup)

---

## 🗑️ Delete Operation (Important Design)

### File Deletion
1. Unlink from folder’s file linked list
2. Remove entry from hash map index
3. Free allocated memory

### Folder Deletion
- Uses **Post-order DFS**
- Deletes all files first
- Recursively deletes subfolders
- Deletes the folder node at the end

✔️ Ensures:
- No memory leaks
- No dangling pointers
- Clean recursive cleanup

---

## ⚙️ Build & Run Instructions

### Recommended Project Structure
```
AlgoFS/
 ├── src/
 │    ├── main.cpp
 │    ├── FileSystem.cpp
 │    ├── SearchIndex.cpp
 │    ├── Sorting.cpp
 │    └── TaskQueue.cpp
 ├── include/
 │    └── *.h
 ├── bin/
 └── README.md
```

### Compile
```bash
mkdir -p bin
g++ src/main.cpp src/FileSystem.cpp src/SearchIndex.cpp src/Sorting.cpp src/TaskQueue.cpp -o bin/algofs
```

### Run
```bash
./bin/algofs
```

> ⚠️ Note: Linux is **case-sensitive**. Ensure the executable name matches exactly.

---

## 🧠 Learning Outcomes
This project demonstrates:
- Practical use of **Trees, Linked Lists, Hash Maps, Queues**
- Recursive DFS traversal (pre-order & post-order)
- Memory management in C++
- Real-world application of **time–space tradeoff**
- Clean system-style architecture design

---

## 📈 Future Enhancements
- File permissions (read/write)
- Undo/Redo using Stack
- File content simulation
- Persistent storage (optional)
- CLI command parser (like `ls`, `cd`, `rm`)

---

## 🧑‍💻 Author
**Harshal Pawar**  
DSA-focused system design project for learning, interviews, and portfolio.

---

⭐ If you like this project, consider starring the repository!

