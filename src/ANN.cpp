/* 
 *  File:     ANN.cpp
 *  Author:   Andrew Moore, Hue Truong, and Alex Reno
 *
 *  Created:  March 8, 2020, 12:00 PM
 */

/**************************************Change Log *******************************/

// Created initial file for ANN definitions - A.M. 08 Mar 2020

/**************************************End Change Log ***************************/

/**************************************To Do List ******************************/

/**************************************End To Do List **************************/

#include "../include/ANN.h"
#include "../include/Utilities.h"
#include "../include/Fold.h"
#include <time.h>
#include <algorithm>

using namespace std;

// Function ANNI
// Inputs:
//       trainPath - A string containing the resultsPath to the training directory
//       testPath - A string containing the resultsPath to the test directory
//       folds - An integer indicating the number of folds to create from the wave object.
//       learnRate - A double indicating the learning rate to apply to the algorithm.
//       epochs - An integer indicating the number of epochs to generate data over.
//       codebooks - An integer indicating the number of codebooks to be used for training / analysis.
//       alg - An integer indicating the algorithm(s) to use in training / analysis.
//       channels - An integer indicating the number of channels in the audio samples.
//       resultsPath - A string containing the location of the output files.
//       debug - A flag that controls debug output.
// Outputs: None
// Purpose: ANNI is an artificial neural network that is used to learn the classifications of music.
void ANNI(string trainPath, string testPath, int folds, double learnRate, int epochs, int codeBooks, int alg, int channels, string resultsPath, bool debug)
{
    ofstream outFile;                         // A stream pointer for data output.
    ofstream debugFile;                       // A stream pointer for debug output.

    string outFileName;                       // Will hold the output file name with the resultsPath

    resultsPath += "/";

    outFileName = resultsPath + "ANNIResults.txt";

    if (debug)
    {
        cout << "ANNI called..." << endl << endl;
        cout << "\tfolds = " << folds << endl;
        cout << "\tlearnRate = " << learnRate << endl;
        cout << "\tepochs = " << epochs << endl;
        cout << "\tcodeBooks = " << codeBooks << endl;
        cout << "\talg = " << alg << endl;
        cout << "\tchannels = " << channels << endl;
        cout << "\tresultsPath = " << resultsPath << endl;
        cout << "\tdebug = " << debug << endl << endl;
    }

    outFile.open((resultsPath + "/ANNIResults.txt").c_str(), ios::app);

    outFile << timeStamp() << ":  ANNI RUN" << endl << endl;

    if (debug)
        cout << timeStamp() << ":  ANNI RUN" << endl << endl;

    for (int i = 0; i < 100; i++)
        outFile << "*";
  
    outFile << endl << endl;
    outFile.close();

    switch(alg) // Prepare the data vectors
    {
        case 0:  // Use all algorithms
        {
            // Analyze the FFT
            lvqHelper("FFT", trainPath, testPath, outFileName, folds, learnRate, epochs, codeBooks, channels, resultsPath, debug);

            // Analyze the Zero Cross
            lvqHelper("Zero Cross", trainPath, testPath, outFileName, folds, learnRate, epochs, codeBooks, channels, resultsPath, debug);

            // Analyze Spectrum Flux
            lvqHelper("Spectrum Flux", trainPath, testPath, outFileName, folds, learnRate, epochs, codeBooks, channels, resultsPath, debug);
            // Analyze the Cepstrum
 
            lvqHelper("Real Cepstrum", trainPath, testPath, outFileName, folds, learnRate, epochs, codeBooks, channels, resultsPath, debug);
            // Analyzed the Spectrum Centroid
            lvqHelper("Spectrum Centroid", trainPath, testPath, outFileName, folds, learnRate, epochs, codeBooks, channels, resultsPath, debug);

            break;
        }
        case 1:  // Use FFT
        {
            lvqHelper("FFT", trainPath, testPath, outFileName, folds, learnRate, epochs, codeBooks, channels, resultsPath, debug);
 
            break;
        }
        case 2:  // Use Zero Cross
        {
            lvqHelper("Zero Cross", trainPath, testPath, outFileName, folds, learnRate, epochs, codeBooks, channels, resultsPath, debug);

            break;
        }
        case 3:  // Use Spectrum Flux
        {
            lvqHelper("Spectrum Flux", trainPath, testPath, outFileName, folds, learnRate, epochs, codeBooks, channels, resultsPath, debug);

            break;
        }
        case 4:  // Use Cepstrum
        {
            lvqHelper("Real Cepstrum", trainPath, testPath, outFileName, folds, learnRate, epochs, codeBooks, channels, resultsPath, debug);

            break;
        }
        case 5:  // Use Spectrum Centroid
        {
            lvqHelper("Spectrum Centroid", trainPath, testPath, outFileName, folds, learnRate, epochs, codeBooks, channels, resultsPath, debug);

            break;
        }
        default:
        {
            cout << "Invalid algorithm." << endl;
            break;
        }
    }

    return;
}

// Function lvqHelper
// Inputs:
//       algorithm - A string containing the name of the algorithm being run against.
//       trainPath - A string containing the path to the training dataset
//       testPath - A string indicating the path to the test data set.
//       resultsOutput - A string containing the full resultsPath to the output file.
//       learnRate - A double indicating the learning rate to apply to the algorithm.
//       folds - An integer indicating the niumber of folds to create from the wave object
//       epochs - An integer indicating the number of epochs to generate data over
//       codebooks - An integer indicating the number of codebooks to be used for training / analysis
//       channels - An integer indicating the number of channels in the audio samples
//       resultsPath - A string containing the location of the output files
//       debug - A flag that controls debug output.
// Outputs:
// Purpose:  Peforms ths LVQ on a two dimensional vector of doubles.
void lvqHelper(string algorithm, string trainPath, string testPath, string resultsOutput, int folds, double learnRate, int epochs, int codeBooks, int channels, string resultsPath, bool debug)
{
    ofstream outFile;                          // A stream pointer for data output
    ofstream debugFile;                        // A stream pointer for debug output

    string fileName;                           // Will contain the name of the database file
    string sampleFileName;                     // Will contain the name of the sample file.

    vector<Fold> foldedLeft;                   // A vector of folded left channel objects
    vector<Fold> foldedRight;                  // A vector of folded right channel objects
    vector<Fold> trainSet;                     // A vector of training objects
    vector<Fold> testSet;                      // A vector of test sets 
    vector<string> BMUnames;                   // Will hold the names of the training set samples
    vector<string> sampleNames;                // Will hold the names of the samples being analyzed

    int alg;                                   // Used to tell the folder which algorithm

    switch(channels)
    {
        case 1:
        {
            break;
        }
        case 2:
        {

            // Resize the fold vectors
            foldedLeft.resize(folds);
            foldedRight.resize(folds);   
             
            if (algorithm.compare("FFT") == 0)
            {
                fileName = trainPath + "/Databases/stereoFFT.txt";
                sampleFileName = testPath + "/Databases/stereoFFT.txt";
                alg = 1;
            }
            else if (algorithm.compare("Zero Cross") == 0)
            {
                alg = 2;
                fileName = trainPath + "/Databases/stereoZeroCross.txt";
                sampleFileName = testPath + "/Databases/stereoZeroCross.txt";
            }
            else if (algorithm.compare("Spectrum Flux") == 0)
            {
                alg = 3;
                fileName = trainPath + "/Databases/stereoSpectrumFlux.txt";
                sampleFileName = testPath + "/Databases/stereoSpectrumFlux.txt";;
            }
            else if (algorithm.compare("Real Cepstrum") == 0)
            {
                alg = 4;
                fileName = trainPath + "/Databases/stereoCepstrum.txt";
                sampleFileName = testPath + "/Databases/stereoCepstrum.txt";
            }
            else if (algorithm.compare("Spectrum Centroid") == 0)
            {
                alg = 5;
                fileName = trainPath + "/Databases/stereoSpectrumCentroid.txt";
                sampleFileName = testPath + "/Databases/stereoSpectrumCentroid.txt";
            }

            outFile.open(resultsOutput, ios::app);
            outFile << timeStamp() << ":  Preparing left channel of " << fileName << " with "
                    << folds << " folds..." << endl;
            outFile.close();

            if (debug)
                cout << timeStamp() << ":  Preparing left channel of " << fileName << " with "
                     << folds << " folds..." << endl;

            // Prepare left training set
            prepareFolds(0, folds, alg, 0, channels, fileName, foldedLeft, BMUnames, resultsPath, debug);

            outFile.open(resultsOutput, ios::app);
            outFile << timeStamp() << ":  Finished preparing left channel." << endl;
            outFile << timeStamp() << ":  Preparing right channel of " << fileName << " with "
                    << folds << " folds..." << endl;
            outFile.close();

            if (debug)
            {
                cout << timeStamp() << ":  Finished preparing left channel." << endl;
                cout << timeStamp() << ":  Preparing right channel of " << fileName << " with " 
                     << folds << " folds..." << endl;
            }

            // Prepare right training set
            prepareFolds(0, folds, alg, 1, channels, fileName, foldedRight, BMUnames, resultsPath, debug);

            outFile.open(resultsOutput, ios::app);
            outFile << timeStamp() << ":  Finished preparing right channel." << endl;
            outFile.close();

            if (debug)
                cout << timeStamp() << ":  Finished preparing right channel." << endl;

            // Train on the left fold
            for (int i = 0; i < foldedLeft.size(); i++)
            {
                outFile.open(resultsOutput, ios::app);
                outFile << timeStamp() << ":  Creating training set for left " << algorithm << "..." << endl;
                outFile.close();

                if (debug)
                    cout << timeStamp() << ":  Creating training set for left " << algorithm << "..." << endl;

                genTrainSet(foldedLeft, trainSet, i);

                outFile.open(resultsOutput, ios::app);
                outFile << timeStamp() << ":  Training set created." << endl;
                outFile << timeStamp() << ":  Creating test set from folded left " << algorithm << "..." << endl;
                outFile.close();
 
                if (debug)
                {
                    cout << timeStamp() << ":  Training set created." << endl;
                    cout << timeStamp() << ":  Creating test set from folded left " << algorithm << "..." << endl;
                }

    
                // Generate the test set
                prepareFolds(1, 1, alg, 0, channels, sampleFileName, testSet, sampleNames, resultsPath, debug);

                outFile.open(resultsOutput, ios::app);
                outFile << timeStamp() << ":  Test set created." << endl;
                outFile << timeStamp() << ":  Starting Learning Vector Quantization for " << algorithm << "..." << endl;
                outFile.close();

                if (debug)
                {
                    cout << timeStamp() << ":  Test set created." << endl;
                    cout << timeStamp() << ":  Starting Learning Vector Quantization for " << algorithm 
                         << " left channel..." << endl;
                }
             
                // Make prediction based on training set
                cout << "ResultsPath = " << resultsPath << endl;
                cout << "ResultsOutput = " << resultsOutput << endl;
                learningVectorQuantization(trainSet, testSet, BMUnames, sampleNames, algorithm, alg,  0, codeBooks, learnRate, epochs, resultsOutput, resultsPath, debug);

                trainSet.clear();

            } // End train left fold loop

            // Clean out vectors for the right fold
            testSet.clear();
            sampleNames.clear();

            // Train on the right fold
            for (int i = 0; i < foldedRight.size(); i++)
            {
                outFile.open(resultsOutput, ios::app);
                outFile << timeStamp() << ":  Creating training set for right " << algorithm << "..." << endl;
                outFile.close();

                if (debug)
                    cout << timeStamp() << ":  Creating training set for right " << algorithm << "..." << endl;

                // Create training set from right fold
                genTrainSet(foldedRight, trainSet, i);

                outFile.open(resultsOutput, ios::app);
                outFile << timeStamp() << ":  Training set created." << endl;
                outFile << timeStamp() << ":  Creating test set from folded right " << algorithm << "..." << endl;
                outFile.close();

                if (debug)
                {
                    cout << timeStamp() << ":  Training set created." << endl;
                    cout << timeStamp() << ":  Creating test set from folded right " << algorithm << "..." << endl;
                }

                // Use prepareFolds to generate a test set from the right channel of the samples
                prepareFolds(1, 1, alg, 1, channels, sampleFileName, testSet, sampleNames, resultsPath, debug);

                outFile.open(resultsOutput, ios::app);
                outFile << timeStamp() << ":  Test set created." << endl;
                outFile << timeStamp() << ":  Starting Learning Vector Quantization for " << algorithm 
                        << " right channel..." << endl;
                outFile.close();

                if (debug)
                {
                    cout << timeStamp() << ":  Test set created." << endl;
                    cout << timeStamp() << ":  Starting Learning Vector Quantization for "<< algorithm  
                         << " right channel.." << endl;
                }

                learningVectorQuantization(trainSet, testSet, BMUnames, sampleNames, algorithm, alg, 1, codeBooks, learnRate, epochs, resultsOutput, resultsPath, debug);

                outFile.open(resultsOutput, ios::app);
                outFile << timeStamp() << ":  Learning Vector Quantization complete." << endl;
                outFile.close();

                if (debug)
                    cout << timeStamp() << ":  Learning Vector Quantization complete." << endl;

                trainSet.clear();
            } // End train right fold loop

            break;
        }
        default:
        {
            cout << "twoDVectorPrep given unsupported number of channels." << endl;
            break;
        }
    }

    return;
}

// Function prepareFolds
// Inputs:
//       testSet - A boolean flag to control test set generation.
//       folds - An integer indicating the number of folds to create.
//       alg - An integer specifying the algorithm being worked on.
//       currChan - An integer specifiying the current channel being manipulated.
//       channels - An integer indicating the total channels in the audio samples
//       &folded - A vector of Fold objects
//       resultsPath - A string indicating the path for data output
//       debug - A boolean flag that controls debug output
// Outputs: None
// Purpose:  Break a given dataset into the correct number of folds for analysis.
void prepareFolds(bool testSet, int folds, int alg, int currChan, int channels, string fileName, vector<Fold> &folded, vector<string> &names, string resultsPath, bool debug)
{
    int foldSize;                         // The size of each fold
    int currIndex;                        // Index to add to fold
    int currFold;                         // Current fold to add data
    int grabName;                         // Controls whether to grab the name
    vector<double> dataFold;              // A vector to hold the new fold of data
    vector<double> tempVec;               // A vector that will hold the data from the file
    string line;                          // A string to hold line of data.
    string data;                          // Will hold the complex number as a string
    ifstream inFile;                      // A stream pointer for data input.
    ofstream outFile;                     // A stream pointer for data output.
    int sampleCount;                      // Count the number of samples in the training database
    double tempDoub;                      // Will hold a temporary double value
    complex<double> tempComplex;          // Will hold a temporary complex number
    stringstream convert;                 // Will be used to convert a string to a double


    currIndex = 0;
    currFold = 0;
    grabName = 1;
    sampleCount = 0;

    inFile.open((fileName).c_str(), ios::in);

    while(std::getline(inFile, line))
    {
        names.push_back(line);

        std::getline(inFile, line);
        std::getline(inFile, line);

        if (channels == 2)
            std::getline(inFile, line); 

        sampleCount++;
    }

    inFile.close();

    foldSize = sampleCount / folds;

    if (testSet)
        folded.resize(sampleCount);

    inFile.open((fileName).c_str(), ios::in);

    while (std::getline(inFile, line))
    {
        if (grabName == 1)
            grabName = -1;
        else
        {
            if (currChan == 1)  // Skip the left channel
                std::getline(inFile, line);

            if (line.size() > 0)
            {
                if ((alg == 3) || (alg == 5))
                {
                    convert << line;
                    convert >> tempDoub;

                    if (!convert.fail())
                        tempVec.push_back(tempDoub);
                }
                else
                {
                    for (int i = 0; i < line.length(); i++)
                    {
                        if ((line[i] != ' ') && (line[i] != '\0'))
                            data += line[i];
                        else if (data.size() > 0)
                        {
                            convert << data;

                            if (alg == 1) // FFT
                            {
                                convert >> tempComplex;

                                if (!convert.fail())
                                    tempVec.push_back(real(tempComplex));
                            }
                            else
                            {
                                convert >> tempDoub;

                                if (!convert.fail())
                                    tempVec.push_back(tempDoub);
                            }

                            data = "";
                            convert.str("");
                            convert.clear();
                        }
                    }
                }

                // Load the current vector to the fold
                if (folds == 1)
                {
                    folded.at(0).pushFold(tempVec);
                }
                else
                {
                    folded.at(currFold).pushFold(tempVec);
                    currIndex++;

                    if (currIndex == foldSize)
                    {
                        currIndex = 0;
                        currFold++;
                    }
                }

                std::getline(inFile, line);
            }
            else
                grabName = 1;

            // Skip the channel we're not on
            if (grabName == 0)
                std::getline(inFile, line);
            else if (grabName == -1)
                grabName = 0;
        }
    }

    inFile.close();

    return;
}

// Function learningVectorQuantization
// Inputs:
//       trainSet - A vector of Fold objects representing the training set.
//       samples - A vector of Fold objects representing the sample set to test.
//       BMUnames -  A vector of strings containing the names for BMU options.
//       sampleNames - A vector of strings containing the names of the files being analyzed
//       algorithm -  A string containing the algorithm being used.
//       alg - An integer indicating the algorithm being used.
//       currChan - An integer indicating the current channel.
//       codeBooks - An integer indicating the number of codebooks used for training/analysis
//       learnRate - A double indicating the learning rate
//       epochs - An integer indicating the number of epochs to train over.
//       fileName - A string indicating the name of the output file.
//       resultsPath - A string indicating the path for output files.
//       debug - A boolean flag that controls debug output.
// Output: None
// Purpose:  To determine the effectiveness of a training set 
void learningVectorQuantization(vector<Fold> trainSet, vector<Fold> samples, vector<string> BMUnames, vector<string> sampleNames, string algorithm, int alg, int currChan, int codeBooks, double learnRate, int epochs, string fileName, string resultsPath, bool debug)
{
    vector<vector<double> > codeBookSet;        // Will hold the set of codebooks for training
    vector<double> set;                         // Represents a code book vector
    vector<double> tempSample;                  // Will hold a temporary sample
    ofstream outFile;                           // A stream pointer for data output
    int match;                                  // Will contain the BMU for the sample
    string channel;
    match = -1;


    // Set which channel is being worked with
    if (currChan == 0)
        channel = "Left";
    else if (currChan == 1)
        channel = "Right";

    // Initialize the codeBookSet to be the correct size
    for (int i = 0; i < trainSet.size(); i++)
        codeBookSet.push_back(set);

    outFile.open((resultsPath).c_str(), ios::app);
    outFile << "\t" << timeStamp() << ":  Training codebooks..." << endl << endl;
    outFile.close();

    if (debug)
        cout << "\t" << timeStamp() << ":  Training codebooks..." << endl << endl;

    trainCodeBooks(trainSet, codeBookSet, alg, codeBooks, learnRate, epochs, fileName, resultsPath, debug); 

    outFile.open((resultsPath).c_str(), ios::app);
    outFile << endl << "\t" << timeStamp() << ":  Codebooks trained." << endl;
    outFile.close();

    if (debug)
        cout << endl << "\t" << timeStamp() << ":  Codebooks trained." << endl;

    cout << "samples.size() = " << samples.size() << endl;
    cout << "samples[0].size() = " << samples[0].getSize() << endl;
    for (int i = 0; i < samples.size(); i++)
    {
        tempSample = samples[0].getFold(i);
      
        if (tempSample.size() > 0)
        {
            match = getBestMatch(codeBookSet, tempSample, fileName, resultsPath, debug);

            outFile.open("predictions.txt", ios::app);
            outFile << "The best match for " << sampleNames[i] << " using the " << channel << " channel " << algorithm
                    << " is " << BMUnames[match] << endl;
            outFile.close();

            cout << "The best match for " << sampleNames[i] << " using the " << channel << " channel "  << algorithm
                 << " is  " << BMUnames[match] << endl << endl;
        }
    }

    outFile.open("predictions.txt", ios::app);
    outFile << endl;
    outFile.close();

    return;
}

// Function euclideanDistance (float vector)
// Inputs:
//       row1 - A vector of floats containing the first row
//       row2 - A vector of floats containing the second row
//       resultsPath - A string containing the location of the output directory
//       debug - A flag that controls debug output.
// Outputs:
//       distance - A double describing the euclidean distance between row1 and row2
// Purpose:  Calculate the euclidean distance between the first and second row
double euclideanDistance(vector<double> row1, vector<double> row2, string resultsPath, bool debug)
{
    double distance;     // Will describe the euclidean distance between the row1 and row2
    int control;         // The shortest vector will control the loop
    double v1;           // Vector 1 index value
    double v2;           // Vector 2 index value

    distance = 0;
    v1 = 0;
    v2 = 0;

    if (row1.size() < row2.size())
        control = row1.size();
    else
        control = row2.size();
   
    for (int i = 0; i < control; i++)
    {
        v1 = row1[i];
        v2 = row2[i];
        
        if (v1 == 0)
            v1 = 1;
        if (v2 == 0)
            v2 = 1;

        distance += (v1 - v2) * (v1 - v2);
    }

    return sqrt(distance);
}

// Function getBestMatch
// Inputs:
//       knownData - A vector containing known data sets for comparison
//       testRow - An array containing spectral flux data to compare.
//       resultsPath - A string containing the location of the output directory
//       fileName - A string indicating the file name for data output.
//       debug - A flag that controls debug output
// Output:
//       category - An integer describing the category the audio belongs to
// Purpose:  Finds the best match of a piece of audio by comparing its spectral flux to known data.
int getBestMatch(vector<vector<double> > knownData, vector<double> testRow, string fileName, string resultsPath, bool debug)
{
    int match;                      // An integer describing which element of the knownData is the BMU
    vector<double> distances;       // Contains the euclidean distances of the vectors
    
    match = 0;

    // Calculate the euclidean distances between the rows
    for (int i = 0; i < knownData.size(); i++)
    {
        if (knownData[i].size() > 0)
            distances.push_back(euclideanDistance(knownData[i], testRow, resultsPath, debug));
    }

    // Find the shortest euclidean distance
    for (int i = 1; i < distances.size(); i++)
    {
        if (distances[i] < distances[i-1])
            match = i;
    }

    return match;
}

// Function randomDatabase
// Inputs:
//       database - A vector of Fold objects representing the known data.
//       trainSet - An n-D vector of doubles that will contain the subset of training data for comparisons
//       alg - The algorithm being run
//       resultsPath - A string containing the path to the output directory.
//       debug - A flag controlling the debug output.
// Outputs:  None
// Purpose: This creates a random database consisting of a subset of known data for use by ANNI.
void randomDatabase(vector<Fold> database, vector<vector<double> > &trainSet, int alg, string resultsPath, bool debug)
{

    int records;       // Contains the total number of records in the database
    int lowerBound;    // A random number containing the lower boundary of the subset.
    int upperBound;    // A random number containing the upper boundary of the subset.

    int lowerBoundInner;  // The lower boundary of the inner fold
    int upperBoundInner; // The upper boundary of the inner fold

    records = database.size();

    lowerBound = 0;
    upperBound = -1;
    lowerBoundInner = 0;
    upperBoundInner = -1;

    while (upperBound <= lowerBound)
    {
        if (records > 2)
        {
            lowerBound = (rand() % (records - 1)) + 1;
            upperBound = (rand() % (records - lowerBound)) + lowerBound;
        }
        else
        {
            lowerBound = 0;
            upperBound = 1;
        }
    }

    for (int i = lowerBound; i < upperBound; i++)
    {
        records = database[i].getSize();

        if (records > 0)
        {
            while (upperBoundInner <= lowerBoundInner)
            {
                if (records > 1)
                {
                    lowerBoundInner = (rand() % (records -1)) + 1;
                    upperBoundInner = (rand() % (records - lowerBoundInner)) + lowerBoundInner;
                }
                else
                {
                    lowerBoundInner = 0;
                    upperBoundInner = 1;
                }
            }
        
            for (int j = lowerBoundInner; j < upperBoundInner; j++)
            {
                trainSet.push_back(database[i].getFold(j));
            }
        }
    }
    return;
}

// Function trainCodeBooks
// Inputs:
//       trainSet - A vector of Fold objects representing the training set.
//       codeBookSet - An n-D vector that will contain the subset of training data for comparisons
//       alg - The algorithm being run
//       nBooks - An integer describing the number of codebooks to generate
//       lRate - A double describing the learning rate
//       epochs - An integer describing the number of learning epochs
//       fileName - A string indicating the file name for data output.
//       resultsPath - A string containing the path to the output directory
//       debug - A flag controlling the debug output.
// Output: None
// Purpose:  This function is used to generate the number of specified codebooks for running the algorithm.
void trainCodeBooks(vector<Fold> trainSet, vector<vector<double> > &codeBookSet, int alg, int nBooks, double lRate, int epochs, string fileName,string resultsPath, bool debug)
{
    double rate;        // The learning rate of the current epoch
    double error;       // Used to calculate the error rate in the learning
    double sumError;    // The summation of the total errors in the predictions
    int bmu;            // The index of the best matching codebook entry for the current database line
    ofstream outFile;   // A stream pointer for data output.

    vector<double> tempFold;    // Will temporarily hold a fold

    // Initialize variables   
    rate = 0;
    error = 0;
    sumError = 0;
    bmu = 0;

    cout << "ResultsPath = " << resultsPath << endl;
    outFile.open((resultsPath + "ANNIResults.txt").c_str(), ios::app);
    outFile << "\t\t" << timeStamp() << ":  Creating " << nBooks << " codebooks from training set..." << endl;
    outFile.close();

    if (debug)
        cout << "\t\t" << timeStamp() << ":  Creating " << nBooks << " codebooks from training set..." << endl;

    // Generate the codebooks
    for (int i = 0; i < nBooks; i++)
    {
        randomDatabase(trainSet, codeBookSet, alg, resultsPath, debug);
    }

    outFile.open((resultsPath + "ANNIResults.txt").c_str(), ios::app);
    outFile << "\t\t" << timeStamp() << ":  " << nBooks << " codebooks created." << endl;
    outFile << "\t\t" << timeStamp() << ":  Training codebooks over " << epochs << " epochs..." << endl;
    outFile.close();

    if (debug)
    {
        cout << "\t\t" << timeStamp() << ":  " << nBooks << " codebooks created." << endl;
        cout << "\t\t" << timeStamp() << ":  Training codebooks over " << epochs << " epochs..." << endl;
    }

    // Train the codebooks over the specified number of epochs
    for (int i = 1; i < (epochs+1); i++)
    {
        rate = lRate * (1.0-(static_cast<float>(i-epochs)));        

        sumError = 0.0;

        for (int j = 0; j < trainSet.size(); j++)
        {
            for (int k = 0; k < trainSet[j].getSize(); k++)
            {
                tempFold = trainSet[j].getFold(k);

                bmu = getBestMatch(codeBookSet, tempFold, fileName, resultsPath, debug);
      
                for (int m = 0; m < tempFold.size(); m++)
                {
                    if (codeBookSet[bmu].size() > 0)
                    {
                        if (m < codeBookSet[bmu].size() - 1)
                        {
                            error = tempFold[m] - codeBookSet[bmu][m];

                            sumError += error * error;

                            if (codeBookSet[bmu][codeBookSet[bmu].size()-1] == tempFold[tempFold.size() - 1])
                                codeBookSet[bmu][m] += rate * error;
                            else
                                codeBookSet[bmu][m] -= rate * error;
                        }
                    }
                }
            }
        }

        outFile.open((resultsPath + "ANNIResults.txt").c_str(), ios::app);
        outFile << endl << "\t\t\tEpoch:  " << i << endl << "\t\t\tLearning Rate:  " << rate
                << endl << "\t\t\tError:  " << setprecision(3) << sumError << endl;
        outFile.close();

        if (debug)
            cout << endl << "\t\t\tEpoch: " << i << endl << "\t\t\tLearning Rate:  " << rate 
                 << endl << "\t\t\tError:  " << setprecision(3) << sumError << endl;
    }
         
    return;
}
