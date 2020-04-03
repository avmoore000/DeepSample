/* 
 *  File:    AudioWave.cpp
 *  Author:  Andrew Moore, Hue Truong, and Alex Reno
 *
 *  Created: March 27, 2020, 12:30 PM
 */

/**************************************Change Log *******************************/

// Created the initial implementation for the AudioWave class - A.M. 27 Mar 2020

/**************************************End Change Log ***************************/

/**************************************To Do List ******************************/
/**************************************End To Do List **************************/

#include "../include/AudioWave.h"

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
    
    vector<string> file;

    sourceFiles.push_back(file);
    sourceFiles.push_back(file);
}

// Function ~AudioWave
// Inputs: None
// Outputs: None
// Purpose: This is the destructor for an AudioWave object.
AudioWave::~AudioWave()
{
    system(("rm -rf temp").c_str());
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

    // Set up the source file for the left channel
   
    system(("mkdir " + dirName).c_str());

//    system(mkdir(dirName.c_str(), 0777));

    outFile.open(dirName + "/srcLeftChan.txt", ios::out);
    sourceFiles[0].push_back((dirName + "/srcLeftChan.txt"));

    for (int i = 0; i < leftChannel.size(); i++)
    {
        outFile << i << " " << real(leftChannel.at(i)) << endl;
    }

    // Set up the source file for the left channel FFT
    outFile.close();
    outFile.open((dirName + "/srcLeftFFT").c_str(), ios::out);
    sourceFiles[0].push_back((dirName + "/srcLeftFFT"));

    for (int i = 0; i < leftFFT.size(); i++)
    {
        outFile << i << real(leftFFT.at(i)) << endl;
    }

    // Set up the source file for the left zero cross
    outFile.close();
    outFile.open((dirName + "/srcLeftZeroCross").c_str(), ios::out);
    sourceFiles[0].push_back((dirName + "/srcLeftZeroCross"));

    for (int i = 0; i < zeroData[0].size(); i++)
    {
        outFile << i << " " << zeroData[0].at(i) << endl;
    }

    // Set up the source file for the left spectrum flux
    outFile.close();
    outFile.open((dirName + "/srcLeftSFlux").c_str(), ios::out);
    sourceFiles[0].push_back((dirName + "/srcLeftSFlux"));

    outFile << "1 " << spectrumData[0] << endl;

    cout << "Making it to the cepstrum setup" << endl;

    // Set up the source file for the left cepstrum
    outFile.close();
    outFile.open((dirName + "/srcLeftCepstrum").c_str(), ios::out);
    sourceFiles[0].push_back((dirName + "/srcLeftCepstrum"));

    for (int i = 0; i < cepstrumData[0].size(); i++)
    {
        outFile << i << " " << cepstrumData[0].at(i) << endl;
    }

    cout << "Making it past the cepstrum setup" << endl;
 
    // Set up the source file for the left spectrum centroid
    outFile.close();
    outFile.open((dirName + "/srcLeftSCentroid").c_str(), ios::out);
    sourceFiles[0].push_back((dirName + "/srcLeftSCentroid"));

    // Set up sources for the right channel
    if (channels == 2)
    {
        // Set up source file for right channel
        outFile.close();
        outFile.open((dirName + "/srcRightChannel").c_str(), ios::out);
        sourceFiles[1].push_back((dirName + "/srcRightChannel"));

        for (int i = 0; i < rightChannel.size(); i++)
        {
            outFile << i << " " << real(rightChannel.at(i)) << endl;
        }

        // Set up source file for right FFT
        outFile.close();
        outFile.open((dirName + "/srcRightFFT").c_str(), ios::out);
        sourceFiles[1].push_back((dirName + "/srcRightFFT"));

        for (int i = 0; i < rightFFT.size(); i++)
        {
            outFile << i << " " << real(rightFFT.at(i)) << endl;
        }

        // Set up source file for right zero cross
        outFile.close();
        outFile.open((dirName + "/srcRightZeroCross").c_str(), ios::out);
        sourceFiles[1].push_back((dirName + "/srcRightZeroCross"));

        for (int i = 0; i < zeroData[1].size(); i++)
        {
            outFile << i << " " << zeroData[1].at(i) << endl;
        }

        // Set up source file for right spectral flux
        outFile.close();
        outFile.open((dirName + "/srcRightSFlux").c_str(), ios::out);
        sourceFiles[1].push_back((dirName + "/srcRightSFlux"));

        outFile << "1 " << spectrumData[1] << endl;

        // Set up source file for right cepstrum
        outFile.close();
        outFile.open((dirName + "/srcRightCepstrum").c_str(), ios::out);
        sourceFiles[1].push_back((dirName + "/srcRightCepstrum"));

        for (int i = 0; i < cepstrumData[1].size(); i++)
        {
            outFile << i << " " << cepstrumData[1].at(i) << endl;
        }

        // Set up source file for righ spectrum centroid
        outFile.close();
        outFile.open((dirName + "/srcRightSCentroid").c_str(), ios::out);
        sourceFiles[1].push_back((dirName + "/srcRightSCentroid"));

        outFile.close();
    }
    
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

// Function pushSpectrum
// Inputs:
//       data - A double containing the data to add.
// Outputs: None
// Purpose:  Push new data onto the spectrumData vector.
void AudioWave::pushSpectrum(double data)
{
    spectrumData.push_back(data);

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
//       chan - An integer indicating the channel to access.
//       index - An integer indicating the source file to look up.
// Outputs:
//        sourceFile - A string containing the filename and path of the source file.
// Purpose:  Return the name and path of a source file for graphing.
string AudioWave::getSourceFile(int chan, int index)
{
    return sourceFiles[chan][index];
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

// Function  getSSize
// Inputs: None
// Outputs: size - An integer describing the size.
// Purpose:  Return the size of the spectrumData vector
int AudioWave::getSSize()
{
    return spectrumData.size();
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

// Function getSpectrumDataPoint
// Inputs:
//       chan - An integer indicating which channel to pull the data from.
// Outputs: dataPoint - A double containing the datapoint.
// Purpose: Returns the datapoint from the indicated channel and location.
double AudioWave::getSpectrumDataPoint(int chan)
{
    double dataPoint;

    dataPoint = NULL;

    if (chan < spectrumData.size())
        dataPoint = spectrumData.at(chan);

    return dataPoint;
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
