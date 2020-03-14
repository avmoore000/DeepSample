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

using namespace std;

// Function ANNI
// Inputs:
//       zeroCrossResults - An n-dimensional vector containing the zero cross of the audio file.
//       spectrumFluxResults - An array of doubles containing the spectral flux of the audio file.
//       path - A string containing the location of the output files.
//       audioName - A string containing the name of the current audio file.
//       channels - The number of channels in the audio file.
//       debug - A flag that controls debug output.
// Outputs: None
// Purpose: ANNI is an artificial neural network that is used to learn the classifications of music.
void ANNI(vector<vector<float> > zeroCrossResults, double spectrumFluxResults[],string path, string audioName,int channels, bool debug)
{
    ofstream outFile;    // File pointer for outputting results and debug information.
    string fileName;     // Name of the output file for ANNI to use.
    
    fileName = path + "/" + "ANNIResults.txt";

    if (fileExists(fileName))
        outFile.open(fileName, ios::app);
    else
    {
        outFile.open(fileName, ios::out);
   
        outFile << "ANNI Results" << endl << endl;

        for (int i = 0; i < 100; i++)
            outFile << "*";
  
        outFile << endl << endl;
    }

    if (debug)
    {
        outFile << "ZeroCross size = " << zeroCrossResults.size() << endl;
        outFile << "SpectrumFlux[0] = " << spectrumFluxResults[0] << endl;

        if (channels == 2)
            outFile << "SpectrumFlux[1] = " << spectrumFluxResults[1] << endl;
    }

    outFile << audioName << ":" << endl;

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
double euclideanDistance(vector<double> row1,vector<double> row2,string path,bool debug)
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
int getBestMatch(vector<vector<float> > knownData, vector<float> testRow, string path,int channels, bool debug)
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
int getBestMatch(vector<vector<double> > knownData, double testRow[], string path,int channels, bool debug)
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
void randomDatabase(vector<vector<double> > database, vector<vector<double> > trainSet,string path, bool debug)
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
