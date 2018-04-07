#include <string>
#include <cstdlib>
#include <vector>
#include <list>
using namespace std;

template <typename Key>
class Hash {
public:
  size_t operator() (const Key& k) const;
};

// default implementations of the Hash function are provided for standard type int and string
template <>
class Hash<string> {
public:
  size_t operator() (const string& key) {
    // size_t is guaranteed to be able to store an array index
    size_t HashVal = 0;
    for(char ch : key) {
      HashVal = 37 * HashVal + ch;
    }
    return HashVal;
  }
};

// user-defined implementation of the Hash function
class Employee {
public:
  string name;
  int age;
  double salary;
};

template <>
class Hash<Employee> {
public:
  size_t operator() (const Employee& key) {
    static Hash<string> fn;
    return fn(key.name);
  }
};

template <typename Elem>
class HashTable {

public:
  explicit HashTable(int size = 101) : theLists(size) {}

  bool contains(const Elem& e) {
    size_t HashVal = Hashfn(e);
    return theLists[HashVal].find(e) != theLists[HashVal].end();
  }

  void makeEmpty() {
    currentSize = 0;
    for(auto& theList : theLists) {
      theList.clear();  
    }
  }

  /*
   * Return: True if e is inserted to the Hash table. 
   *         False if e has been in the Hash table.
   * */
  bool insert(const Elem& e) {
    if(contains(e))
      return false;
    size_t HashVal = Hashfn(e);
    theLists[HashVal].push_back(e);
    currentSize ++;
    // reHash
    if(currentSize >= theLists.size())
      reHash();
    return true;
  }

  /*
   * Return: True if e is removed from the Hash table
   * */
  bool remove(const Elem& e) {
    if(!contains(e))
      return false;
    size_t HashVal = Hashfn(e);
    theLists[HashVal].erase(e);
    currentSize --;
    return true;
  }
   
private:
  vector<list<Elem>> theLists;  // Hash table using separate chaining 
  int currentSize; // number of elements in the Hash table

  void reHash() {
     
  }

  size_t Hashfn(const Elem& x) const {
    static Hash<Elem> fn;  // the Hash functor for elements only need to be allocated once
    return fn(x) % theLists.size(); 
  }
};

