/* 
 *  File:     AudioSegmentation.cpp
 *  Author:   Andrew Moore and Hue Truong
 *
 *  Created:  February 29, 2020 2:09 PM
 */

/**************************************Change Log *******************************/

// Created zeroCrossing.cpp file - A.M and H.T Feb 29 2020

/**************************************End Change Log ***************************/

/**************************************To Do List ******************************/

/**************************************End To Do List **************************/

#include "../include/zeroCrossing.h"
#include "../include/Utilities.h"

using namespace std;

// Function zeroCrossing
// Inputs:  
//        leftChannel - A vector of complex doubles describing the left half of the audio signal.
//        rightChannel - A vector of complex doubles describing the right half of the audio signal.
//        zeroCross - A 2D vector of floating points describing the results of the zero crossing algorithm.
//        channels - An integer describing the number of channels in the audio wave.
//        debug - A flag to enable or disable debug messages.
//        path - A string containing the path for file output.
// Outputs:  None
// Purpose:  The zeroCrossing function is an implementation of the zero crossing signal
// analysis algorithm.  It counts the positive and negative changes within the signal
// and records the results in a 2D vector that is passed by the user.
void zeroCross (vector<complex<double> > leftChannel,vector<complex<double> > rightChannel,vector<vector<float> > &zeroCross,int channels,bool debug,string path)
{
    bool sign[2];           // Keep track of sign changes
    int lower;              // Mark the current lower bound of printed data
    int upper;              // Mark the current upper bound of printed data
    int fieldWidth;         // Specify the width of the data fields in output.

    string outputName;      // Name of file to store zeroCrossing results
    vector<string> values;  // Store the values of current data points
    ofstream outFile;       // File pointer for outputting results
   
    outputName = path + "/zeroCrossing.txt";

    fieldWidth = 10;
    lower = 0;
    upper = 0;

    // Initialize the values vector
    for (int i = 0; i < 6; i++)
        values.push_back("");

    if (debug)
        outFile.open((path + "/zeroCrossing.txt").c_str(), ios::app);

    outFile << endl << endl << "ZeroCross Algorithm" << endl << endl;
    cout << "Zero Cross Algorithm Started" << endl;

    for (int i = 0; i < 100; i++)
        outFile << "*";

    outFile << endl << endl;

    if (debug)
    {
        outFile << "Left Channel:" << endl << endl;
         
        for (int i = 0; i < 100; i++)
            outFile << "*";

        outFile << endl << endl;

        outFile.close();
    }

    // Always perform zero crossing on the left channel
    for (int i = 0; i < leftChannel.size() - 1; i++)
    {
        upper = i;
   
        sign[0] = getSign(real(leftChannel[i]), debug, outputName);
        sign[1] = getSign(real(leftChannel[i+1]), debug, outputName);

        // If signs are not equal, a signal change has occured.
        if (sign[0] != sign[1])
            zeroCross[0][i+1] = 1;

        values[0] += createString(i,fieldWidth);
        values[1] += createString(real(leftChannel[i]),fieldWidth);
        values[2] += createString(real(leftChannel[i+1]),fieldWidth);
        values[3] += createString(sign[0],fieldWidth);
        values[4] += createString(sign[1],fieldWidth);
        values[5] += createString(zeroCross[0][i+1],fieldWidth);

        if ( ((i != 0) && ((i % 4) == 0)) || i == (leftChannel.size() - 2) )
        {
            printer(outputName, values, 0, lower, upper);

            lower = i + 1;

            for (int j = 0; j < values.size() - 1; j++)
                values[j] = "";
        }
    }

    if (channels == 2)
    {
        if (debug)
        {

            outFile.open((path + "/zeroCrossing.txt").c_str(), ios::app);

            outFile << endl << endl << "Right Channel:" << endl << endl;
       
            for (int i = 0; i < 100; i++)
                outFile << "*";

            outFile << endl << endl;
           
            outFile.close();
        }

        lower = 0;

        for (int i = 0; i <= rightChannel.size() - 1; i++)
        {
            upper = i;
 
            sign[0] = getSign(real(rightChannel[i]), debug, outputName);
            sign[1] = getSign(real(rightChannel[i]), debug, outputName);

            //If signs are not equal, a signal change has occured.
            if (sign[0] != sign[1])
                zeroCross[1][i+1] = 1;

            values[0] += createString(i,fieldWidth);
            values[1] += createString(real(rightChannel[i]),fieldWidth);
            values[2] += createString(real(rightChannel[i+1]),fieldWidth);
            values[3] += createString(sign[0],fieldWidth);
            values[4] += createString(sign[1],fieldWidth);
            values[5] += createString(zeroCross[1][i+1],fieldWidth);
           
            if ( ((i != 0) && ((i % 4) == 0)) || (i == rightChannel.size() - 1) )
            {
                printer(outputName, values, 0, lower, upper);

                lower = i + 1;

                for (int j = 0; j < values.size() - 1; j++)
                    values[j] = "";
            }
        }
    }

    if (debug)
    {
        outFile.open(outputName, ios::app);

        cout << "ZeroCross Algorithm Complete." << endl << endl;
        outFile << "ZeroCross Algorithm Complete. " << endl << endl;
    
        for (int i = 0; i < 100; i++)
            outFile << "*";
        outFile << endl << endl;

        outFile.close();
    }

}

// Function getSign
// Inputs:
//    data - A float containing the current data point.
//    debug - A flag to enable or disable debug messages.
// Outputs:
//    sign - A boolean stating whether the signal has changed from positive to negative or vice versa.
// Purpose: Determines if a sign change has occured.
bool getSign(complex<double> data, bool debug, string outputName)
{
    bool sign = 0;

    if (real(data) > 0)
        sign = 1;
    else
        sign = 0;

    return sign;
}
