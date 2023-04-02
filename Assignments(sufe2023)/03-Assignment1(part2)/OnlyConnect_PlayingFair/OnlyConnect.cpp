/* File: OnlyConnect.cpp
 *
 * TODO: Edit these comments to describe anything interesting or noteworthy in your implementation.
 *
 * TODO: Edit these comments to leave a puzzle for your section leader to solve!
 */
#include "OnlyConnect.h"
#include <cctype>
#include "strlib.h"
using namespace std;

string onlyConnectize(string phrase) {
    /* TODO: The next few lines just exist to make sure you don't get compiler
     * warning messages when this function isn't implemented. Delete this
     * comment and the next few lines, then implement this function.
     */
    (void) phrase;

    if (phrase.length()==0) {
        return "";
    }
    if (phrase.length()==1) {
        char ch = phrase[0];
        if(isalpha(ch)) {
            if (ch!='a'&&ch!='A'&&ch!='e'&&ch!='E'&&ch!='i'&&ch!='I'&&ch!='o'&&ch!='O'&&ch!='u'&&ch!='U') {
                return toUpperCase(phrase);
            }
            else return "";
        }
        else return "";
    }
    else
        return onlyConnectize(phrase.substr(0,phrase.length()-1))
                +onlyConnectize(phrase.substr(phrase.length()-1));
}


/* * * * * * Provided Test Cases * * * * * */
#include "GUI/SimpleTest.h"

PROVIDED_TEST("Handles single-character inputs.") {
    EXPECT_EQUAL(onlyConnectize("A"), "");
    EXPECT_EQUAL(onlyConnectize("Q"), "Q");
}

PROVIDED_TEST("Converts lower-case to upper-case.") {
    EXPECT_EQUAL(onlyConnectize("lowercase"), "LWRCS");
    EXPECT_EQUAL(onlyConnectize("uppercase"), "PPRCS");
}

/* TODO: You will need to add your own tests into this suite of test cases. Think about the sorts
 * of inputs we tested here, and, importantly, what sorts of inputs we *didn't* test here. Some
 * general rules of testing:
 *
 *    1. Try extreme cases. What are some very large cases to check? What are some very small cases?
 *
 *    2. Be diverse. There are a lot of possible inputs out there. Make sure you have tests that account
 *       for cases that aren't just variations of one another.
 *
 *    3. Be sneaky. Don't just try standard inputs. Try weird ones that you wouldn't expect anyone to
 *       actually enter, but which are still perfectly legal.
 *
 * Happy testing!
 */






