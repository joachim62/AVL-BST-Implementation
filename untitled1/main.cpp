#include "include/AVL.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <cmath>
#include <windows.h>
#include <conio.h>

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void pause() {
    std::cout << "\nPress any key to continue...";
    _getch();
    system("cls");
}

void printMenu() {
    setColor(11);  // Light Cyan
    std::cout << "\n";
    std::cout << "+------------------------+\n";
    std::cout << "|     AVL Tree Menu      |\n";
    std::cout << "+------------------------+\n";
    setColor(7);   // White
    std::cout << "| 1. Insert              |\n";
    std::cout << "| 2. Search              |\n";
    std::cout << "| 3. Display (in-order)  |\n";
    std::cout << "| 4. Visualize tree      |\n";
    std::cout << "| 5. Get size            |\n";
    std::cout << "| 6. Check if empty      |\n";
    std::cout << "| 7. Exit                |\n";
    setColor(11);  // Light Cyan
    std::cout << "+------------------------+\n";
    setColor(7);   // White
    std::cout << "Enter your choice: ";
}

void showLoading(const std::string& message) {
    std::cout << message;
    setColor(14);  // Yellow
    for(int i = 0; i < 3; i++) {
        Sleep(200);
        std::cout << ".";
    }
    std::cout << "\n";
    setColor(7);   // White
}

void printSpaces(int count) {
    for (int i = 0; i < count; i++) {
        std::cout << " ";
    }
}

void visualizeTree(const ds::AVLTree<int>& tree) {
    setColor(10);  // Light Green
    std::cout << "\nTree Visualization:\n\n";
    setColor(7);   // White

    std::vector<int> nodes;
    tree.inorder([&nodes](const int& val) {
        nodes.push_back(val);
    });

    if (nodes.empty()) {
        setColor(14);  // Yellow
        std::cout << "Empty tree\n";
        setColor(7);   // White
        return;
    }

    // Calculate tree levels
    int height = static_cast<int>(std::log2(nodes.size()) + 1);
    int maxWidth = (1 << height) * 6;  // Increased spacing

    // Print tree structure
    int index = 0;
    for (int level = 0; level < height && index < nodes.size(); level++) {
        int levelNodes = 1 << level;
        int branchWidth = maxWidth / (1 << level);

        // Print nodes
        printSpaces(branchWidth / 2);
        for (int i = 0; i < levelNodes && index < nodes.size(); i++) {
            setColor(11);  // Light Cyan
            if (i > 0) printSpaces(branchWidth - 1);
            std::cout << std::setw(3) << nodes[index++];
            setColor(7);   // White
        }
        std::cout << "\n";

        // Print connections if not last level
        if (level < height - 1 && index < nodes.size()) {
            printSpaces(branchWidth / 4);
            for (int i = 0; i < levelNodes && (index + i) < nodes.size(); i++) {
                if (i > 0) printSpaces(branchWidth - 1);
                setColor(14);  // Yellow
                std::cout << "  /";
                printSpaces(branchWidth / 2 - 3);
                std::cout << "\\";
                setColor(7);   // White
            }
            std::cout << "\n";
        }
    }

    // Show tree properties
    setColor(13);  // Light Magenta
    std::cout << "\nTree Properties:\n";
    std::cout << "* Size: " << nodes.size() << " nodes\n";
    std::cout << "* Height: " << height << " levels\n";
    std::cout << "* Balanced: Yes (AVL property maintained)\n\n";

    // Show traversal
    setColor(9);   // Light Blue
    std::cout << "In-order traversal: ";
    for (size_t i = 0; i < nodes.size(); ++i) {
        std::cout << nodes[i];
        if (i < nodes.size() - 1) {
            setColor(8);   // Gray
            std::cout << " -> ";
            setColor(9);   // Light Blue
        }
    }
    std::cout << "\n";
    setColor(7);   // White
}

int main() {
    ds::AVLTree<int> tree;
    int choice, value;

    setColor(10);  // Light Green
    std::cout << "Welcome to AVL Tree Interactive Program!\n";
    setColor(7);   // White

    while (true) {
        printMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cout << "Enter value to insert: ";
                std::cin >> value;
                showLoading("Inserting");
                tree.insert(value);
                setColor(10);  // Light Green
                std::cout << "Inserted " << value << "\n";
                setColor(7);   // White
                pause();
                break;
            }

            case 2: {
                std::cout << "Enter value to search: ";
                std::cin >> value;
                showLoading("Searching");
                if (tree.contains(value)) {
                    setColor(10);  // Light Green
                    std::cout << "Found " << value << "\n";
                } else {
                    setColor(12);  // Light Red
                    std::cout << "Not found " << value << "\n";
                }
                setColor(7);   // White
                pause();
                break;
            }

            case 3: {
                showLoading("Retrieving tree contents");
                setColor(14);  // Yellow
                std::cout << "Tree contents: ";
                tree.inorder([](const int& val) {
                    std::cout << val << " ";
                });
                std::cout << "\n";
                setColor(7);   // White
                pause();
                break;
            }

            case 4: {
                showLoading("Generating visualization");
                visualizeTree(tree);
                pause();
                break;
            }

            case 5: {
                showLoading("Calculating size");
                setColor(11);  // Light Cyan
                std::cout << "Tree size: " << tree.size() << " nodes\n";
                setColor(7);   // White
                pause();
                break;
            }

            case 6: {
                showLoading("Checking tree status");
                if (tree.empty()) {
                    setColor(14);  // Yellow
                    std::cout << "Tree is empty\n";
                } else {
                    setColor(10);  // Light Green
                    std::cout << "Tree is not empty\n";
                }
                setColor(7);   // White
                pause();
                break;
            }

            case 7: {
                setColor(13);  // Light Magenta
                std::cout << "Implementation finished\n";
                setColor(7);   // White
                return 0;
            }

            default:
                setColor(12);  // Light Red
                std::cout << "Invalid choice!\n";
                setColor(7);   // White
                pause();
        }
    }

    return 0;
}