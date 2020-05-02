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
// Edited all tests to use the AudioWave object. - A.M. 30 Mar 2020
// Added testing for audio loading and the fft algorithm - A.M. 30 Mar 2020
// Standardized order of function arguments.  - A.M. 30 Mar 2020
// Added testing for Spectrum Centroid. -A.R. 22 Apr 2020

/**************************************End Change Log ***************************/

/**************************************To Do List ******************************/

/**************************************End To Do List **************************/

#include "../include/TestSuite.h"

using namespace std;
using namespace std::chrono;

// Function audioTest
// Inputs:
//       &wave - An AudioWave object.
//       audioFileName - A string indicating the name of the audio file being loaded.
//       audioDir - A string indicating the path to the audio file directory.
//       sanName - A string indicating the name of the audio file without path information.
//       channels - An integer indicating the number of channels in the audio file.
//       fileName - A string indicating the file for data output.
//       path - A string indicating the path for output files.
//       debug - A boolean flag that controls debug output
// Outputs: None
// Purpose: This is a test function for loading audio
void audioTest(AudioWave &wave, string audioFileName, string audioDir, string sanName, int channels, bool fullPrecision, string fileName, string path, bool debug)
{
    ofstream outFile;        // A stream pointer for data output
    ofstream debugFile;      // A stream pointer for debug output

    outFile.open((path + "/" + fileName).c_str(), ios::app);
    outFile << timeStamp() << ":  Starting Audio Test" << endl;
    outFile.close();

    if (debug)
    {
        debugFile.open((path + "/audioLoaderTestSuiteDebug.txt").c_str(), ios::app);
        debugFile << "Audio Test Suite" << endl;
    }
 
    auto start = high_resolution_clock::now();
    loadAudio(wave, audioFileName, audioDir, sanName, channels, fullPrecision, path, debug);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    outFile.open((path + "/" + fileName).c_str(), ios::app);
    outFile << timeStamp() << ":  Audio Test completed in " << duration.count() << " us." << endl << endl;
    outFile << "\tLeft Channel Size:  " << wave.getLeftSize() << endl;
    outFile << "\tRight Channel Size:  " << wave.getRightSize() << endl;

    outFile << endl;
    outFile.close();

    if (debug)
    {
        debugFile << "Audio Loader Test complete." << endl;
 
        debugFile.close();
    }

    return;
}
// Function fftTest
// Inputs:
//       wave - An AudioWave object.
//       fileName - A string indicating the file for data output.
//       path - A string indicating the path for output files..
//       debug -  A boolean flag that controls debug output.
// Outputs: None
// Purpose: This is a test function for the FFT algorithm.
void fftTest(AudioWave &wave, string fileName, string path, bool debug)
{
    ofstream outFile;               // A stream pointer for data output
    ofstream debugFile;             // A stream pointer for debug output

    outFile.open((path + "/" + fileName).c_str(), ios::app);
    outFile << timeStamp() << ":  Starting FFT Test..." << endl;
    outFile.close();

    if (debug)
    {
        debugFile.open((path + "/FFTTestSuiteDebug.txt").c_str(), ios::app);
        debugFile << "FFT Test Suite" << endl;
    }

    auto start = high_resolution_clock::now();
    fft(wave, fileName, path, debug);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    outFile.open((path + "/" + fileName).c_str(), ios::app);
    outFile << timeStamp() << ":  FFT Test completed in " << duration.count() << " us." << endl;
    outFile.close();

    if (debug)
    {
        debugFile << "FFT Test Suite complete." << endl << endl;
        debugFile.close();
    }

    return;
}

// Function zeroCrossingTest
// Inputs:
//       &wave - An AudioWave object.
//       fileName - A string indicating the file for data output.
//       path - A string indicating the path for output files.
//       debug - A boolean flag that controls debug output.
// Outputs: None
// Purpose:  This is a test function for the zero crossing algorithm.
void zeroCrossingTest(AudioWave &wave, string fileName, string path, bool debug)
{
    ofstream outFile;               // A stream pointer for data output
    ofstream debugFile;             // A stream pointer for debug output

    outFile.open((path + "/" + fileName).c_str(), ios::app);
    outFile << timeStamp() << ":  Starting Zero Cross Test..." << endl;
    outFile.close();

    if (debug)
    {
        debugFile.open((path + "/zeroCrossTestSuiteDebug.txt").c_str(), ios::app);
        debugFile << "Zero Cross Test Suite" << endl;
    }

    auto start = high_resolution_clock::now();
    zeroCross(wave, fileName, path, debug);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    outFile.open((path + "/" + fileName).c_str(), ios::app);
    outFile << timeStamp() << ":  Zero Cross Test completed in " << duration.count() << " ms." << endl;
    outFile << endl << "\tZero Cross Database contains " << wave.getZSize(0) << " channels." << endl;
    outFile << "\tLeft Channel Zero Cross Size:  " << wave.getZSize(1) << endl;
    outFile << "\tRight Channel Zero Cross Size:  " << wave.getZSize(2) << endl << endl;
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

        debugFile << "Zero Cross Suite completed." << endl;

        debugFile.close();
    }

    return;
}
    
// Function spectrumFluxTest
// Inputs:
//       &wave - An AudioWave object.
//       fileName - A string indicating the file for data output.
//       path - A string indicating the path for output files.
//       debug - A boolean flag that controls the debug output.
// Outputs:  None
// Purpose:  This function tests the spectrum flux algorithm.
void spectrumFluxTest(AudioWave &wave, string fileName, string path, bool debug)
{
    ofstream outFile;                  // A stream pointer for data output.
    ofstream debugFile;                // A stream pointer for debug output.

    outFile.open((path + "/" + fileName).c_str(), ios::app);
    outFile << timeStamp() << ":  Starting Spectrum Flux Test..." << endl;
    outFile.close();

    if (debug)
    {
        debugFile.open((path + "/spectrumFluxTestDebug.txt").c_str(), ios::app);
        debugFile << "Spectrum Flux Test Suite:  " << endl << endl;
    }

    auto start = high_resolution_clock::now();
    spectralFlux(wave, fileName, path, debug);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    outFile.open((path + "/" + fileName).c_str(), ios::app);
    outFile << timeStamp() << ":  Spectrum Flux Test completed in " << duration.count() << " us." << endl;
    outFile << endl << "\tSpectrum Flux Results:" << endl;
    outFile << endl << "\tTotal Vector Size:  " << wave.getSFSize() << endl;
    outFile << "\tLeft Channel:  " << wave.getSpectrumFDataPoint(0) << endl;
 
    if (wave.getChannels() == 2)
        outFile << "\tRight Channel:  " << wave.getSpectrumFDataPoint(1) << endl;

    outFile << endl;

    outFile.close();

    if (debug)
    {
        debugFile << "Spectrum Flux Test Results:" << endl;
        debugFile << "Left Channel:  " << wave.getSpectrumFDataPoint(0) << endl;

        if (wave.getChannels() == 2)
            debugFile << "Right Channel:  " << wave.getSpectrumFDataPoint(1) << endl;

        debugFile << endl << "Spectrum Flux test complete." << endl;

        debugFile.close();
    }


    return;
}

// Function cepstrumTest
// Inputs:
//       &wave - An AudioWave object.
//       fileName - A string indicating the file for data output.
//       path - A string indicating the path for output files.
//       debug - A boolean flag that controls debug output.
// Outputs: None
// Purpose:  This function tests the cepstrum algorithm
void cepstrumTest(AudioWave &wave, string fileName, string path, bool debug)
{
    ofstream outFile;       // A stream pointer for data output.
    ofstream debugFile;     // A stream pointer for debug output.

    outFile.open((path + "/" + fileName).c_str(), ios::app);
    outFile << timeStamp() << ":  Starting Cepstrum Test..." << endl;
    outFile.close();

    if (debug)
    {
        debugFile.open((path + "/cepstrumTestSuiteDebug.txt").c_str(), ios::app);
        debugFile << "Cepstrum Test Suite" << endl;
    }

    auto start = high_resolution_clock::now();
    // cepstrum()
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    outFile.open((path + "/" + fileName).c_str(), ios::app);
    outFile << timeStamp() << ":  Cepstrum Test completed in " << duration.count() << " us." << endl;
    outFile << endl << "\tCepstrum database contains:  " << endl;

    outFile << endl;
    outFile.close();

    if (debug)
    {
        debugFile << "Cepstrum Test Suite complete." << endl;
        debugFile.close();
    }

    return;
}

// Function spectrumCentroidTest
// Inputs:
//       &wave - An AudioWave object.
//       fileName - A string indicating the file for data output.
//       path - A string indicating the path for output files.
//       debug - A boolean flag that controls the debug output.
// Outputs:  None
// Purpose:  This function tests the spectrum centroid algorithm.
void spectrumCentroidTest(AudioWave &wave, string fileName, string path, bool debug)
{
    ofstream outFile;                  // A stream pointer for data output.
    ofstream debugFile;                // A stream pointer for debug output.

    outFile.open((path + "/" + fileName).c_str(), ios::app);
    outFile << timeStamp() << ":  Starting Spectrum Centroid Test..." << endl;
    outFile.close();

    if (debug)
    {
        debugFile.open((path + "/spectrumCentroidTestDebug.txt").c_str(), ios::app);
        debugFile << "Spectrum Centroid Test Suite:  " << endl << endl;
    }

    auto start = high_resolution_clock::now();
    spectralCentroid(wave, fileName, path, debug);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    outFile.open((path + "/" + fileName).c_str(), ios::app);
    outFile << timeStamp() << ":  Spectrum Centroid Test completed in " << duration.count() << " us." << endl;
    outFile << endl << "\tSpectrum Centroid Results:" << endl;
    outFile << endl << "\tTotal Vector Size:  " << wave.getSCSize() << endl;
    outFile << "\tLeft Channel:  " << wave.getSpectrumCDataPoint(0) << endl;
 
    if (wave.getChannels() == 2)
        outFile << "\tRight Channel:  " << wave.getSpectrumCDataPoint(1) << endl;

    outFile << endl;

    outFile.close();

    if (debug)
    {
        debugFile << "Spectrum Centroid Test Results:" << endl;
        debugFile << "Left Channel:  " << wave.getSpectrumCDataPoint(0) << endl;

        if (wave.getChannels() == 2)
            debugFile << "Right Channel:  " << wave.getSpectrumCDataPoint(1) << endl;

        debugFile << endl << "Spectrum Centroid test complete." << endl;

        debugFile.close();
    }


    return;
}

// Function anniTest
// Inputs:
//       &wave - An AudioWave object.
//       fileName - A string indicating the file for data output.
//       path - A string indicating the path for output files.
//       debug - A boolean flag that controls the debug output.
// Outputs: None
// Purpose:  This function tests the performance of ANNI.
void anniTest(AudioWave &wave, string fileName, string path, bool debug)
{
    ofstream outFile;                        // A stream pointer for data output
    ofstream debugFile;                      // A stream pointer for debug output
 
    outFile.open((path + "/" + fileName).c_str(), ios::app);
    outFile << timeStamp() << ":  Starting ANNI Test..." << endl;
    outFile.close();

    if (debug)
    {
        debugFile.open((path + "/ANNITestSuiteDebug.txt").c_str(), ios::app);    
        debugFile << "ANNI Test Suite" << endl << endl;
    }

    auto start = high_resolution_clock::now();
    //ANNI()
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    outFile.open((path + "/" + fileName).c_str(), ios::app);
    outFile << timeStamp() << ":  ANNI Test completed in " << duration.count() << " us." << endl;
    outFile << endl << "\tANNI Results:  " << endl;

    outFile << endl;
    outFile.close();

    if (debug)
    {
        debugFile << "ANNI Test complete." << endl;
        debugFile.close();
    }

    return;
}
