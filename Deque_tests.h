#include <iostream>
#include "Deque.h"

void test_deque() {
    Deque::Deque<int> dq;

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
    dq.erase(dq.begin()+1);
    std::cout << dq << std::endl;
    dq.insert(dq.begin()+1, 9);
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

void test_complex_deque() {
    typedef Deque::Deque<int> Di;
    typedef Deque::Deque<Di> DDi;

    Di di;
    di.push_back(10);
    di.push_back(20);

    DDi ddi;
    ddi.push_back(di);
}
