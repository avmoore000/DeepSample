/* 
 *  File:     spectrumCentroid.cpp
 *  Author:   Andrew Moore, Hue Truong, and Alex Reno
 *
 *  Created:  April 8, 2020, sometime after 3:00 PM
 */

/**************************************Change Log *******************************/

// Copied spectrum flux algorithm source file - A.R. 8 Apr 2020
// Replaced all instances of "Flux" with "Centroid" - A.R. 9 Apr 2020
// Actually changed the code to be a Spectrum Centroid algorithm

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

    double sCentroid;                    // Will be used during calculation.
    vector<double> normT;                // A vector of normalized datapoint from a single channel.
    vector<vector<double> > norms;       // A vector of both the right and left normalized channels.
    bool nt;                             // A flag to control the part of the summation being worked.

    sCentroid = 0;
    nt = 0;
    
    for (int i = 0; i < 2; i++)
        norms.push_back(normT);

    outFile.open((path + "/" + fileName).c_str(), ios::app);
    outFile << timestamp() << ":  Spectrum Centroid Algorithm started..." << endl;
    outFile.close();

    if (debug)
    {
        debugFile.open((path + "/SpectrumCentroid/SpectrumCentrAlgDebug.txt").c_str(), ios::app);  
        debugFile << "Spectrum Centroid Algorithm Debug" << endl << endl;

        cout << timestamp() << ":  Spectrum Centroid Algorithm started..." << endl;
    }

    normalize(wave, norms, fileName, path, debug);

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
        }

        for (int j = 0; j < norms[i].size() - 1; j++)
        {
            if (j == 0)
                sCentroid += norms[i].at(j) * norms[i].at(j);    
            else
                sCentroid += (norms[i].at(j) - norms[i].at(j-1)) * (norms[i].at(j) - norms[i].at(j-1));

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

        // Update the spectrum centroid database for the wave object
        wave.pushSpectrum(sCentroid);

        if (debug)
        {
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
