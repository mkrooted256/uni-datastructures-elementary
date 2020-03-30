#include <iostream>
#include <fstream>
#include "Deque.h"
#include "Dinorray.h"
#include "CircularDeque.h"

#include "Deque_tests.h"
#include "Dinorray_tests.h"
#include "CircularDeque_tests.h"

#include "Queue.h"
#include "Stack.h"

#include "Mathparser.h"

namespace lab3_list {
    typedef Deque::Deque<char> Word;
    typedef Deque::Deque<Word> Sentence;

    bool is_alphabetical(Word &w) {
        char c = 'a';
        for (auto i: w) {
            if (i != c) return false;
            c++;
        }
        return true;
    }

    bool operator==(const Word &a, const Word &b) {
        auto i = a.begin(), j = b.begin();
        for (; i != a.end() and j != b.end(); ++i, ++j) {
            if (*i != *j) return false;
        }
        return i == a.end() and j == b.end();
    }

    std::ostream &operator<<(std::ostream &o, Word &w) {
        for (auto i: w)
            o << i;
        return o;
    }

    void task() {
        Sentence sentence;

        std::ifstream in("in-lab3.txt");
        in >> std::noskipws;
        char c;
        while (true) {
            Word word;
            // Skip space
            while (in >> c and isspace(c)) {}
            // Still no symbol => eof
            if (!isgraph(c) or in.eof()) break;

            // Now c contains non-space - append as first symbol of word
            word.push_back(c);
            // Read word till space
            while (in >> c and !isspace(c))
                word.push_back(c);
            // Register word
            sentence.push_back(word);
        }
        in.close();

        if (sentence.empty()) {
            std::cout << "Empty input!" << std::endl;
            return;
        }
        Word first = sentence.front();
        for (auto w: sentence) {
            if (is_alphabetical(w) and not(w == first)) {
                w.pop_front();
                w.push_back('.');
                std::cout << w << std::endl;
            }
        }
    }
}

namespace lab3_array {
    typedef Dinorray::Dinorray<char> Word;
    typedef Dinorray::Dinorray<Word> Sentence;

    bool is_alphabetical(Word &w) {
        char c = 'a';
        for (auto i: w) {
            if (i != c) return false;
            c++;
        }
        return true;
    }

    bool operator==(const Word &a, const Word &b) {
        auto i = a.begin(), j = b.begin();
        for (; i != a.end() and j != b.end(); ++i, ++j) {
            if (*i != *j) return false;
        }
        return i == a.end() and j == b.end();
    }

    std::ostream &operator<<(std::ostream &o, Word &w) {
        for (auto i: w)
            o << i;
        return o;
    }

    void task() {
        Sentence sentence;

        std::ifstream in("in-lab3.txt");
        in >> std::noskipws;
        char c;
        while (true) {
            Word word;
            // Skip space
            while (in >> c and isspace(c)) {}
            // Still no symbol => eof
            if (!isgraph(c) or in.eof()) break;

            // Now c contains non-space - append as first symbol of word
            word.push_back(c);
            // Read word till space
            while (in >> c and !isspace(c))
                word.push_back(c);
            // Register word
            sentence.push_back(word);
        }
        in.close();

        if (sentence.empty()) {
            std::cout << "Empty input!" << std::endl;
            return;
        }
        Word first = sentence.front();
        for (auto w: sentence) {
            if (is_alphabetical(w) and not(w == first)) {
                w.pop_front();
                w.push_back('.');
                std::cout << w << std::endl;
            }
        }
    }
}

namespace lab4 {
    void mathparsing_task() {
        std::string input[] = {
                "(3-((4+5)*(6-7)))+(2+1)",
                "1+2",
                "1+(4+5)",
                "(1+2)*(4+5)",
                "(1+2)*5",
                "(1+2)*(3+(4+5))",
                "(1+2)*((3+4)+5)",
                "((3+4)+5)*(1+2)",
                "(5-(3+4))*(1+2)",
                "1*((5-(3+4))*(1+2))",
                "((5-(3+4))*(1+2))*1",
                "8/4",
        };

        for (const auto &s: input) {
            MathStatement ms = build_from_infix(s);
            std::cout << ms.getLine() << " = " << ms.compute() << std::endl;
        }
    }
}

int main() {
//    std::cout << "List task:" << std::endl;
//    lab3_list::task();
//    std::cout << std::endl << "Array task:" << std::endl;
//    lab3_array::task();

//    lab4::mathparsing_task();
//
//    test_deque();
//    std::cout<<" -------- " << std::endl;
//    test_complex_deque();
//    std::cout<<" -------- " << std::endl;
//    test_array();
//    std::cout<<" -------- " << std::endl;
//    test_complex_array();

    // Lab 3 additional tasks
    // Deque
//    Deque::Deque<int> dq;
//    dq.push_back(1);
//    dq.push_back(99);
//    dq.push_back(2);
//    dq.push_back(3);
//    std::cout << dq << std::endl;
//    dq.erase(dq.end()-3);
//    std::cout << dq << std::endl;
//    // Array
//    Dinorray::Dinorray<int> rr;
//    rr.push_back(1);
//    rr.push_back(99);
//    rr.push_back(2);
//    rr.push_back(3);
//    std::cout << rr << std::endl;
//    rr.erase(rr.end()-3);
//    std::cout << rr << std::endl;
//
//    std::cout << " ============= " << std::endl;

    // Circular Deque test
//    test_circular_deque();
//    test_complex_circular_deque();
//    std::cout << " ------ " << std::endl;
//    test_circularity_of_cdq();
//    std::cout << " ------ " << std::endl;
//    test_circular_queue();
//    std::cout << " ------ " << std::endl;

    return 0;
}