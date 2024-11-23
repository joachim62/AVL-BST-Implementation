#include <iostream>
#include <iomanip>
#include <chrono>
#include <functional>
#include <vector>
#include <windows.h>
#include "test_basic.h"
#include "test_advanced.h"
#include "performance_tests.h"

namespace Color {
    const std::string RED     = "\033[91m";  // Bright Red
    const std::string GREEN   = "\033[92m";  // Bright Green
    const std::string YELLOW  = "\033[93m";  // Bright Yellow
    const std::string BLUE    = "\033[94m";  // Bright Blue
    const std::string MAGENTA = "\033[95m";  // Bright Magenta
    const std::string CYAN    = "\033[96m";  // Bright Cyan
    const std::string WHITE   = "\033[97m";  // Bright White
    const std::string RESET   = "\033[0m";
    const std::string BOLD    = "\033[1m";
}

class ProgressBar {
private:
    const int width = 50;
    const char full_block = '#';
    const char empty_block = '-';
    const std::vector<char> spinner = {'|', '/', '-', '\\'};  //ASCII spinner
    int spinner_idx = 0;

public:
    void update(float progress, const std::string& status) {
        int pos = width * progress;

        std::cout << "\r"
                  << Color::CYAN << spinner[spinner_idx] << " " << Color::RESET
                  << Color::BOLD << Color::BLUE << "[" << Color::RESET;

        // Progress Bar
        for (int i = 0; i < width; ++i) {
            if (i < pos) {
                if (i < width / 3) std::cout << Color::RED;
                else if (i < width * 2/3) std::cout << Color::YELLOW;
                else std::cout << Color::GREEN;
                std::cout << full_block << Color::RESET;
            }
            else std::cout << Color::WHITE << empty_block << Color::RESET;
        }

        std::cout << Color::BOLD << Color::BLUE << "] " << Color::RESET
                  << Color::BOLD << std::setw(3) << static_cast<int>(progress * 100.0) << "% "
                  << Color::CYAN << status << Color::RESET
                  << std::flush;

        spinner_idx = (spinner_idx + 1) % spinner.size();
    }

    void complete(const std::string& message) {
        update(1.0f, "");
        std::cout << "\n" << Color::GREEN << "+ " << message << Color::RESET << "\n";
    }
};

class TestRunner {
private:
    struct TestResult {
        std::string name;
        bool passed;
        double duration;
        std::string error_message;
    };

    std::vector<TestResult> results;
    ProgressBar progress_bar;

    double runWithTimer(const std::function<void()>& test, const std::string& name) {
        auto start = std::chrono::high_resolution_clock::now();

        // Simulate progress for the test
        for (float progress = 0.0f; progress <= 1.0f; progress += 0.01f) {
            progress_bar.update(progress, "Running " + name + "...");
            Sleep(10);  // Windows sleep function (milliseconds), adjustable
        }

        try {
            test();
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            results.push_back({name, true, duration.count() / 1000.0, ""});
            progress_bar.complete(name + " completed successfully!");
            return duration.count() / 1000.0;
        }
        catch (const std::exception& e) {
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            results.push_back({name, false, duration.count() / 1000.0, e.what()});
            std::cout << Color::RED << "Error in " << name << ": " << e.what() << Color::RESET << "\n";
            return duration.count() / 1000.0;
        }
    }

public:
    void runAllTests() {
        printHeader();

        // Run test suites
        runTestSuite("Basic Tests", test::BasicTests::runAll);
        runTestSuite("Advanced Tests", test::AdvancedTests::runAll);

        // Run performance tests
        std::cout << "\nStarting Performance Tests...\n";
        test::PerformanceTests::runAll();

        printSummary();
    }

private:
    void printHeader() {
        std::cout << Color::BLUE << Color::BOLD;
        std::cout << "\n====================================\n";
        std::cout << "         BST Test Runner\n";
        std::cout << "====================================\n" << Color::RESET;
        std::cout << Color::CYAN << "Starting tests...\n\n" << Color::RESET;
    }

    void runTestSuite(const std::string& name, const std::function<void()>& suite) {
        std::cout << Color::YELLOW << Color::BOLD << "\nRunning " << name << "..." << Color::RESET << "\n";
        runWithTimer(suite, name);
    }

    void printSummary() {
        int passed = 0;
        int total = results.size();

        std::cout << Color::BLUE << Color::BOLD;
        std::cout << "\n====================================\n";
        std::cout << "           Test Summary\n";
        std::cout << "====================================\n" << Color::RESET;

        for (const auto& result : results) {
            if (result.passed) {
                passed++;
                std::cout << Color::GREEN << "+ " << Color::RESET;
            } else {
                std::cout << Color::RED << "- " << Color::RESET;
            }

            std::cout << Color::BOLD << std::left << std::setw(20) << result.name << Color::RESET
                     << " (" << std::fixed << std::setprecision(3) << result.duration << "s)";

            if (!result.passed) {
                std::cout << Color::RED << " ! " << result.error_message << Color::RESET;
            }
            std::cout << "\n";
        }

        std::cout << "\n" << Color::BOLD << "Results: " << Color::RESET;
        if (passed == total) {
            std::cout << Color::GREEN << Color::BOLD;
        } else {
            std::cout << Color::RED << Color::BOLD;
        }

        std::cout << passed << "/" << total << " tests passed" << Color::RESET << "\n";

        double totalTime = 0;
        for (const auto& result : results) {
            totalTime += result.duration;
        }
        std::cout << Color::CYAN << "Total time: " << std::fixed << std::setprecision(3)
                  << totalTime << " seconds" << Color::RESET << "\n\n";
    }
};

int main() {
    // Enable Windows console virtual terminal sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= 0x0004;
            SetConsoleMode(hOut, dwMode);
        }
    }

    TestRunner runner;

    try {
        runner.runAllTests();
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << Color::RED << "Fatal error: " << e.what() << Color::RESET << "\n";
        return 1;
    }
}