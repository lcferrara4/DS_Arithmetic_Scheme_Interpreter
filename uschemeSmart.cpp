// uschemeSmart.cpp

#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <unistd.h>

using namespace std;

// Structures ------------------------------------------------------------------

struct Node {
    Node(string value, Node *left=nullptr, Node *right=nullptr);
    ~Node();

    string value;
    Node * left;
    Node * right;

    friend ostream &operator<<(ostream &os, const Node &n);
};

ostream &operator<<(ostream &os, const Node &n) {
    return os;
}

// Parser ----------------------------------------------------------------------

string parse_token(istream &s) {
    string token;
    return token;
}

Node *parse_expression(istream &s) {
    return new Node(token, left, right);
}

// Interpreter -----------------------------------------------------------------

void evaluate_r(const Node *n, stack<int> &s) {
}

int evaluate(const Node *n) {
    return 0;
}

// Main execution --------------------------------------------------------------

int main(int argc, char *argv[]) {
    string line;
    bool batch = false;
    bool debug = false;
    int c;

    while ((c = getopt(argc, argv, "bd")) != -1) {
        switch (c) {
            case 'b': batch = true; break;
            case 'd': debug = true; break;
        }
    }

    while (!cin.eof()) {
        if (!batch) {
            cout << ">>> ";
            cout.flush();
        }

        if (!getline(cin, line)) {
            break;
        }

        if (debug) { cout << "LINE: " << line << endl; }

        stringstream s(line);
        Node *n = parse_expression(s);
        if (debug) { cout << "TREE: " << *n << endl; }

        cout << evaluate(n) << endl;

        delete n;
    }

    return 0;
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
