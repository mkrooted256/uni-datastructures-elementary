#include <iostream>
#include "CircularDeque.h"
#include "Queue.h"

void test_circular_deque() {
    Deque::CircularDeque<int> dq;

    dq.push_back(1);
    std::cout << dq << std::endl;
    dq.pop_back();
    std::cout << dq << std::endl;

    dq.push_back(1);
    std::cout << dq << std::endl;
    dq.pop_front();
    std::cout << dq << std::endl;

    dq.push_front(1);
    std::cout << dq << std::endl;
    dq.pop_back();
    std::cout << dq << std::endl;

    dq.push_front(1);
    std::cout << dq << std::endl;
    dq.pop_front();
    std::cout << dq << std::endl;

    dq.push_back(1);
    dq.push_back(2);
    dq.push_back(3);
    std::cout << dq << std::endl;
    dq.erase(dq.begin() + 1);
    std::cout << dq << std::endl;
    dq.insert(dq.begin() + 1, 9);
    std::cout << dq << std::endl;
    dq.push_front(0);
    dq.push_front(-1);
    std::cout << dq << std::endl;

    dq.pop_front();
    std::cout << dq << std::endl;
    dq.pop_front();
    dq.pop_front();
    dq.pop_front();
    std::cout << dq << std::endl;
}

void test_complex_circular_deque() {
    typedef Deque::CircularDeque<int> Di;
    typedef Deque::CircularDeque<Di> DDi;

    Di di;
    di.push_back(10);
    di.push_back(20);

    DDi ddi;
    ddi.push_back(di);
}

void test_circularity_of_cdq() {
    Deque::CircularDeque<int> dq;

    dq.push_back(1);
    dq.push_back(2);
    dq.push_back(3);
    dq.push_back(4);
    std::cout << dq << std::endl;

    dq.insert(dq.begin() - 2, 60);
    dq.insert(dq.begin() - 3, 50);
    std::cout << dq << std::endl;

    dq.insert(dq.end() + 2, -20);
    dq.insert(dq.end() + 3, -10);
    std::cout << dq << std::endl;
}

void test_circular_queue() {
    Deque::CircularQueue<int> cdq;
    cdq.push(1);
    cdq.push(2);
    cdq.push(3);
    cdq.push(4);
    std::cout << cdq << std::endl;
    cdq.pop();
    cdq.pop();
    std::cout << cdq << std::endl;
}