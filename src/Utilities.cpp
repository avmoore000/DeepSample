/* 
 *  File:    Utilities.cpp
 *  Author:  Andrew Moore
 *
 *  Created: February 23, 2020, 3:25 PM
 */

/**************************************Change Log *******************************/

// Created source file for utilities - A.M. Feb 23 2020
// Added in the printer function definition

/**************************************End Change Log ***************************/

/**************************************To Do List ******************************/

/**************************************End To Do List **************************/
#include "../include/Utilities.h"

using namespace std;

// Function printer
// Inputs:  
//        fileName - A string containing the name of the output file.
//        value - A string to be added to the output file.
//        algo - An integer specifying the algorithm that called the printer.
//        lineNumber - The line number being written
//        begin - An integer describing the beginning of the printed range.
//        end - An integer describing the end of the printed range.
//        bound - An integer used to control the end of the loop.
// Outputs:  None
// Purpose:  Formats and outputs text to a file.
void printer (string fileName, string value[], int algo, int lineNumber, int begin, int end, int bound)
{
    ofstream outFile;  // Points to user specified output file

    stringstream stringBuilder;  // This will be used to create the output string

    string line[bound];

    outFile.open(fileName, ios::app);

    switch (algo)  // Switch to determine which algorithm we are using.
    {
        case 0:  // ZeroShift algorithm
        {
            for (int i = 0; i < bound; i++)
            {
                if (i == 0)
                    line[i] = "Iteration:";
                if (i == 1)
                    line[i] = "Real I [" + to_string(begin) + " - " + to_string(end) + "]:";
                if (i == 2)
                    line[i] = "Real I+1 [" + to_string(begin) + " - " + to_string(end) + "]:";
                if (i == 3)
                    line[i] = "Sign 1 [" + to_string(begin) + " - " + to_string(end) + "]:";
                if (i == 4)
                    line[i] = "Sign 2 [" + to_string(begin) + " - " + to_string(end) + "]:";
                if (i == 5)
                    line[i] = "ZeroCross [" + to_string(begin) + " - " + to_string(end) + "]:";

                outFile << line[i] << setiosflags(ios_base::left) << setw(30-line[i].length()) << " "
                        << resetiosflags(ios_base::left) << setiosflags(ios_base::right) << value[i]
                        << resetiosflags(ios_base::right) << endl << endl;

            }
           
            for (int i = 0; i < 100; i++)
                outFile << "_";

            outFile << endl << endl;
 
            break;
        } // End ZeroShift algorithm

        case 2:  // Spectrum Flux algorithm
        {
            break;
        }  // End Spectrum Flux algorithm

        case 3:  // Cepstral algorithm
        {
            break;
        }  // End Cepstral algorithm

        case 4:  // Complex Cepstral algorithm
        {
            break;
        }  // End Complex Cepstral algorithm

        default:
            break;
    }

    outFile.close();
}
