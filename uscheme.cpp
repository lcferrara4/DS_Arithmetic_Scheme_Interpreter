// uscheme.cpp

#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <unistd.h>

using namespace std;

// Globals ---------------------------------------------------------------------

bool BATCH = false;
bool DEBUG = false;

// Structures ------------------------------------------------------------------

struct Node {
  
    string value;
    Node * left;
    Node * right;

    Node(string i_value, Node *i_left = nullptr, Node *i_right = nullptr){
        value = i_value; 
        left = i_left; 
        right = i_right; 
        
    } //constructor 

    ~Node(){
        delete left;
        delete right; 
    } // destructor

    friend ostream &operator<<(ostream &os, const Node &n); 
};

ostream &operator<<(ostream &os, const Node &n) {
   
    os << "(Node: value=" << n.value;
    
    if( n.left != nullptr){
        os << ", left=";
        os << *(n.left);
    }
    if( n.right != nullptr){
        os << ", right=";
        os << *(n.right);
    }

    os << ")";

    return os;
}

// Parser ----------------------------------------------------------------------

string parse_token(istream &s) {
    string token= ""; 
    cout<<"parsing token"<<endl; 
    while(s.peek() == ' ' && s.peek() != EOF){
        s.get();    
    }
    
    if( !isalnum(s.peek())){
        token = s.get();
    }
    else if(isdigit(s.peek())){
        while(isdigit(s.peek())){ //s.peek() != ' ' && s.peek() != -1){
            token += s.get(); 
        }
    }
    
    return token;
}

Node *parse_expression(istream &s) {

    Node* left = nullptr;
    Node* right= nullptr;
    
    string token = parse_token(s); 
    cout<<"parsing expression"<<endl; 
    if (token == "" || token == ")"){
        cout<<"end"<<endl; 
        return nullptr; 
    }

    if (token == "("){
        token = parse_token(s); 
        left = parse_expression(s); 
        if (left){
            right = parse_expression(s); 
        }
        if (right){
            parse_token(s); 
        }
    }
    return new Node(token, left, right);
}

// Interpreter -----------------------------------------------------------------

void evaluate_r(const Node *n, stack<int> &s) {
    if( isdigit(n.value) ){
        s.push(stoi(n.value));
    }
    else{
        int t1 = s.pop();
        int t2 = s.pop();
        //case n.value


    }
}

int evaluate(const Node *n) {
    stack<int> s;
    evaluate_r(n, s);
    return 0;
}

// Main execution --------------------------------------------------------------

int main(int argc, char *argv[]) {
    string line;
    int c;

    while ((c = getopt(argc, argv, "bdh")) != -1) {
        switch (c) {
            case 'b': BATCH = true; break;
            case 'd': DEBUG = true; break;
            default:
                cerr << "usage: " << argv[0] << endl;
                cerr << "    -b Batch mode (disable prompt)"   << endl;
                cerr << "    -d Debug mode (display messages)" << endl;
                return 1;
        }
    }

    while (!cin.eof()) {
        if (!BATCH) {
            cout << ">>> ";
            cout.flush();
        }

        if (!getline(cin, line)) {
            break;
        }

        if (DEBUG) { cout << "LINE: " << line << endl; }

        stringstream s(line);
        Node *n = parse_expression(s);
        if (DEBUG) { cout << "TREE: " << *n << endl; }

        cout << evaluate(n) << endl;

        delete n;
    }

    return 0;
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
