/*
 * No sanity check. Assume methods are always called valid.
 * */
#include <iostream>
#include <set>

template <typename Comparable>
class BinarySearchTree {
  public:
    BinarySearchTree() : root {nullptr} {}

    BinarySearchTree(const BinarySearchTree& rhs) {
      root = clone(rhs);
    }

    BinarySearchTree(BinarySearchTree&& rhs) : root {rhs.root} {
      rhs.root = nullptr;
    }
  
    BinarySearchTree& operator=(const BinarySearchTree& rhs) {
      if(this == &rhs) return;
      makeEmpty(root); 
      root = clone(rhs);
      return *this;
    }

    BinarySearchTree& operator=(BinarySearchTree&& rhs) {
      std::swap(root, rhs.root);
      return *this;
    }

    ~BinarySearchTree() {
      root = nullptr;
      makeEmpty(root);
    }

    const Comparable& findMin() const {
      return findMin(root);
    }

    const Comparable& findMax() const {
      return findMax(root);
    }
    
    bool contains(const Comparable& x) const {
      return contains(x, root);
    }

    bool isEmpty() const {
      return root == nullptr;
    }

    void printTree(std::ostream& out = std::cout) const {
      inorder(out, root);
      out << "\n";
    }
    
    void makeEmpty() {
      makeEmpty(root);
      root = nullptr;
    }
     
    void insert(const Comparable& x) {
      root = insert(x, root);
    }

    void insert(Comparable&& x) {
      root = insert(std::move(x), root);
    }

    void remove(const Comparable& x) {
      root = remove(x, root);
    }
    
  private:
    struct Node {
      Comparable data;
      Node* left;
      Node* right;

      Node(const Comparable& data, Node* lt, Node* rt) : data {data}, left {lt}, right {rt} {}
      Node(Comparable&& data, Node* lt, Node* rt) : data {data}, left {lt}, right {rt} {}
    };

    Node* root;

    Node* insert(const Comparable& x, Node* cur) {
      if(!cur)
        return new Node {x, nullptr, nullptr};
      if(cur->data == x)
        return cur;
      else if(x < cur->data) {
        cur->left = insert(x, cur->left);
        return cur;
      }
      cur->right = insert(x, cur->right);
      return cur;
    }

    Node* insert(Comparable&& x, Node* cur) {
      if(!cur)
        return new Node{std::move(x), nullptr, nullptr};
      if(cur->data == x)
        return cur;
      else if(x < cur->data) {
        cur->left = insert(std::move(x), cur->left);
        return cur;
      }
      cur->right = insert(std::move(x), cur->right);
      return cur;
    }

    Node* remove(const Comparable& x, Node* cur) {
      if(!cur) return nullptr;

      if(x < cur->data) {
        cur->left = remove(x, cur->left);
        return cur;

      } else if(x > cur->data) {
        cur->right = remove(x, cur->right);
        return cur;

      } else if(cur->left && cur->right) {
        Node* minNode = findMin(cur->right);
        cur->data = std::move(minNode->data);
        remove(cur->data, cur->right);
        return cur;
      } else {
        Node* res = cur->left ? cur->left : cur->right;
        delete cur;
        return res;
      }
    }

    Node* findMin(Node* cur) const {
      while(cur && cur->left) {
        cur = cur->left;
      }
      return cur;
    }

    Node* findMax(Node* cur) const {
      while(cur && cur->right) {
        cur = cur->right;
      }
      return cur;
    }

    bool contains(const Comparable& x, Node* cur) const {
      if(x > cur->data)
        return contains(x, cur->right);
      else if(x < cur->data)
        return contains(x, cur->left);
      else
        return true;
    }

    void inorder(std::ostream& out, Node* cur) const {
      if(!cur) return;
      inorder(out, cur->left);
      out << cur->data <<  " ";
      inorder(out, cur->right);
    }
    
    void makeEmpty(Node* t) {
      if(!t) return;
      makeEmpty(t->left);
      makeEmpty(t->right);
      delete t;
    }

    Node* clone(Node* t) const {
      if(!t) return nullptr;
      return new Node {t.data, clone(t->left), clone(t->right)};
    }
};

int main() {
  using std::set;
  using std::cout;
  using std::endl;

  BinarySearchTree<int> bst;
  set<int> prod;

  srand(time(nullptr));
  // insert 50 random integers
  for(int i = 0;i < 50;i ++) {
    int t = rand() % 1000;
    bst.insert(t);
    prod.insert(t);
  }

  bst.printTree();
  
  for(int x : prod) {
    bst.remove(x);
    bst.printTree();
  }
  bst.printTree();

  return 0;
}

