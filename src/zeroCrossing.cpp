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
//        &wave - An AudioWave object containing the audio file to analyze.
//        fileName - A string indicating the name of the file for output.
//        path - A string containing the path for file output.
//        debug - A boolean flag that controls debug output.
// Outputs:  None
// Purpose:  The zeroCrossing function is an implementation of the zero crossing signal
// analysis algorithm.  It counts the positive and negative changes within the signal
// and records the results in a 2D vector.
void zeroCross(AudioWave &wave, string fileName, string path, bool debug)
{
    ofstream outFile;        // Name of file to store standard output.
    ofstream debugFile;      // Name of file for debug output.

    int step;                // Will control the size of the zero cross frame.
    int chanSize;            // Will hold the size of the current channel.
    double sum;              // Sum of signal changes in current frame;

    sum = 0;
    step = wave.getFrames();
    chanSize = 0;


    outFile.open((path + "/" + fileName).c_str(), ios::app);
    outFile << timestamp() << ":  ZeroCross Algorithm Called..." << endl;
    outFile.close();

    if (debug)
        debugFile.open((path + "/ZeroCrossAlgDebug.txt").c_str(), ios::out);

    // Perform the zero cross for each channel in the wave
    for (int i = 0; i < wave.getChannels(); i++)
    {
        if (i == 0)
        {
            chanSize = wave.getLeftSize();
           
            if (debug)
                debugFile << "Left Channel Zero Cross:  " << endl;
        }
        else if (i == 1)
        {
            chanSize = wave.getRightSize();
          
            if (debug)
                debugFile << "Right Channel Zero Cross:  " << endl;
        }

        for (int j = 0; j < chanSize - 1; j += step)
        {
            int bound = 0;

            if ((j + step) >= chanSize - 1)
                bound = (j + step) - (chanSize-1);
            else 
                bound = j + step;


            for (int k = j; k <= bound; k++)
            {
                sum += abs(sign(real(wave.getChannelData(i,k))) - sign(real(wave.getChannelData(i,k-1))));
            }

            if (debug)
                debugFile << "\tSum of zeroCross[" << j << "-" << bound << " = " << sum << endl;

            sum /= 2;

            if (debug)
                debugFile << "\tsum/2 = " << sum << endl;

            wave.pushZero(i,sum);

            sum = 0;
        }
    } 

    outFile.open((path + "/" + fileName).c_str(), ios::app);
    outFile << timestamp() << ":  ZeroCross Algorithm Finished, Exiting..." << endl;
    outFile.close();

    if (debug)
        debugFile.close();

    return;
}
