/******************************************************
 * File: RandomBag.h
 *
 * A class representing a bag of elements in which
 * values can be added and then removed randomly.
 */
#pragma once
#include "vector.h"

class RandomBag {
public:
    /* Adds an item to the random bag. */
    void add(int value);

    /* Removes a random element from the bag. If the bag is empty,
     * calls error() to report an error.
     */
    int  removeRandom();

    /* Returns how many items are in the bag. The 'const' here means
     * "this function does not modify the RandomBag and therefore can be
     * called on a const RandomBag."
     */
    int  size() const;

    /* Returns whether the bag is empty. */
    bool isEmpty() const;

private:
    Vector<int> elems;
};

