#include "Dinorray.h"
#include <iostream>

void test_array() {
    Dinorray::Dinorray<int> r;

    r.push_back(1);
    std::cout << r << std::endl;
    r.pop_back();
    std::cout << r << std::endl;

    r.push_back(1);
    std::cout << r << std::endl;
    r.pop_front();
    std::cout << r << std::endl;

    r.push_front(1);
    std::cout << r << std::endl;
    r.pop_back();
    std::cout << r << std::endl;

    r.push_front(1);
    std::cout << r << std::endl;
    r.pop_front();
    std::cout << r << std::endl;

    r.push_back(1);
    r.push_back(2);
    r.push_back(3);
    std::cout << r << std::endl;
    r.erase(r.begin() + 1);
    std::cout << r << std::endl;
    r.insert(r.begin() + 1, 9);
    std::cout << r << std::endl;
    r.push_front(0);
    r.push_front(-1);
    std::cout << r << std::endl;

    r.pop_front();
    std::cout << r << std::endl;
    r.pop_front();
    r.pop_front();
    r.pop_front();
    std::cout << r << std::endl;
}

void test_complex_array() {
    typedef Dinorray::Dinorray<int> Di;
    typedef Dinorray::Dinorray<Di> DDi;
//
//    Di di(1);
//    di.push_back(10);
//    di.push_back(20);
//
//    DDi ddi(1);
//    ddi.push_back(std::move(di));
//    std::cout << "Finish" << std::endl;

    struct Tester {
        int label{0};

        Tester(int label): label(label) {
            std::cout << "+" << label << " ";
        }
        Tester() {
            std::cout << "+" << label << " ";
        }

        Tester(const Tester& src): label(src.label) {
            std::cout << "||" << label << " ";
        }

        Tester(Tester&& src): label(src.label) {
            std::cout << "=>" << label << " ";
        }

        Tester& operator=(const Tester& src) {
            if( this != &src ) {
                label = src.label;
                std::cout << "=" << label << " ";
            }
            return *this;
        }

        ~Tester() {
            std::cout << "-" << label << " ";
        }
    };

    Dinorray::Dinorray<Tester> r(4);
    r.push_back(
            Tester(1)
    );
    r.push_back(
            Tester(2)
    );
    r.push_back(
            Tester(3)
    );

}