#include <iostream>
#include "set.h"
#include "console.h"
using namespace std;


/* Given a set of remaining elements, returns all ways we can pick
 * numRemaining more of them and add then to the set soFar.
 */
Set<Set<string>>
   combinationsRec(const Set<string>& elems,
                   int numRemaining,
                   const Set<string>& soFar) {
    /* Base Case: If we are not allowed to pick any more people,
     * then the only possible set we can make is the one we've
     * already selected in soFar. So we'll return a set of all
     * the possible options, which will be a set just containing
     * soFar.
     */
    if (numRemaining == 0) {
        return { soFar };
    }
    /* Base Case: If we're asked to pick more people than remain,
     * there are no ways to do so. So we'll return a set containing
     * all 0 ways to do this.
     */
    else if (numRemaining > elems.size()) {
        return { };
    }
    /* Recursive Case: Pick a person and decide what to
     * do with them.
     */
    else {
        /* Select someone. */
        auto elem = elems.first();
        auto remaining = elems - elem;

        /* Option 1: Exclude this person. We still need to pick
         * numRemaining people. Find all the ways to do this.
         */
        auto without = combinationsRec(remaining,
                                       numRemaining,
                                       soFar);

        /* Option 2: Include this person. We need to pick one
         * fewer person at this point. Find all ways to do this.
         */
        auto with = combinationsRec(remaining,
                                    numRemaining - 1,
                                    soFar + elem);

        /* These two options, collectively, cover all possible
         * ways we could form a set of numRemaining additional
         * people.
         */
        return with + without;
    }
}

Set<Set<string>> combinationsOf(const Set<string>& elems,
                                int numToPick) {
    /* Check validity. */
    if (numToPick < 0) {
        error("You shouldn't ask for a negative number of people.");
    }

    return combinationsRec(elems, numToPick, {});
}

/* Current members of the US Supreme Court. I've listed them by
 * seniority here, but internally they'll be stored alphabetically
 * in the Set.
 */
const Set<string> usSupremeCourt = {
    "Roberts",
    "Thomas",
    "Alito",
    "Sotomayor",
    "Kagan",
    "Gorsuch",
    "Kavanaugh",
    "Barrett",
    "Jackson"
};

int main() {
    auto combinations = combinationsOf(usSupremeCourt, 5);

    cout << "There are " << combinations.size()
         << " combinations. They are: " << endl;

    for (auto combination: combinations) {
        cout << combination << endl;
    }
    return 0;
}
