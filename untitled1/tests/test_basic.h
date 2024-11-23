#ifndef TEST_BASIC_H
#define TEST_BASIC_H

#include <cassert>
#include <string>
#include <vector>
#include <iostream>
#include "../include/bst.h"

namespace test {

class BasicTests {
public:
    static void runAll() {
        std::cout << "\nRunning Basic Tests...\n";
        std::cout << "----------------------\n";

        testInsertion();
        std::cout << "+ Insertion tests passed\n";

        testRemoval();
        std::cout << "+ Removal tests passed\n";

        testSearch();
        std::cout << "+ Search tests passed\n";

        testTraversal();
        std::cout << "+ Traversal tests passed\n";

        testEmptyTree();
        std::cout << "+ Empty tree tests passed\n";

        std::cout << "All basic tests passed successfully!\n";
    }

private:
    static void testInsertion() {
        ds::BST<int> tree;

        // Test single insertion
        tree.insert(5);
        assert(tree.size() == 1);
        assert(tree.contains(5));

        // Test multiple insertions
        tree.insert(3);
        tree.insert(7);
        assert(tree.size() == 3);
        assert(tree.contains(3));
        assert(tree.contains(7));

        // Test duplicate insertion
        tree.insert(5);
        assert(tree.size() == 3);  // Size shouldn't change

        // Test with different types
        ds::BST<std::string> stringTree;
        stringTree.insert("hello");
        assert(stringTree.contains("hello"));
        assert(!stringTree.contains("world"));
    }

    static void testRemoval() {
        ds::BST<int> tree;

        // Test removing from empty tree
        assert(!tree.remove(5));

        // Test removing existing elements
        tree.insert(5);
        tree.insert(3);
        tree.insert(7);

        assert(tree.remove(3));
        assert(tree.size() == 2);
        assert(!tree.contains(3));

        assert(tree.remove(5));
        assert(tree.size() == 1);
        assert(!tree.contains(5));

        assert(tree.remove(7));
        assert(tree.empty());
    }

    static void testSearch() {
        ds::BST<int> tree;

        // Test empty tree
        assert(!tree.contains(5));

        // Test existing elements
        tree.insert(5);
        tree.insert(3);
        tree.insert(7);

        assert(tree.contains(5));
        assert(tree.contains(3));
        assert(tree.contains(7));
        assert(!tree.contains(4));
    }

    static void testTraversal() {
        ds::BST<int> tree;
        tree.insert(2);
        tree.insert(1);
        tree.insert(3);

        std::vector<int> result;
        tree.inorder([&result](const int& val) {
            result.push_back(val);
        });

        // Verify inorder traversal
        std::vector<int> expected = {1, 2, 3};
        assert(result == expected);
    }

    static void testEmptyTree() {
        ds::BST<int> tree;

        // Test empty tree properties
        assert(tree.empty());
        assert(tree.size() == 0);
        assert(!tree.contains(1));
        assert(!tree.remove(1));

        // Test empty tree traversal
        std::vector<int> result;
        tree.inorder([&result](const int& val) {
            result.push_back(val);
        });
        assert(result.empty());
    }
};

}

#endif