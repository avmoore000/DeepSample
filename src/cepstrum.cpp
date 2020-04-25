/* 
 *  File:     cepstrum.cpp
 *  Author:   Andrew Moore, Hue Truong, and Alex Reno
 *
 *  Created:  February 29, 2020, 2:12 PM
 */

/**************************************Change Log *******************************/

// Created independent source file for cepstrum algorithms - A.M. and H.T. Feb 29 2020
//
/************************************End Change Log *****************************/

/**************************************End To Do List **************************/

#include "../include/cepstrum.h"
#include "../include/FourierTransform.h"
#include "../include/Utilities.h"
#include <math.h>
using namespace std;

// Function cepstrum
// Inputs:
//    raw - A vector of numbers describing the audio waveform.
//    windowSize - size of hamming window
// Outputs:
//    finalCepstrum - Returns the inverse fourier transform of the wave in the form of a vector of real numbers.
// Purpose:  Perform the cepstrum segmentation algorithm on the given audio sample, according to the real cepstrum equation.
vector<double> rCepstrum(vector<double>& raw, double windowSize)
{
    vector<double> rawWave;

    rawWave = raw; 

    inverseFT(windowHamming(rawWave, windowSize), "", 0);

    vector<double> finalCepstrum = abs(log(rawWave));

    return finalCepstrum;
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

// Function windowHamming
// Inputs:
//    rawCepstrum - A vector of complex numbers to be used to create the hamming window.
//    windowSize - Size of the hamming window
// Outputs:
//    cepstrumHamming - A vector of doubles transformed by the hamming window.
// Purpose:  Create the hamming window for use in the cepstrum algorithm.
vector<double> windowHamming(vector<double>& raw, double windowSize)
{
    vector<double> cepstrumHamming;
    //Runs through loop to apply hamming window
    for(int i = 0; i < raw.size(); ++i){
        //Applies the hamming window to every real part of the element in the vector list
        cepstrumHamming.at(i) = 0.54 - 0.46 * cos((2 * M_PI * cepstrumHamming.at(i)) / windowSize - 1.0);      
    }
    return cepstrumHamming;
}
