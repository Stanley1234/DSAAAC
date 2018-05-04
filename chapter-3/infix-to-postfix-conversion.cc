/*
 * Given an infix instance a + b * c + ( d * e + f ) * g
 * Output its postfix
 *
 * */
#include <stack>
#include <iostream>
using namespace std;

bool isOp(char ch) {
  return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')';
}

bool lower(char c1, char c2) {
  return (c1 == '+' || c1 == '-') && (c2 == '*' || c2 == '/');
}

bool higher(char c1, char c2) {
  return (c1 == '*' || c1 == '/') && (c2 == '+' || c2 =='-');
}

int main() {
  stack<char> ops;
  char ch;
  
  while(cin >> ch) {
    if(ch == ' ') continue;
    if(isOp(ch)) {
      if(ch == '(') {
        ops.push(ch);
      } else if (ch == ')') {
        while(ops.top() != '(') {
          cout << ops.top();
          ops.pop();
        }     
        ops.pop();
      } else if(ops.empty() || ops.top() == '(' || !higher(ops.top(), ch)) {
        ops.push(ch);
      } else {
        while(!ops.empty() && ops.top() != '(' && !lower(ops.top(), ch)) {
          cout << ops.top();
          ops.pop();
        }
        ops.push(ch);
      }
    } else {
      cout << ch;
    }
  }
  while(!ops.empty())  {
    cout << ops.top();
    ops.pop();
  }

  return 0;
}


