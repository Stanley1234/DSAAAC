#include <vector>
#include <string>
#include <iostream>
#include <time.h>
using namespace std;

template <typename Key>
class Hash {
  public:
    size_t operator() (const Key& elem);
};

template <typename Elem>
class HashTable {
  public:
    explicit HashTable(int size = 101) : table(nextPrime(size)) {
      makeEmpty();
    } 

    bool contains(const Elem& e) const {
      return isActive(findPos(e));
    }

    void makeEmpty() {
      currentSize = 0;
      for(auto& e : table) {
        e.info = EMPTY;
      }
    }

    bool insert(const Elem& e) {
      int pos = findPos(e);
      if(isActive(pos))
        return false;
      table[pos].info = ACTIVE;
      table[pos].e = e;
      currentSize ++;
      if(currentSize >= table.size() / 2)  // rehashing when load factor >= 1/2
        rehash();
      return true;
    }

    bool insert(Elem&& e) {
      int pos = findPos(e);
      if(isActive(pos))
        return false;
      table[pos].info = ACTIVE;
      table[pos].e = move(e);
      currentSize ++;
      if(currentSize >= table.size() / 2)
        rehash();
      return true;
    }

    bool remove(const Elem& e) {
      int pos = findPos(e);
      if(!isActive(pos))
        return false;
      table[pos].info = DELETED;
      currentSize --;
      return false;
    }
    
  private:
    enum EntryType { ACTIVE, DELETED, EMPTY };

    struct HashEntry {
      Elem e;
      EntryType info;

      HashEntry(const Elem& e = Elem{}, EntryType i = EMPTY) : e {e}, info {i} {}
      HashEntry(Elem&& e, EntryType i = EMPTY) : e {move(e)}, info {i} {}
    };

    vector<HashEntry> table;
    int currentSize;

    bool isActive(int pos) const {
      return table[pos].info == ACTIVE;
    }

    /* Combining hash function and quadratic probing together, compute the position of element e
     * Return: either the first position where e can be inserted if e is not in the hash table
     *         or the position where e is stored in the hash table
     * */
    int findPos(const Elem& e) const {
      static Hash<Elem> h;
      size_t homePos = h(e);
      int currentPos = homePos % table.size();
      int offset = 1;
      
      // this can cause problem because the deleted item is still counted
      // so the hash table can get full prematurely
      while(table[currentPos].info != EMPTY && table[currentPos].e != e) {
        currentPos = currentPos + offset;
        if(currentPos >= table.size()) 
          currentPos -= table.size();
        offset += 2;  // f(i) = f(i - 1) + 2i - 1
                      // 2i - 1 = 1, 3, 5, 7, .. 
      }
      return currentPos;
    }

    int nextPrime(int n) const {
      bool flag = true;
      while(true) {
        for(int i = 2;i * i <= n;i ++) {
          if(n % i == 0) {
            flag = false;
            break;
          }
        }
        if(flag) return n;
        flag = true;
        n ++;
      }
      return -1;
    }

    void rehash() {
      vector<HashEntry> oldTable = move(table);
      table.resize(nextPrime(oldTable.size() * 2));
      for(HashEntry elem : oldTable) {
        insert(move(elem.e));
      }
    }
};

/* TEST */
template<>
class Hash<string> {
  public:
    size_t operator()(const string& s) {
      size_t hashVal = 0;
      for(char ch : s) {
        hashVal = hashVal * 37 + ch;
      }
      return hashVal;
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
  
  clock_t start = clock();
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
  clock_t end = clock();
  cout << "The total execution time is " << (double)(end - start) / CLOCKS_PER_SEC << endl;

  return 0;
}


