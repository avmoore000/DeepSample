/* 
 *  File:     spectrumFlux.cpp
 *  Author:   Andrew Moore, Hue Truong, and Alex Reno
 *
 *  Created:  February 9, 2020, 3:17 PM
 */

/**************************************Change Log *******************************/

// Created individual source for spectrum flux algorithm - A.M. and H.T. Feb 29 2020
// Standardized the function argument order - A.M. 30 Mar 2020

/**************************************End Change Log ***************************/

/**************************************To Do List ******************************/

/**************************************End To Do List **************************/

#include "../include/spectrumFlux.h"
#include "../include/Utilities.h"

using namespace std;

// Function spectrumFlux
// Inputs:
//        &wave - An AudioWave object.
//        fileName - A string indicating the file for data output.
//        path - A string indicating the path for output files.
//        debug - A boolean flag that controls the debug output.
// Outputs: None
// Purpose:  spectrumFlux calculate the spectral flux between each frame of a given wave.
void spectralFlux(AudioWave &wave, string fileName, string path, bool debug)
{
    ofstream outFile;                    // A stream pointer for data output.
    ofstream debugFile;                  // A stream pointer for debug output.

    double sFlux;                        // Will be used when calculating the flux.
    vector<double> normT;                // A vector of normalized datapoint from a single channel.
    vector<vector<double> > norms;       // A vector of both the right and left normalized channels.
    bool nt;                             // A flag to control the part of the summation being worked.

    sFlux = 0;
    nt = 0;
    
    for (int i = 0; i < 2; i++)
        norms.push_back(normT);

    outFile.open((path + "/" + fileName).c_str(), ios::app);
    outFile << timestamp() << ":  Spectrum Flux Algorithm started..." << endl;
    outFile.close();

    if (debug)
    {
        debugFile.open((path + "/SpectrumFlux/SpectrumFluxAlgDebug.txt").c_str(), ios::app);  
        debugFile << "Spectrum Flux Algorithm Debug" << endl << endl;

        cout << timestamp() << ":  Spectrum Flux Algorithm started..." << endl;
    }

    // Make sure we have an fft to work with
    if (wave.getLeftFFTSize() == 0)
    {
        fft(wave, fileName, path, debug);
    }

    normalize(wave, norms, fileName, path, debug);

    // Calculate the spectral flux of all channels in audio signal
    for (int i = 0; i < wave.getChannels(); i++)
    {

        outFile.open((path + "/" + fileName).c_str(), ios::app);

        if (i == 0)
        {
            outFile << timestamp() << ":  Calculating left channel spectral flux..." << endl;

            if (debug)
                cout << timestamp() << ":  Calculating left channel spectral flux..." << endl;
        }
        else if (i == 1)
        {
            outFile << timestamp() << ":  Calculating right channel spectral flux..." << endl;
            
            if (debug)
                cout << timestamp() << ":  Calculating right channel spectral flux..." << endl;
        }

        outFile.close();

        if (debug)
        {
            if (i == 0)
            {
                if (wave.getChannels() > 1)
                    debugFile << "Left Channel Spectral Flux Calculation:";
                else
                    debugFile << "Spectral Flux Calculation:";
            }
            else if ( i == 1)
                debugFile << "Right Channel Spectral Flux Calculation:";

            debugFile << endl << endl << "\t";
        }

        for (int j = 0; j < norms[i].size() - 1; j++)
        {
            if (j == 0)
                sFlux += norms[i].at(j) * norms[i].at(j);    
            else
                sFlux += (norms[i].at(j) - norms[i].at(j-1)) * (norms[i].at(j) - norms[i].at(j-1));

            if (debug)
            {
                if (j == 0)
                    debugFile << "(" << norms[i].at(j) << " * " << norms[i].at(j) << ") ";
                else
                    debugFile << "( (" << norms[i].at(j) << " - " << norms[i].at(j-1)
                              << ") * (" << norms[i].at(j) << " - " << norms[i].at(j-1)
                              << ") )";

                if (j != norms[i].size() - 1)
                    debugFile << " + ";

                if (j % 10)
                    debugFile << endl << "\t";
            }
        }

        // Update the spectrum flux database for the wave object
        wave.pushSpectrumF(sFlux);

        if (debug)
        {
            debugFile << endl << "]" << endl << endl;
        }

        outFile.open((path + "/" + fileName).c_str(), ios::app);
        
        if (i == 0)
        {
            outFile << timestamp() << ":  Left channel spectral flux calculated." << endl;

            if (debug)
                cout << timestamp() << ":  Left channel spectral flux calculated." << endl;
        }
        else if (i == 1)
        {
            outFile << timestamp() << ":  Right channel spectral flux calculated." << endl;

            if (debug)
                cout << timestamp() << ":  Right channel spectral flux calculated." << endl;
        }
    }

    outFile.open((path + "/" + fileName).c_str(), ios::app);
    outFile << timestamp() << ":  Spectrum Flux Algorithm Completed." << endl;
    outFile.close();

    if (debug)
    {
        debugFile << "Spectrum Flux Algorithm completed." << endl;
        debugFile.close();

        cout << timestamp() << ":  Spectrum Flux algorithm returning..." << endl;
    }

    return;
}
