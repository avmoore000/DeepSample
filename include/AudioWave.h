/* 
 *  File:    AudioWave.h
 *  Author:  Andrew Moore, Hue Truong, and Alex Reno
 *
 *  Created: March 27, 2020, 12:00 PM
 */

/**************************************Change Log *******************************/

// Created the initial header for the AudioWave class - A.M. 27 Mar 2020

/**************************************End Change Log ***************************/

/**************************************To Do List ******************************/
/**************************************End To Do List **************************/

#include <iostream>
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
        void setRightFFT(vector<complex<double> >)             // Initialize the rightFFT member
        void setZeroData();                                    // Initialize the zeroData member

        // Updaters
        void pushCepstrum(int, double);                        // Push a value to cepstrumData
        void pushLeftChannel(complex<double>);                 // Push a value to leftChannel
        void pushRightChannel(complex<double>);                // Push a value to rightChannel
        void pushSpectrum(int,double);                         // Push a value to spectrumData
        void pushZero(int, double);                            // Push a value to zeroData

        // Getters
        string getFileName();                                  // Return fileName
        vector<complex<double> > getLeftChannel();             // Return leftChannel
        vector<complex<double> > getLeftFFT();                 // Return leftFFT
        vector<complex<double> > getRightChannel();            // Return rightChannel
        vector<complex<double> > getRightFFT();                // Return rightFFT
        complex<double> getChannelData(int, int);              // Return value from channel
        double getCepstrumDataPoint(int);                      // Return value from cepstrumData
        double getFFTDataPoint(int,int);                       // Return value from FFT data
        double getSpectrumDataPoint(int);                      // Return value from spectrumData
        double getZeroDataPoint(int, int);                     // Return value from zeroData
        int getChannels();                                     // Return channels
        int getChannelSize(int);                               // Return size of channel
        int getFrames();                                       // Return frames
        int getCSize(int);                                     // Return cepstrumData size
        int getLeftSize();                                     // Return leftChannel size
        int getRightSize();                                    // Return rightChannel size
        int getSSize();                                        // Return spectrumData size
        int getZSize();                                        // Return zeroData size     
      
    private:

        // Data members

        // Wave specific member variables
        string fileName;                                       // Name of audio file.
        vector<vector<double> > zeroData;                      // Zero cross data
        vector<vector<double> > cepstrumData;                  // Cepstrum data
        vector<complex<double> > leftChannel;                  // Left channel
        vector<complex<double> > leftFFT;                      // Left channel FFT
        vector<complex<double> > rightChannel;                 // Right channel.
        vector<complex<double> > rightFFT;                     // Right channel FFT
        vector<double>  spectrumData;                          // Spectrum Flux data
        int channels;                                          // Number of channels
        int frames;                                            // Number of frames
};
#endif
