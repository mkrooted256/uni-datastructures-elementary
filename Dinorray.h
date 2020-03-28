#ifndef LAB3_REMASTERED_DEQUE_H
#define LAB3_REMASTERED_DEQUE_H

#include <algorithm>

namespace Dinorray {
    template<class T>
    class Dinorray {
        T * mem;
        size_t size;
        size_t capacity;
    public:
        class iterator : public std::iterator<std::random_access_iterator_tag, T, size_t, const T *, T> {
             size_t index;
        public:
            explicit iterator(size_t index) : index(index) {}

            iterator &operator++() {
                index++;
                return *this;
            }
            iterator &operator--() {
                index--;
                return *this;
            }
            T operator*() const { return mem[index]; }

            // Access index
            size_t getIndex() const {
                return index;
            }

            // Movement
            iterator operator+(size_t steps) {
                return iterator(index + steps);
            }
            iterator operator-(size_t steps) {
                return iterator(index - steps);
            }
            iterator operator-(iterator rhs) {
                return iterator(index - rhs.index);
            }
        };
        class reverse_iterator : public std::reverse_iterator<iterator> {};

    private:
        void reserve(size_t newcap) {
            auto newmem = new T[newcap];
            memcpy(newmem, mem, capacity * sizeof(T));
            capacity = newcap;
            delete [] mem;
            mem = newmem;
        }

    public:
        explicit Dinorray(size_t init_cap=16) : mem(new T[init_cap]), size(0), capacity(init_cap) {}

        // STL utility functions

        // Iter, pointing to the first element
        iterator begin() { return iterator(0); }
        // Iter, pointing to the virtual element after the last
        iterator end() { return iterator(size); }

        // RIter, pointing to the last element
        reverse_iterator rbegin() { return iterator(size-1); }
        // RIter, pointing to virtual element before the first
        reverse_iterator rend() { return iterator(-1); }

        // First and last elements
        T front() { return mem[0]; }
        T back() { return mem[size-1]; }

        // Insert (before)
        iterator insert(iterator pos, T val) {
            if (size == capacity)
                reserve(capacity * 2);

            auto ipos = pos.getIndex();
            memmove(mem+ipos+1, mem+ipos, size-ipos);
            mem[ipos] = val;

            return iterator(ipos+1);
        }

        // Delete
        iterator erase(iterator pos) {
            auto ipos = pos.getIndex();
            memmove(mem+ipos, mem+ipos+1, size-ipos-1);
            return iterator(ipos);
        }

        // Pushes - insert edge element
        void push_back(T val) { insert(end()); }
        void push_front(T val) { insert(begin()); }

        // Popes - destroys edge element
        void pop_back() { erase(back()); }
        void pop_front() { erase(front()); }

        bool empty() {
            // True if there are no elements between virtual edge elements
            return size == 0;
        }

        ~Dinorray() {
            delete [] mem;
        }

    };
}

#endif //LAB3_REMASTERED_DEQUE_H
