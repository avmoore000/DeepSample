/* 
 *  File:     zeroCrossing.cpp
 *  Author:   Andrew Moore, Hue Truong, and Alex Reno
 *
 *  Created:  February 29, 2020 2:09 PM
 */

/**************************************Change Log *******************************/

// Created zeroCrossing.cpp file - A.M and H.T Feb 29 2020
// Standardized function argument order - A.M. 30 Mar 2020

/**************************************End Change Log ***************************/

/**************************************To Do List ******************************/

/**************************************End To Do List **************************/

#include "../include/zeroCrossing.h"
#include "../include/Utilities.h"

using namespace std;

// Function zeroCrossing
// Inputs:  
//        &wave - An AudioWave object.
//        fileName - A string indicating the file for data output.
//        path - A string indicating the path for output files.
//        debug - A boolean flag that controls debug output.
// Outputs:  None
// Purpose:  The zeroCrossing function is an implementation of the zero crossing signal
// analysis algorithm.  It counts the positive and negative changes within the signal
// and records the results in a 2D vector.
void zeroCross(AudioWave &wave, string fileName, string path, bool debug)
{
    ofstream outFile;        // A stream pointer for data output
    ofstream debugFile;      // A stream pointer for debug output

    int step;                // Will control the size of the zero cross frame.
    int chanSize;            // Will hold the size of the current channel.
    double sum;              // Sum of signal changes in current frame;

    sum = 0;
    step = wave.getFrames();
    chanSize = 0;

    // Temporarily disable debug
    debug = 0;

    outFile.open((path + "/" + fileName).c_str(), ios::app);
    outFile << timestamp() << ":  ZeroCross Algorithm Called..." << endl;
    outFile.close();

    if (debug)
    {
        debugFile.open((path + "/ZeroCrossAlgDebug.txt").c_str(), ios::out);
        cout << timestamp() << ":  ZeroCross Algorithm Called..." << endl;
    }

    // Perform the zero cross for each channel in the wave
    for (int i = 0; i < wave.getChannels(); i++)
    {
        if (i == 0)
        {
            chanSize = wave.getLeftSize();

            outFile.open((path + "/" + fileName).c_str(), ios::app);
            outFile << timestamp() << ":  Calculating left channel zero cross..." << endl;
            outFile.close();
           
            if (debug)
            {
                debugFile << "Left Channel Zero Cross:  " << endl;

                cout << timestamp() << ":  Calculating left channel zero cross..." << endl;
            }
        }
        else if (i == 1)
        {
            chanSize = wave.getRightSize();

            outFile.open((path + "/" + fileName).c_str(), ios::app);
            outFile << timestamp() << ":  Calculating right channel zero cross..." << endl;
            outFile.close();
          
            if (debug)
            {
                debugFile << "Right Channel Zero Cross:  " << endl;

                cout << timestamp() << ":  Calculating right channel zero cross..." << endl;
            }
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
                if (k == 0)
                    sum += abs(sign(real(wave.getChannelData(i,k))));
                else
                    sum += abs(sign(real(wave.getChannelData(i,k))) - sign(real(wave.getChannelData(i,k-1))));
            }

            if (debug)
                debugFile << "\tSum of zeroCross[" << j << "-" << bound << " = " << sum << endl;

            sum /= 2;

            if (debug)
                debugFile << "\tsum/2 = " << sum << endl;

            if (i == 0)
                wave.pushZero(i,sum);

            sum = 0;
        }

        outFile.open((path + "/" + fileName).c_str(), ios::app);

        if (i == 0)
        {
            outFile << timestamp() << ":  Left Channel Zero Cross calculated." << endl;

            if (debug)
                cout << timestamp() << ":  Left Channel Zero Cross calculated." << endl;
        }
        else if (i == 1)
        {
            outFile << timestamp() << ":  Right Channel Zero Cross calculated."  << endl;

            if (debug)
                cout << timestamp() << ":  Right Channel Zero Cross calculated." << endl;
        }
 
    } 

    outFile.open((path + "/" + fileName).c_str(), ios::app);
    outFile << timestamp() << ":  ZeroCross Algorithm completed." << endl;
    outFile.close();

    if (debug)
    {
        cout << timestamp() << ":  ZeroCross Algorithm returning..." << endl;
        debugFile.close();
    }

    return;
}
