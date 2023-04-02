/*
 * File: PlayingFair.cpp
 */
#include "PlayingFair.h"
#include "error.h"
using namespace std;

string aSequenceOfOrder(int n) {
    /* TODO: The next few lines just exist to make sure you don't get compiler
     * warning messages when this function isn't implemented. Delete this
     * comment and the next few lines, then implement this function.
     */
    (void) n;
    return "";
}

string bSequenceOfOrder(int n) {
    /* TODO: The next few lines just exist to make sure you don't get compiler
     * warning messages when this function isn't implemented. Delete this
     * comment and the next few lines, then implement this function.
     */
    (void) n;
    return "";
}

/* * * * * * Tests Below This Point * * * * * */
#include "GUI/SimpleTest.h"

PROVIDED_TEST("Sequences of order 3 are correct.") {
    /* Some very basic checks. */
    EXPECT_EQUAL(aSequenceOfOrder(3), "ABBABAAB");
    EXPECT_EQUAL(bSequenceOfOrder(3), "BAABABBA");
}

PROVIDED_TEST("Triggers error on negative inputs.") {
    /* The EXPECT_ERROR macro expects the given expression to call error(). Remember that
     * you need to guard against invalid inputs.
     */
    EXPECT_ERROR(aSequenceOfOrder(-137));
    EXPECT_ERROR(bSequenceOfOrder(-137));
}

