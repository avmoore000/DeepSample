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

using namespace std;

// Function ANNI
// Inputs:
//       folds - An integer indicating the number of folds to create from the wave object.
//       learnRate - A double indicating the learning rate to apply to the algorithm.
//       epochs - An integer indicating the number of epochs to generate data over.
//       codebooks - An integer indicating the number of codebooks to be used for training / analysis.
//       alg - An integer indicating the algorithm(s) to use in training / analysis.
//       channels - An integer indicating the number of channels in the audio samples.
//       path - A string containing the location of the output files.
//       debug - A flag that controls debug output.
// Outputs: None
// Purpose: ANNI is an artificial neural network that is used to learn the classifications of music.
void ANNI(int folds, double learnRate, int epochs, int codeBooks, int alg, int channels, string path, bool debug)
{
    ofstream outFile;    // A stream pointer for data output.
    ofstream debugFile;  // A stream pointer for debug output.
    ifstream inFile;      // A stream pointer for data input.

    string data;         // A string to hold lines of data.

    vector<vector<complex<double> > > foldedLeftFFT;
    vector<vector<complex<double> > > foldedRightFFT;
    vector<vector<float> > foldedZeroCross;
    vector<double> foldedSpectrumFlux;

    bool line;

    outFile.open((path + "/ANNIResults.txt").c_str(), ios::app);

    outFile << timestamp() << ":  ANNI RUN" << endl << endl;

    for (int i = 0; i < 100; i++)
        outFile << "*";
  
    outFile << endl << endl;

    line = 0; 

    switch(alg)
    {
        case 0:  // Use all algorithms
        {
            break;
        }
        case 1:  // Use FFT
        {
            if (channels == 1)
                inFile.open((path + "/Databases/monoFFT.txt").c_str(), ios::in);
            else if (channels == 2)
                inFile.open((path + "/Databases/stereoFFT.txt").c_str(), ios::in);
            
            while (inFile >> data)
            {
                cout << data << endl;
            }
                                  
            break;
        }
        case 2:  // Use Zero Cross
        {
            if (channels == 1)
                inFile.open((path + "/Databases/monoZeroCross.txt").c_str(), ios::in);
            else if (channels == 2)
                inFile.open((path + "/Databases/stereoZeroCross.txt").c_str(), ios::in);

            while (inFile >> data)
            {
                cout << data << endl;
            }

            break;
        }
        case 3:  // Use Spectrum Flux
        {
            if (channels == 1)
                inFile.open((path + "/Databases/monoSpectrumFlux.txt").c_str(), ios::in);
            else if (channels == 2)
                inFile.open((path + "/Databases/stereoSpectrumFlux.txt").c_str(), ios::in);

            while (inFile >> data)
            {
                cout << data << endl;
            }

            break;
        }
        case 4:  // Use Cepstrum
        {
            if (channels == 1)
                inFile.open((path + "/Databases/monoCepstrum.txt").c_str(), ios::in);
            else if (channels == 2)
                inFile.open((path + "/Databases/stereoCepstrum.txt").c_str(), ios::in);

            while (inFile >> data)
            {
                cout << data << endl;
            }

            break;
        }
        case 5:  // Use Spectrum Centroid
        {
            if (channels == 1)
                inFile.open((path + "/Databases/monoSpectrumCentroid.txt").c_str(), ios::in);
            else if (channels == 2)
                inFil.open((path + "/Databases/stereoSpectrumCentroid.txt").c_str(), ios::in);

            while (inFile >> data)
            {
                cout << data << endl;
            }

            break;
        }
        default:
        {
            cout << "Invalid algorithm." << endl;
            break
        }
    }

    return;
}

// Function euclideanDistance (float vector)
// Inputs:
//       row1 - A vector of floats containing the first row
//       row2 - A vector of floats containing the second row
//       path - A string containing the location of the output directory
//       debug - A flag that controls debug output.
// Outputs:
//       distance - A double describing the euclidean distance between row1 and row2
// Purpose:  Calculate the euclidean distance between the first and second row
double euclideanDistance(vector<double> row1, vector<double> row2, string path, bool debug)
{
    double distance;     // Will describe the euclidean distance between the row1 and row2

    for (int i = 0; i < row1.size(); i++)
    {
        distance += (row1[i] - row2[i]) * (row1[i] - row2[i]);
    }

    return sqrt(distance);
}

// Function getBestMatch (zero crossing)
// Inputs:
//       knownData - A vector containing known data sets for comparison
//       testRow - A vector containing the row to test against the knownData
//       path - A string containing the location of the output directory
//       channels - An integer describing the number of channels in the audio
//       debug - A flag that controls debug output
// Output:
//       category - An integer describing the category the audio belongs to
// Purpose:  Finds the best match of a piece of audio by comparing its zerocross to known data.
int getBestMatch(vector<vector<float> > knownData, vector<float> testRow, int channels, string path, bool debug)
{
    int match;

    return match;
}

// Function getBestMatch (spectral flux)
// Inputs:
//       knownData - A vector containing known data sets for comparison
//       testRow - An array containing spectral flux data to compare.
//       path - A string containing the location of the output directory
//       channels - An integer describing the number of channels in the audio
//       debug - A flag that controls debug output
// Output:
//       category - An integer describing the category the audio belongs to
// Purpose:  Finds the best match of a piece of audio by comparing its spectral flux to known data.
int getBestMatch(vector<vector<double> > knownData, vector<double> testRow, int channels, string path, bool debug)
{
    int match;                             // Will have the value of the match
    double tempDist;                       // Used to hold the calculated distance
    vector<vector<double> > distances;     // Will contain the distances that have been calculated
    vector<double> tempRow;                // Used to convert testRow to vector
    ifstream dataBase;                     // File pointer that will contain the database of known data patterns
    string dataBaseName;                   // A string containing the name of the database
    string line;                           // Hold each line of the database
    int lineNum;                           // Track the line number we are on in the database.

    lineNum = -1;

    dataBaseName = path + "/spectralFlux.txt";

    tempRow.push_back(testRow[0]);

    if (channels == 2)
        tempRow.push_back(testRow[1]);

    // Get the euclidean distances between the knownData and the testRow
    for (int i = 0; i < knownData.size(); i++)
    {
        tempDist = euclideanDistance(knownData[i],tempRow,path,debug);

        for (int j = 0; j < knownData[i].size(); j++)
            distances[i].push_back(knownData[i][j]);
        distances[i].push_back(tempDist);
    }

    // Output distances before sorting
    for (int i = 0; i < distances.size(); i++)
    {
        for (int j = 0; j < distances[i].size(); j++)
            cout << distances[i][j] << " ";
        cout << endl;
    }

    // Find the shortest distance
    sort(distances.begin(),distances.end(),sortDist);

    // Output distances after sorting
    for (int i = 0; i < distances.size(); i++)
    {
        for (int j = 0; j < distances[i].size(); j++)
            cout << distances[i][j] << " ";
        cout << endl;
    }

    dataBase.open(dataBaseName.c_str(),ios::in);

    while(getline(dataBase, line))
    {
        lineNum++;
        string tempNum = "";
        double leftFlux = 0;
        double rightFlux = 0;

        for (int i = 0; i < line.length(); i++)
        {
            char element = line[i];

            if (element != ' ')
                tempNum += line[i]; 
            else
            {
                if (leftFlux == 0)
                    leftFlux = stod(tempNum);
                else
                    rightFlux = stod(tempNum);

                tempNum = "";
            }
        }

        // Check to see if the entry in the database is the match
        if ((leftFlux == distances[0][0]) && (rightFlux == distances[0][1]))               
        {
            match = lineNum;
            break;
        }
    }   

    dataBase.close();
    
    return match;
}

// Function randomDatabase
// Inputs:
//       database - A vector containing known data points for generating training set.
//       trainSet - A vector that will contain the subset of training data for comparisons
//       path - A string containing the path to the output directory.
//       debug - A flag controlling the debug output.
// Outputs:  None
// Purpose: This creates a random database consisting of a subset of known data for use by ANNI.
void randomDatabase(vector<vector<double> > database, vector<vector<double> > &trainSet,string path, bool debug)
{

    int records;       // Contains the total number of records in the database
    int lowerBound;    // A random number containing the lower boundary of the subset.
    int upperBound;    // A random number containing the upper boundary of the subset.

    records = database.size();

    lowerBound = (rand() % (records - 1)) + 1;
    upperBound = (rand() % (records - lowerBound)) + lowerBound;

    for (int i = lowerBound; i < upperBound; i++)
    {
        trainSet.push_back(database[i]);
    }

    return;
}

// Function trainCodeBooks
// Inputs:
//       database - A vector containing known data points for generating the training set
//       trainSet - A vector that will contain the subset of training data for comparisons
//       nBooks - An integer describing the number of codebooks to generate
//       lRate - A double describing the learning rate
//       epochs - An integer describing the number of learning epochs
//       channels - An integer describing the number of channels in the audio file
//       path - A string containing the path to the output directory
//       debug - A flag controlling the debug output.
// Output: None
// Purpose:  This function is used to generate the number of specified codebooks for running the algorithm.
void trainCodeBooks(vector<vector<double> > database, vector<vector<double> > trainSet,int nBooks, double lRate, int epochs, int channels,string path, bool debug)
{
    double rate;        // The learning rate of the current epoch
    double error;       // Used to calculate the error rate in the learning
    double sumError;    // The summation of the total errors in the predictions
    int bmu;            // The index of the best matching codebook entry for the current database line


    // Initialize variables   
    rate = 0;
    error = 0;
    sumError = 0;
    bmu = 0;

    // Generate the codebooks
    for (int i = 0; i < nBooks; i++)
    {
        randomDatabase(database, trainSet, path, debug);
    }

    // Train the codebooks over the specified number of epochs
    for (int i = 1; i < (epochs+1); i++)
    {
        rate = lRate * (1.0/(i/epochs));        

        for (int j = 0; j < database.size(); j++)
        {
            bmu = getBestMatch(trainSet,database[j], channels, path, debug);

            for (int k = 0; k < database[j].size(); j++)
            {
                error = database[j][k] - trainSet[bmu][k];

                sumError += error * error;

                if (trainSet[bmu][trainSet[bmu].size()-1] == database[j][database[j].size()-1])
                    trainSet[bmu][k] += rate * error;
                else
                    trainSet[bmu][k] -= rate * error;
            }
        }

        cout << "Epoch: " << i << " LRate:  " << rate << "  Error:  " << sumError << endl;
    }
         
    return;
}
