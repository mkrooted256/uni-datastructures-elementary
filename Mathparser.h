#include <utility>
#include <functional>
#include <ostream>
#include "Stack.h"

#ifndef LAB3_MATHPARSER_H
#define LAB3_MATHPARSER_H

typedef int t;

struct statement_node {
    enum types {
        VAL, OP, IDLE
    } type;

    t val;
    char op;

    statement_node() : type(IDLE), val(0), op(0) {}

    statement_node(t val) : type(VAL), val(val), op(0) {}

    statement_node(char op) : type(OP), val(0), op(op) {}

    friend std::ostream &operator<<(std::ostream &os, const statement_node &node) {
        if (node.type == VAL)
            os << node.val;
        else if (node.type == OP)
            os << "(" << node.op << ")";
        else
            os << "[?]";
        return os;
    }
};

std::function<t(t, t)> operation_resolver(const char &op) {
    if (op == '*') {
        return [](t l, t r) { return l * r; };
    }
    if (op == '/') {
        return [](t l, t r) { return l / r; };
    }
    if (op == '+') {
        return [](t l, t r) { return l + r; };
    }
    if (op == '-') {
        return [](t l, t r) { return l - r; };
    }
    return [](t l, t r) { return 0; };
}

bool isop(char c) {
    const char ops[] = "+-*/";
    for (auto o: ops)
        if (c == o) return true;
    return false;
}

struct IllegalState : public std::exception {
    std::string details;

    IllegalState(std::string details) : details(std::move(details)) {}

    IllegalState() : details() {}
};

class MathStatement {
    Dinorray::Stack<statement_node> line;
public:
    MathStatement(Dinorray::Stack<statement_node> line) : line(std::move(line)) {};

    t compute() {
        if (line.empty()) throw std::exception();

        t result = 0;
        auto computer = Dinorray::Stack<statement_node>();
        int complength = 0;
        for (auto node: line) {
            if (node.type == statement_node::VAL) {
                computer.push(node);
                complength++;
            } else {
                // Operation
                auto r = computer.pop().val;
                auto l = computer.pop().val;
                computer.push(statement_node(operation_resolver(node.op)(l, r)));
                complength--;
            }
        }
        if (complength == 1) return computer.pop().val;
        throw IllegalState("Final computer length != 1");
    }

    const Dinorray::Stack<statement_node> &getLine() const {
        return line;
    }
};

MathStatement build_from_infix(const std::string &str) {
    Dinorray::Stack line = Dinorray::Stack<statement_node>();

    char c;
    int depth = 0;
    int i = 0;
    int len = str.length();

    Dinorray::Stack<statement_node> ops;   // Operations
    int opslen = 0;

    while (i < len) {
        c = str[i];
        if (c == '(') {
            depth++;
        } else if (c == ')') {
            if (depth == 0) throw IllegalState("Unexpected null depth");
            if (opslen == 0) throw IllegalState("Operations stack empty");
            depth--;
            line.push(ops.pop());
            opslen--;
        } else if (std::isdigit(c)) {
            t val = c - '0';
            while (std::isdigit(str[i + 1])) {
                c = str[++i];
                val = val * 10 + c - '0';
            }
            line.push(statement_node(val));
        } else if (isop(c)) {
            ops.push(statement_node(c));
            opslen++;
        } else
            throw IllegalState("Invalid character");
        i++;
    }
    if (opslen == 1)
        line.push(ops.pop());
    else
        throw IllegalState("Suspicious - operation stack not empty");

    return MathStatement(line);
}

#endif //LAB3_MATHPARSER_H
