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
   
    vector<vector<double> > foldedLeft;        // Will hold the left channel split into folds
    vector<vector<double> > foldedRight;       // Will hold the right channel split into folds
    vector<vector<double> > trainSet;          // Will hold the training set
    vector<vector<double> > testSet;           // Will hold the test set
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
            prepareFolds(1,folds, alg, 0, channels, fileName, foldedLeft, BMUnames, resultsPath, debug);

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
            prepareFolds(1,folds, alg, 1, channels, fileName, foldedRight, BMUnames, resultsPath, debug);

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
 
                cout << "trainSet.size() = " << trainSet.size() << endl;

                if (debug)
                {
                    cout << timeStamp() << ":  Training set created." << endl;
                    cout << timeStamp() << ":  Creating test set from folded left " << algorithm << "..." << endl;
                }

    
                // Generate the test set
                prepareFolds(0, folds, alg, 0, channels, sampleFileName, testSet, sampleNames, resultsPath, debug);
                //cout << "sampleFileName = " << sampleFileName << endl;
               // cout << "testSet.size() = " << testSet.size() << endl;

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
                learningVectorQuantization(trainSet, testSet, BMUnames, sampleNames, algorithm, 0, codeBooks, learnRate, epochs, resultsOutput, resultsPath, debug);

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

                cout << "trainSet.size() = " << trainSet.size() << endl;

                if (debug)
                {
                    cout << timeStamp() << ":  Training set created." << endl;
                    cout << timeStamp() << ":  Creating test set from folded right " << algorithm << "..." << endl;
                }

                // Use prepareFolds to generate a test set from the right channel of the samples
                prepareFolds(0, folds, alg, 1, channels, sampleFileName, testSet, sampleNames, resultsPath, debug);

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

                learningVectorQuantization(trainSet, testSet, BMUnames, sampleNames, algorithm, 1, codeBooks, learnRate, epochs, resultsOutput, resultsPath, debug);

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
//       folding -  A boolean flag indicating a fold is being prepared
//       folds - An integer indicating the number of folds to create.
//       alg - An integer specifying the algorithm being worked on.
//       currChan - An integer specifiying the current channel being manipulated.
//       channels - An integer indicating the total channels in the audio samples
//       &folded - An n-dimensional vector of doubles that will hold the folded FFT
//       resultsPath - A string indicating the path for data output
//       debug - A boolean flag that controls debug output
// Outputs: None
// Purpose:  Break a given dataset into the correct number of folds for analysis.
void prepareFolds(bool folding, int folds, int alg, int currChan, int channels, string fileName, vector<vector<double> > &folded, vector<string> &names, string resultsPath, bool debug)
{
    int foldSize;                         // The size of each fold
    int currIndex;                        // Index to add to fold
    int currentFold;                      // Current fold to add data
    bool grabName;                        // Controls whether to grab the name
    vector<double> dataFold;              // A vector to hold the new fold of data
    vector<double> tempVec;               // A vector that will hold the data from the file
    string line;                          // A string to hold line of data.
    string data;                          // Will hold the complex number as a string
    ifstream inFile;                      // A stream pointer for data input.
    ofstream outFile;                     // A stream pointer for data output.


    currIndex = 0;
    currentFold = 0;
    grabName = 1;

    cout << "FileName = " << fileName << endl;

    // Initialize the folded vector
    if (folding)
    {
        for (int i = 0; i < folds; i++)
        {
            folded.push_back(dataFold);
        }
    }

    // Load the data file into a vector to work with
    inFile.open((fileName).c_str(), ios::in);

    while(std::getline(inFile, line))
    {
        data = "";

        if (grabName == 1)
        {
            names.push_back(line);
            grabName = 0;
        }
        else
        {
            if (currChan == 1) // Skip the left channel
                std::getline(inFile, line);

            if (line.size() > 0)
            {
                if ((alg == 3) || (alg == 5))
                {
                   tempVec.push_back(stod(line));
                }
                else
                {
                    for (int i = 0; i <= line.length(); i++)
                    {
                        if ((line[i] != ' ') && (line[i] != '\0'))
                        {
                            data += line[i];
                        }
                        else
                        {
                            if (data.size() > 0)
                            {
                                if (alg == 1)
                                    tempVec.push_back(real(stod(data)));
                                else
                                    tempVec.push_back(stod(data));
                            }

                            data = "";
                        }
                    }
                }

                if (!folding)
                {
                    folded.push_back(dataFold);

                    for (int i = 0; i < tempVec.size(); i++)
                        folded[folded.size()-1].push_back(tempVec[i]);
                }
            }
            else
                grabName = 1;  // The next line will be an audio name.

            if ((currChan == 0) && (grabName != 1))
            {
                std::getline(inFile, line);
            }
            else if ((currChan == 1) && (grabName != 1))
            {
                std::getline(inFile, line);
                grabName = 1;
            }
        }
    }

    inFile.close();

    if (folding)
    {
        // Split the tempVec into folds
        foldSize = tempVec.size() / folds;
 
        if (foldSize <= 0)
            foldSize = 1;

        outFile.open((resultsPath + "/ANNIResults.txt").c_str(), ios::app);
        outFile << "\tNumber of Folds:  " << folds << endl;
        outFile << "\tFold Size:  " << foldSize << endl;
        outFile.close();

        if (debug)
        {
            cout << "\tNumber of Folds:  " << folds << endl;
            cout << "\tFold Size:  " << foldSize << endl;
        }

        for (int i = 0; i < folds; i++)
        {
            for (int k = 0; k < foldSize-1; k++)
            {
                if (currIndex < tempVec.size())
                    folded[i].push_back(tempVec[k]);
                else
                {
                    currIndex = 0;
                    folded[i].push_back(tempVec[k]);
                }
           
                currIndex++;  

            }

            outFile.open((resultsPath + "/ANNIResults.txt").c_str(), ios::app);
            outFile << "\tCurrent Fold:  (" << (i+1) << " / " << folds << ")" << endl;
            outFile << "\tFold Size:  " << folded[i].size() << endl << endl;
            if (debug)
            {
                cout << "\tCurrent Fold:  (" << (i+1) << " / " << folds << ")" << endl;
                cout << "\tFold Size:  " << folded[i].size() << endl << endl;
            }
        
        }
    }
    return;
}

// Function learningVectorQuantization
// Inputs:
//       trainSet - An n-dimensional vector of doubles representing the training set.
//       samples - An n-dimenstional vector of doubles representing the sample set
//       BMUnames -  A vector of strings containing the names for BMU options.
//       sampleNames - A vector of strings containing the names of the files being analyzed
//       algorithm -  A string containing the algorithm being used.
//       currChan - An integer indicating the current channel.
//       codeBooks - An integer indicating the number of codebooks used for training/analysis
//       learnRate - A double indicating the learning rate
//       epochs - An integer indicating the number of epochs to train over.
//       fileName - A string indicating the name of the output file.
//       resultsPath - A string indicating the path for output files.
//       debug - A boolean flag that controls debug output.
// Output: None
// Purpose:  To determine the effectiveness of a training set 
void learningVectorQuantization(vector<vector<double> > trainSet, vector<vector<double> > samples, vector<string> BMUnames, vector<string> sampleNames, string algorithm, int currChan, int codeBooks, double learnRate, int epochs, string fileName, string resultsPath, bool debug)
{
    vector<vector<double> > codeBookSet;        // Will hold the set of codebooks for training
    vector<double> set;                         // Represents a code book vector
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

    trainCodeBooks(trainSet, codeBookSet, codeBooks, learnRate, epochs, fileName, resultsPath, debug); 

    outFile.open((resultsPath).c_str(), ios::app);
    outFile << endl << "\t" << timeStamp() << ":  Codebooks trained." << endl;
    outFile.close();

    if (debug)
        cout << endl << "\t" << timeStamp() << ":  Codebooks trained." << endl;

    for (int i = 0; i < samples.size(); i++)
    {
        if (samples[i].size() > 0)
        {
            match = getBestMatch(codeBookSet, samples[i], fileName, resultsPath, debug);

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

    distance = 0;

    if (row1.size() < row2.size())
        control = row1.size();
    else
        control = row2.size();
    
    for (int i = 0; i < control; i++)
    {
        distance += (row1[i] - row2[i]) * (row1[i] - row2[i]);
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

    cout << "knownData.size() = " << knownData.size() << endl;
    // Calculate the euclidean distances between the rows
    for (int i = 0; i < knownData.size(); i++)
    {
        distances.push_back(euclideanDistance(knownData[i], testRow, resultsPath, debug));
    }

    for (int z = 0; z < distances.size(); z++)
        cout << "distance[" << z << "] = " << distances[z] << endl;

    // Find the shortest euclidean distance
    for (int i = 1; i < distances.size(); i++)
    {
        if (distances[i] < distances[i-1])
            match = i;
    }

    cout << "match = " << match << endl;
    return match;
}

// Function randomDatabase
// Inputs:
//       database - An n-D vector of doubles containing known data points for generating training set.
//       trainSet - An n-D vector of doubles that will contain the subset of training data for comparisons
//       resultsPath - A string containing the path to the output directory.
//       debug - A flag controlling the debug output.
// Outputs:  None
// Purpose: This creates a random database consisting of a subset of known data for use by ANNI.
void randomDatabase(vector<vector<double> > database, vector<vector<double> > &trainSet,string resultsPath, bool debug)
{

    int records;       // Contains the total number of records in the database
    int lowerBound;    // A random number containing the lower boundary of the subset.
    int upperBound;    // A random number containing the upper boundary of the subset.

    for (int i = 0; i < database.size(); i++)
    {
        records = database[i].size();

        if (database[i].size() > 0)
        {
            if (records > 1)
            { 
                lowerBound = (rand() % (records - 1)) + 1;
                upperBound = (rand() % (records - lowerBound)) + lowerBound;
            }
            else
            {
                lowerBound = 0;
                upperBound = 1;
            }

            for (int j = lowerBound; j < upperBound; j++)
            {
                trainSet[i].push_back(database[i][j]);
            }
        }
    }

    return;
}

// Function trainCodeBooks
// Inputs:
//       trainSet - An n-D vector of doubles containing known data points for generating the training set
//       codeBookSet - An n-D vector that will contain the subset of training data for comparisons
//       nBooks - An integer describing the number of codebooks to generate
//       lRate - A double describing the learning rate
//       epochs - An integer describing the number of learning epochs
//       fileName - A string indicating the file name for data output.
//       resultsPath - A string containing the path to the output directory
//       debug - A flag controlling the debug output.
// Output: None
// Purpose:  This function is used to generate the number of specified codebooks for running the algorithm.
void trainCodeBooks(vector<vector<double> > trainSet, vector<vector<double> > &codeBookSet,int nBooks, double lRate, int epochs, string fileName,string resultsPath, bool debug)
{
    double rate;        // The learning rate of the current epoch
    double error;       // Used to calculate the error rate in the learning
    double sumError;    // The summation of the total errors in the predictions
    int bmu;            // The index of the best matching codebook entry for the current database line
    ofstream outFile;   // A stream pointer for data output.

    // Initialize variables   
    rate = 0;
    error = 0;
    sumError = 0;
    bmu = 0;

    outFile.open((resultsPath).c_str(), ios::app);
    outFile << "\t\t" << timeStamp() << ":  Creating " << nBooks << " codebooks from training set..." << endl;
    outFile.close();

    if (debug)
        cout << "\t\t" << timeStamp() << ":  Creating " << nBooks << " codebooks from training set..." << endl;

    // Generate the codebooks
    for (int i = 0; i < nBooks; i++)
    {
        randomDatabase(trainSet, codeBookSet, resultsPath, debug);
    }

    outFile.open((resultsPath).c_str(), ios::app);
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
            bmu = getBestMatch(codeBookSet, trainSet[j], fileName, resultsPath, debug);
       
            for (int k = 0; k < trainSet[j].size(); k++)
            {
                if (k < codeBookSet[bmu].size() - 1)
                {
                    error = trainSet[j][k] - codeBookSet[bmu][k];

                    sumError += error * error;

                    if (codeBookSet[bmu][codeBookSet[bmu].size()-1] == trainSet[j][trainSet[j].size()-1])
                        codeBookSet[bmu][k] += rate * error;
                    else
                        codeBookSet[bmu][k] -= rate * error;
                }
            }
        }

        outFile.open((resultsPath).c_str(), ios::app);
        outFile << endl << "\t\t\t" << "Epoch:  " << i << endl << "\t\t\tLearning Rate:  " << rate
                << endl << "\t\t\tError:  " << setprecision(3) << sumError << endl;
        outFile.close();

        if (debug)
            cout << endl << "\t\t\tEpoch: " << i << endl << "\t\t\tLearning Rate:  " << rate 
                 << endl << "\t\t\tError:  " << setprecision(3) << sumError << endl;
    }
         
    return;
}
