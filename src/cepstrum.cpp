/* 
 *  File:     cepstrum.cpp
 *  Author:   Andrew Moore and Hue Truong
 *
 *  Created:  February 29, 2020, 2:12 PM
 */

/**************************************Change Log *******************************/

// Created independent source file for cepstrum algorithms - A.M. and H.T. Feb 29 2020
//
/************************************End Change Log *****************************/

/**************************************End To Do List **************************/

#include "../include/cepstrum.h"
#include "../include/Utilities.h"

using namespace std;
/*
// Function cepstrum
// Inputs:
//    x - A vector of complex numbers describing the audio waveform.
// Outputs:
//    cep - Returns the inverse fourier transform of the wave in the form of a vector of complex numbers.
// Purpose:  Perform the cepstrum segmentation algorithm on the given audio sample.
vector<complex<double>> cCepstrum(vector<complex<double>> x)
{
    //Raw interpretation of complex cepstrum equation
    vector<complex<double>> absfft = abs(FourierTransform(x)); //absolute value of fft
    vector<complex<double>> log = log(absfft); //log of the absolute value

    vector<complex<double>> Ccepstrum = inverseFT(log); //applies inverse Fourier Transform
    return Ccepstrum;
}

vector<double> realCepstrum(vector<complex<double>> x)
{ //filters only real numbers to a new vector
    vector<complex<double>> complexCepstrum = cepstrum(x);
    vector<double> realnum;

    for(int i = 0; i < complex.size(); ++i){
        if(complexCepstrum.at(i) != isnan){ //If element in complex set is a real number, then push the element into a new set
            realnum.push_back(real(x.at(i)));
        }
    }

    return realnum;
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
//    n - A vector of complex numbers to be used to create the hamming window.
// Outputs:
//    newn - A vector of complex numbers describing the hamming window.
// Purpose:  Create the hamming window for use in the cepstrum algorithm.
vector<complex<double>> windowHamming(vector<complex<double>> n)
{
       vector<complex<double>> windowed_signal;
       //arbitrary integer N == fixed window size;
        double N = 200;

    //Applies the hamming window to every element in the vector list
    for(int i = 0; i <= n.size(); i++){
        windowed_signal.at(i) = 0.54 - 0.46 * cos((2 * M_PI * windowed_signal.at(i)) / N - 1.0); //Raw interpretation of Hamming Window equation
    }
    return windowed_signal;
}*/
