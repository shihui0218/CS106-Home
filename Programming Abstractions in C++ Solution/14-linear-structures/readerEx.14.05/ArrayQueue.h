//
// ArrayQueue.h
//
// This interface exports a template version of the ArrayQueue class.
//
// --------------------------------------------------------------------------
// Attribution: "Programming Abstractions in C++" by Eric Roberts
// Chapter 14, Exercise 5
// Stanford University, Autumn Quarter 2012
// http://web.stanford.edu/class/archive/cs/cs106b/cs106b.1136/materials/CS106BX-Reader.pdf
//
// This code comes from Figures 14.6 - 14.8.
// --------------------------------------------------------------------------
//

#ifndef _array_queue_h
#define _array_queue_h

#include "error.h"

//
// Class: ArrayQueue<ValueType>
// -----------------------
// This class implements a queue of the specified value type.

template <typename ValueType>
class ArrayQueue {
    
public:
    
    //  Constructor: ArrayQueue
    //  Usage: ArrayQueue<ValueType> queue;
    //  ------------------------------
    //  Initializes a new empty queue.
    
    ArrayQueue();
    
    // Destructor: ~ArrayQueue
    // Usage: (usually implicit)
    // -------------------------
    // Frees any heap storage associated with this queue.
    
    ~ArrayQueue();
    
    // Method: size
    // Usage: int nElems = queue.size();
    // --------------------------------
    // Returns the number of values in this queue.
    
    int size() const;
    
    // Method: isEmpty
    // Usage: if (queue.isEmpty()) . . .
    // ---------------------------------
    // Returns true if this queue contains no elements.
    
    bool isEmpty() const;
    
    // Method: clear
    // Usage: queue.clear();
    // --------------------
    // Removes all elements from this queue.
    
    void clear();
    
    // Method: enqueue
    // Usage: queue.enqueue(value);
    // -------------------------
    // Adds value to the end of the queue.
    
    void enqueue(ValueType value);
    
    // Method: dequeue
    // Usage: ValueType value = queue.dequeue();
    // -------------------------------------
    // Removes and returns the first item in the queue.  This method
    // signals an error if called on an empty queue.
    
    ValueType dequeue();
    
    // Method: peek
    // Usage: ValueType value = queue.peek();
    // --------------------------------------
    // Returns the first value in the queue without
    // removing it.  Raises and error if called on an empty queue.
    
    ValueType peek() const;
    
    // Copy constructor: ArrayQueue
    // Usage: (usually implicit)
    // -------------------------
    // Initializes the current object to be a deep copy of the specified source.
    
    ArrayQueue(const ArrayQueue<ValueType> & src);
    
    // Operator: =
    // Usage: dst = src;
    // -----------------
    // Assigns src to dst so that the two queues are independent copies.
    
    ArrayQueue & operator=(const ArrayQueue<ValueType> & src);
    
    // Private section
    
    // Implementation notes
    // --------------------
    // The array-based queue stores the elements in successive index
    // positions in an array, just as a stack does.  What makes the
    // queue structure more complex is the need to avoid shifting
    // elements as the queue expands and contracts.  In the array
    // model, this goal is achieved by keeping track of both the
    // head and tail indices.  The tail index increases by one each
    // time an element is enqueued, and the head index increases by
    // one each time an element is dequeued.  Each index therefore
    // marches toward the end of the allocated array and will
    // eventually reach the end.  Rather than allocate new memory,
    // this implementation lets each index wrap around back to the
    // beginning as if the ends of the array of elements were joined
    // to form a circle.  This representation is called a ring buffer.
    //
    // The elements of the queue are stored in a dynamic array of the
    // specified element type.  If the space in the array is ever
    // exhausted, the implementation doubles the array capacity.
    // Note that the queue capacity is reached when there is still
    // one unsued element in the array.  If the queue is allowed to
    // fill completely, the head and tail indices will have the same
    // value, and the queue will appear empty.
    
private:
    
    static const int INITIAL_CAPACITY = 10;
    
    // Instance variables
    
    ValueType *array;           // A dynamic array of elements
    int capacity;               // The allocated size of the array
    int head;                   // The index of the head element
    int tail;                   // The index of the tail element
    
    // Private method prototypes
    
    void deepCopy(const ArrayQueue<ValueType> & src);
    void expandCapacity();
    
};

// Logically separate the templatized implementation of the stack
// from the interface through a *.cpp file.

#include "ArrayQueue.cpp"

#endif // _array_queue_h
