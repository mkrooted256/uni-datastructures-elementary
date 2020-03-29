#ifndef LAB3_REMASTERED_DEQUE_H
#define LAB3_REMASTERED_DEQUE_H

#include <algorithm>

namespace Deque {
    template<class T>
    struct Node {
        Node *prev;
        Node *next;
        T val;
        
        Node() : next(nullptr), prev(nullptr), val() {}
        Node(Node *prev, Node *next) : next(next), prev(prev) {}
        Node(Node *prev, Node *next, const T& val) : next(next), prev(prev), val(val) {}
    };

    template<class T>
    class Deque {
    public:
        class iterator : public std::iterator<std::bidirectional_iterator_tag, T, size_t, const T *, T> {
            Node<T> * node;
        public:
            explicit iterator(Node<T> * node) : node(node) {}

            iterator &operator++() {
                node = node->next;
                return *this;
            }
            iterator &operator--() {
                node = node->prev;
                return *this;
            }
            bool operator==(iterator other) const { return node == other.node; }
            bool operator!=(iterator other) const { return !(*this == other); }
            T operator*() const { return node->val; }

            // Node access
            Node<T> *getNode() const {
                return node;
            }

            // Movement
            iterator operator+(size_t steps) {
                auto n = node;
                for (int i=0; i<steps; i++) {
                    n = n->next;
                }
                return iterator(n);
            }
            iterator operator-(size_t steps) {
                auto n = node;
                for (int i=0; i<steps; i++) {
                    n = n->prev;
                }
                return iterator(n);
            }
        };
        class reverse_iterator : public std::reverse_iterator<iterator> {};

    private:
        Node<T> *_begin;
        Node<T> *_end;

        void recycle() {
            while (not empty())
                pop_back();
            delete _begin;
            delete _end;
        }

    public:
        // Setup service border nodes
        Deque() : _begin(new Node<T>(nullptr, nullptr)), _end(new Node<T>(nullptr, nullptr)) {
            _begin->next = _end;
            _end->prev = _begin;
        }

        // Copy constructor
        Deque(const Deque& src): Deque() {
            auto node = _begin;
            for(auto i: src) {
                node->next = new Node<T>(node, _end, i);
                node = node->next;
            }
            _end->prev = node;
        }

        // Assignment operator
        Deque& operator=(const Deque& rhs) {
            if (this != &rhs) {
                recycle();
                _begin = new Node<T>(nullptr, nullptr);
                _end = new Node<T>(nullptr, nullptr);
                _begin -> next = _end;
                auto node = _begin;
                for(auto i: rhs) {
                    node->next = new Node<T>(node, _end, i);
                    node = node->next;
                }
                _end->prev = node;
            }
            return *this;
        }


        // STL utility functions

        // Iter, pointing to the first element
        iterator begin() const { return iterator(_begin->next); }
        // Iter, pointing to the virtual element after the last
        iterator end() const { return iterator(_end); }

        // RIter, pointing to the last element
        reverse_iterator rbegin() const { return reverse_iterator(_end->prev); }
        // RIter, pointing to virtual element before the first
        reverse_iterator rend() const { return reverse_iterator(_begin); }

        // First and last elements
        T front() { return _begin->next->val; }
        T back() { return _end->prev->val; }

        // Insert (before)
        iterator insert(iterator pos, const T& val) {
            auto right = pos.getNode();
            auto left = right->prev;
            auto nnode = new Node<T>(left, right, val); // New node
            left->next = nnode;
            right->prev = nnode;
            return iterator(nnode);
        }

        // Delete
        iterator erase(iterator pos) {
            auto delnode = pos.getNode();
            auto left = delnode->prev;
            auto right = delnode->next;
            left->next = right;
            right->prev = left;
            delete delnode;
            return iterator(right);
        }

        // Pushes - insert edge element
        void push_back(const T& val) { insert(end(), val); }
        void push_front(const T& val) { insert(begin(), val); }

        // Popes - destroys edge element
        void pop_back() { erase(end()-1); }
        void pop_front() { erase(begin()); }

        bool empty() {
            // True if there are no elements between virtual edge elements
            return _end->prev == _begin;
        }

        ~Deque() {
            recycle();
        }

    };
}

template <class T>
std::ostream& operator<<(std::ostream& os, Deque::Deque<T> &dq) {
    for (auto i: dq) {
        os << i << " ";
    }
    return os;
}

#endif //LAB3_REMASTERED_DEQUE_H
