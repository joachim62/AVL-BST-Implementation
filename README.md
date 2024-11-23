
# Intro:
A comprehensive C++ implementation of AVL and Binary Search Trees with suitable applications, interactive visualization, and extensive testing suite.

Data Structures: AVL/BST Implementation and Applications
# Project Structure:
project_root/


 
├── include/

│   ├── AVL.h                # AVL Tree implementation (self-balancing BST)

│   └── BST.h                # Binary Search Tree base implementation

├── examples/

│   ├── Contacts.cpp         # Contact management using AVL

│   └── stock_market.cpp     # Stock market tracker using AVL

├── tests/

│   ├── test_basic.h         # Basic BST/AVL operations testing

│   ├── test_advanced.h      # Advanced tree operations testing

│   ├── performance_tests.h  # Performance comparison (BST vs AVL)

│   └── test_main.cpp        # Test suite runner

└── main.cpp                 # Interactive AVL visualization program

# Features:  
### Binary Search Tree (BST)
Standard BST operation (Insert, Search, Delete, etc..)
In-order, Pre-order and Post-order traversals.
Base Implementation for AVL extension

### AVL Tree
Self-balancing mechanism
Automatic height adjustment
Blance Factor Maintenance
Complex Rotation Handling
Performance Optimization

### Interative Visualization
Real-time tree structure display
Color-coded node representation
Balance factor visualization
Operation: Result Feedback

# Getting Started

### Pre-requisites:
C++ Compiler ( Supporting C++ 17)

Windows OS ( For Visualization )

### Compilation
// Compile main program
#### g++ main.cpp -o main

#### ./main

Usage: The interative program provides following options:
1. Insert Value
2. Search Value
3. Display Tree (In-order)
4. Visualize Tree Structure
5. Get Tree Size
6. Check Tree if empty
7. Exit

### Cases
Contacts.cpp
#### g++ cases/Contact.cpp -o contacts

#### ./contacts

stock_market.cpp
#### g++ cases/stock_market.cpp -o stocks

#### ./stocks

### Testing
#### g++ tests/test_main.cpp -o tests

#### ./tests


# NOTE:
### The compilation command may vary based on:
-Compiler Version

-System Configuration

-Preffered Output Name

-C++ Standard Requirement

For specific instance:
### g++ -std=c++17 main.cpp -o main
### ./main

Both command acheive the same result, freely modify the best suit for your working environment.



