#ifndef LAB3_REMASTERED_DEQUE_H
#define LAB3_REMASTERED_DEQUE_H

#include <algorithm>

namespace Dinorray {
    template<class T>
    class Node {
        Node *prev;
        Node *next;
        T val;
    public:
        Node() : next(nullptr), prev(nullptr), val() {}
        Node(Node *prev, Node *next) : next(next), prev(prev) {}
        Node(Node *prev, Node *next, T val) : next(next), prev(prev), val(val) {}

        Node *Next() const {
            return next;
        }

        Node *Prev() const {
            return prev;
        }

        T Val() const {
            return val;
        }
    };

    template<class T>
    class Dinorray {
    public:
        class iterator : public std::iterator<std::bidirectional_iterator_tag, T, size_t, const T *, T> {
            Node<T> * node;
        public:
            explicit iterator(Node<T> * node) : node(node) {}

            iterator &operator++() {
                node = node->Next();
                return *this;
            }
            iterator &operator--() {
                node = node->Prev();
                return *this;
            }
            bool operator==(iterator other) const { return node == other.node; }
            bool operator!=(iterator other) const { return !(*this == other); }
            T operator*() const { return node->Val(); }

            // Node access
            Node<T> *getNode() const {
                return node;
            }

            // Movement
            iterator operator+(size_t steps) {
                auto n = node;
                for (int i=0; i<steps; i++) {
                    n = n->Next();
                }
                return iterator(n);
            }
            iterator operator-(size_t steps) {
                auto n = node;
                for (int i=0; i<steps; i++) {
                    n = n->Prev();
                }
                return iterator(n);
            }
        };
        class reverse_iterator : public std::reverse_iterator<iterator> {};

    private:
        Node<T> *_begin;
        Node<T> *_end;
    public:
        // Setup service border nodes
        Dinorray() : _begin(new Node<T>()), _end(new Node<T>()) {
            _begin = Node(nullptr, _end);
            _end = Node(_begin, nullptr);
        }

        // STL utility functions

        // Iter, pointing to the first element
        iterator begin() { return iterator(_begin->Next()); }
        // Iter, pointing to the virtual element after the last
        iterator end() { return iterator(_end); }

        // RIter, pointing to the last element
        reverse_iterator rbegin() { return iterator(_end->Prev()); }
        // RIter, pointing to virtual element before the first
        reverse_iterator rend() { return iterator(_begin); }

        // First and last elements
        T front() { return _begin->Next()->Val(); }
        T back() { return _end->Prev()->Val(); }

        // Insert (before)
        iterator insert(iterator pos, T val) {
            auto nprev = pos.getNode()->Prev();
            auto nnext = pos.getNode();
            auto nnode = new Node<T>(nprev, nnext, val); // New node
            nprev = Node(nprev->Prev(), nnode, nprev->Val()); // change nprev->next
            nnext = Node(nnode, nnext->Next(), nnext->Val()); // change nnext->prev
            return iterator(nnode);
        }

        // Delete
        iterator erase(iterator pos) {
            auto nprev = pos.getNode()->Prev();
            auto nnext = pos.getNode();
            nprev = Node(nprev->Prev(), nnext, nprev->Val()); // change nprev->next
            nnext = Node(nprev, nnext->Next(), nnext->Val()); // change nnext->prev
            return iterator(nnext);
        }

        // Pushes - insert edge element
        void push_back(T val) { insert(end()); }
        void push_front(T val) { insert(begin()); }

        // Popes - destroys edge element
        void pop_back() { erase(back()); }
        void pop_front() { erase(front()); }

        bool empty() {
            // True if there are no elements between virtual edge elements
            return _begin->Next() == _end;
        }

        ~Dinorray() {
            while (not empty())
                pop_back();
            delete _begin;
            delete _end;
        }

    };
}

#endif //LAB3_REMASTERED_DEQUE_H
