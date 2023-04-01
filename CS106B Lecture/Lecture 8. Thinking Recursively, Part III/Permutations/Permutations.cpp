/* File: Permutations.cpp
 *
 * Functions to list off all permutations of a collection of elements.
 */
#include <iostream>
#include <string>
#include "set.h"
#include "console.h"
using namespace std;

/* Recursive function to generate permutations. Given a string of
 * unchosen characters and a string of what we've made thus far,
 * returns all permutations that can be formed that start with
 * soFar and that use the remaining letters in str.
 */
Set<string> permutationsRec(const string& str,
                            const string& soFar) {
    /* Base Case: If we've already decided on the order,
     * go with that order.
     */
    if (str == "") {
        /* There is just one option - pick soFar. */
        return { soFar };
    }
    /* Recursive Case: Otherwise, try all ways we could pick
     * which letter comes next.
     */
    else {
        Set<string> result;
        for (int i = 0; i < str.length(); i++) {
            /* Use up character at index i. */
            result += permutationsRec(str.substr(0, i) + str.substr(i + 1),
                                      soFar + str[i]);
        }
        return result;
    }
}

/* Given a string, returns all permutations of that string. */
Set<string> permutationsOf(const string& str) {
    return permutationsRec(str, "");
}

int main() {
    Set<string> permutations = permutationsOf("CAKE");
    cout << "There are " << permutations.size() << " permutations." << endl;
    return 0;
}

