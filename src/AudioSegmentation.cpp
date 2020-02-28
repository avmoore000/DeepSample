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
// Edited zeroCrossing algorithm to work on both mono and stereo waves. - A.M. Feb 27 2020
// Implemented spectrum flux algorithm - A.M. Feb 28 2020

/**************************************End Change Log ***************************/

/**************************************To Do List ******************************/

// Create function implementation for cepstral analysis
// Create function implementation for complex cepstra analysis

/**************************************End To Do List **************************/

#include "../include/AudioSegmentation.h"
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
void zeroCrossing (vector<complex<double> > leftChannel,vector<complex<double> > rightChannel,vector<vector<float> > &zeroCross,int channels,bool debug,string path)
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

// Function spectrumFlux
// Inputs:
//        leftChannel - A vector of complex doubles describing the left channel of the audio wave.
//        rightChannel - A vector of complex doubles describing the right channel of the audio wave.
//        spectralFlux - An array of doubles that will hold the results of the calculations
//        channels - An integer describing the number of channels in the audiofile.
//        debug - A flag that controls the debug output.
//        path - A string containing the path for output files.
// Outputs: None
// Purpose:  spectrumFlux calculate the spectral flux between each frame of a given wave.
void spectrumFlux(vector<complex<double> > leftChannel,vector<complex<double> > rightChannel,double spectralFlux[],int channels,bool debug,string path)
{
    const int BLOCKSIZE = 4096;           // Used to calculate the number of frames

    int frames;                           // Determine the size of the windows
    double mag;                           // Will contain the magnitude of the vector within the frame.
    vector<double> normT;                 // The normalized vector in the first window
    bool nt;                              // Flag to control which part of the summation we are doing.

    ofstream outFile;                     // File used for outputing results.

    frames = 0;
    mag = 0;
    nt = 0;
    spectralFlux[0] = 0;
    spectralFlux[1] = 0;

    outFile.open((path + "/spectrumFlux.txt"),ios::out);

    outFile << "Spectrum Flux" << endl << endl;

    // Calculate the number of frames per window
    frames = BLOCKSIZE / channels;

    // Compute spectrum flux for left channel

    // Normalize the left channel
    normalize(leftChannel,normT,frames,1,debug,path);

    if (debug)
    {
        outFile << "Left Channel Calculation:  " << endl << endl;
        outFile << "F_t = ";
    }

    // Calculate the spectral flux of the left channel
    for (int i = 0; i <= normT.size() - 1; i++)
    {
        if (i == 0)
        {
            spectralFlux[0] += normT[i] * normT[i];
        } 
        else
        {
            spectralFlux[0] += (normT[i] - normT[i-1]) * (normT[i] - normT[i-1]);
        }

        if (debug)
        {
            if (i == 0)
                outFile << "(" << normT[i] << " * " << normT[i] << ") ";
            else 
                outFile << "( (" << normT[i] << " * " << normT[i] << ") * (" << normT[i] << " - " << normT[i-1] << ") )";

            if (i != normT.size() - 1)
                outFile << " + ";

            if (i % 10)
                outFile << endl << "     ";
        }
    }

    if (debug)
    {
        outFile << endl << "F_t = " << spectralFlux[0] << endl << endl;

        for (int i = 0; i < 100; i++)
            outFile << "*";

        outFile << endl << endl;
    }

    if (channels == 2) // Compute the spectrum flux of right channel
    {
        if (debug)
        {   
            outFile << "Right Channel Calculation:  " << endl << endl;
            outFile << "F_t = ";
        }
        // Normalize the right channel
        normalize(rightChannel,normT,frames,2,debug,path);

        // Calculate the spectral flux of the right channel
        for (int i = 0; i <= normT.size() - 1; i++)
        {
            if (i == 0)
            {
                spectralFlux[1] += normT[i] * normT[i];
            }
            else
            {
                spectralFlux[1] += (normT[i] - normT[i-1]) * (normT[i] - normT[i-1]);
            }

            if (debug)
            {   
                if (i == 0) 
                    outFile << "(" << normT[i] << " * " << normT[i] << ") ";
                else 
                    outFile << "( (" << normT[i] << " * " << normT[i] << ") * (" << normT[i] << " - " << normT[i-1] << ") )";
            
                if (i != normT.size() - 1)
                    outFile << " + ";
            
                if (i % 10) 
                    outFile << endl << "     ";
            }   
        }
        if (debug)
        {
            outFile << endl << "F_t = " << spectralFlux[1] << endl << endl;

            for (int i = 0; i < 100; i++)
                outFile << "*";

            outFile << endl << endl;
        }

    }
    
    outFile << "End of Spectrum Flux" << endl;
    outFile.close();   

    return;
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
