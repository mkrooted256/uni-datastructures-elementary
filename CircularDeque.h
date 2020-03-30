#ifndef LAB3_REMASTERED_CIRCULARDEQUE_H
#define LAB3_REMASTERED_CIRCULARDEQUE_H

#include "Deque.h"

namespace Deque {
    template<class T>
    class CircularDeque {
    public:
        class iterator : public std::iterator<std::bidirectional_iterator_tag, T, size_t, const T *, T> {
            const CircularDeque<T> *dq;
            Node<T> *node;
        public:
            explicit iterator(Node<T> *node, CircularDeque<T> *dq) : node(node), dq(dq) {}
            explicit iterator(Node<T> *node, const CircularDeque<T> *dq) : node(node), dq(dq) {}

            iterator &operator++() {
                // Circularity - if end, jump to first
                if (node->next == nullptr)
                    node = dq->rend().base().getNode();
                else
                    node = node->next;
                return *this;
            }

            iterator &operator--() {
                // Circularity - if rend, jump to last
                if (node->prev == nullptr)
                    node = dq->end().getNode();
                else
                    node = node->prev;
                return *this;
            }

            bool operator==(iterator other) const { return node == other.node and dq == other.dq; }

            bool operator!=(iterator other) const { return !(*this == other); }

            T operator*() const { return node->val; }

            // Node access
            Node<T> *getNode() const {
                return node;
            }

            // Movement
            iterator operator+(size_t steps) {
                auto result = iterator(node, dq);
                for (int i = 0; i < steps; i++) {
                    ++result;
                }
                return result;
            }

            iterator operator-(size_t steps) {
                auto result = iterator(node, dq);
                for (int i = 0; i < steps; i++) {
                    --result;
                }
                return result;
            }
        };

        typedef std::reverse_iterator<iterator> reverse_iterator;

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
        CircularDeque() : _begin(new Node<T>(nullptr, nullptr)), _end(new Node<T>(nullptr, nullptr)) {
            _begin->next = _end;
            _end->prev = _begin;
        }

        // Copy constructor
        CircularDeque(const CircularDeque &src) : CircularDeque() {
            auto node = _begin;
            for (auto i: src) {
                node->next = new Node<T>(node, _end, i);
                node = node->next;
            }
            _end->prev = node;
        }

        // Assignment operator
        CircularDeque &operator=(const CircularDeque &rhs) {
            if (this != &rhs) {
                recycle();
                _begin = new Node<T>(nullptr, nullptr);
                _end = new Node<T>(nullptr, nullptr);
                _begin->next = _end;
                auto node = _begin;
                for (auto i: rhs) {
                    node->next = new Node<T>(node, _end, i);
                    node = node->next;
                }
                _end->prev = node;
            }
            return *this;
        }


        // STL utility functions

        // Iter, pointing to the first element
        iterator begin() const { return iterator(_begin->next, this); }

        // Iter, pointing to the virtual element after the last
        iterator end() const { return iterator(_end, this); }

        // RIter, pointing to the last element
        reverse_iterator rbegin() const { iterator a(_end->prev, this); return std::make_reverse_iterator(a); }

        // RIter, pointing to virtual element before the first
        reverse_iterator rend() const { iterator a(_begin, this); return std::make_reverse_iterator(a); }

        // First and last elements
        T front() { return _begin->next->val; }

        T back() { return _end->prev->val; }

        // Insert (before)
        iterator insert(iterator pos, const T &val) {
            auto right = pos.getNode();
            auto left = right->prev;
            auto nnode = new Node<T>(left, right, val); // New node
            left->next = nnode;
            right->prev = nnode;
            return iterator(nnode, this);
        }

        // Delete
        iterator erase(iterator pos) {
            auto delnode = pos.getNode();
            auto left = delnode->prev;
            auto right = delnode->next;
            left->next = right;
            right->prev = left;
            delete delnode;
            return iterator(right, this);
        }

        // Pushes - insert edge element
        void push_back(const T &val) { insert(end(), val); }

        void push_front(const T &val) { insert(begin(), val); }

        // Popes - destroys edge element
        void pop_back() { erase(end() - 1); }

        void pop_front() { erase(begin()); }

        bool empty() {
            // True if there are no elements between virtual edge elements
            return _end->prev == _begin;
        }

        ~CircularDeque() {
            recycle();
        }

    };
}

template<class T>
std::ostream &operator<<(std::ostream &os, const Deque::CircularDeque<T> &cdq) {
    for (auto i: cdq) {
        os << i << " ";
    }
    return os;
}

#endif //LAB3_REMASTERED_CIRCULARDEQUE_H
