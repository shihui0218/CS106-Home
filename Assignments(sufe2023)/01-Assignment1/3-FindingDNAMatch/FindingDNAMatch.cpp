/*
 * File: FindDNAMatch.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * This file solves the DNA matching exercise from the text.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
using namespace std;

/* Prototypes */

int findDNAMatch(string s1, string s2, int start = 0);
string matchingStrand(string strand);
void findAllMatches(string s1, string s2);

/* Main program */

int main() {
   findAllMatches("TTGCC", "TAACGGTACGTC");
   findAllMatches("TGC", "TAACGGTACGTC");
   findAllMatches("CCC", "TAACGGTACGTC");
   return 0;
}

/*
 * Function: findAllMatches
 * Usage: findAllMatches(s1, s2);
 * ------------------------------
 * Finds all positions at which s1 can bind to s2.
 */

void findAllMatches(string s1, string s2) {
   int start = 0;
   while (true) {
      int index = findDNAMatch(s1, s2, start);
      if (index == -1) break;
      cout << s1 << " matches " << s2 << " at position " << index << endl;
      start = index + 1;
   }
   if (start == 0) {
      cout << s1 << " has no matches in " << s2 << endl;
   }
}


/*
 * Function: findDNAMatch
 * Usage: int pos = findDNAMatch(s1, s2);
 *        int pos = findDNAMatch(s1, s2, start);
 * ---------------------------------------------
 * Returns the first index position at which strand s1 would bind to
 * the strand s2, or -1 if no such position exists.  If the start
 * parameter is supplied, the search begins at that index position.
 */

int findDNAMatch(string s1, string s2, int start) {

    // [TODO: modify and fill in the code]
    int i =0,j = 0;
    int len1 = s1.length();
    int len2 = s2.length();

    string str1 = matchingStrand(s1);
    string str2 = s2;

    while (i<len1 && j<len2) {
        if(str1[i] == str2[j]) {
            i++;
            j++;
        }else {
            start++;
            i = 0;
            j = start;
        }
        if(i == len1) {
            return j-len1;
        }
    }

    return -1;
}

string matchingStrand(string strand) {
    for(int i = 0;i<strand.length();i++) {
        if(strand[i] == 'T')
            strand[i] = 'A';
        else{
            if(strand[i] == 'A')
                 strand[i] = 'T';
            else{
                if(strand[i] == 'C')
                     strand[i] = 'G';
                else{
                    if(strand[i] == 'G')
                         strand[i] = 'C';
                }
            }
        }
    }
    return strand;
}
