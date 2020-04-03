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
//    &wave - An AudioWave object.
//    fileName - A string indicating the audio file to load.
//    audioDir - A string indicating the path to the audio file directory.
//    sanName - A string indicating the name of the audio file without path information.
//    channels - An integer indicating the number of channels in the audio file.
//    fullPrecision - A boolean flag specifying the precision of the output..
//    path - A string indicating the path for output files.
//    debug - A boolean flag that controls debug output.    
// Outputs:  None
// Purpose:  convertSound takes an audio file and converts it to a numerical representation.
static void convertSound(AudioWave &wave, string fileName, string audioDir, string sanName, int channels, bool fullPrecision, string path, bool debug)
{
    SNDFILE *infile = NULL;       // This will point to the audio file for conversion  
    SF_INFO sfinfo;               // Will contain the details of the audio file, such as frame rate, sample rate etc.
    float buf [BLOCKSIZE];        // Used to load the soundfile in chunks
    double dataPoint[channels];   // Temporary variable to store numerical representations of data channel
    complex<double> tempSig;      // Temporary variable to hold the complex number representation of the wave.s
    sf_count_t frames;            // Keep track of the number of frames
    int readcount;                // Keep track of whether there is a frame to be counted.
    ofstream outFile;             // Stream pointer for data output.
    ofstream debugFile;           // Stream pointer for debug output.
   
    if (debug)
    {
        debugFile.open((path + "/Debug/convertSoundDebug.txt").c_str(), ios::app);
        debugFile << "Convert sound called..." << endl;
        debugFile << "Filename = " << fileName << endl;
        debugFile << "Channels = " << channels << endl;
    }

    // Attempt to open the input file, make sure it is a readable format.   
    if((infile = sf_open(fileName.c_str(), SFM_READ, &sfinfo)) == NULL)
        cout << "Error opening audio file." << endl;

    // Determine the number of frames for processing the audio file
    frames = BLOCKSIZE / channels;

    if (debug)
        debugFile << "Frames = " << frames << endl;

    wave.setName(sanName);
    wave.setFrames(frames);

    while ((readcount = sf_readf_float (infile, buf, frames)) > 0)
    {      
        for (int i = 0; i < readcount; i++)
        {       
            for (int j = 0; j < channels; j++)
            {
                dataPoint[j] = buf[i * channels + j];

                /*
                if (save)
                {
                    if (fullPrecision)
                        outFile << OP_DBL_Digs-1 << ", " << buf[i * channels + j];
                    else
                        outFile << buf[i * channels + j];
                        //fprintf (outFile, " % 12.10f", buf [i * channels + j]);
                }
                */
            }

            // Always get channel 1
            if (dataPoint[0] < 0)
                tempSig = -polar(dataPoint[0], 0.0);
            else
                tempSig = polar(dataPoint[0], 0.0);

            wave.pushLeftChannel(tempSig);

            // Properly handle stereo sound.
            if (wave.getChannels() == 2)
            {
                if (dataPoint[1] < 0)
                    tempSig = -polar(abs(dataPoint[0]), 0.0);
                else
                    tempSig = polar(abs(dataPoint[0]), 0.0);

                wave.pushRightChannel(tempSig);
            }

            if (debug)
                debugFile << endl;
        } 
    }

    return;
}

// Function loadAudio
// Inputs:
//    wave - An AudioWave object.
//    fileName - A string indicating the audio file to load.
//    audioDir - A string indicating the path to the audio file directory.
//    sanName - A string indicating the name of the audio file without path information.
//    channels - An integer describing the number of channels in the audio file.
//    fullPrecision - A boolean flag specifying the precision of the output.
//    path - A string describing the path to the output directory
//    debug - A boolean flag that controls debug output.
// Outputs: None
// Purpose:  loadAudio is wrapper function for the convertSound function
void loadAudio(AudioWave &wave, string fileName, string audioDir, string sanName, int channels, bool fullPrecision, string path, bool debug)
{
    convertSound(wave, fileName, audioDir, sanName, channels, fullPrecision, path, debug);

    return;

}
