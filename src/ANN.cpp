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
    ofstream outFile;                         // A stream pointer for data output.
    ofstream debugFile;                       // A stream pointer for debug output.
    ifstream inFile;                          // A stream pointer for data input.

    string data;                              // A string to hold lines of data.
    string fileName;                          // A string to hold the name of the input file.

    vector<vector<double> > foldedLeftFFT;    // Will hold the leftFFT split into folds
    vector<vector<double> > foldedRightFFT;   // Will hold the rightFFT split into folds.
    vector<vector<double> > fftTrainSet;      // Will hold a FFT training set.
    vector<vector<double> > fftTestSet;       // Will hold a FFT test set.

    if (debug)
    {
        cout << "ANNI called..." << endl << endl;
        cout << "\tfolds = " << folds << endl;
        cout << "\tlearnRate = " << learnRate << endl;
        cout << "\tepochs = " << epochs << endl;
        cout << "\tcodeBooks = " << codeBooks << endl;
        cout << "\talg = " << alg << endl;
        cout << "\tchannels = " << channels << endl;
        cout << "\tpath = " << path << endl;
        cout << "\tdebug = " << debug << endl << endl;
    }

    outFile.open((path + "/ANNIResults.txt").c_str(), ios::app);

    outFile << timestamp() << ":  ANNI RUN" << endl << endl;

    if (debug)
        cout << timestamp() << ":  ANNI RUN" << endl << endl;

    for (int i = 0; i < 100; i++)
        outFile << "*";
  
    outFile << endl << endl;
    outFile.close();

    switch(alg) // Prepare the data vectors
    {
        case 0:  // Use all algorithms
        {
            break;
        }
        case 1:  // Use FFT
        {
            if (channels == 1)
            {
                fileName = path + "Databases/monoFFT.txt";

                outFile.open((path + "ANNIResults.txt").c_str(), ios::app);
                outFile << timestamp() << "Preparing " << fileName << " with " << folds << " folds..." << endl;
                outFile.close();

                prepareFolds(folds, 0, channels, fileName, foldedLeftFFT, path, debug);
            }
            else if (channels == 2)
            {
                fileName= path + "Databases/stereoFFT.txt";

                outFile.open((path + "ANNIResults.txt").c_str(), ios::app);
                outFile << timestamp() << ":  Preparing Left Channel of " << fileName << " with " 
                        << folds << " folds..." << endl;
                outFile.close();

                if (debug)
                    cout << timestamp() << ":  Preparing Left Channel of " << fileName << " with " 
                         << folds << " folds..." << endl;
                
                prepareFolds(folds, 0, channels, fileName, foldedLeftFFT, path, debug);

                outFile.open((path + "ANNIResults.txt").c_str(), ios::app);
                outFile << timestamp() << ":  Finished Preparing Left Channel." << endl;
                outFile << timestamp() << ":  Preparing Right Channel of " << fileName << " with "
                        << folds << " folds..." << endl;
                outFile.close();

                if (debug)
                {
                    cout << timestamp() << ":  Finished Preparing Left Channel." << endl;
                    cout << timestamp() << ":  Preparing Right Channel of " << fileName << " with " 
                         << folds << " folds..." << endl;
                }

                prepareFolds(folds, 1, channels, fileName, foldedRightFFT, path, debug);

                outFile.open((path + "ANNIResults.txt").c_str(), ios::app);
                outFile << timestamp() << ":  Finished Preparing Right Channel." << endl;
                outFile << timestamp() << ":  Performing Learning Vector Quantization on left FFT..." << endl << endl;
                outFile.close();

                if (debug) 
                { 
                    cout << timestamp() << ":  Finished Preparing Right Channel." << endl;
                    cout << timestamp() << ":  Preparing Learning Vector Quantization on left FFT..." << endl << endl;
                }

                // Train on the left fold
                for (int i = 0; i < foldedLeftFFT.size(); i++)
                {

                    outFile.open((path + "ANNIResults.txt").c_str(), ios::app);
                    outFile << "\t" << timestamp() << ":  Creating training set for folded left FFT..." << endl;
                    outFile.close();

                    if (debug)
                        cout << "\t" << timestamp() << ":  Creating training set for folded left FFT..." << endl;

                    // Create a training set based on the whole set of folds
                    for (int j = 0; j < foldedLeftFFT.size(); j++)
                    {
                        if (j != i)
                            fftTrainSet.push_back(foldedLeftFFT[j]);
                    }

                    outFile.open((path + "ANNIResults.txt").c_str(), ios::app);
                    outFile << "\t" << timestamp() << ":  Training set created." << endl;
                    outFile.close();

                    if (debug)
                        cout << "\t" << timestamp() << ":  Training set created." << endl;

                    outFile.open((path + "ANNIResults.txt").c_str(), ios::app);
                    outFile << "\t" << timestamp() << ":  Creating test set from folded left FFT..." << endl;
                    outFile.close();

                    if (debug)
                        cout << "\t" << timestamp() << ":  Creating test set from folded left FFT..." << endl;
      
                    for (int j = 0; j < foldedLeftFFT.size(); j++)
                        fftTestSet.push_back(foldedLeftFFT[j]);

                    outFile.open((path + "ANNIResults.txt").c_str(), ios::app);
                    outFile << "\t" << timestamp() << ":  Test set created." << endl;
                    outFile.close();

                    if (debug)
                        cout << "\t" << timestamp() << ":  Test set created." << endl;

                    // Make a prediction based on the training set
                    learningVectorQuantization(fftTrainSet, fftTestSet, codeBooks, learnRate, epochs, fileName, path, debug);

                }

                outFile.open((path + "ANNIResults.txt").c_str(), ios::app);
                outFile << endl << timestamp() << ":  Learning Vector Quantization complete." << endl << endl;
                outFile.close();

                if (debug)
                    cout << endl << timestamp() << ":  Learning Vector Quantization complete." << endl << endl;
            }
 
            break;
        }
        case 2:  // Use Zero Cross
        {
            if (channels == 1)
                inFile.open((path + "/Databases/monoZeroCross.txt").c_str(), ios::in);
            else if (channels == 2)
                inFile.open((path + "/Databases/stereoZeroCross.txt").c_str(), ios::in);

            break;
        }
        case 3:  // Use Spectrum Flux
        {
            if (channels == 1)
                inFile.open((path + "/Databases/monoSpectrumFlux.txt").c_str(), ios::in);
            else if (channels == 2)
                inFile.open((path + "/Databases/stereoSpectrumFlux.txt").c_str(), ios::in);

            break;
        }
        case 4:  // Use Cepstrum
        {
            if (channels == 1)
                inFile.open((path + "/Databases/monoCepstrum.txt").c_str(), ios::in);
            else if (channels == 2)
                inFile.open((path + "/Databases/stereoCepstrum.txt").c_str(), ios::in);

            break;
        }
        case 5:  // Use Spectrum Centroid
        {
            if (channels == 1)
                inFile.open((path + "/Databases/monoSpectrumCentroid.txt").c_str(), ios::in);
            else if (channels == 2)
                inFile.open((path + "/Databases/stereoSpectrumCentroid.txt").c_str(), ios::in);

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

// Function prepareFolds (FFT version)
// Inputs:
//       folds - An integer indicating the number of folds to create
//       curChan - An integer specifiying the current channel being manipulated.
//       channels - An integer indicating the total channels in the audio samples
//       &fft - An n-dimensional vector of doubles that will hold the folded FFT
//       path - A string indicating the path for data output
//       debug - A boolean flag that controls debug output
// Outputs: None
// Purpose:  Break a given FFT into the correct number of folds for analysis.
void prepareFolds(int folds, int curChan, int channels, string fileName, vector<vector<double> > &fft, string path, bool debug)
{
    int foldSize;                         // The size of each fold
    int start;                            // Index to start making fold
    int currentFold;                      // Current fold to add data
    vector<double> dataFold;              // A vector to hold the new fold of data
    string line;                          // A string to hold line of data.
    string data;                          // Will hold the complex number as a string
    ifstream inFile;                      // A stream pointer for data input.
    ofstream outFile;                     // A stream pointer for data output.


    start = 0;
    currentFold = 0;

    // Initialize the fft 
    for (int i = 0; i < folds; i++)
    {
        fft.push_back(dataFold);
    }

    // Grab the line of data
    inFile.open((fileName).c_str(), ios::in);

    if (channels == 1)
    {
        std::getline(inFile, line);  // Get rid of the first name
   
        while (std::getline(inFile, line))
        {
            data = "";
            foldSize = line.size() / folds;

            outFile.open((path + "/ANNIResults.txt").c_str(), ios::app);
            outFile << "\tSize of data line:  " << line.size() << endl;
            outFile << "\tFold Size:  " << foldSize << endl;
            outFile << "\tCurrent Fold:  (" << (currentFold + 1) <<" / " << folds << ")" << endl << endl;
            outFile.close();

            if (debug)
            {
                cout << "\tSize of data line:  " << line.size() << endl;
                cout << "\tFold Size:  " << foldSize << endl;
                cout << "\tCurrent Fold:  (" << (currentFold + 1) << " / " << folds << ")" << endl << endl;
            }

            for (int i = 0; i < line.size(); i++)
            {
                if (line[i] != ' ')
                {
                    data += line[i];
                }
                else
                {
                    if ( (i + 1) < (start + foldSize))
                    {

                        fft[currentFold].push_back(stod(data));
                        data = "";
                    }
                    else
                    {
                        start += foldSize;
                        currentFold++;

                        if (currentFold > (fft.size() - 1))
                            currentFold = fft.size() - 1;
                    }
                }
                    
            }

            std::getline(inFile, line);
        }
    }
    else if (channels == 2)
    {
        std::getline(inFile, line);

        while (std::getline(inFile, line))
        {
            data = "";

            if (curChan == 1)
                std::getline(inFile, line);

            foldSize = line.size() / folds;

            outFile.open((path + "/ANNIResults.txt").c_str(), ios::app);
            outFile << "\tSize of data line:  " << line.size() << endl;
            outFile << "\tFold Size:  " << foldSize << endl;
            outFile << "\tCurrent Fold:  (" << (currentFold + 1) << " / " << folds << ")" << endl << endl;
            outFile.close();

            if (debug)
            {
                cout << "\tSize of data line:  " << line.size() << endl;
                cout << "\tFold Size:  " << foldSize << endl;
                cout << "\tCurrent Fold:  (" << (currentFold + 1) << " / " << folds << ")" << endl << endl;
            }

            for (int i = 0; i < line.size(); i++)
            {
                if ((line[i] != ' '))
                {
                    data += line[i];
                }
                else 
                {
                    if ((i + 1) < (start + foldSize) )
                    {
                        fft[currentFold].push_back(stod(data));
                        data = "";
                    }
                    else
                    {
                        start += foldSize;
                        currentFold++;

                        if (currentFold > fft.size() - 1)
                            currentFold = fft.size() - 1;
                    }
                }
            }

            std::getline(inFile, line);
        }
    }

    return;
}

// Function learningVectorQuantization (FFT version)
// Inputs:
//       trainSet - An n-dimensional vector of doubles representing the training set.
//       testSet - An n-dimensional vector of doubles representing the test set.
//       codeBooks - An integer indicating the number of codebooks used for training/analysis
//       learnRate - A double indicating the learning rate
//       epochs - An integer indicating the number of epochs to train over.
//       fileName - A string indicating the name of the output file.
//       path - A string indicating the path for output files.
//       debug - A boolean flag that controls debug output.
// Output: None
// Purpose:  To determine the effectiveness of a training set 
void learningVectorQuantization(vector<vector<double> > trainSet, vector<vector<double> > testSet, int codeBooks, double learnRate, int epochs, string fileName, string path, bool debug)
{
    vector<vector<double> > codeBookSet;        // Will hold the set of codebooks for training
    ofstream outFile;                           // A stream pointer for data output

    outFile.open((path + "ANNIResults.txt").c_str(), ios::app);
    outFile << "\t" << timestamp() << ":  Training codebooks..." << endl << endl;
    outFile.close();

    if (debug)
        cout << "\t" << timestamp() << ":  Training codebooks..." << endl << endl;

    trainCodeBooks(trainSet, codeBookSet, codeBooks, learnRate, epochs, fileName, path, debug); 

    outFile.open((path + "ANNIResults.txt").c_str(), ios::app);
    outFile << endl << "\t" << timestamp() << ":  Codebooks trained." << endl;
    outFile.close();

    if (debug)
        cout << endl << "\t" << timestamp() << ":  Codebooks trained." << endl;

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

// Function getBestMatch (FFT)
// Inputs:
//       knownData - A vector containing known data sets for comparison
//       testRow - An array containing spectral flux data to compare.
//       path - A string containing the location of the output directory
//       fileName - A string indicating the file name for data output.
//       debug - A flag that controls debug output
// Output:
//       category - An integer describing the category the audio belongs to
// Purpose:  Finds the best match of a piece of audio by comparing its spectral flux to known data.
int getBestMatch(vector<vector<double> > knownData, vector<double> testRow, string fileName, string path, bool debug)
{
    int match;

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
//       fileName - A string indicating the file name for data output.
//       path - A string containing the path to the output directory
//       debug - A flag controlling the debug output.
// Output: None
// Purpose:  This function is used to generate the number of specified codebooks for running the algorithm.
void trainCodeBooks(vector<vector<double> > database, vector<vector<double> > &trainSet,int nBooks, double lRate, int epochs, string fileName,string path, bool debug)
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

    outFile.open((path + "ANNIResults.txt").c_str(), ios::app);
    outFile << "\t\t" << timestamp() << ":  Creating " << nBooks << " codebooks from training set..." << endl;
    outFile.close();

    if (debug)
        cout << "\t\t" << timestamp() << ":  Creating " << nBooks << " codebooks from training set..." << endl;

    // Generate the codebooks
    for (int i = 0; i < nBooks; i++)
    {
        randomDatabase(database, trainSet, path, debug);
    }

    outFile.open((path + "ANNIResults.txt").c_str(), ios::app);
    outFile << "\t\t" << timestamp() << ":  " << nBooks << " codebooks created." << endl;
    outFile << "\t\t" << timestamp() << ":  Training codebooks over " << epochs << " epochs..." << endl;
    outFile.close();

    if (debug)
    {
        cout << "\t\t" << timestamp() << ":  " << nBooks << " codebooks created." << endl;
        cout << "\t\t" << timestamp() << ":  Training codebooks over " << epochs << " epochs..." << endl;
    }

    // Train the codebooks over the specified number of epochs
    for (int i = 1; i < (epochs+1); i++)
    {
        rate = lRate * (1.0/(i/epochs));        

        for (int j = 0; j < database.size(); j++)
        {
            bmu = getBestMatch(trainSet, database[j], fileName, path, debug);

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

        outFile.open((path + "ANNIResults.txt").c_str(), ios::app);
        outFile << endl << "\t\t\t" << "Epoch:  " << i << endl << "\t\t\tLearning Rate:  " << rate
                << endl << "\t\t\tError:  " << sumError << endl;
        outFile.close();

        if (debug)
            cout << endl << "\t\t\tEpoch: " << i << endl << "\t\t\tLearning Rate:  " << rate 
                 << endl << "\t\t\tError:  " << sumError << endl;
    }
         
    return;
}
