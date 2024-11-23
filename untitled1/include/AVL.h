
#ifndef AVL_H
#define AVL_H

#include <algorithm>
#include <memory>
#include <functional>

namespace ds {

template<typename T>
class AVLTree {
private:
    struct Node {
        T data;
        int height;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        Node(const T& value) : data(value), height(1) {}
    };

    std::unique_ptr<Node> root;
    size_t size_;

    int getHeight(const Node* node) const {
        return node ? node->height : 0;
    }

    int getBalance(const Node* node) const {
        return node ? getHeight(node->left.get()) - getHeight(node->right.get()) : 0;
    }

    void updateHeight(Node* node) {
        if (node) {
            node->height = 1 + std::max(getHeight(node->left.get()),
                                      getHeight(node->right.get()));
        }
    }

    std::unique_ptr<Node> rightRotate(std::unique_ptr<Node> y) {
        auto x = std::move(y->left);
        auto T2 = std::move(x->right);

        x->right = std::move(y);
        x->right->left = std::move(T2);

        updateHeight(x->right.get());
        updateHeight(x.get());

        return x;
    }

    std::unique_ptr<Node> leftRotate(std::unique_ptr<Node> x) {
        auto y = std::move(x->right);
        auto T2 = std::move(y->left);

        y->left = std::move(x);
        y->left->right = std::move(T2);

        updateHeight(y->left.get());
        updateHeight(y.get());

        return y;
    }

    std::unique_ptr<Node> balance(std::unique_ptr<Node> node) {
        if (!node) return nullptr;

        updateHeight(node.get());
        int balance = getBalance(node.get());

        // Left Heavy Situation
        if (balance > 1) {
            if (getBalance(node->left.get()) < 0) {
                node->left = leftRotate(std::move(node->left));
            }
            return rightRotate(std::move(node));
        }

        // Right Heavy Situation
        if (balance < -1) {
            if (getBalance(node->right.get()) > 0) {
                node->right = rightRotate(std::move(node->right));
            }
            return leftRotate(std::move(node));
        }

        return std::move(node);
    }

    std::unique_ptr<Node> insert(std::unique_ptr<Node> node, const T& value) {
        if (!node) {
            size_++;
            return std::make_unique<Node>(value);
        }

        if (value < node->data) {
            node->left = insert(std::move(node->left), value);
        } else if (value > node->data) {
            node->right = insert(std::move(node->right), value);
        } else {
            return node; // Duplicate value
        }

        return balance(std::move(node));
    }

public:
    AVLTree() : size_(0) {}

    void insert(const T& value) {
        root = insert(std::move(root), value);
    }

    bool contains(const T& value) const {
        const Node* current = root.get();
        while (current) {
            if (value < current->data) {
                current = current->left.get();
            } else if (value > current->data) {
                current = current->right.get();
            } else {
                return true;
            }
        }
        return false;
    }

    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

    // Traversal with Callback Func
    void inorder(const std::function<void(const T&)>& callback) const {
        inorderTraversal(root.get(), callback);
    }

private:
    void inorderTraversal(const Node* node, const std::function<void(const T&)>& callback) const {
        if (node) {
            inorderTraversal(node->left.get(), callback);
            callback(node->data);
            inorderTraversal(node->right.get(), callback);
        }
    }
};

}

#endif