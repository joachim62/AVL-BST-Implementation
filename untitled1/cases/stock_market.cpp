#include "../include/AVL.h"
#include <string>
#include <iostream>
#include <iomanip>

struct StockPrice {
    std::string symbol;
    double price;

    bool operator<(const StockPrice& other) const {
        return price < other.price;
    }

    bool operator>(const StockPrice& other) const {
        return price > other.price;
    }
};

class StockMarket {
private:
    ds::AVLTree<StockPrice> priceTree;

public:
    void addStock(const std::string& symbol, double price) {
        priceTree.insert(StockPrice{symbol, price});
    }

    void printPriceRange() const {
        std::cout << "\nCurrent Stock Prices:\n";
        std::cout << "--------------------\n";
        priceTree.inorder([](const StockPrice& stock) {
            std::cout << std::left << std::setw(10) << stock.symbol
                     << "$ " << std::fixed << std::setprecision(2) << stock.price << "\n";
        });
    }
};

int main() {
    StockMarket market;


    market.addStock("AAPL", 150.50);
    market.addStock("GOGL", 2800.75);
    market.addStock("MSFT", 290.25);
    market.addStock("AMZN", 3300.00);
    market.addStock("TSLA", 750.80);


    market.printPriceRange();

    return 0;
}