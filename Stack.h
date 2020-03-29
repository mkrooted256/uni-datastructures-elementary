#ifndef LAB3_REMASTERED_STACK_H
#define LAB3_REMASTERED_STACK_H

#include "Deque.h"
#include "Dinorray.h"

namespace Deque {
    template<class T>
    class Stack {
        Deque <T> deq;
    public:
        void push(const T &val) {
            deq.push_back(val);
        }

        T pop() {
            auto val = deq.back();
            deq.pop_back();
            return val;
        }

        typedef typename Deque<T>::iterator iterator;

        iterator begin() { return deq.begin(); }

        iterator end() { return deq.end(); }

        const Deque <T> &getDeq() const {
            return deq;
        }

        bool empty() {
            return deq.empty();
        }

        friend std::ostream &operator<<(std::ostream &os, const Stack &stack) {
            os << stack.deq;
            return os;
        }
    };
}

namespace Dinorray {
    template<class T>
    class Stack {
        Dinorray <T> deq;
    public:
        void push(const T &val) {
            deq.push_back(val);
        }

        T pop() {
            auto val = deq.back();
            deq.pop_back();
            return val;
        }

        typedef typename Dinorray<T>::iterator iterator;

        iterator begin() { return deq.begin(); }

        iterator end() { return deq.end(); }

        const Dinorray <T> &getDeq() const {
            return deq;
        }

        bool empty() {
            return deq.empty();
        }

        friend std::ostream &operator<<(std::ostream &os, const Stack &stack) {
            os << stack.deq;
            return os;
        }
    };
}

#endif //LAB3_REMASTERED_STACK_H
