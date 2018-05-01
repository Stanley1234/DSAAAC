#include <utility>
#include <stdexcept>
#include <iostream>
#include <iomanip>

template <typename Object>
class List {
  private:
    struct Node {
      Object data;
      Node* prev;
      Node* next;

      Node(const Object& d = Object{}, Node* p = nullptr, Node* n = nullptr) :
        data {d}, prev {p}, next {n} {}
      Node(Object&& d, Node* p = nullptr, Node* n = nullptr) : 
        data {std::move(d)}, prev {p}, next {n} {}
    };

  public:
    class const_iterator {
      public:
        explicit const_iterator(Node* cur) : cur {cur} {}
        
        const Object& operator*() { return *cur; }
        
        const_iterator& operator++() { 
          cur = cur->next;
          return *this;
        }
        
        bool operator==(const_iterator& rhs) const { return cur == rhs.cur; }
        bool operator!=(const_iterator& rhs) const { return !(*this == rhs); }

      private:
        Node* cur;
        
        friend class List;
    };

    class iterator {
      public:
        explicit iterator(Node* cur) : cur {cur} {}

        Object& operator*() { return *cur; }
        Object* operator->() { return cur; }
        
        iterator& operator++() {
          cur = cur->next;
          return *this;
        }

        bool operator==(const iterator& rhs) { return cur == rhs.cur; }
        bool operator!=(const iterator& rhs) { return !(*this == rhs); }

      private:
        Node* cur;

        friend class List;
    };

  public:
    List() { init(); }

    ~List() {
      clear();
      delete head;
      delete tail;
    }

    List(const List& rhs) {
      init();
      for(auto& x : rhs) {
        push_back(x);
      }
    }

    List(List&& rhs) {
      init();
      for(auto& x : rhs) {
        push_back(std::move(x));
      }
      rhs.theSize = 0;
      rhs.head = nullptr;
      rhs.tail = nullptr;
    }

    List& operator=(const List& rhs) {
      if(this == &rhs)
        return;
      List copy = rhs;
      std::swap(*this, copy);
      return *this;
    }

    List& operator=(List&& rhs) {
      std::swap(*this, rhs);
      return *this;
    }

    iterator begin() { return iterator {head->next}; }
    const_iterator begin() const { return const_iterator {head->next}; }

    iterator end() { return iterator {tail}; }
    const_iterator end() const { return const_iterator {tail}; }

    int size() const { return theSize; }
    bool empty() const { return size() == 0; }

    void clear() {
      while(!empty())
        pop_back();
      theSize = 0;
    }
    
    Object& front() { 
      if(empty())
        throw std::runtime_error{"List is empty."};
      return head->next;
    }

    const Object& front() const {
      if(empty())
        throw std::runtime_error{"List is empty."};
      return head->next;
    }

    Object& back() {
      if(empty()) 
        throw std::runtime_error{"List is empty."};
      return tail->prev;
    }

    const Object& back() const {
      if(empty())
        throw std::runtime_error{"List is empty."};
      return tail->prev;
    }

    void push_front(const Object& x) {
      insert(iterator {head->next}, std::move(x));
    }

    void push_front(Object&& x) {
      insert(iterator {head->next}, std::move(x));
    }

    void push_back(const Object& x) {
      insert(end(), x);
    }

    void push_back(Object&& x) {
      insert(end(), std::move(x));
    }

    void pop_front() {
      if(empty())
        throw std::runtime_error{"List is empty."};
      Node* dnode = head->next;
      dnode->next->prev = head;
      head->next = dnode->next;
      delete dnode;
      theSize --;
    }

    void pop_back() {
      if(empty())
        throw std::runtime_error{"List is empty."};
      Node* dnode = tail->prev;
      dnode->prev->next = tail;
      tail->prev = dnode->prev;
      delete dnode;
      theSize --;
    }

    iterator insert(iterator iter, const Object& x) {
      theSize ++;
      Node* p = iter.cur;
      return iterator {p->prev = p->prev->next = new Node{x, p->prev, p}};
    }

    iterator insert(iterator iter, Object&& x) {
      theSize ++;
      Node* p = iter.cur;
      return iterator {p->prev = p->prev->next = new Node{std::move(x), p->prev, p}};
    }

    iterator erase(iterator iter) {
      if(iter == end())
        throw std::runtime_error {"Cannot delete at the end of the list"};
      
      Node* p = iter.cur;
      iterator ret {p->next};

      p->prev->next = p->next;
      p->next->prev = p->prev;
      delete p;
      theSize --;

      return ret;
    }

    iterator erase(iterator from, iterator to) {
      iterator cur = from;
      while(cur != to)
        cur = erase(cur);
      return to;
    }

  private:
    int theSize;
    Node* head;
    Node* tail;

    void init() {
      theSize = 0;

      head = new Node{};
      tail = new Node{};
      head->next = tail;
      tail->prev = head;
    }
};

// Test
int main() {
  List<int> lst;

  for(int i = 0;i < 200;i ++)
    lst.push_back(i);
  
  lst.erase(lst.begin(), lst.end());

  std::cout << lst.size() << std::endl;
  std::cout << std::boolalpha << lst.empty() << std::noboolalpha << std::endl;

  return 0;
}
