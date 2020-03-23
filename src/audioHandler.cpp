/* 
 *  File:    audioHandler.cpp
 *  Author:  Andrew Moore, Hue Truong, and Alex Reno
 *
 *  Created: February 9, 2020, 1:46 PM
 */

/**************************************Change Log *******************************/

// Created initial audio handling function.  - A.M. Feb 09 2020.
// Added convertSound function for converting wave to complex number - A.M. Feb 25 2020

/**************************************End Change Log ***************************/

/**************************************To Do List ******************************/
/**************************************End To Do List **************************/

#include "../include/audioHandler.h"

#define BLOCKSIZE 4096

#ifdef DBL_DECIMAL_DIG
        #define OP_DBL_Digs (DBL_DECIMAL_DIG)
#else
        #ifdef DECIMAL_DIG
                #define OP_DBL_Digs (DECIMAL_DIG)
        #else
                #define OP_DBL_Digs (DBL_DIG + 3)
        #endif
#endif

// Function convertSound
// Inputs:
//    fileName - A string containing the name of the audio file.
//    data - A vector of complex doubles that will hold the complex number representation of the audio file.
//    channels - An integer specifying the number of channels in the audio file, defaults to stereo.
//    fullPrecision - A boolean flag that controls to precision of the output, defaults to full precision.
// Outputs:  None
// Purpose:  convertSound takes an audio file and converts it to a numerical representation.
static void convertSound (string fileName,vector<complex<double> > &leftChannel,vector<complex<double> > &rightChannel,int channels,bool fullPrecision,bool debug, string path, string audioDir, string sanName)
{
    SNDFILE *infile = NULL;       // This will point to the audio file for conversion  
    SF_INFO sfinfo;               // Will contain the details of the audio file, such as frame rate, sample rate etc.
    float buf [BLOCKSIZE];        // Used to load the soundfile in chunks
    double dataPoint[channels];   // Temporary variable to store numerical representations of data channel
    complex<double> tempSig;      // Temporary variable to hold the complex number representation of the wave.s
    sf_count_t frames;            // Keep track of the number of frames
    int readcount;                // Keep track of whether there is a frame to be counted.
    ofstream outFile;             // Stores the numerical representation of the wave file for troubleshooting.
    string outputName;            // Will be used to generate the name of the output file.

    if (debug)
    {
        outputName =  audioDir + sanName + "_converted.txt";

        outFile.open(outputName, ios::out);
    }

    // Attempt to open the input file, make sure it is a readable format.   
    if((infile = sf_open(fileName.c_str(), SFM_READ, &sfinfo)) == NULL)
        cout << "Error opening audio file." << endl;

    // Determine the number of frames for processing the audio file
    frames = BLOCKSIZE / channels;

    while ((readcount = sf_readf_float (infile, buf, frames)) > 0)
    {      
        for (int i = 0; i < readcount; i++)
        {       
            for (int j = 0; j < channels; j++)
            {
                dataPoint[j] = buf[i * channels + j];

                if (debug)
                {
                    if (fullPrecision)
                        outFile << OP_DBL_Digs-1 << ", " << buf[i * channels + j];
                    else
                        outFile << buf[i * channels + j];
                        //fprintf (outFile, " % 12.10f", buf [i * channels + j]);
                }
            }

            if (channels == 1)  // Mono
            { 
                if (dataPoint[0] < 0)
                    tempSig = -polar(dataPoint[0], 0.0);
                else
                    tempSig = polar(dataPoint[0], 0.0);

               leftChannel.push_back(tempSig);
            }
            else  // Stereo, going to be twice the size
            {
                if (dataPoint[0] < 0)
                    tempSig = -polar(abs(dataPoint[0]), 0.0);
                else 
                    tempSig = polar(abs(dataPoint[0]), 0.0);

                leftChannel.push_back(tempSig);  // First channel

                if (dataPoint[1] < 0)
                    tempSig = -polar(abs(dataPoint[0]), 0.0);
                else
                    tempSig = polar(abs(dataPoint[0]), 0.0);

                rightChannel.push_back(tempSig); // Second channel
            }

            if (debug)
                outFile << endl;
        } 
    }

    if (debug)
        outFile.close(); 

    return;
}

// Function loadAudio
// Inputs:
//    fileName - A string containing the name of the audio file to be converted.
//    leftChannel - A vector of complex doubles that will contain the left channel of the audio wave.
//    rightChannel - A vector of complex doubles that will contain the right channel of the audio wave.
//    channels - An integer describing the number of channels in the audio file.
//    debug - A boolean flag that controls debug output
//    path - A string describing the path to the output directory
//    audioDir - A string describing the path to the individual audio directory
// Outputs: None
// Purpose:  loadAudio is wrapper function for the convertSound function
void loadAudio(string fileName, vector<complex<double> > &leftChannel, vector<complex<double> > &rightChannel, int channels,  bool debug, string path, string audioDir, string sanName)
{
    if (debug)
    {
        cout << "Audio loader called." << endl;
    }

    convertSound(fileName,leftChannel,rightChannel,channels,1,debug,path,audioDir,sanName);

    if (debug)
    {
        cout << "Audio loader returned." << endl;
    }

    return;

}
