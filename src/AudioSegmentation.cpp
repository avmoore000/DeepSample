/* 
 *  File:     AudioSegmentation.cpp
 *  Author:   Andrew Moore and Hue Truong
 *
 *  Created:  February 9, 2020, 3:17 PM
 */

/**************************************Change Log *******************************/

// Created source file for audio segmentation algorithms - A.M. Feb 09 2020
// Added zeroCrossing function implementation - A.M. Feb 09 2020
// Added getSign function implementation - A.M. Feb 09 2020
// Updated debug mode to use a print function - A.M. Feb 23 2020
// Added in the function definition for windowHamming - A.M. and H.T. Feb 23 2020
// Added in the function definition for cepstrum - A.M. and H.T. Feb 23 2020

/**************************************End Change Log ***************************/

/**************************************To Do List ******************************/

// Create function implementation for Spectral Flux
// Create function implementation for cepstral analysis
// Create function implementation for complex cepstra analysis

/**************************************End To Do List **************************/
#include "../include/AudioSegmentation.h"
#include "../include/Utilities.h"

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
void zeroCrossing (vector<complex<double> >data, float zeroCross[], int nx, bool debug)
{
    // Keep track of the current and next data point.
    bool sign1, sign2;

    // Output data
    string outputName = "Results/zeroCrossing.txt";
    ofstream outFile;
    outFile.open(outputName, ios::out);

    int j = 0;
    int bound = 6;
    int lower = 0;
    int upper = 0;
    int percent = 0;  // Keep track of completion percentage

    // Strings used to build output file.
    stringstream stringBuilder;
    string values[6];

    for (int i = 0; i < 100; i++)
        outFile << "*";

    for (int i = 0; i < 6; i++)
        values[i] = "";

    cout << "Data.size() = " << data.size() << endl;

    percent = (5*data.size()) / 100;

    outFile << endl << endl << "ZeroCross Algorithm" << endl << endl;
    cout << "ZeroCross Algorithm Running" << endl << endl;

    if (debug)
    {
        outFile << "NX = " << nx << endl << endl;
        outFile << "Zero Crossing calculations:  " << endl << endl;
    }

    outFile.close();

    // Loop through the data
    for (int i = 0; i < nx-1; i++)
    {
        upper = i;
        sign1 = getSign(real(data[i]),debug, outputName);
        sign2 = getSign(real(data[i+1]),debug, outputName);

        // If the signs are not equal, there has been a change in signal.
        if (sign1 != sign2)
            zeroCross[i+1] = 1;

        if (debug)
        {
	    stringBuilder << setiosflags(ios_base::left) << setw(10) << to_string(i+1) + "  ";
	    values[0] += stringBuilder.str();
	    stringBuilder.str("");
	    stringBuilder << setiosflags(ios_base::left) << setw(10) << to_string(real(data[i])) + "  ";
	    values[1] += stringBuilder.str();
            stringBuilder.str("");
	    stringBuilder << setiosflags(ios_base::left) << setw(10) << to_string(real(data[i+1])) + "  ";
	    values[2] += stringBuilder.str();
	    stringBuilder.str("");
	    stringBuilder << setiosflags(ios_base::left) << setw(10) << to_string(sign1) + "  ";
	    values[3] += stringBuilder.str();
	    stringBuilder.str("");
	    stringBuilder << setiosflags(ios_base::left) << setw(10) << to_string(sign2) + "  ";
	    values[4] += stringBuilder.str();
	    stringBuilder.str("");
	    stringBuilder << setiosflags(ios_base::left) << setw(10) << to_string(zeroCross[i+1]) + "  ";
	    values[5] += stringBuilder.str();
	    stringBuilder.str("");

            if ((i != 0) && ((i%4) == 0))
            {
                printer(outputName, values, 0, 1, lower, upper, bound);
            
                lower = i + 1;   

                for (int j = 0; j < 6; j++)
                    values[j] = "";
	    }
	    else
            {
                j += 1;
	    }
        }

        if ((i%percent) == 0)
        {
            cout << "#";
        }
    }

    cout << endl << endl; 

    outFile.open(outputName, ios::app);

    cout << "ZeroCross Algorithm Complete." << endl << endl;
    outFile << "ZeroCross Algorithm Complete. " << endl << endl;
    
    for (int i = 0; i < 100; i++)
        outFile << "*";
    outFile << endl << endl;

    outFile.close();

}

/*
// Function cepstrum
// Inputs:
//    x - A vector of complex numbers describing the audio waveform.
// Outputs:
//    cep - Returns the inverse fourier transform of the wave in the form of a vector of complex numbers.
// Purpose:  Perform the cepstrum segmentation algorithm on the given audio sample.
vector<complex<double> > cepstrum(vector<complex<double> > x)
{
    vector<complex<double> > absfft = abs(FourierTransform(x)); // Absolute left value of fft
    vector<complex<double> > log = log(absfft);  // Log of the absolute value
    vector<complex<double> > cep = inverseFT(log);  // Applies inverse fourier transform to the wave.

    return cep;
    
}
*/

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
vector<complex<double> > windowHamming(vector<complex<double> > n)
{
    vector<complex<double> > newn;

    double N = 200;  // Arbitrary N; fixed window size

    // Apply the hamming window to every element in the vector list.
    for (int i = 0; i < n.size(); i++)
    {
        newn.at(i) = 0.54 - 0.46 * cos((2 * M_PI * n.at(i)) / N - 1.0);  // Formula 
    }

    return newn;
}
