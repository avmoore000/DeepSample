/* 
 *  File:    AudioWave.h
 *  Author:  Andrew Moore, Hue Truong, and Alex Reno
 *
 *  Created: March 27, 2020, 12:00 PM
 */

/**************************************Change Log *******************************/

// Created the initial header for the AudioWave class - A.M. 27 Mar 2020
// Renamed Spectral Flux related functions and added Spectral Centroid functions - A.R. 9 Apr 2020

/**************************************End Change Log ***************************/

/**************************************To Do List ******************************/
/**************************************End To Do List **************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
#include <string>
using namespace std;

#ifndef AudioWave_H
#define AudioWave_H

// Class AudioWave
class AudioWave
{
    public:

        AudioWave(string, int);                                // Class constructor
        ~AudioWave();                                          // Class destructor

        // Initializers
        void setCepstrumData();                                // Initialize the cepstrumData member
        void setChannels(int);                                 // Initialize the channels member
        void setFrames(int);                                   // Initialize the frames member
        void setName(string);                                  // Initialize the fileName member
        void setLeftFFT(vector<complex<double> >);             // Initialize the leftFFT member
        void setRightFFT(vector<complex<double> >);            // Initialize the rightFFT member
        void setYMaximums();                                   // Initialize the max member
        void setYMinimums();                                   // Initialize the min member
        void setZeroData();                                    // Initialize the zeroData member
        void setSourceFiles();                                 // Initialize the sourceFiles member

        // Updaters
        void pushCepstrum(int, double);                        // Push a value to cepstrumData
        void pushLeftChannel(complex<double>);                 // Push a value to leftChannel
        void pushRightChannel(complex<double>);                // Push a value to rightChannel
        void pushSpectrumF(double);                            // Push a value to spectrumFData
        void pushSpectrumC(double);                            // Push a value to spectrumCData
        void pushZero(int, double);                            // Push a value to zeroData

        // Getters
        string getFileName();                                  // Return fileName
        string getSourceFile(int);                             // Return name of source file.
        vector<complex<double> > getLeftChannel();             // Return leftChannel
        vector<complex<double> > getLeftFFT();                 // Return leftFFT
        vector<complex<double> > getRightChannel();            // Return rightChannel
        vector<complex<double> > getRightFFT();                // Return rightFFT
        complex<double> getChannelData(int, int);              // Return value from channel
        double getCepstrumDataPoint(int);                      // Return value from cepstrumData
        double getFFTDataPoint(int,int);                       // Return value from FFT data
        double getSpectrumFDataPoint(int);                     // Return value from spectrumFData
        double getSpectrumCDataPoint(int);                     // Return value from spectrumCData
        double getYMaximum(int, int);                          // Return maximum value of a dataset.
        double getYMinimum(int, int);                          // Return minimum value of a dataset.
        double getZeroDataPoint(int, int);                     // Return value from zeroData
        int getChannels();                                     // Return channels
        int getChannelSize(int);                               // Return size of channel
        int getFrames();                                       // Return frames
        int getCSize(int);                                     // Return cepstrumData size
        int getLeftSize();                                     // Return leftChannel size
        int getRightSize();                                    // Return rightChannel size
        int getLeftFFTSize();                                  // Return size of left fft
        int getRightFFTSize();                                 // Return size of right fft
        int getSFSize();                                       // Return spectrumFData size
        int getSCSize();                                       // Return spectrumCData size
        int getZSize(int);                                     // Return zeroData size     
      
    private:

        // Data members

        // Wave specific member variables
        string fileName;                                       // Name of audio file.
        vector<vector<double> > zeroData;                      // Zero cross data
        vector<vector<double> > cepstrumData;                  // Cepstrum data
        vector<string > sourceFiles;                           // Graphing source files.
        vector<complex<double> > leftChannel;                  // Left channel
        vector<complex<double> > leftFFT;                      // Left channel FFT
        vector<complex<double> > rightChannel;                 // Right channel.
        vector<complex<double> > rightFFT;                     // Right channel FFT
        vector<double>  spectrumFData;                         // Spectrum Flux data
        vector<double>  spectrumCData;                         // Spectrum Centroid data
        int channels;                                          // Number of channels
        int frames;                                            // Number of frames

        vector<double> max;                                    // Maximums of the data vectors
        vector<double> min;                                    // Minimums of the data vectors
};
#endif
