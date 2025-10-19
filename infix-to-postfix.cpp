#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// Simple array-based stack for characters or integers
template<typename T>
class Stack {
    T data[1000];
    int topIndex;
public:
    Stack() : topIndex(-1) {
    }
    void push(T val) { 
        if (topIndex < 999) data[++topIndex] = val; 
    }
    void pop() { 
        if (topIndex >= 0) topIndex--; 
    }
    T top() { 
        return data[topIndex]; 
    }
    bool empty() { 
        return topIndex == -1; 
    }
};

// Check if character is an operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool isAlphabet(char c) { return isalpha(c); }

// Return precedence of operators. Higher number means higher precedence
int precedence(char c) {
    if (c == '^') {
        return 3;
    }
    if (c == '*' || c == '/') {
        return 2;
    }
    if (c == '+' || c == '-') {
        return 1;
    }
    return 0;
}

// Convert infix expression to postfix and returns false on error and sets errorMessage
bool infixToPostfix(const string& infix, string& postfix, string& errorMessage) {
    Stack<char> stackOperator;
    postfix.clear();
    int i = 0;
    int n = (int)infix.size();

    while (i < n) {
        char c = infix[i];

        if (isspace(c)) {
            i++;
            continue;
        }

        if (isdigit(c)) {
            // Parse multi-digit number
            string number;
            while (i < n && isdigit(infix[i])) {
                number += infix[i];
                i++;
            }
            postfix += number + " ";
            continue;
        }

        if (isAlphabet(c)) {
            // Variable is a single letter
            postfix += c;
            postfix += " ";
            i++;
            continue;
        }

        if (c == '(') {
            stackOperator.push(c);
            i++;
            continue;
        }

        if (c == ')') {
            // Pop until '(' found
            bool foundLeftParenthesis = false;
            while (!stackOperator.empty()) {
                char topOperator = stackOperator.top();
                stackOperator.pop();
                if (topOperator == '(') {
                    foundLeftParenthesis = true;
                    break;
                } else {
                    postfix += topOperator;
                    postfix += " ";
                }
            }
            if (!foundLeftParenthesis) {
                errorMessage = "ERROR: mismatched parentheses";
                return false;
            }
            i++;
            continue;
        }

        if (isOperator(c)) {
            // Pop operators with higher or equal precedence except '^'
            while (!stackOperator.empty() && isOperator(stackOperator.top())) {
                char topOperator = stackOperator.top();
                int topPrecedence = precedence(topOperator);
                int currentPrecedence = precedence(c);
                if (topPrecedence > currentPrecedence || (topPrecedence == currentPrecedence && c != '^')) {
                    stackOperator.pop();
                    postfix += topOperator;
                    postfix += " ";
                } else {
                    break;
                }
            }
            stackOperator.push(c);
            i++;
            continue;
        }

        // Invalid character
        errorMessage = "ERROR: invalid token";
        return false;
    }

    // Pop remaining operators
    while (!stackOperator.empty()) {
        char topOperator = stackOperator.top();
        stackOperator.pop();
        if (topOperator == '(' || topOperator == ')') {
            errorMessage = "ERROR: mismatched parentheses";
            return false;
        }
        postfix += topOperator;
        postfix += " ";
    }

    // Remove trailing space
    if (!postfix.empty() && postfix.back() == ' ') postfix.pop_back();

    return true;
}

int findValue(char var, char* variableNames, int* variableValues, int variableBind) {
    for (int i = 0; i < variableBind; i++) {
        if (variableNames[i] == var) return variableValues[i];
    }
    return -1;
}

// Evaluate postfix expression with variable values and returns false on error and sets errorMessage
bool evaluatePostfix(const string& postfix, char* variableNames, int* variableValues, int variableBind, int& result, string& errorMessage) {
    Stack<int> stackOperand;
    int n = (int)postfix.size();
    int i = 0;

    while (i < n) {
        if (isspace(postfix[i])) {
            i++;
            continue;
        }

        if (isdigit(postfix[i])) {
            // Parse number
            int num = 0;
            while (i < n && isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            stackOperand.push(num);
            continue;
        }

        if (isAlphabet(postfix[i])) {
            // Variable
            char variableName = postfix[i];
            int val = findValue(variableName, variableNames, variableValues, variableBind);
            if (val == -1) {
                errorMessage = string("ERROR: unknown variable ") + variableName;
                return false;
            }
            stackOperand.push(val);
            i++;
            continue;
        }

        if (isOperator(postfix[i])) {
            // Need two operands
            if (stackOperand.empty()) {
                errorMessage = "ERROR: invalid token";
                return false;
            }
            int b = stackOperand.top(); stackOperand.pop();
            if (stackOperand.empty()) {
                errorMessage = "ERROR: invalid token";
                return false;
            }
            int a = stackOperand.top(); stackOperand.pop();
            int res = 0;
            char op = postfix[i];

            if (op == '+') {
                res = a + b;
            } else if (op == '-') {
                res = a - b;
            } else if (op == '*') {
                res = a * b;
            } else if (op == '/') {
                if (b == 0) {
                    errorMessage = "ERROR: divide by zero";
                    return false;
                }
                res = a / b;
            } else if (op == '^') {
                if (b < 0) {
                    errorMessage = "ERROR: invalid token";
                    return false;
                }
                // Compute power using simple loop
                res = 1;
                for (int j = 0; j < b; j++) {
                    // Check for overflow 
                    res *= a;
                }
            } else {
                errorMessage = "ERROR: invalid token";
                return false;
            }
            stackOperand.push(res);
            i++;
            continue;
        }

        // Invalid token
        errorMessage = "ERROR: invalid token";
        return false;
    }

    if (stackOperand.empty()) {
        errorMessage = "ERROR: invalid token";
        return false;
    }

    result = stackOperand.top();
    stackOperand.pop();

    if (!stackOperand.empty()) {
        errorMessage = "ERROR: invalid token";
        return false;
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string infix;
    if (!getline(cin, infix)) return 0;

    string line;
    if (!getline(cin, line)) return 0;

    // Parse number of variables
    int variableBind = 0;
    try {
        variableBind = stoi(line);
    } catch (...) {
        variableBind = 0;
    }

    char* variableNames = new char[variableBind];
    int* variableValues = new int[variableBind];
    for (int i = 0; i < variableBind; i++) {
        variableNames[i] = '\0';
        variableValues[i] = -1;
    }

    // Read variable bindings
    for (int i = 0; i < variableBind; i++) {
        if (!getline(cin, line)) break;
        // Remove spaces
        string trimmed;
        for (char ch : line) {
            if (!isspace(ch)) trimmed += ch;
        }
        // Find '='
        size_t equalPosition = trimmed.find('=');
        if (equalPosition == string::npos || equalPosition == 0 || equalPosition == trimmed.size() - 1) continue;
        char variableName = trimmed[0];
        string stringValue = trimmed.substr(equalPosition + 1);
        try {
            int variableValue = stoi(stringValue);
            variableNames[i] = variableName;
            variableValues[i] = variableValue;
        } catch (...) {
            // ignore invalid
        }
    }

    string postfix;
    string errorMessage;

    bool ok = infixToPostfix(infix, postfix, errorMessage);

    // Print postfix expression 
    cout << postfix << '\n';

    if (!ok) {
        cout << errorMessage << '\n';
        delete[] variableNames;
        delete[] variableValues;
        return 0;
    }

    int result = 0;
    bool successfulEvaluation = evaluatePostfix(postfix, variableNames, variableValues, variableBind, result, errorMessage);

    if (!successfulEvaluation) {
        cout << errorMessage << '\n';
    } else {
        cout << result << '\n';
    }

    delete[] variableNames;
    delete[] variableValues;

    return 0;
}