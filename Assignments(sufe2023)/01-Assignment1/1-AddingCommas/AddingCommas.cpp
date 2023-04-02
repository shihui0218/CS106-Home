/*
 * File: AddCommas.cpp
 * -------------------
 * Name: [TODO: enter name here]
 * This program adds commas to numeric strings.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "simpio.h"
#include "console.h"
using namespace std;

/* Function prototypes */

string addCommas(string digits);

/* Main program */

int main() {
   while (true) {
      string digits = getLine("Enter a number: ");
      if (digits == "") break;
      cout << addCommas(digits) << endl;
   }
   return 0;
}

/*
 * Function: addCommas
 * Usage: string str = addCommas(digits);
 * --------------------------------------
 * Adds commas at every third position of the string digits
 * starting on the right.
 */

string addCommas(string digits) {

    // [TODO: modify and fill in  the code]
   int len = digits.length();

   for(int i = len-3;i > 0;i -= 3)
    digits.insert(i,",");
   cout << digits;

   return "";

}
