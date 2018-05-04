/*
 * Efficiently implementg a queue class using a singly linked list
 * with no header or tail nodes
 * */
#include <stdexcept>
#include <iostream>

template <typename Object>
class Stack {

  private:
    struct Node {
      Object data;
      Node* next;

      Node(const Object& d, Node* next = nullptr) : data {d}, next {next} {}
      Node(Object&& d, Node* next = nullptr) : data {std::move(d)}, next {next} {}
    };

  public:
    Stack() : size {0}, head {nullptr} {}

    ~Stack() {
      Node* p;
      while(head) {
        p = head;
        head = head->next;
        delete p;
      }
    }

    bool empty() const {
      return size == 0;
    }

    int count() const {
      return size;
    }
    
    Object& top() {
      if(empty())
        throw std::runtime_error {"Stack is empty."};
      return head->data;
    }

    void push(const Object& x) {
      Node* newnode = new Node {x, head};
      head = newnode;
      size ++;
    }

    void push(Object&& x) {
      Node* newnode = new Node {std::move(x), head};
      head = newnode;
      size ++;
    }

    void pop() {
      if(empty())
        throw std::runtime_error {"Stack is empty."};
      Node* curnode = head;
      head = head->next;
      delete curnode;
      size --;
    }

  private:
    int size;
    Node* head;
};

int main() {
  Stack<int> s;

  for(int i = 0;i < 300;i ++) {
    s.push(i);
  }
  while(!s.empty()) {
    std::cout << s.top() << " ";
    s.pop();
  }
  std::cout << std::endl;

  return 0;
}
