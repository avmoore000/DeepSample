/* 
 *  File:     spectrumCentroid.cpp
 *  Author:   Andrew Moore, Hue Truong, and Alex Reno
 *
 *  Created:  April 8, 2020, sometime after 3:00 PM
 */

/**************************************Change Log *******************************/

// Copied spectrum flux algorithm source file - A.R. 8 Apr 2020
// Replaced all instances of "Flux" with "Centroid" - A.R. 9 Apr 2020
// Changed the code to be a Spectral Centroid algorithm - A.R. 11 Apr 2020
// Reviewed code and edited to use the new helper function - A.R. 20 Apr 2020

/**************************************End Change Log ***************************/

/**************************************To Do List ******************************/

/**************************************End To Do List **************************/

#include "../include/spectrumCentroid.h"
#include "../include/Utilities.h"

using namespace std;

// Function spectralCentroid
// Inputs:
//        &wave - An AudioWave object.
//        fileName - A string indicating the file for data output.
//        path - A string indicating the path for output files.
//        debug - A boolean flag that controls the debug output.
// Outputs: None
// Purpose:  spectralCentroid calculates the spectral centroid between each frame of a given wave.
void spectralCentroid(AudioWave &wave, string fileName, string path, bool debug)
{
    ofstream outFile;                    // A stream pointer for data output.
    ofstream debugFile;                  // A stream pointer for debug output.
    ostringstream debugDenominator;      // A second stream for debug output.
    string debdenom;                     // The contents of debugDenominator to be combined into debugFile.

    double sCentroid;                    //*
    double scNumerator;                  //* Will be used during calculation.
    double scDenominator;                //*/

    vector<double> realT;                // The Fourier Transform magnitudes of a single channel.
    vector<vector<double> > reals;       // A vector of both the right and left fft magnitudes.
    bool nt;                             // A flag to control the part of the summation being worked.

    sCNumerator = 0;
    sCDenominator = 0;
    nt = 0;
    
    for (int i = 0; i < 2; i++)
        reals.push_back(realT);

    outFile.open((path + "/" + fileName).c_str(), ios::app);
    outFile << timestamp() << ":  Spectrum Centroid Algorithm started..." << endl;
    outFile.close();

    if (debug)
    {
        debugFile.open((path + "/SpectrumCentroid/SpectrumCentrAlgDebug.txt").c_str(), ios::app);  
        debugFile << "Spectrum Centroid Algorithm Debug" << endl << endl;

        cout << timestamp() << ":  Spectrum Centroid Algorithm started..." << endl;
    }

    // Make sure we have an fft to work with
    if (wave.getLeftFFTSize() == 0)
    {
        fft(wave, fileName, path, debug);
    }

    realify(wave, reals, fileName, path, debug);

    // Calculate the spectral centroid of all channels in audio signal
    for (int i = 0; i < wave.getChannels(); i++)
    {

        outFile.open((path + "/" + fileName).c_str(), ios::app);

        if (i == 0)
        {
            outFile << timestamp() << ":  Calculating left channel spectral centroid..." << endl;

            if (debug)
                cout << timestamp() << ":  Calculating left channel spectral centroid..." << endl;
        }
        else if (i == 1)
        {
            outFile << timestamp() << ":  Calculating right channel spectral centroid..." << endl;
            
            if (debug)
                cout << timestamp() << ":  Calculating right channel spectral centroid..." << endl;
        }

        outFile.close();

        if (debug)
        {
            debugDenominator.str(string());
            if (i == 0)
            {
                if (wave.getChannels() > 1)
                    debugFile << "Left Channel Spectral Centroid Calculation:";
                else
                    debugFile << "Spectral Centroid Calculation:";
            }
            else if ( i == 1)
                debugFile << "Right Channel Spectral Centroid Calculation:";

            debugFile << endl << endl << "\t";
            debugFile << "( ";
            debugDenominator << "( ";
        }

        for (int j = 0; j < reals[i].size() - 1; j++)
        {
            sCNumerator += reals[i].at(j) * j;  
            sCDenominator += reals[i].at(j);

            if (debug)
            {
                debugFile << "(" << reals[i].at(j) << " * " << i << ")";
                debugDenominator << "(" << reals[i].at(j) << ")";

                if (j != reals[i].size() - 1)
                    debugFile << " + ";
                    debugDenominator << " + ";

                if (j % 10)
                    debugFile << endl << "\t";
                    debugDenominator << endl << "\t";
            }
        }

        // Update the spectrum centroid database for the wave object
        sCentroid = sCNumerator / sCDenominator;
        wave.pushSpectrumC(sCentroid);

        if (debug)
        {
            debugDenominator << " )";
            debdenom = debugDenominator.str();
            debugFile << " ) / " << debdenom;
            debugFile << endl << "]" << endl << endl;
        }

        outFile.open((path + "/" + fileName).c_str(), ios::app);
        
        if (i == 0)
        {
            outFile << timestamp() << ":  Left channel spectral centroid calculated." << endl;

            if (debug)
                cout << timestamp() << ":  Left channel spectral centroid calculated." << endl;
        }
        else if (i == 1)
        {
            outFile << timestamp() << ":  Right channel spectral centroid calculated." << endl;

            if (debug)
                cout << timestamp() << ":  Right channel spectral centroid calculated." << endl;
        }
    }

    outFile.open((path + "/" + fileName).c_str(), ios::app);
    outFile << timestamp() << ":  Spectrum Centroid Algorithm Completed." << endl;
    outFile.close();

    if (debug)
    {
        debugFile << "Spectrum Centroid Algorithm completed." << endl;
        debugFile.close();

        cout << timestamp() << ":  Spectrum Centroid Algorithm returning..." << endl;
    }

    return;
}
