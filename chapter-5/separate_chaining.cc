#include <string>
#include <cstdlib>
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <time.h>
using namespace std;

template <typename Key>
class Hash {
public:
  size_t operator() (const Key& k) const;
};

template <typename Elem>
class HashTable {

public:
  explicit HashTable(int size = 101) : theLists(size) {}

  bool contains(const Elem& e) {
    int hashVal = hashfn(e);
    return find(theLists[hashVal].begin(), theLists[hashVal].end(), e) != theLists[hashVal].end();
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
    int hashVal = hashfn(e);
    theLists[hashVal].push_back(e);
    currentSize ++;
    // rehash
    if(currentSize >= theLists.size())
      rehash();
    return true;
  }

  bool insert(Elem&& e) {
    if(contains(e))
      return false;
    int hashVal = hashfn(e);
    theLists[hashVal].emplace_back(move(e));
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
    int hashVal = hashfn(e);
    theLists[hashVal].remove(e);
    currentSize --;
    return true;
  }
   
private:
  vector<list<Elem>> theLists;  // hash table using separate chaining 
  int currentSize; // number of elements in the hash table

  void rehash() {
    vector<list<Elem>> oldLists {move(theLists)};
    
    theLists.resize(oldLists.size() * 2);
    for(auto& oldList : oldLists) {
      for(auto& e : oldList) {
        insert(move(e));
      }
    }
  }

  size_t hashfn(const Elem& x) const {
    static Hash<Elem> fn;  // the hash functor for elements only need to be allocated once
    return fn(x) % theLists.size(); 
  }
};

/* TEST */

// default implementations of the hash function are provided for standard type int and string
template <>
class Hash<string> {
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


string randomString(int len) {
  static const char alphanum[] =
    "0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";
  
  vector<char> s(len);
  for(int i = 0;i < len;i ++) {
    s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
  }
  
  string res;
  for(char ch : s) {
    res += ch;
  }
  return res;
}

int main() {
  HashTable<string> ht;

  clock_t startTime = clock();

  srand(time(nullptr));
  // insert
  vector<string> lss;
  for(int i = 0;i < 2000000;i ++) {
    string s = randomString(rand() % 10);
    ht.insert(s);  
    lss.emplace_back(move(s));
  }
  
  // query
  for(string& str : lss) {
    ht.contains(str);
    // randomly delete
    ht.remove(lss[rand() % lss.size()]);
  }
  for(int i = 0;i < 300;i ++) {
    ht.contains(randomString(rand() % 10));
  }

  clock_t endTime = clock();
  cout << "The total execution time for this program is " << (double)(endTime - startTime) / CLOCKS_PER_SEC << endl;

  return 0;
}



