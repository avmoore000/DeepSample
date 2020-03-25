/* 
 *  File:     zeroCrossing.cpp
 *  Author:   Andrew Moore, Hue Truong, and Alex Reno
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
//        zeroCross - An 2D vector of doubles describing the results of the zero crossing algorithm.
//        channels - An integer describing the number of channels in the audio wave.
//        frames - The number of frames in the audio file.
//        debug - A flag to enable or disable debug messages.
//        path - A string containing the path for file output.
// Outputs:  None
// Purpose:  The zeroCrossing function is an implementation of the zero crossing signal
// analysis algorithm.  It counts the positive and negative changes within the signal
// and records the results in a 2D vector that is passed by the user.
void zeroCross (vector<complex<double> > leftChannel, vector<complex<double> > rightChannel, vector<vector<float> > &zeroCross, int channels, string path, bool debug)
{
    int lower;              // Mark the current lower bound of printed data
    int upper;              // Mark the current upper bound of printed data
    int fieldWidth;         // Specify the width of the data fields in output
    double sum;             // Will hold the sum of the signal changes for the current frame.

    string outputName;      // Name of file to store zeroCrossing results
    vector<string> values;  // Store the values of current data points
    ofstream outFile;       // File pointer for outputting results
   
    outputName = path + "/zeroCrossing.txt";

    fieldWidth = 10;
    lower = 0;
    upper = 0;
    sum = 0;

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
    summation(leftChannel, zeroCross, 1, channels, path, debug);

    if (channels == 2)
    {
        summation(rightChannel, zeroCross, 1, channels, path, debug);

        if (debug)
        {

            outFile.open((path + "/zeroCrossing.txt").c_str(), ios::app);

            outFile << endl << endl << "Right Channel:" << endl << endl;
       
            for (int i = 0; i < 100; i++)
                outFile << "*";

            outFile << endl << endl;
           
            outFile.close();
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

// Function summation
// Inputs:
//       data - A vector of complex doubles describing an audio wave
//       zeroCrossResults - A 2D vector of floats that will contain the zero cross results for each frame of the wave.
//       frames - An integer describing the number of frames in the audio file.
//       currentChannel - An integer describing the current channel
//       debug - A boolean flag that controls debug output
//       path - A string describing the path for debug output.
// Outputs: None
// Purpose:  To calculate the zerocross of a particular frame.
void summation(vector<complex<double> > data, vector<vector<float> > &zeroCrossResults,int currentChannel, int channels, string path, bool debug)
{
    const int BLOCKSIZE = 4096;

    double summedSigns;    // Will hold the summation of the signs for the current frame.
    int step;              // Used to calculate the beginning of the next frame.

    step = BLOCKSIZE / channels;
    summedSigns = 0;
    
    for (int i = 1; i < data.size() - 1; i += step)
    {
        int bound = 0;

        if ((i+step) >= data.size())
            bound = (i + step) - data.size();
        else
            bound = i + step;

        for (int j = i; j <= bound; j++)
            summedSigns += abs(sign(real(data[j])) - sign(real(data[j-1])));

        summedSigns = summedSigns / 2;

        if (currentChannel == 1)
            zeroCrossResults[0].push_back(summedSigns);
        else if (currentChannel == 2)
            zeroCrossResults[1].push_back(summedSigns);

        summedSigns = 0;
    }

    return;
}
