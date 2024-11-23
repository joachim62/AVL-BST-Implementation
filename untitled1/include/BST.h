#ifndef BST_HPP
#define BST_HPP

#include <memory>
#include <stack>
#include <queue>
#include <functional>
#include <stdexcept>
#include <algorithm>

namespace ds {

template<typename T>
class BST {
private:
    struct Node {
        T data;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        int height;

        explicit Node(const T& value) : data(value), left(nullptr), right(nullptr), height(1) {}
        explicit Node(T&& value) : data(std::move(value)), left(nullptr), right(nullptr), height(1) {}
    };

    using NodePtr = std::shared_ptr<Node>;
    NodePtr root_;
    size_t size_{0};

public:
    class iterator {
    private:
        std::stack<NodePtr> stack_;
        NodePtr current_;

        void pushLeft(NodePtr node) {
            while (node) {
                stack_.push(node);
                node = node->left;
            }
        }

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        iterator() = default;

        explicit iterator(NodePtr root) {
            pushLeft(root);
            if (!stack_.empty()) {
                current_ = stack_.top();
            }
        }

        reference operator*() { return current_->data; }
        pointer operator->() { return &current_->data; }

        iterator& operator++() {
            if (stack_.empty()) {
                current_ = nullptr;
                return *this;
            }

            NodePtr node = stack_.top();
            stack_.pop();
            pushLeft(node->right);
            current_ = stack_.empty() ? nullptr : stack_.top();
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const iterator& other) const {
            return (stack_.empty() && other.stack_.empty()) ||
                   (!stack_.empty() && !other.stack_.empty() && stack_.top() == other.stack_.top());
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }
    };

    // Constructors and assignment operators
    BST() noexcept = default;

    BST(const BST& other) {
        root_ = clone(other.root_);
        size_ = other.size_;
    }

    BST(BST&& other) noexcept
        : root_(std::move(other.root_)), size_(other.size_) {
        other.size_ = 0;
    }

    BST& operator=(const BST& other) {
        if (this != &other) {
            BST temp(other);
            std::swap(root_, temp.root_);
            std::swap(size_, temp.size_);
        }
        return *this;
    }

    BST& operator=(BST&& other) noexcept {
        if (this != &other) {
            root_ = std::move(other.root_);
            size_ = other.size_;
            other.size_ = 0;
        }
        return *this;
    }

    ~BST() = default;

    // Iterator methods
    iterator begin() noexcept { return iterator(root_); }
    iterator end() noexcept { return iterator(); }

    // Capacity
    size_t size() const noexcept { return size_; }
    bool empty() const noexcept { return size_ == 0; }

    // Modifiers
    void insert(const T& value) {
        root_ = insertImpl(root_, value);
    }

    void insert(T&& value) {
        root_ = insertImpl(root_, std::move(value));
    }

    bool remove(const T& value) {
        bool found = false;
        root_ = removeImpl(root_, value, found);
        return found;
    }

    void clear() noexcept {
        root_.reset();
        size_ = 0;
    }

    // Lookup
    bool contains(const T& value) const noexcept {
        auto current = root_;
        while (current) {
            if (value == current->data) return true;
            current = (value < current->data) ? current->left : current->right;
        }
        return false;
    }

    const T& min() const {
        if (!root_) throw std::runtime_error("Tree is empty");
        return findMin(root_)->data;
    }

    const T& max() const {
        if (!root_) throw std::runtime_error("Tree is empty");
        auto current = root_;
        while (current->right) current = current->right;
        return current->data;
    }

    // Traversal methods
    void inorder(const std::function<void(const T&)>& func) const {
        inorderImpl(root_, func);
    }

    void preorder(const std::function<void(const T&)>& func) const {
        preorderImpl(root_, func);
    }

    void postorder(const std::function<void(const T&)>& func) const {
        postorderImpl(root_, func);
    }

    void levelorder(const std::function<void(const T&)>& func) const {
        if (!root_) return;
        std::queue<NodePtr> q;
        q.push(root_);
        while (!q.empty()) {
            NodePtr current = q.front();
            q.pop();
            func(current->data);
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
    }

private:
    // Helper methods
    NodePtr clone(const NodePtr& node) const {
        if (!node) return nullptr;
        NodePtr newNode = std::make_shared<Node>(node->data);
        newNode->left = clone(node->left);
        newNode->right = clone(node->right);
        newNode->height = node->height;
        return newNode;
    }

    int getHeight(const NodePtr& node) const noexcept {
        return node ? node->height : 0;
    }

    void updateHeight(NodePtr& node) noexcept {
        if (node) {
            node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        }
    }

    int balanceFactor(const NodePtr& node) const noexcept {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    NodePtr rotateRight(NodePtr& y) {
        NodePtr x = y->left;
        NodePtr T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    NodePtr rotateLeft(NodePtr& x) {
        NodePtr y = x->right;
        NodePtr T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    NodePtr balance(NodePtr& node) {
        if (!node) return nullptr;

        updateHeight(node);
        int balance = balanceFactor(node);

        // Left Heavy
        if (balance > 1) {
            if (balanceFactor(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }

        // Right Heavy
        if (balance < -1) {
            if (balanceFactor(node->right) > 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }

        return node;
    }

    NodePtr insertImpl(NodePtr& node, T value) {
        if (!node) {
            size_++;
            return std::make_shared<Node>(std::move(value));
        }

        if (value < node->data) {
            node->left = insertImpl(node->left, std::move(value));
        } else if (value > node->data) {
            node->right = insertImpl(node->right, std::move(value));
        }

        return balance(node);
    }

    NodePtr findMin(NodePtr node) const {
        while (node && node->left) node = node->left;
        return node;
    }

    NodePtr removeImpl(NodePtr& node, const T& value, bool& found) {
        if (!node) return nullptr;

        if (value < node->data) {
            node->left = removeImpl(node->left, value, found);
        }
        else if (value > node->data) {
            node->right = removeImpl(node->right, value, found);
        }
        else {
            found = true;

            // Case 1: No children
            if (!node->left && !node->right) {
                size_--;
                return nullptr;
            }

            // Case 2: One child
            if (!node->left) {
                size_--;
                return node->right;
            }
            if (!node->right) {
                size_--;
                return node->left;
            }

            // Case 3: Two children
            NodePtr successor = findMin(node->right);
            node->data = successor->data;
            node->right = removeImpl(node->right, successor->data, found);
            return balance(node);
        }

        return balance(node);
    }

    void inorderImpl(const NodePtr& node, const std::function<void(const T&)>& func) const {
        if (!node) return;
        inorderImpl(node->left, func);
        func(node->data);
        inorderImpl(node->right, func);
    }

    void preorderImpl(const NodePtr& node, const std::function<void(const T&)>& func) const {
        if (!node) return;
        func(node->data);
        preorderImpl(node->left, func);
        preorderImpl(node->right, func);
    }

    void postorderImpl(const NodePtr& node, const std::function<void(const T&)>& func) const {
        if (!node) return;
        postorderImpl(node->left, func);
        postorderImpl(node->right, func);
        func(node->data);
    }
};

}

#endif // BST_HPP