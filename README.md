# Student Record Management System (Binary Search Tree)

[![C++ Version](https://img.shields.io/badge/Language-C%2B%2B17%20%2F%20C%2B%2B20-blue.svg)](https://isocpp.org/)
[![Platform](https://img.shields.io/badge/IDE-Microsoft%20Visual%20Studio%202022-purple.svg)](https://visualstudio.microsoft.com/)
[![Coursework](https://img.shields.io/badge/Academic-UTAR%20UCCD1024-orange.svg)](#)

An optimized, memory-efficient data management program engineered in C++ that leverages custom **Binary Search Trees (BST)** to handle rapid searching, structural cloning, and algorithmic tree traversals. Designed as a standalone system to efficiently catalog and manipulate student records utilizing recursive algorithms and deep-tree traversal patterns.

---

## 🚀 Key Engineering Features

* **Dynamic Data Ingestion:** Parses structure-formatted external files (`student.txt`) to build balanced runtime nodes mapping to unique student IDs.
* **Deep Architectural Analysis:** Custom implementation of recursive height-calculation modules to locate and map all leaf nodes residing at the absolute deepest layer of the hierarchy tree.
* **Bi-Directional Traversal System:** Features decoupled in-order traversal variants enabling linear sorted presentation (Ascending/Descending) to the console interface or standard text export.
* **Subtree Isolation (Cloning):** Implements dynamic memory allocation logic to safely copy and clone distinct data sub-branches from a parent tree into clean runtime target workspaces without altering the initial structural matrix.
* **Level-Order & Path Trace Diagnostics:** Leverages queue-less tracking methods to print sequential hierarchical layers and trace every distinct active structural pathway out to external boundary paths.

---

## 🛠️ Technical Stack & Environment

* **Core Language:** C++
* **Development Platform:** Microsoft Visual Studio 2022
* **Data Core Concepts:** Binary Search Trees, Tail Recursion, High-Depth Traversal, Memory Clones, File System Streams (`fstream`)

---

## 📊 Core Architecture Details

### The Data Node Structure
Each node within the system manages a complex dataset block bound to a structural pointer framework:
* **Key Variable:** Student ID (`int`)
* **Payload Package:** Student Name, Local Address, Date of Birth (DOB), Contact Phone, Course Enrolled, and CGPA Metrics.

### Sample Execution Pathways
```text
      [ 123 ]
      /     \
   [65]     [126]
     \      /   \
    [78] [125]  [234]
