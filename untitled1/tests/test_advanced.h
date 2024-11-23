#ifndef TEST_ADVANCED_H
#define TEST_ADVANCED_H

#include <cassert>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>
#include "../include/bst.h"

namespace test {

class AdvancedTests {
public:
    static void runAll() {
        std::cout << "\nRunning Advanced Tests...\n";
        std::cout << "------------------------\n";

        testBalancing();
        std::cout << "+ Balancing tests passed\n";

        testIterator();
        std::cout << "+ Iterator tests passed\n";

        testStressTest();
        std::cout << "+ Stress tests passed\n";

        testTypeCompatibility();
        std::cout << "+ Type compatibility tests passed\n";

        testEdgeCases();
        std::cout << "+ Edge cases tests passed\n";

        std::cout << "All advanced tests passed successfully!\n";
    }

private:
    static void testBalancing() {
        ds::BST<int> tree;

        // Left-Heavy Scenario Testing
        tree.insert(30);
        tree.insert(20);
        tree.insert(10);

        // Right-Heavy Scenario Testing
        tree.insert(40);
        tree.insert(50);

        // After Balancing, Verify Tree's Properties
        std::vector<int> elements;
        tree.inorder([&elements](const int& val) {
            elements.push_back(val);
        });

        // Verify elements are still in order
        assert(std::is_sorted(elements.begin(), elements.end()));
    }

    static void testIterator() {
        ds::BST<int> tree;
        std::vector<int> numbers = {5, 3, 7, 1, 9, 4, 6};

        // Insert numbers
        for (int num : numbers) {
            tree.insert(num);
        }

        // Iterator Traversal Testing
        std::vector<int> iteratedValues;
        for (const auto& value : tree) {
            iteratedValues.push_back(value);
        }

        // Verify iterator produces sorted sequence
        assert(std::is_sorted(iteratedValues.begin(), iteratedValues.end()));
        assert(iteratedValues.size() == numbers.size());
    }

    static void testStressTest() {
        ds::BST<int> tree;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 1000);

        const int TEST_SIZE = 1000;
        for (int i = 0; i < TEST_SIZE; i++) {
            tree.insert(dis(gen));
        }

        // Verify tree properties
        std::vector<int> elements;
        tree.inorder([&elements](const int& val) {
            elements.push_back(val);
        });
        assert(std::is_sorted(elements.begin(), elements.end()));
    }

    static void testTypeCompatibility() {
        // Test with string
        ds::BST<std::string> stringTree;
        stringTree.insert("hello");
        stringTree.insert("world");
        assert(stringTree.contains("hello"));

        // Test with custom type
        struct Point {
            int x, y;
            bool operator<(const Point& other) const {
                return x < other.x || (x == other.x && y < other.y);
            }
            bool operator>(const Point& other) const {
                return other < *this;
            }
            bool operator==(const Point& other) const {
                return x == other.x && y == other.y;
            }
        };

        ds::BST<Point> pointTree;
        pointTree.insert(Point{1, 2});
        pointTree.insert(Point{3, 4});
        assert(pointTree.contains(Point{1, 2}));
    }

    static void testEdgeCases() {
        ds::BST<int> tree;

        // Test empty tree operations
        assert(tree.empty());
        assert(!tree.remove(1));

        // Test single node operations
        tree.insert(1);
        assert(tree.size() == 1);
        assert(tree.remove(1));
        assert(tree.empty());

        // Test multiple insertions and removals
        tree.insert(2);  // Insert 2
        assert(tree.size() == 1);

        tree.insert(1);  // Insert 1
        assert(tree.size() == 2);

        tree.insert(3);  // Insert 3
        assert(tree.size() == 3);

        // Remove middle element (2)
        bool removed = tree.remove(2);
        assert(removed);
        assert(tree.size() == 2);

        // Verify remaining elements
        assert(tree.contains(1));
        assert(tree.contains(3));
        assert(!tree.contains(2));

        // Test clear operation
        tree.clear();
        assert(tree.empty());
        assert(tree.size() == 0);
    }
};

}

#endif