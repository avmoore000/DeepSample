/* 
 *  File:    AudioWave.cpp
 *  Author:  Andrew Moore, Hue Truong, and Alex Reno
 *
 *  Created: March 27, 2020, 12:30 PM
 */

/**************************************Change Log *******************************/

// Created the initial implementation for the AudioWave class - A.M. 27 Mar 2020
// Renamed Spectral Flux related functions and added Spectral Centroid functions - A.R. 9 Apr 2020

/**************************************End Change Log ***************************/

/**************************************To Do List ******************************/
/**************************************End To Do List **************************/

#include "../include/AudioWave.h"
#include <sys/stat.h>

// Function AudioWave
// Inputs:
//       audioName - A string indicating the full path to an audio file.an.
//       chan - A integer indicating the number of channels in the audio file.
// Outputs: None
// Purpose:  This is the constructor for an AudioWave object.
AudioWave::AudioWave(string audioName, int chan) 
{
    setName(audioName);
    setChannels(chan);
    setFrames(0);
    setZeroData();
    setCepstrumData();
    leftChannel.clear();
    rightChannel.clear();
    string dirName = "temp";

    mkdir(dirName.c_str(), 0777);
}

// Function ~AudioWave
// Inputs: None
// Outputs: None
// Purpose: This is the destructor for an AudioWave object.
AudioWave::~AudioWave()
{
    zeroData.clear();
    cepstrumData.clear();
    leftChannel.clear();
    leftFFT.clear();
    rightChannel.clear();
    rightFFT.clear();
    spectrumFData.clear();
    spectrumCData.clear();
}

// Function setName
// Inputs:
//       audioName - A string containing the fulle path to an audio file.
// Ouputs: None
// Purpose:  Initializes the fileName member variable.
void AudioWave::setName(string audioName)
{
    fileName = audioName;

    return;
}

// Function setSourceFiles
// Inputs: None
// Outputs: None
// Purpose:  Set up the source files and the source file vector for an object.
void AudioWave::setSourceFiles()
{
    ofstream outFile;    // Stream pointer for data output
    string dirName;      // The name of the directory to create the source files at.

    dirName = "temp";

    outFile.open(dirName + "/srcAudioFiles.txt", ios::out);
    sourceFiles.push_back((dirName + "/srcAudioFiles.txt"));

    for (int i = 0; i < leftChannel.size(); i++)
    {
        outFile  << real(leftChannel.at(i));

        if (channels == 2)
        {
            if (i < rightChannel.size())
                outFile << " " << real(rightChannel.at(i));
        }

        outFile << endl;
    }

    // Set up the source file for the left channel FFT
    outFile.close();
    outFile.open((dirName + "/srcFFT.txt").c_str(), ios::out);
    sourceFiles.push_back((dirName + "/srcFFT.txt"));

    for (int i = 0; i < leftFFT.size(); i++)
    {
        outFile << real(leftFFT.at(i));

        if (channels == 2)
        {
            if (i < rightFFT.size())
                outFile << " " << real(rightFFT.at(i));
        }

        outFile << endl;
    }

    // Set up the source file for the left zero cross
    outFile.close();
    outFile.open((dirName + "/srcZeroCross.txt").c_str(), ios::out);
    sourceFiles.push_back((dirName + "/srcZeroCross.txt"));

    for (int i = 0; i < zeroData[0].size(); i++)
    {
        outFile << zeroData[0].at(i);

        if (channels == 2)
        {
            if (i < zeroData[1].size())
                outFile << " " << zeroData[1].at(i);
        }

        outFile << endl;
    }

    // Set up the source file for the left spectrum flux
    outFile.close();
    outFile.open((dirName + "/srcSFlux.txt").c_str(), ios::out);
    sourceFiles.push_back((dirName + "/srcSFlux.txt"));

    outFile <<  spectrumFData[0];

    if (channels == 2)
        outFile << " " << spectrumFData[1];

    outFile << endl;

    // Set up the source file for the left cepstrum
    outFile.close();
    outFile.open((dirName + "/srcCepstrum.txt").c_str(), ios::out);
    sourceFiles.push_back((dirName + "/srcCepstrum.txt"));

    for (int i = 0; i < cepstrumData[0].size(); i++)
    {
        outFile << cepstrumData[0].at(i);

        if (channels == 2)
        {
            if (i < cepstrumData[1].size())
                outFile << " " << cepstrumData[1].at(i);
        }

        outFile << endl;
    }

    // Set up the source file for the left spectrum centroid
    outFile.close();
    outFile.open((dirName + "/srcLeftSCentroid.txt").c_str(), ios::out);
    sourceFiles.push_back((dirName + "/srcSCentroid.txt"));

    return;
}

// Function setChannels
// Inputs:
//       chan - An integer indicating the number of channels in the audio file.
// Outputs: None
// Purpose:  Initializes the channels member variable
void AudioWave::setChannels(int chan)
{
    channels = chan;

    return;
}

// Function setFrames
// Inputs:
//       numFrames - An integer indicating the number of frames in the audio file.
// Outputs: None
// Purpose:  Initializes the frames member variable.
void AudioWave::setFrames(int num)
{
    frames = num;

    return;
}

// Function setZeroData
// Inputs: 
// Outputs: None
// Purpose: Initializes the zeroData member variable 
void AudioWave::setZeroData()
{
    vector<double> dataChannel;

    zeroData.push_back(dataChannel);
    zeroData.push_back(dataChannel);

    return;
}

// Function setCepstrumData
// Inputs: None
// Outputs: None
// Purpose: Initializes the cepstrumData member variable
void AudioWave::setCepstrumData()
{
    vector<double> data;

    cepstrumData.push_back(data);
    cepstrumData.push_back(data);

    return;
}

// Function setLeftFFT
// Inputs:
//       fft - A vector of complex double vectors containing the left channel FFT
// Outputs: None
// Purpose:  Set the value of the leftFFT member vector
void AudioWave::setLeftFFT(vector<complex<double> > fft)
{
    leftFFT = fft;

    return;
}

// Function setRightFFT
// Inputs:
//       fft - A vector of complex double vectors containing the right channel FFT
// Outputs: None
// Purpose:  Set the value of the rightFFT member vector
void AudioWave::setRightFFT(vector<complex<double> > fft)
{
    rightFFT = fft;
 
    return;
}

// Functon pushZero
// Inputs:
//       chan - An integer indicating the channel being pushed to.
//       data - A double containing the data to add.
// Outputs: None
// Purpose:  Push new data onto the zeroData vector.
void AudioWave::pushZero(int chan, double data)
{
    zeroData[chan].push_back(data);

    return;
}

// Function pushSpectrumF
// Inputs:
//       data - A double containing the data to add.
// Outputs: None
// Purpose:  Push new data onto the spectrumFData vector.
void AudioWave::pushSpectrumF(double data)
{
    spectrumFData.push_back(data);

    return;
}

// Function pushCepstrum
// Inputs:
//       chan - An integer indicating the channel being pushed to.
//       data - A double containing the data to add.
// Outputs: None
// Purpose:  Push new data onto the cepstrumData vector.
void AudioWave::pushCepstrum(int chan, double data)
{
    return;
}

// Function pushSpectrumC
// Inputs:
//       data - A double containing the data to add.
// Outputs: None
// Purpose:  Push new data onto the spectrumCData vector.
void AudioWave::pushSpectrumC(double data)
{
    spectrumCData.push_back(data);

    return;
}

// Function pushLeftChannel
// Inputs:
//       data - A complex double containing the data to add.
// Outputs: None
// Purpose:  Push new data onto the leftChannel vector.
void AudioWave::pushLeftChannel(complex<double> data)
{
    leftChannel.push_back(data);

    return;
}

// Function pushRightChannel
// Inputs:
//       data - A complex double containing the data to add.
// Outputs: None
// Purpose:  Push new data onto the rightChannel vector.
void AudioWave::pushRightChannel(complex<double> data)
{
    rightChannel.push_back(data);

    return;
}

// Function getFileName
// Inputs: None
// Outputs:
//        fileName - A string containing the name of the audio file.
// Purpose:  Return the value of the fileName member variable.
string AudioWave::getFileName()
{
    return fileName;
}

// Function getSourceFile
// Inputs:
//       index - An integer indicating the source file to look up.
// Outputs:
//        sourceFile - A string containing the filename and path of the source file.
// Purpose:  Return the name and path of a source file for graphing.
string AudioWave::getSourceFile(int index)
{
    return sourceFiles[index];
}

// Function getChannels
// Inputs: None
// Outputs:
//        channels - An integer indicating the number of channels in the audio file.
// Purpose:  Return the value of the channels member variable
int AudioWave::getChannels()
{
    return channels;
}

// Function getLeftFFTSize
// Inputs: None
// Outputs:
//        size - The size of the left fft
// Purpose:  Return the size fo the left fft
int AudioWave::getLeftFFTSize()
{
    return leftFFT.size();
}

// Function getRightFFTSize
// Inputs: None
// Ouputs:
//       size - The size of the right fft
// Purpos:  Return the size of the right fft
int AudioWave::getRightFFTSize()
{
    return rightFFT.size();
}

// Function getFrames
// Inputs: None
// Outputs:
//        frames - An integer indicating the number of frames in the audio file.
// Purpose:  Return the value of the frames member variable
int AudioWave::getFrames()
{
    return frames;
}

// Function getChannelSize
// Inputs:
//       chan - An integer indicating the channel to look at.
// Outputs: cSize - An integer containing the size of the channel.
// Purpose:  Return the size of a channel in the audio wave object.
int AudioWave::getChannelSize(int chan)
{
    int cSize;

    cSize = 0;

    switch(chan)
    {
        case 1:
        {
            cSize = leftChannel.size();
            break;
        }
        case 2:
        {
            cSize = rightChannel.size();
            break;
        }
        default:
        {
            cout << "Invalid channel requested." << endl;
            break;
        }
    }
  
    return cSize;
}
// Function getLeftSize
// Inputs: None
// Outputs:
//        size - The size of the left channel.
// Purpose:  Return the size of the left channel member vector.
int AudioWave::getLeftSize()
{
    return leftChannel.size();
}

// Function getRightSize
// Inputs: None
// Outputs:
//        size - The size of the right channel.
// Purpose:  Return the size of the right channel member vector.
int AudioWave::getRightSize()
{
    return rightChannel.size();
}

// Function getZSize
// Inputs:
//       chan - An integer indicating the channel to look up the size of.
// Outputs: size - An integer describing the size.
// Purpose:  Return the size of the zeroData vector and its elements.
int AudioWave::getZSize(int chan)
{
    int size;    // Will hold the size of the channel or vector.

    size = 0;

    switch(chan)
    {
        case 0:  // Return the size of the whole vector
        {
            size = zeroData.size();
            break;
        }
        case 1:  // Return the size of the left channel.
        {
            size = zeroData[0].size();
            break;
        }
        case 2:
        {
            if (channels == 2)
                size = zeroData[1].size();
            break;
        }
        default:
        {
            size = -1;
            break;
        }
    }

    return size;
}

// Function  getSFSize
// Inputs: None
// Outputs: size - An integer describing the size.
// Purpose:  Return the size of the spectrumFData vector
int AudioWave::getSFSize()
{
    return spectrumFData.size();
}

// Function getCSize
// Inputs:
//       chan - An integer indicating the channel to look up the size of.
// Outputs: size - An integer descibing the size.
// Purpose:  Return the size of the cepstrumData vector and its elements.
int AudioWave::getCSize(int chan)
{
    int size;

    size = 0;

    switch(chan)
    {
        case 0:
        {
            size = cepstrumData.size();
            break;
        }
        case 1:
        {
            size = cepstrumData[0].size();
            break;
        }
        case 2:
        {
            if (channels == 2)
                size = cepstrumData[1].size();
            break;
        }
        default:
        {
            size = -1;
            break;
        }
    }

    return size;
}

// Function  getSCSize
// Inputs: None
// Outputs: size - An integer describing the size.
// Purpose:  Return the size of the spectrumCData vector
int AudioWave::getSCSize()
{
    return spectrumCData.size();
}

// Function getLeftChannel
// Inputs: None
// Outputs: leftChannel - A vector of complex doubles representing the left channel of the wave.
// Purpose:  Return the leftChannel member vector.
vector<complex<double> > AudioWave::getLeftChannel()
{
    return leftChannel;
}

// Function getRightChannel
// Inputs: None
// Outputs:
//        rightChannel - A vector of complex doubles representing the right channel of the wave.
// Purpose:  Returnthe rightChannel member vector
vector<complex<double> > AudioWave::getRightChannel()
{
    return rightChannel;
}

// Function getLeftFFT
// Inputs: None
// Outputs:
//        leftFFT - A vector of complex double vectors containing the FFT of the left channel.
// Purpose:  Return the leftFFT member vector
vector<complex<double> > AudioWave::getLeftFFT()
{
    return leftFFT;
}

// Function getRightFFT
// Inputs: None
// Outputs:
//        rightFFT - A vector of complex double vectors containing the FFT of the right channel.
// Purpose:  Return the rightFFT member vector.
vector<complex<double> > AudioWave::getRightFFT()
{
    return rightFFT;
}

// Function getChannelData
// Inputs:
//       channel - An integer indicating the channel to pull data from.
//       index - An integer indicating which data point to return.
// Outputs:  value - A complex double containing the requested data.
// Purpose:  Returns a value from a specified channel.
complex<double> AudioWave::getChannelData(int channel, int index)
{
    complex<double> value;

    value = NULL;

    switch(channel)
    {
        case 0:
        {
            value = leftChannel[index];
            break;
        }
        case 1:
        {
            value = rightChannel[index];
            break;
        }
        default:
        {
            cout << "Invalid channel." << endl;
            break;
        }
    }

    return value;
}

    
// Function getZeroDataPoint
// Inputs:
//       chan - An integer indicating which channel to pull the data from.
//       index - An integer indicating which data point to return.
// Outputs: dataPoint - A double containing the datapoint.
// Purpose:  Returns the datapoint from the indicated channel and location.
double AudioWave::getZeroDataPoint(int chan, int index)
{
    double dataPoint;

    dataPoint = NULL;

    switch(chan)
    {
        case 1:
        {
            if (index < zeroData[0].size())
                dataPoint = zeroData[0][index];
            break;
        }
        case 2:
        {
            if (channels == 2)
            {
                if (index < zeroData[1].size())
                    dataPoint = zeroData[1][index];
            }
            
            break;
        }
        default:
            break;
    }
  
    return dataPoint; 
}

// Function getSpectrumFDataPoint
// Inputs:
//       chan - An integer indicating which channel to pull the data from.
// Outputs: dataPoint - A double containing the datapoint.
// Purpose: Returns the datapoint from the indicated channel and location.
double AudioWave::getSpectrumFDataPoint(int chan)
{
    double dataPoint;

    dataPoint = NULL;

    if (chan < spectrumFData.size())
        dataPoint = spectrumFData.at(chan);

    return dataPoint;
}

// Function setYMaximums
// Inputs: None
// Outputs: None
// Purpose: Set up the max values of the data vectors
void AudioWave::setYMaximums()
{
    double tMax;

    tMax = 0;

    // Set up the max of audio wave channels
    for (int i = 0; i < leftChannel.size(); i++)
    {
        if (real(leftChannel.at(i)) > tMax)
            tMax = real(leftChannel.at(i));
    }

    max.push_back(tMax);
    tMax = 0;

    if (channels == 2)
    {
        for (int i = 0; i < rightChannel.size(); i++)
        {
            if (real(rightChannel.at(i)) > tMax)
                tMax = real(rightChannel.at(i));
        }

        max.push_back(tMax);
        tMax = 0;
    }

    // Set up the max of fft vector
   
    for (int i = 0; i < leftFFT.size(); i++)
    {
        if (real(leftFFT.at(i)) > tMax)
            tMax = real(leftFFT.at(i));
    }
    
    max.push_back(tMax);
    tMax = 0;

    if (channels == 2)
    {
        for (int i = 0; i < rightFFT.size(); i++)
        {
            if (real(rightFFT.at(i)) > tMax)
                tMax = real(rightFFT.at(i));
        }
 
        max.push_back(tMax);
        tMax = 0;
    }

    // Set up max of zeroData

    for (int i = 0; i < zeroData[0].size(); i++)
    {
        if (real(zeroData[0].at(i)) > tMax)
            tMax = real(zeroData[0].at(i));
    }
   
        max.push_back(tMax);
        tMax = 0;

    if (channels == 2)
    {
        for (int i = 0; i < zeroData[1].size(); i++)
        {
            if (real(zeroData[1].at(i)) > tMax)
                tMax = real(zeroData[1].at(i));
        }

        max.push_back(tMax);
        tMax = 0;
    }
}

// Function setYMinimums
// Inputs: None
// Outputs: None
// Purpose:  Set up the y minimums for datasets
void AudioWave::setYMinimums()
{
    double tMin;    // Will contain the y minimum

    tMin = 0;

    // Set the y-min for the audio waves

    for (int i = 0; i < leftChannel.size(); i++)
    {
        if (i == 0)
            tMin = real(leftChannel.at(i));
        else if (real(leftChannel.at(i)) < tMin)
            tMin = real(leftChannel.at(i));
        
    }

    min.push_back(tMin);
    tMin = 0;

    if (channels == 2)
    {
        for (int i = 0; i < rightChannel.size(); i++)
        {
            if (i == 0)
                tMin = real(rightChannel.at(i));
            else if (real(rightChannel.at(i)) < tMin)
                tMin = real(rightChannel.at(i));
        }

        min.push_back(tMin);
        tMin = 0;
    }

    // Set the y-min for the fft

    for (int i = 0; i < leftFFT.size(); i++)
    {
        if (i == 0)
            tMin = real(leftFFT.at(i));
        else if (real(leftFFT.at(i)) < tMin)
            tMin = real(leftFFT.at(i));
    }

    min.push_back(tMin);
    tMin = 0;
 
    if (channels == 2)
    {
        for (int i = 0; i < rightFFT.size(); i++)
        {
            if ((i == 0) || (real(rightFFT.at(i)) < tMin))
                tMin = real(rightFFT.at(i));
        }

        min.push_back(tMin);
        tMin = 0;
    }

    // Set the y-min for zeroData

    for (int i = 0; i < zeroData[0].size(); i++)
    {
        if ((i == 0) || (zeroData[0].at(i) < tMin))
            tMin = zeroData[0].at(i);
    }
 
    min.push_back(tMin);
    tMin = 0;

    if (channels == 2)
    {
        for (int i = 0; i < zeroData[1].size(); i++)
        {
            if ((i == 0) || (zeroData[1].at(i) < tMin))
                tMin = zeroData[1].at(i);
        }
  
        min.push_back(tMin);
        tMin = 0;
    }
}

// Function getYMaximum
// Inputs:
//       alg - An integer indicating the algorithm to look up.
//       chan - An integer indicating the channel to look up.
// Outputs:
//        maxi - A double containing the maximum of the dataset.
// Purpose:  Return the maximum of a dataset
double AudioWave::getYMaximum(int alg, int chan)
{
    double maxi;

    switch(alg)
    {
        case 0:  // Audio data
        {
            if (chan == 1)
                maxi = max[0];
            else if (chan == 2)
            {
                if (channels == 2)
                    maxi = max[1];
                else
                    cout << "Invalid channel lookup." << endl;
            }

            break;
        }
        case 1: // FFT data
        {
            if (chan == 1)
            {
                if (channels == 1)
                    maxi = max[1];
                else
                    maxi = max[2];
            }
            else if (chan == 2)
            {
                if (channels == 2)
                    maxi = max[3];
                else
                    cout << "Invalid channel lookup." << endl;
            }

            break;
        }
        case 2:  // Zerocross data
        {
            if (chan == 1)
            {
                if (channels == 1)
                    maxi = max[2];
                else
                    maxi = max[4];
            }
            if (chan == 2)
            { 
                if (channels == 2)
                    maxi = max[5];
                else
                    cout << "Invalid channel lookup." << endl;
            }

            break;
        }
        case 3:  // Spectrum data
        {
            if (chan == 1)
                maxi = spectrumFData[0];
            else if (chan == 2)
                maxi = spectrumFData[1];
      
            break;
        }
        default:
        {
            cout << "Unsupported algorithm for maximum." << endl;
            break;
        }
    } 

    return maxi;
}

// Function getYMinimum
// Inputs:
//       alg - An integer indicating the algorithm to look up.
//       chan - An integer indicating the channel to look up.
// Outputs:
//        mini - A double containing the minimum of a dataset.
// Purpose:  Return the minimum of a dataset
double AudioWave::getYMinimum(int alg, int chan)
{
    double mini;

    switch(alg)
    {
        case 0:  // Audio data
        {
            if (chan == 1)
                mini = min[0];
            else if (chan == 2)
            { 
                if (channels == 2)
                    mini = min[1];
                else
                    cout << "Invalid channel lookup." << endl;
            }
            
            break;
        }
        case 1: // FFT
        {
            if (chan == 1)
            {
                if (channels == 1)
                    mini = min[1];
                else if (channels == 2)
                    mini = min[2];
            }
            else if (chan == 2)
            { 
                if (channels == 2)
                    mini = min[3];
                else
                    cout << "Invalid channel lookup." << endl;
            }

            break;
        }
        case 2: // Zero cross
        {
            if (chan == 1)
            {
                if (channels == 1)
                    mini = min[2];
                else if (channels == 2)
                    mini = min[4];
            }
            else if (chan == 2)
            {
                if (channels == 2)
                    mini = min[5];
                else
                    cout << "Invalid channel lookup." << endl;
            }

            break;
        }
        default:
        {
            cout << "Unsupported algorithm for y minimum" << endl;
            break;
        }
    }

    return mini;
}

// Function getCepstrumDataPoint
// Inputs:
//       chan - An integer indicating which channel to pull the data from.
//       index - An integer indicating the index to access.
// Outputs: dataPoint - A double containing the datapoint
// Purpose: Returns the datapoint from the indicated channel and location.
double AudioWave::getCepstrumDataPoint(int chan)
{
    double dataPoint;
  
    dataPoint = NULL;

    cout << "The cepstrum function is still being developed." << endl;

    return dataPoint;
}

// Function getSpectrumCDataPoint
// Inputs:
//       chan - An integer indicating which channel to pull the data from.
// Outputs: dataPoint - A double containing the datapoint.
// Purpose: Returns the datapoint from the indicated channel and location.
double AudioWave::getSpectrumCDataPoint(int chan)
{
    double dataPoint;

    dataPoint = NULL;

    if (chan < spectrumCData.size())
        dataPoint = spectrumCData.at(chan);

    return dataPoint;
}
