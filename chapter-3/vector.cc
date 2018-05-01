// The main difference between an iterator an d a const_iterator is that operator* cannot appear on the left-hand side of an assignment statement. 

template <typename Elem> 
class Vector {

  public:
    explicit Vector(int initSize = 0) : theSize {initSize}, 
                                        theCapacity {initSize + SPARE_CAPACITY} {
      theVec = new Elem[theCapacity];
    }

    Vector(const Vector& rhs) : theSize {rhs.theSize}, theCapacity {rhs.theCapacity} {
      theVec = new Elem[theCapacity];
      for(int i = 0;i < theSize;i ++) 
        theVec[i] = rhs.theVec[i];
    }

    Vector& operator=(const Vector& rhs) {
      if(this == &rhs) 
        return *this;
      Vector backup {rhs};
      std::swap(*this, rhs);
      return *this;
    }

    Vector(Vector&& rhs) : theCapacity {rhs.theCapacity}, theSize {rhs.theSize}, 
                           theVec {rhs.theVec} {
      rhs.theSize = 0;
      rhs.theCapacity = 0;
      rhs.theVec = nullptr;
    }

    Vector& operator=(Vector&& rhs) {
      if(this == &rhs)
        return *this;
      std::swap(*this, rhs);
      return *this;
    }

    ~Vector() {
      delete theVec;
    }
   
    Elem& operator[] (int index) {
      if(index >= theSize || index < 0) 
        throw std::range_error{"Out of index"};
      return theVec[index];
    }

    const Elem& operator[] (int index) const {
      if(index >= theSize || index < 0)
        throw std::range_error{"Out of index"};
      return theVec[index];
    }

    void resize(int newSize) {
      if(newSize > theCapacity)
        reserve(newSize);
      theSize = newSize;
    }

    bool empty() const { return size() == 0; }

    int size() const { return theSize; }

    int capacity() const { return theCapacity; }

    void push_back(const Elem& x) {
      if (theSize == theCapacity)
        reserve(theCapacity * 2);
      theVec[theSize ++] = x;
    }

    void push_back(Elem&& x) {
      if (theSize == theCapacity)
        reserve(theCapacity * 2);
      theVec[theSize ++] = std::move(x); 
    }

    void pop_back() {
      if(empty()) 
        throw std::logic_error{"no elements"};
      theSize --;
    }
   
    Elem& back() const {
      if(empty())
        throw std::logic_error{"no elements"};
      return theVec[theSize - 1];
    }

    const Elem& back() const {
      if(empty())
        throw std::logic_error{"no elements"};
      return theVec[theSize - 1];
    }

    typedef Elem* iterator;
    typedef const Elem* const_iterator;

    iterator begin() {
      return &theVec[0];
    }
    
    const_iterator begin() const {
      return &theVec[0];
    }
    
    iterator end() {
      return &theVec[size()];
    }

    const_iterator end() const {
      return &theVec[size()];
    }

  private:
    static const int SPARE_CAPACITY = 16;
    int theSize;
    int theCapacity;
    Elem* theVec;
    
    void reserve(int newCapacity) {
      Elem* newVec = new Elem[newCapacity];
      for(int i = 0; i < theSize;i ++) 
        newVec[i] = theVec[i];
      delete[] theVec;
      theVec = newVec;
    }
};

