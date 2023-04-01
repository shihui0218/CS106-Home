/******************************************************************************
 * File: OurStack.cpp
 *
 * Implementation of the OurStack type.
 */
#include "OurStack.h"
#include "error.h"

const int kInitialSize = 4;

/* Initialize the stack with a small array. */
OurStack::OurStack() {
    logicalSize = 0; // No items
    allocatedSize = kInitialSize;
    elems = new int[kInitialSize];
}

/* Free memory for the elements array - if we don't, no one will! */
OurStack::~OurStack() {
    delete[] elems;
}

/* Push onto the stack - if there's space. */
void OurStack::push(int value) {
    /* Out of space? */
    if (logicalSize == allocatedSize) {
        error("Too many sardines, not enough can.");
    }

    /* Slots 0, 1, 2, ..., logicalSize - 1 are all currently in use.
     * The next free slot is therefore at index logicalSize.
     */
    elems[logicalSize] = value;

    /* Another item has been added. */
    logicalSize++;
}

/* Look at the last occupied spot. */
int OurStack::peek() const {
    if (isEmpty()) {
        error("That which is not cannot be!");
    }

    /* Slots 0, 1, 2, ..., logicalSize - 1 are in use. */
    return elems[logicalSize - 1];
}

/* Decrease the number of items we're pretending are here. */
int OurStack::pop() {
    int result = peek(); // Also checks for errors!
    logicalSize--;
    return result;
}

/* Stack size, from an external perspective, is the logical size.
 * The allocated size is purely for internal use and the client
 * has no idea it exists.
 */
int OurStack::size() const {
    return logicalSize;
}

/* We're empty if our size is zero. */
bool OurStack::isEmpty() const {
    return size() == 0;
}
