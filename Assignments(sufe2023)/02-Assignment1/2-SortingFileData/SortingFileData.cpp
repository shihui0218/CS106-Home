/*
 * File: sortingfiledata.cpp
 * -------------------
 * Name: [TODO: enter name here]
 * This program sorts integers read from the text file.
 * [TODO: rewrite the documentation]
 */

#include <fstream>
#include <string>
#include <cctype>
#include "error.h"
#include "filelib.h"
#include "console.h"
#include "simpio.h"

using namespace std;

/* Main program */

int main(){

    // Here, we assume that the number of integers in raw-data.txt does not exceed 100
    int data[100], counter = 0;
    // ------------ Beginning of Task A  ------------
    // Read out the data from raw-data.txt for sorting,
    // and output the result to a binary format file named as sorted-data.bin.
    // Open text format file as input file stream
    ifstream ift("raw-data.txt");
    // Open binary format file as output file stream
    ofstream ofb("sorted-data.bin", ios::binary);

    if(!ift.fail()) {  // If the input stream is opened successfully
        while(!ift.eof()){   // If the file stream does not reach the end of file

        // [TODO: fill in  the code here]
        // Read out the data from input stream and assign it to data array

        }
    }
    else
    {
        cout << "open file error!" << endl;
        return -1;
    }

    // [TODO: fill in  the code]
    // sort data array and output to output stream

    ift.close();
    ofb.close();
    // ------------  End of Task A  ------------

    // ------------ Beginning of Task B  ------------
    // Read out the data from sorted-data.bin, find out the median and output to the screen.
    // Open binary format file as input file stream
     ifstream ifb("sorted-data.bin", ios::binary);
     if(!ifb.fail()) {  // If the input stream is opened successfully
         while(!ifb.eof()){   // If the file stream does not reach the end of file

         // [TODO: fill in  the code here]
         // Read out the data from input stream, find out
         // the median and output to the screen.

         }
     }
     else
     {
         cout << "open file error!" << endl;
         return -1;
     }

     ifb.close();
     // ------------  End of Task B  ------------


    return 0;
}

