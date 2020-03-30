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
        void setName(string);                                  // Set the fileName
        void setChannels(int);                                 // Set the number of channels
        void setFrames(int);                                   // Set the number of frames.
        void setZeroData();                                    // Set up the zeroData vector
        void setCepstrumData();                                // Set up the cepstrumData vector
        void setLeftFFT(vector<complex<double> >);             // Set the FFT of the left channel.
        void setRightFFT(vector<complex<double> >);            // Set the FFT of the right channel.

        // Updaters
        void pushZero(int, double);                            // Push a new value to zeroData
        void pushSpectrum(double);                             // Push a new value to spectrumData
        void pushCepstrum(int, double);                        // Push a new value to cepstrumData
        void pushLeftChannel(complex<double>);                 // Push a new value to leftChannel
        void pushRightChannel(complex<double>);                // Push a new value to rightChannel

        // Getters
        string getFileName();                                  // Returns the fileName
        int getChannels();                                     // Returns the value of channels
        int getFrames();                                       // Returns the value of frames
        double getZeroDataPoint(int, int);                     // Returns value from zeroData
        double getSpectrumDataPoint(int);                      // Returns value from spectrumData
        double getCepstrumDataPoint(int);                      // Returns value from cepstrumData
        complex<double> getChannelData(int, int);              // Returns a value from a channel.
        int getLeftSize();                                     // Returns left channel size.
        int getRightSize();                                    // Returns right channel size.
        int getZSize(int);                                     // Returns zeroCrossData size.
        int getSSize();                                        // Return spectrumData size.
        int getCSize(int);                                     // Return cepstrumData size.
        vector<complex<double> > getLeftChannel();             // Return leftChannel
        vector<complex<double> > getRightChannel();            // Return rightChannel
        vector<complex<double> > getLeftFFT();                 // Return left FFT
        vector<complex<double> > getRightFFT();                // Return right FFT
   
    private:

        // Data members

        // Wave specific member variables
        string fileName;                                       // Name of audio file.
        int channels;                                          // Number of channels.
        int frames;                                            // Number of frames
        vector<complex<double> > leftChannel;                  // Left channel
        vector<complex<double> > rightChannel;                 // Right channel
        vector<vector<double> > zeroData;                      // Zero cross data
        vector<double>  spectrumData;                          // Spectrum Flux data
        vector<vector<double> > cepstrumData;                  // Cepstrum data
        vector<complex<double> > leftFFT;                      // Left channel FFT
        vector<complex<double> > rightFFT;                     // Right channel FFT
};
#endif
