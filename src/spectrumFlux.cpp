/* 
 *  File:     spectrumFlux.cpp
 *  Author:   Andrew Moore and Hue Truong
 *
 *  Created:  February 9, 2020, 3:17 PM
 */

/**************************************Change Log *******************************/

// Created individual source for spectrum flux algorithm - A.M. and H.T. Feb 29 2020

/**************************************End Change Log ***************************/

/**************************************To Do List ******************************/

/**************************************End To Do List **************************/

#include "../include/spectrumFlux.h"
#include "../include/Utilities.h"

using namespace std;

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
void spectralFlux(vector<complex<double> > leftChannel,vector<complex<double> > rightChannel,double spectralFlux[],int channels,bool debug,string path)
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
