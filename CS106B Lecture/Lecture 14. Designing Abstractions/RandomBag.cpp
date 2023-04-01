#include "RandomBag.h"
using namespace std;

/* Adds an item to the underlying vector. */
void RandomBag::add(int value) {
    /* Without qualification, 'elems' refers to the 'elems' vector for
     * the particular RandomBag this function is being called on.
     */
    elems += value;
}

/* Picks a random index from the vector and removes the item there. */
int RandomBag::removeRandom() {
    /* If we're empty, we can't remove something. */
    if (isEmpty()) {
        error("What is the sound of one hand clapping?");
    }

    /* Pick an index uniformly at random from the bag. */
    int index  = randomInteger(0, elems.size() - 1);

    /* Write down what's there, then remove it. */
    int result = elems[index];
    elems.remove(index);

    /* Return the item we wrote down. */
    return result;
}

/* Our size is the vector's size. */
int RandomBag::size() const {
    return elems.size();
}

/* We're empty if our size is zero. */
bool RandomBag::isEmpty() const {
    /* size() here means 'call the size() function on this RandomBag.' */
    return size() == 0;
}
