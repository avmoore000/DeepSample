/* 
 * File:   AudioSegmentation.cpp
 * Author: Andrew Moore
 *
 * Created on February 9, 2020, 3:17 PM
 */

/**************************************Change Log *******************************/

// Created source file for audio segmentation algorithms - A.M. Feb 09 2020
// Added zeroCrossing function implementation - A.M. Feb 09 2020
// Added getSign function implementation - A.M. Feb 09 2020

/**************************************End Change Log ***************************/

/**************************************To Do List ******************************/

// Create function implementation for Spectral Flux
// Create function implementation for cepstral analysis
// Create function implementation for complex cepstra analysis

/**************************************End To Do List **************************/
#include <iostream>
#include "AudioSegmentation.h"

using namespace std;

// Function zeroCrossing
// Inputs:  
//        *data - A pointer to the user generated waves
//        zeroCross - A pointer to the array that will store the zero cross results.
//        nx - the size of each data point in the dataset
//        debug - a flag to enable or disable debug messages.
// Outputs:  None
// Purpose:  The zeroCrossing function is an implementation of the zero crossing signal
// analysis algorithm.  It counts the positive and negative changes within the signal
// and records the results in an array of zeros and ones that is passed by the user.
void zeroCrossing (float *data, float *zeroCross, int nx, bool debug)
{
    // Keep track of the current and next data point.
    bool sign1, sign2;

    // Allocate space in memory based on the size of the data points.
    memset(zeroCross, 0, nx*sizeof(float));

    if (debug)
    {
        cout << "ZeroCross Algorithm" << endl << endl;
        cout << "NX = " << nx << endl;
    }

    // Loop through the data
    for (int i = 0; i < nx-1; i++)
    {
        sign1 = getSign(data[i],debug);
        sign2 = getSign(data[i+1],debug);;

        // If the signs are not equal, there has been a change in signal.
        if (sign1 != sign2)
            zeroCross[i+1] = 1;

        if (debug)
        {
            cout << "Iteration " << i << ":" << endl;
            cout << "sign1 = " << sign1 << endl;
            cout << "sign2 = " << sign2 << endl;
            cout << "zeroCross[" << i+1 << "] = " << zeroCross[i+1] << endl << endl;
        }
    }
}

// Function getSign
// Inputs
//    data - A float containing the current data point.
//    debut - A flag to enable or disable debug messages.
// Outputs:
//    sign - A boolean stating whether the signal has changed from positive to negative or vice versa.
// Purpose: Determines if a sign change has occured.
bool getSign(float data, bool debug)
{
    bool sign = 0;

    if (data > 0)
        sign = 1;
    else
        sign = 0;

    return sign;
}
