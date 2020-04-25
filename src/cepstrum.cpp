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
//    realCepstrum - Returns the inverse fourier transform of the wave in the form of a vector of real numbers.
// Purpose:  Perform the cepstrum segmentation algorithm on the given audio sample, according to the real cepstrum equation.
vector<double> rCepstrum(vector<double>& raw, double windowSize)
{
    vector<double> realCepstrum;
    for(int i = 0; i < raw.size(); ++i){

        //pushes transformed element, based on cepstrum equation, to a new vector list
        realCepstrum.push_back(abs(log(inverseFT(windowHamming(raw.at(i), windowSize),"",0)))); 

    }
    return realCepstrum;
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
//    rawElement - A single element of a vector to be transformed through the hamming window.
//    windowSize - Size of the hamming window
// Outputs:
//    cepstrumHamming - A vector of doubles transformed by the hamming window.
// Purpose:  Create the hamming window for use in the cepstrum algorithm.
double windowHamming(vector<double>& rawElement, double windowSize)
{
    double cepstrumHamming;
    
        //Applies the hamming window to every real part of the element in the vector list
        cepstrumHamming = 0.54 - 0.46 * cos((2 * M_PI * rawElement / windowSize - 1.0);      

    return cepstrumHamming;
}
