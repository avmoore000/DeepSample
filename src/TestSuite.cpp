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
//       leftChannel - A vector of complex doubles describing the left side of the audio wave.
//       rightChannel - A vector of complex doubles describing the right side of the audio wave.
//       channels - An integer describing the number of channels in the audio file.
//       debug - A boolean flag that controls debug output
//       fileName - A string containing the filname of hte output file
//       filePath - A string containg the directory for file output
// Outputs: None
// Purpose:  This is a test function for the zero crossing algorithm.
void zeroCrossingTest(vector<complex<double> > leftChannel,vector<complex<double> > rightChannel,int channels,bool debug,string fileName,string filePath)
{
    int m = 2;                                             // Specify number of rows in vector
    int n = leftChannel.size();                            // Specify number of columns of vector
    vector<float> dataPoints(n,0);                         // A vector that will contain the data points for each channel	
    vector<vector<float> > zeroCrossResults(2,dataPoints);        // Holds the datapoints for both waves in a 2D vector 
    string outputFileName;                                 // Name of the file to output to
    ofstream output;                                       // Points to the file to output results

    outputFileName = filePath + "/" + fileName;
  
    output.open(outputFileName.c_str(), ios::app);

    auto start = high_resolution_clock::now();
    zeroCross(leftChannel,rightChannel,zeroCrossResults,channels,debug,filePath);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Zero Crossing Algorithm completed in " << duration.count() << " ms." << endl;
    output << "Zero Crossing Algorithm completed in " << duration.count() << " ms." << endl << endl;

    if (debug)
    {
        output << "Zero Crossing Results" << endl << endl;

        output << "Left Channel Signal Array:  " << endl;
        output << "[" << endl;

        for (int i = 0; i < leftChannel.size()-1; i++)
        {
            output << leftChannel[i] << " ";

	    if ((i != 0) && ((i%10) == 0))
	        output << endl;
        }
        output << endl << "]" << endl << endl;

        if (channels == 2)
        {
            output << "Right Channel Signal Array:  " << endl << "[" << endl;

            for (int i = 0; i < rightChannel.size(); i++)
            {
                output << rightChannel[i] << " ";

                if ((i != 0) && ((i%10) == 0))
                    output << endl;
            }

            output << endl << "]" << endl << endl;
        }
    }
    
    output << "ZeroCrossTest Left Channel:  " << endl;
    output << "[" << endl;

    for (int i = 0; i < leftChannel.size(); i++)
    {
        output << zeroCrossResults[0][i] << " ";
          
        if ((i > 0) && ((i % 50) == 0))
            output << endl;
    }
    output << endl << "]";

    if (channels == 2)
    { 
        output << endl << endl << "ZeroCrossTest Right Channel:" << endl << "[" << endl;

        for (int i = 0; i < zeroCrossResults.size(); i++)
        {
            for (int j = 0; j < leftChannel.size(); j++)
            {
                output << zeroCrossResults[i][j] << " ";

                if ((j > 0) && ((j % 50) == 0))
                    output << endl;
            }
        }
    }
    
    output << endl << "]" << endl << endl;

    output.close();
    
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
    spectralFlux(leftChannel,rightChannel,spectralFluxResults,channels,debug,path);
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
    loadAudio(audioName,leftChannel,rightChannel,channels,debug);

    // Perform the fft on the audio
    fft(leftChannel,debug,path);

    if (channels == 2)
        fft(rightChannel,debug,path);

    // Get zero crossing vector for audio file

    vector<float> dataPoints(leftChannel.size(),0);            // A vector containing datapoints for each channel
    vector<vector<float> > zeroCrossResults(2,dataPoints);     // A vector containing zero crossing results

    zeroCross(leftChannel,rightChannel,zeroCrossResults,channels,debug,path);

    // Get the spectrum flux for audio file
    spectralFlux(leftChannel,rightChannel,spectralFluxResults,channels,debug,path);


    auto start = high_resolution_clock::now();
    ANNI(zeroCrossResults,spectralFluxResults,path,audioName,channels,1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop-start);

    cout << "ANNI completed in " << duration.count() << " ms." << endl;
    outputFile << "ANNI completed running with " << audioName << " as input in " 
               << duration.count() << " ms." << endl << endl;

    return;
}
