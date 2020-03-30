#ifndef LAB3_REMASTERED_QUEUE_H
#define LAB3_REMASTERED_QUEUE_H

#include <ostream>
#include "Deque.h"
#include "Dinorray.h"

namespace Deque {
    template<class T>
    class Queue {
        Deque <T> deq;
    public:
        void push(const T &val) {
            deq.push_back(val);
        }

        T pop() {
            auto val = deq.front();
            deq.pop_front();
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

        friend std::ostream &operator<<(std::ostream &os, const Queue &queue) {
            os << queue.deq;
            return os;
        }
    };

    template<class T>
    class CircularQueue {
        CircularDeque <T> deq;
    public:
        void push(const T &val) {
            deq.push_back(val);
        }

        T pop() {
            auto val = deq.front();
            deq.pop_front();
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

        friend std::ostream &operator<<(std::ostream &os, const CircularQueue &queue) {
            os << queue.deq;
            return os;
        }
    };
}

namespace Dinorray {
    template<class T>
    class Queue {
        Dinorray <T> deq;
    public:
        void push(const T &val) {
            deq.push_back(val);
        }

        T pop() {
            auto val = deq.front();
            deq.pop_front();
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

        friend std::ostream &operator<<(std::ostream &os, const Queue &queue) {
            os << queue.deq;
            return os;
        }
    };
}

#endif //LAB3_REMASTERED_QUEUE_H
