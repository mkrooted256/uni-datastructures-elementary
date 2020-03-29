#include <iostream>
#include <fstream>
#include "Deque.h"
#include "Dinorray.h"

#include "Deque_tests.h"
#include "Dinorray_tests.h"

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

namespace lab3_array {
    typedef Dinorray::Dinorray<char> Word;
    typedef Dinorray::Dinorray<Word> Sentence;

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

int main() {
    std::cout << "List task:" << std::endl;
    lab3_list::task();
    std::cout << std::endl << "Array task:" << std::endl;
    lab3_array::task();

//    test_deque();
//    std::cout<<" -------- " << std::endl;
//    test_complex_deque();
//    std::cout<<" -------- " << std::endl;
//    test_array();
//    std::cout<<" -------- " << std::endl;
//    test_complex_array();

    return 0;
}