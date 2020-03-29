#ifndef LAB3_REMASTERED_DINORRAY_H
#define LAB3_REMASTERED_DINORRAY_H

#include <algorithm>

namespace Dinorray {
    template<class T>
    class Dinorray {
        T *mem;
        size_t size;
        size_t capacity;
    public:
        class iterator : public std::iterator<std::random_access_iterator_tag, T, size_t, const T *, T> {
            size_t index;
            T *mem;

            iterator(size_t index, T *mem) : index(index), mem(mem) {}

        public:
            iterator(size_t index, const Dinorray &rr) : index(index), mem(rr.mem) {}

            iterator &operator++() {
                index++;
                return *this;
            }

            iterator &operator--() {
                index--;
                return *this;
            }

            T operator*() const { return mem[index]; }

            bool operator==(iterator other) const { return index == other.index and mem == other.mem; }

            bool operator!=(iterator other) const { return !(*this == other); }

            // Access index
            size_t getIndex() const {
                return index;
            }

            // Movement
            iterator operator+(size_t steps) {
                return iterator(index + steps, mem);
            }

            iterator operator-(size_t steps) {
                return iterator(index - steps, mem);
            }

            iterator operator-(iterator rhs) {
                return iterator(index - rhs.index, mem);
            }
        };

        class reverse_iterator : public std::reverse_iterator<iterator> {
        };

        void reserve(size_t newcap) {
            auto newmem = new T[newcap];
            memcpy(newmem, mem, capacity * sizeof(T));
            capacity = newcap;
            delete[] mem;
            mem = newmem;
        }

        explicit Dinorray(size_t init_cap = 16) : mem(new T[init_cap]), size(0), capacity(init_cap) {}

        // Copy constructor
        Dinorray(const Dinorray &src) : mem(new T[src.capacity]), size(src.size), capacity(src.capacity) {
            memcpy(mem, src.mem, capacity * sizeof(T));
        }

        // Assignment operator
        Dinorray &operator=(const Dinorray &rhs) {
            if (this != &rhs) {
                delete[] mem;
                mem = new T[rhs.capacity];
                size = rhs.size;
                capacity = rhs.capacity;
                memcpy(mem, rhs.mem, capacity * sizeof(T));
            }
            return *this;
        }

        // STL utility functions

        // Iter, pointing to the first element
        iterator begin() const { return iterator(0, *this); }

        // Iter, pointing to the virtual element after the last
        iterator end() const { return iterator(size, *this); }

        // RIter, pointing to the last element
        reverse_iterator rbegin() const { return iterator(size - 1, *this); }

        // RIter, pointing to virtual element before the first
        reverse_iterator rend() const { return iterator(-1, *this); }

        // First and last elements
        const T &front() { return mem[0]; }

        const T &back() { return mem[size - 1]; }

        // Insert (before)
        iterator insert(iterator pos, T val) {
            if (size == capacity)
                reserve(capacity * 2);

            auto ipos = pos.getIndex();
            memmove(mem + ipos + 1, mem + ipos, (size - ipos) * sizeof(T));
            mem[ipos] = val;
            size++;

            return iterator(ipos + 1, *this);
        }

        // Delete
        iterator erase(iterator pos) {
            auto ipos = pos.getIndex();
            memmove(mem + ipos, mem + ipos + 1, (size - ipos - 1) * sizeof(T));
            size--;
            return iterator(ipos, *this);
        }

        // Pushes - insert edge element
        void push_back(const T &val) { insert(end(), val); }

        void push_front(const T &val) { insert(begin(), val); }

        // Popes - destroys edge element
        void pop_back() { erase(end() - 1); }

        void pop_front() { erase(begin()); }

        bool empty() {
            // True if there are no elements between virtual edge elements
            return size == 0;
        }

        ~Dinorray() {
            delete[] mem;
        }

    };
}

template<class T>
std::ostream &operator<<(std::ostream &os, const Dinorray::Dinorray<T> &rr) {
    for (auto i: rr) {
        os << i << " ";
    }
    return os;
}

#endif //LAB3_REMASTERED_DINORRAY_H
