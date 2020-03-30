/* 
 *  File:   TestSuite.cpp
 *  Author: Hue Truong, Andrew Moore, and Alex Reno
 *
 *  Created February 27, 2020, 12:28 PM
 *
 */

/**************************************Change Log *******************************/

// Added a change log and to do list section - A.M. Feb 09 2020
// Implemented a 2D vector to contain zeroCross results

/**************************************End Change Log ***************************/

/**************************************To Do List ******************************/

/**************************************End To Do List **************************/

#include "../include/TestSuite.h"

using namespace std;
using namespace std::chrono;

// Function zeroCrossingTest
// Inputs:
//       wave - An AudioWave object containing the audio file to analyze.
//       fileName - A string containing the filname of the output file
//       path - A string containg the directory for file output
//       debug - A boolean flag that controls debug output.
// Outputs: None
// Purpose:  This is a test function for the zero crossing algorithm.
void zeroCrossingTest(AudioWave &wave, string fileName, string path, bool debug)
{
    ofstream outFile;               // Points to the file to output results
    ofstream debugFile;             // Points to the file for outputting debug data

    outFile.open((path + "/" + fileName).c_str(), ios::app);
    outFile << timestamp() << ":  Zero Cross Test called..." << endl;
    outFile.close();

    if (debug)
        debugFile.open((path + "/zeroCrossTestSuiteDebug.txt").c_str(), ios::app);

    auto start = high_resolution_clock::now();
    zeroCross(wave, fileName, path, debug);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    outFile.open((path + "/" + fileName).c_str(), ios::app);
    outFile << timestamp() << ":  Zero Cross Test Completed in " << duration.count() << " ms." << endl;
    outFile.close();

    if (debug)
    {
        // Output the left channel zero crossing results

        debugFile << "Zero Crossing Results" << endl << endl;
        debugFile << "Left Channel Signal Array:  " << endl;
        debugFile << "[" << endl << "\t";

        for (int i = 0; i < wave.getLeftSize() - 1; i++)
        {
            debugFile << wave.getZeroDataPoint(0, i);

            if ((i != 0) && ((i % 50) == 0))
                debugFile << endl << "\t";
        }

        debugFile << endl << "]" << endl << endl;

        // Output the right channel zero crossing results

        if (wave.getChannels() == 2)
        {
            debugFile << "Right Channel Signal Array:  " << endl;
            debugFile << "[" << endl << "\t";

            for (int i = 0; i < wave.getRightSize() - 1; i++)
            {
                debugFile << wave.getZeroDataPoint(1, i);

                if ((i != 0) && ((i % 50) == 0))
                    debugFile << endl << "\t";
            }

            debugFile << endl << "]" << endl << endl;
        }
    }

    outFile.open((path + "/" + fileName).c_str(), ios::app);
    outFile << timestamp() << ":  Zero Cross Test Suite Exiting..." << endl;
    outFile.close();

    if (debug)
        debugFile.close();

    return;
}
    
// Function spectrumFluxTest
// Inputs:
//       leftChannel - A vector of complex doubles describing the left channel of an audio wave.
//       rightChannel - A vector of complex doubles describing the right channel of an audio wave.
//       channels - An integer describing the number of channels in the audio file.
//       debug - A flag that controls the debug output.
//       outputFile - A string describing the file to output results
//       path - A string describing the path for the output file directory
// Outputs: None
// Purpose:  This function tests the spectrum flux algorithm.
void spectrumFluxTest(vector<complex<double> > leftChannel,vector<complex<double> > rightChannel,int channels,bool debug,string fileName,string path)
{
    string outputFileName;             // Contains the name of the output file
    ofstream outputFile;               // A stream pointer for data output.
    double spectralFluxResults[2];     // Will hold the results of the spectrum flux algorithm.

    outputFileName = path + "/" + fileName;

    outputFile.open(outputFileName.c_str(), ios::app);

    auto start = high_resolution_clock::now();
    spectralFlux(leftChannel, rightChannel, spectralFluxResults, channels, path, debug);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Spectrum Flux Algorithm completed in " << duration.count() << " ms." << endl;
    outputFile << "Spectrum Flux Algorithm completed in " << duration.count() << " ms." << endl << endl;    
    
    outputFile << "Left Channel Spectral Flux:  " << spectralFluxResults[0] << endl;

    if (channels == 2)
    {
        outputFile << "Right Channel Spectral Flux:  " << spectralFluxResults[1] << endl;
    }

    outputFile << endl;

    outputFile.close();
    return;
}

// Function cepstrumTest
// Inputs:
//       leftChannel - A vector of complex doubles describing the left channel of an audio wave.
//       rightChannel - A vector of complex doubles describing the right channel of an audio wave.
//       channels - An integer describing the number of channels in an audio file
//       debug - A flag that controls debug output
//       outputFile - A string descibing the file to output results
//       path - A string describing the path for the output file directory
// Outputs: None
// Purpose:  This function tests the cepstrum algorithm
void cepstrumTest(vector<complex<double> > leftChannel, vector<complex<double> > rightChannel, int channels, bool debug, string fileName, string path)
{
    return;
}

// Function anniTest
// Inputs:
//       path - A string describing the path for the output directory
//       audioName - A string containing the name of the current audio file.
//       channels - An integer describing the number of channels in the audio.
//       debug - A flag that controls the debug output.
// Outputs: None
// Purpose:  This function tests the performance of ANNI.
void anniTest(string path,string fileName,string audioName,int channels,bool debug)
{
    string outputFileName;                   // Contains the name of the output file.
    ofstream outputFile;                     // A stream pointer for data output.
    double spectralFluxResults[2];           // Will hold the results of the spectral flux algorithm.
    
    vector<complex<double> > leftChannel;    // Container to hold the left side of the wave.
    vector<complex<double> > rightChannel;   // Container to hold the right side of the wave.
    
    outputFileName = path + "/" + fileName;

    outputFile.open(outputFileName.c_str(),ios::app);

    cout << "ANNI Test started" << endl;

    // Load the audio file
    //loadAudio(audioName, leftChannel, rightChannel, "", "", channels, "", debug);

    // Perform the fft on the audio
    //fft(leftChannel, path, debug);

    if (channels == 2)
      //  fft(rightChannel, path, debug);

    // Get zero crossing vector for audio file

    vector<float> dataPoints(leftChannel.size(),0);            // A vector containing datapoints for each channel
    //vector<vector<float> > zeroCrossResults(2,dataPoints);     // A vector containing zero crossing results

    //zeroCross(leftChannel, rightChannel, zeroCrossResults,channels, path, debug);

    // Get the spectrum flux for audio file
    spectralFlux(leftChannel, rightChannel, spectralFluxResults, channels, path, debug);


    auto start = high_resolution_clock::now();
    //ANNI(zeroCrossResults, spectralFluxResults, audioName, channels, path, debug);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop-start);

    cout << "ANNI completed in " << duration.count() << " ms." << endl;
    outputFile << "ANNI completed running with " << audioName << " as input in " 
               << duration.count() << " ms." << endl << endl;

    return;
}
