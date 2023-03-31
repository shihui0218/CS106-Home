//
// LinkedListVector.h
//
// This interface exports a template version of a Vector class based
// upon a linked list implementation (instead of the classic array-based
// implementation).
//
// --------------------------------------------------------------------------
// Attribution: "Programming Abstractions in C++" by Eric Roberts
// Chapter 14, Exercise 10
// Stanford University, Autumn Quarter 2012
// http://web.stanford.edu/class/archive/cs/cs106b/cs106b.1136/materials/CS106BX-Reader.pdf
//
// This file refactors the Vector class (vector.h) packaged with the
// Stanford C++ Library to use a linked-list implementation.
// --------------------------------------------------------------------------
//
// Refactored by Glenn Streiff on 3/1/17.
//

#ifndef _linked_list_vector_h
#define _linked_list_vector_h

#include <iterator>
#include <iostream>
#include <sstream>
#include <string>
#include "foreach.h"
#include "strlib.h"

/*
 * Class: Vector<ValueType>
 * ------------------------
 * This class stores an ordered list of values similar to an array.
 * It supports traditional array selection using square brackets, but
 * also supports inserting and deleting elements.  It is similar in
 * function to the STL <code>vector</code> type, but is simpler both
 * to use and to implement.
 */

template <typename ValueType>
class Vector {

public:

/*
 * Constructor: Vector
 * Usage: Vector<ValueType> vec;
 *        Vector<ValueType> vec(n, value);
 * ---------------------------------------
 * Initializes a new vector.  The default constructor creates an
 * empty vector.  The second form creates a linked list with <code>n</code>
 * elements, each of which is initialized to <code>value</code>;
 * if <code>value</code> is missing, the elements are initialized
 * to the default value for the type.
 */

   Vector();
   explicit Vector(int n, ValueType value = ValueType());

/*
 * Destructor: ~Vector
 * -------------------
 * Frees any heap storage allocated by this vector.
 */

   virtual ~Vector();

/*
 * Method: size
 * Usage: int nElems = vec.size();
 * -------------------------------
 * Returns the number of elements in this vector.
 */

   int size() const;

/*
 * Method: isEmpty
 * Usage: if (vec.isEmpty()) ...
 * -----------------------------
 * Returns <code>true</code> if this vector contains no elements.
 */

   bool isEmpty() const;

/*
 * Method: clear
 * Usage: vec.clear();
 * -------------------
 * Removes all elements from this vector.
 */

   void clear();

/*
 * Method: get
 * Usage: ValueType val = vec.get(index);
 * --------------------------------------
 * Returns the element at the specified index in this vector.  This
 * method signals an error if the index is not in the array range.
 */

   ValueType & get(int index) const;

/*
 * Method: set
 * Usage: vec.set(index, value);
 * -----------------------------
 * Replaces the element at the specified index in this vector with
 * a new value.  The previous value at that index is overwritten.
 * This method signals an error if the index is not in the vector range.
 */

   void set(int index, const ValueType & value);

/*
 * Method: insert
 * Usage: vec.insert(0, value);
 * ----------------------------
 * Inserts the element into this vector before the specified index.
 * All subsequent elements are shifted one position to the right.  This
 * method signals an error if the index is outside the range from 0
 * up to and including the length of the vector.
 */

   void insert(int index, ValueType value);

/*
 * Method: remove
 * Usage: vec.remove(index);
 * -------------------------
 * Removes the element at the specified index from this vector.
 * All subsequent elements are shifted one position to the left.  This
 * method signals an error if the index is outside the array range.
 */

   void remove(int index);

/*
 * Method: add
 * Usage: vec.add(value);
 * ----------------------
 * Adds a new value to the end of this vector.  To ensure compatibility
 * with the <code>vector</code> class in the Standard Template Library,
 * this method is also called <code>push_back</code>.
 */

   void add(ValueType value);
   void push_back(ValueType value);

/*
 * Operator: []
 * Usage: vec[index]
 * -----------------
 * Overloads <code>[]</code> to select elements from this vector.
 * This extension enables the use of traditional array notation to
 * get or set individual elements.  This method signals an error if
 * the index is outside the vector range.  The file supports two
 * versions of this operator, one for <code>const</code> vectors and
 * one for mutable vectors.
 */

   ValueType & operator[](int index);
   const ValueType & operator[](int index) const;

/*
 * Operator: +
 * Usage: v1 + v2
 * --------------
 * Concatenates two vectors.
 */

   Vector operator+(const Vector & v2) const;

/*
 * Operator: +=
 * Usage: v1 += v2;
 *        v1 += value;
 * -------------------
 * Adds all of the elements from <code>v2</code> (or the single
 * specified value) to <code>v1</code>.  As a convenience, the
 * <code>Vector</code> package also overloads the comma operator so
 * that it is possible to initialize a vector like this:
 *
 *<pre>
 *    Vector&lt;int&gt; digits;
 *    digits += 0, 1, 2, 3, 4, 5, 6, 7, 8, 9;
 *</pre>
 */

   Vector & operator+=(const Vector & v2);
   Vector & operator+=(const ValueType & value);

/*
 * Method: toString
 * Usage: string str = vec.toString();
 * -----------------------------------
 * Converts the vector to a printable string representation.
 */

   std::string toString();

/*
 * Method: mapAll
 * Usage: vec.mapAll(fn);
 * ----------------------
 * Calls the specified function on each element of the vector in
 * ascending index order.
 */

   void mapAll(void (*fn)(ValueType)) const;
   void mapAll(void (*fn)(const ValueType &)) const;

   template <typename FunctorType>
   void mapAll(FunctorType fn) const;

/*
 * Additional Vector operations
 * ----------------------------
 * In addition to the methods listed in this interface, the Vector
 * class supports the following operations:
 *
 *   - Stream I/O using the << and >> operators
 *   - Deep copying for the copy constructor and assignment operator
 *   - Iteration using the range-based for statement or STL iterators
 *
 * The iteration forms process the Vector in index order.
 */

/* Private section */

/**********************************************************************/
/* Note: Everything below this point in the file is logically part    */
/* of the implementation and should not be of interest to clients.    */
/**********************************************************************/

private:

/*
 * Implementation notes: Vector data structure
 * -------------------------------------------
 * The elements of the Vector are stored in a linked list of
 * the specified element type.  
 */

/* Instance variables */

    struct CellT {
        ValueType val;
        CellT *next;
    };
    
    CellT *head = new CellT;
    int count;                  /* The number of elements in use     */

/* Private methods */

   void deepCopy(const Vector & src);

/*
 * Hidden features
 * ---------------
 * The remainder of this file consists of the code required to
 * support deep copying and iteration.  Including these methods
 * in the public interface would make that interface more
 * difficult to understand for the average client.
 */

public:

/*
 * Deep copying support
 * --------------------
 * This copy constructor and operator= are defined to make a deep copy,
 * making it possible to pass or return vectors by value and assign
 * from one vector to another.
 */

   Vector(const Vector & src);
   Vector & operator=(const Vector & src);

/*
 * Operator: ,
 * -----------
 * Adds an element to the vector passed as the left-hand operatand.
 * This form makes it easier to initialize vectors in old versions of C++.
 */

   Vector & operator,(const ValueType & value);

/*
 * Iterator support
 * ----------------
 * The classes in the StanfordCPPLib collection implement input
 * iterators so that they work symmetrically with respect to the
 * corresponding STL classes.
 */

   class iterator :
      public std::iterator<std::random_access_iterator_tag, ValueType> {

   private:
      const Vector *vp;
      int index;

   public:

      iterator() {
         this->vp = NULL;
      }

      iterator(const iterator & it) {
         this->vp = it.vp;
         this->index = it.index;
      }

      iterator(const Vector *vp, int index) {
         this->vp = vp;
         this->index = index;
      }

      iterator & operator++() {
         index++;
         return *this;
      }

      iterator operator++(int) {
         iterator copy(*this);
         operator++();
         return copy;
      }

      iterator & operator--() {
         index--;
         return *this;
      }

      iterator operator--(int) {
         iterator copy(*this);
         operator--();
         return copy;
      }

      bool operator==(const iterator & rhs) {
         return vp == rhs.vp && index == rhs.index;
      }

      bool operator!=(const iterator & rhs) {
         return !(*this == rhs);
      }

      bool operator<(const iterator & rhs) {
         extern void error(std::string msg);
         if (vp != rhs.vp) error("Iterators are in different vectors");
         return index < rhs.index;
      }

      bool operator<=(const iterator & rhs) {
         extern void error(std::string msg);
         if (vp != rhs.vp) error("Iterators are in different vectors");
         return index <= rhs.index;
      }

      bool operator>(const iterator & rhs) {
         extern void error(std::string msg);
         if (vp != rhs.vp) error("Iterators are in different vectors");
         return index > rhs.index;
      }

      bool operator>=(const iterator & rhs) {
         extern void error(std::string msg);
         if (vp != rhs.vp) error("Iterators are in different vectors");
         return index >= rhs.index;
      }

      iterator operator+(const int & rhs) {
         return iterator(vp, index + rhs);
      }

      iterator operator+=(const int & rhs) {
         index += rhs;
         return *this;
      }

      iterator operator-(const int & rhs) {
         return iterator(vp, index - rhs);
      }

      iterator operator-=(const int & rhs) {
         index -= rhs;
         return *this;
      }

      int operator-(const iterator & rhs) {
         extern void error(std::string msg);
         if (vp != rhs.vp) error("Iterators are in different vectors");
         return index - rhs.index;
      }

      ValueType & operator*() {
         return vp->get(index);
      }

      ValueType *operator->() {
         return &vp->get(index);
      }

      ValueType & operator[](int k) {
         return vp->get(index + k);
      }

   };

   iterator begin() const {
      return iterator(this, 0);
   }

   iterator end() const {
      return iterator(this, count);
   }

};

/* Implementation section */

extern void error(std::string msg);

/*
 * Implementation notes: Vector constructor and destructor
 * -------------------------------------------------------
 * The constructor allocates storage for the dynamic array
 * and initializes the other fields of the object.  The
 * destructor frees the memory used for the array.
 */

template <typename ValueType>
Vector<ValueType>::Vector() {
    count = 0;
    head->next = NULL;
}

template <typename ValueType>
Vector<ValueType>::Vector(int n, ValueType value) {
    count = n;
    head->next = NULL;
    for (int i = 0; i < n; i++) {
        this->add(value);
    }
}

template <typename ValueType>
Vector<ValueType>::~Vector() {
    this->clear();
}

/*
 * Implementation notes: Vector methods
 * ------------------------------------
 * The basic Vector methods are straightforward and should require
 * no detailed documentation.
 */

template <typename ValueType>
int Vector<ValueType>::size() const {
   return count;
}

template <typename ValueType>
bool Vector<ValueType>::isEmpty() const {
   return count == 0;
}

template <typename ValueType>
void Vector<ValueType>::clear() {
    for (int i = 0; i < count; i++) {
        remove(0);
    }
    count = 0;
}

template <typename ValueType>
ValueType & Vector<ValueType>::get(int index) const {
    if (index < 0 || index >= count) error("get: index out of range");
    CellT *cp = head->next;
    for (int i = 0; i < index; i++) {
        cp = cp->next;
    }
    return cp->val;
}

template <typename ValueType>
void Vector<ValueType>::set(int index, const ValueType & value) {
    if (index < 0 || index >= count) error("set: index out of range");
    CellT *cp = head->next;
    for (int i = 0; i < index; i++) {
        cp = cp->next;
    }
    cp->val = value;
}

/*
 * Implementation notes: insert, remove, add
 * -----------------------------------------
 * These methods must shift the existing elements in the list to
 * make room for a new element or to close up the space left by a
 * deleted one.
 */

template <typename ValueType>
void Vector<ValueType>::insert(int index, ValueType value) {
    if (index < 0 || index > count) error("insert: index out of range");
    CellT *cp = head;
    for (int i = 0; i < index; i++) {
        cp = cp->next;
    }
    CellT *newcp = new CellT;
    newcp->val = value;
    newcp->next = cp->next;     // wire out
    cp->next = newcp;           // wire in
    ++count;
}

template <typename ValueType>
void Vector<ValueType>::remove(int index) {
    if (index < 0 || index >= count) error("remove: index out of range");
    CellT *cp = head;
    for (int i = 0; i < index; i++) {
        cp = cp->next;
    }
    CellT *save = cp->next->next;
    delete cp->next;
    cp->next = save;
    count--;
}

template <typename ValueType>
void Vector<ValueType>::add(ValueType value) {
    insert(count, value);
}

template <typename ValueType>
void Vector<ValueType>::push_back(ValueType value) {
    insert(count, value);
}

/*
 * Implementation notes: Vector selection
 * --------------------------------------
 * The following code implements traditional array selection using
 * square brackets for the index.
 */

template <typename ValueType>
ValueType & Vector<ValueType>::operator[](int index) {
    if (index < 0 || index >= count) error("Selection index out of range");
    return get(index);
}
template <typename ValueType>
const ValueType & Vector<ValueType>::operator[](int index) const {
    if (index < 0 || index >= count) error("Selection index out of range");
    return get(index);
}

template <typename ValueType>
Vector<ValueType> Vector<ValueType>::operator+(const Vector & v2) const {
   Vector<ValueType> vec = *this;
   foreach (ValueType value in v2) {
      vec.add(value);
   }
   return vec;
}

template <typename ValueType>
Vector<ValueType> & Vector<ValueType>::operator+=(const Vector & v2) {
   foreach (ValueType value in v2) {
      *this += value;
   }
   return *this;
}

template <typename ValueType>
Vector<ValueType> & Vector<ValueType>::operator+=(const ValueType & value) {
   this->add(value);
   return *this;
}

template <typename ValueType>
std::string Vector<ValueType>::toString() {
   ostringstream os;
   os << *this;
   return os.str();
}

/*
 * Implementation notes: copy constructor and assignment operator
 * --------------------------------------------------------------
 * The constructor and assignment operators follow a standard paradigm,
 * as described in the associated textbook.
 */

template <typename ValueType>
Vector<ValueType>::Vector(const Vector & src) {
    deepCopy(src);
}

template <typename ValueType>
Vector<ValueType> & Vector<ValueType>::operator=(const Vector & src) {
    if (this != &src) {
       this->clear();
       deepCopy(src);
    }
    return *this;
}

template <typename ValueType>
void Vector<ValueType>::deepCopy(const Vector & src) {
    count = src.count;
    head->next = NULL;
    CellT *cp = head;
    for (int i = 0; i < count; i++) {
        CellT *newcell = new CellT;
        newcell->val = src[i];
        newcell->next = NULL;
        cp->next = newcell;
        cp = newcell;
    }
}

/*
 * Implementation notes: The , operator
 * ------------------------------------
 * The comma operator works adding the right operand to the vector and
 * then returning the vector by reference so that it is set for the next
 * value in the chain.
 */

template <typename ValueType>
Vector<ValueType> & Vector<ValueType>::operator,(const ValueType & value) {
   this->add(value);
   return *this;
}

/*
 * Implementation notes: mapAll
 * ----------------------------
 * The various versions of the mapAll function apply the function or
 * function object to each element in ascending index order.
 */

template <typename ValueType>
void Vector<ValueType>::mapAll(void (*fn)(ValueType)) const {
    CellT *cp = head->next;
    for (int i = 0; i < count; i++) {
        fn(cp->val);
        cp = cp->next;
    }
}

template <typename ValueType>
void Vector<ValueType>::mapAll(void (*fn)(const ValueType &)) const {
    CellT *cp = head->next;
    for (int i = 0; i < count; i++) {
        fn(cp->val);
        cp = cp->next;
    }
}

template <typename ValueType>
template <typename FunctorType>
void Vector<ValueType>::mapAll(FunctorType fn) const {
    CellT *cp = head->next;
    for (int i = 0; i < count; i++) {
        fn(cp->val);
        cp = cp->next;
    }
}

/*
 * Implementation notes: << and >>
 * -------------------------------
 * The insertion and extraction operators use the template facilities in
 * strlib.h to read and write generic values in a way that treats strings
 * specially.
 */

template <typename ValueType>
std::ostream & operator<<(std::ostream & os, const Vector<ValueType> & vec) {
   os << "{";
   int len = vec.size();
   for (int i = 0; i < len; i++) {
      if (i > 0) os << ", ";
      writeGenericValue(os, vec[i], true);
   }
   return os << "}";
}

template <typename ValueType>
std::istream & operator>>(std::istream & is, Vector<ValueType> & vec) {
   char ch;
   is >> ch;
   if (ch != '{') error("operator >>: Missing {");
   vec.clear();
   is >> ch;
   if (ch != '}') {
      is.unget();
      while (true) {
         ValueType value;
         readGenericValue(is, value);
         vec += value;
         is >> ch;
         if (ch == '}') break;
         if (ch != ',') {
            error(std::string("operator >>: Unexpected character ") + ch);
         }
      }
   }
   return is;
}

#endif
