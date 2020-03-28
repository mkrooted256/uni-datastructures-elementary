#include <iostream>
#include <fstream>
#include "Deque.h"
#include "Dinorray.h"

namespace lab3_list {
    typedef Deque::Deque<char> Word;
    typedef Deque::Deque<Word> Sentence;

    bool is_alphabetical(Word& w) {
        char c = 'a';
        for (auto i: w) {
            if (i != c) return false;
            c++;
        }
        return true;
    }

    bool operator==(const Word& a, const Word& b) {
        auto i = a.begin(), j = b.begin();
        for (; i != a.end() and j != b.end(); ++i, ++j) {
            if (*i != *j) return false;
        }
        return i == a.end() and j == b.end();
    }

    std::ostream& operator<<(std::ostream& o, Word& w) {
        for (auto i: w)
            o << i;
        return o;
    }

    void task() {
        Sentence sentence;

        std::ifstream in("in.txt");
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
            if (is_alphabetical(w) and not (w == first)) {
                w.pop_front();
                w.push_back('.');
                std::cout << w << std::endl;
            }
        }
    }
}

template <class T>
std::ostream& operator<<(std::ostream& os, Deque::Deque<T> &dq) {
    for (auto i: dq) {
        os << i << " ";
    }
    return os;
}

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

int main() {
    lab3_list::task();

    return 0;
}