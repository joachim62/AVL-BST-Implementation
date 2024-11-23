#ifndef PERFORMANCE_TESTS_H
#define PERFORMANCE_TESTS_H

#include <chrono>
#include <iostream>
#include <random>
#include <iomanip>
#include "../include/bst.h"

namespace test {

class PerformanceTests {
public:
    static void runAll() {
        std::cout << "\nRunning Performance Tests...\n";
        std::cout << "==========================\n";

        testInsertionPerformance();
        std::cout << "+ Insertion performance test completed\n";

        testSearchPerformance();
        std::cout << "+ Search performance test completed\n";

        testRemovalPerformance();
        std::cout << "+ Removal performance test completed\n";
    }

private:
    static void testInsertionPerformance() {
        ds::BST<int> tree;
        const int TEST_SIZE = 100000;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, TEST_SIZE * 2);

        auto start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < TEST_SIZE; i++) {
            tree.insert(dis(gen));
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        std::cout << "Inserted " << TEST_SIZE << " elements in "
                  << duration.count() << "ms ("
                  << std::fixed << std::setprecision(2)
                  << (duration.count() * 1000.0 / TEST_SIZE) << " μs per insertion)\n";
    }

    static void testSearchPerformance() {
        ds::BST<int> tree;
        const int TEST_SIZE = 1000000;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, TEST_SIZE * 2);

        // First insert elements
        std::vector<int> values;
        for(int i = 0; i < TEST_SIZE; i++) {
            int val = dis(gen);
            values.push_back(val);
            tree.insert(val);
        }

        // Test search
        auto start = std::chrono::high_resolution_clock::now();
        for(int value : values) {
            tree.contains(value);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        std::cout << "Searched " << TEST_SIZE << " elements in "
                  << duration.count() << "ms ("
                  << std::fixed << std::setprecision(2)
                  << (duration.count() * 1000.0 / TEST_SIZE) << " μs per search)\n";
    }

    static void testRemovalPerformance() {
        ds::BST<int> tree;
        const int TEST_SIZE = 100000;
        std::vector<int> values;

        // Insert elements
        for(int i = 0; i < TEST_SIZE; i++) {
            values.push_back(i);
            tree.insert(i);
        }

        // Shuffle the values for random removal
        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(values.begin(), values.end(), gen);

        // Removal Testing
        auto start = std::chrono::high_resolution_clock::now();
        for(int value : values) {
            tree.remove(value);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        std::cout << "Removed " << TEST_SIZE << " elements in "
                  << duration.count() << "ms ("
                  << std::fixed << std::setprecision(2)
                  << (duration.count() * 1000.0 / TEST_SIZE) << " μs per removal)\n";
    }
};

}

#endif