#include <string>
#include <cstdlib>
using namespace std;


template <typename Key>
class hash {
public:
  size_t operator() (const Key& k) const;
};

// default implementations of the hash function are provided for standard type int and string
template <>
class hash<string> {
public:
  size_t operator() (const string& key) {
    // size_t is guaranteed to be able to store an array index
    size_t hashVal = 0;
    for(char ch : key) {
      hashVal = 37 * hashVal + ch;
    }
    return hashVal;
  }
};

// user-defined implementation of the hash function
class Employee {
private:
  string name;
  int age;
  double salary;
};

template <>
class hash<Employee> {
public:
  size_t operator() (const string& key) {
    static hash<string> fn;
    return fn(key.name);
  }
}


template <typename Elem>
class HashTable {

public:
  explicit HashTable(int size = 101) : theLists(size) {}

  bool contains(const Elem& e) {
    size_t hashVal = hashfn(e);
    return theLists[hashVal].find(e) != theLists[hashVal].end();
  }

  void makeEmpty() {
    currentSize = 0;
    for(auto& theList : theLists) {
      theList.clear();  
    }
  }

  /*
   * Return: True if e is inserted to the hash table. 
   *         False if e has been in the hash table.
   * */
  bool insert(const Elem& e) {
    if(contains(e))
      return false;
    size_t hashVal = hashfn(e);
    theLists[hashVal].push_back(e);
    currentSize ++;
    // rehash
    if(currentSize >= theLists.size())
      rehash();
    return true;
  }

  /*
   * Return: True if e is removed from the hash table
   * */
  bool remove(const Elem& e) {
    if(!contains(e))
      return false;
    size_t hashVal = hashfn(e);
    theLists[hashVal].erase(e);
    currentSize --;
    return true;
  }
   
private:
  vector<list<Elem>> theLists;  // hash table using separate chaining 
  int currentSize; // number of elements in the hash table

  void rehash() {
     
  }

  size_t hashfn(const Elem& x) const {
    static hash<Elem> fn;  // the hash functor for elements only need to be allocated once
    return fn(x) % theLists.size(); 
  }
};

