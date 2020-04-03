/* 
 *  File:    Utilities.cpp
 *  Author:  Hue Truong, Andrew Moore, and Alex Reno
 *
 *  Created: February 23, 2020, 3:25 PM
 */

/**************************************Change Log *******************************/

// Created source file for utilities - A.M. Feb 23 2020
// Added in the printer function definition - A.M. Feb 23 2020
// Added vector normalization function - A.M. Feb 28 2020
// Added functions for genereating plots with gnuplot - A.M. Mar 22 2020

/**************************************End Change Log ***************************/

/**************************************To Do List ******************************/

/**************************************End To Do List **************************/

#include "../include/Utilities.h"

// Function printer
// Inputs:  
//        fileName - A string containing the name of the output file.
//        value - A string to be added to the output file.
//        algo - An integer specifying the algorithm that called the printer.
//        begin - An integer describing the beginning of the printed range.
//        end - An integer describing the end of the printed range.
// Outputs:  None
// Purpose:  Formats and outputs text to a file.
void printer (string fileName, vector<string> value, int algo, int begin, int end)
{
    ofstream outFile;                // A stream pointer for data output
    stringstream stringBuilder;      // This will be used to create the output string
    string line;                     // Stores the line as the string is built

    outFile.open(fileName, ios::app);

    switch (algo)  // Switch to determine which algorithm we are using.
    {
        case 0:  // ZeroShift algorithm
        {
            for (int i = 0; i < value.size() - 1; i++)
            {
                if (i == 0)
                    line = "Iteration:";
                if (i == 1)
                    line = "Real I [" + to_string(begin) + " - " + to_string(end) + "]:";
                if (i == 2)
                    line = "Real I+1 [" + to_string(begin) + " - " + to_string(end) + "]:";
                if (i == 3)
                    line = "Sign 1 [" + to_string(begin) + " - " + to_string(end) + "]:";
                if (i == 4)
                    line = "Sign 2 [" + to_string(begin) + " - " + to_string(end) + "]:";
                if (i == 5)
                    line = "ZeroCross [" + to_string(begin) + " - " + to_string(end) + "]:";

                outFile << line << setiosflags(ios_base::left) << setw(30-line.length()) << " "
                        << resetiosflags(ios_base::left) << setiosflags(ios_base::right) << value[i]
                        << resetiosflags(ios_base::right) << endl << endl;

            }
           
            for (int i = 0; i < 100; i++)
                outFile << "_";

            outFile << endl << endl;
 
            break;
        } // End ZeroShift algorithm

        case 2:  // Spectrum Flux algorithm
        {
            break;
        }  // End Spectrum Flux algorithm

        case 3:  // Cepstral algorithm
        {
            break;
        }  // End Cepstral algorithm

        case 4:  // Complex Cepstral algorithm
        {
            break;
        }  // End Complex Cepstral algorithm

        default:
            break;
    }

    outFile.close();
}

// Function createString (int version)
// Inputs:
//       data - An integer to be converted to a string.
//       fieldWidth - An integer specifying the width of the data field.
// Outputs:  
//       newString - The string version of the input
// Purpose:  Generate strings from given input
string createString(int data, int fieldWidth)
{
    stringstream stringBuilder;
            
    stringBuilder << setiosflags(ios_base::left) << setw(fieldWidth) << to_string(data) + "  " << resetiosflags(ios_base::left);

    return stringBuilder.str();
}

// Function createString (double version)
// Inputs:
//       data - A double to be converted to a string.
//       fieldWidth - An integer specifying the width of the data field.
// Outputs:
//       newString - The string version of the input
// Purpose:  Generate strings from given input
string createString(double data, int fieldWidth)
{
    stringstream stringBuilder;

    stringBuilder << setiosflags(ios_base::left) << setw(fieldWidth) << to_string(data) + " " << resetiosflags(ios_base::left);

    return stringBuilder.str();
}

// Function createString (boolean version)
// Inputs:
//       data - A boolean to be converted to a string.
//       fieldWidth - An integer specifying the width of the data field.
// Outputs:
//       newString - The string version of the input.
// Purpose:  Generate strings from given input
string createString(bool data, int fieldWidth)
{
    stringstream stringBuilder;
 
    stringBuilder << setiosflags(ios_base::left) << setw(fieldWidth) << to_string(data) + " " << resetiosflags(ios_base::left);

    return stringBuilder.str();
}

// Function fileExists
// Inputs:
//       fileName - A string containing the name of the file to check
// Outputs:
//       file - A filestream object cast to a boolean representing the results of the check.
// Purpose: Determine the existance of a file
bool fileExists(string fileName)
{
    ifstream infile(fileName.c_str());

    if (infile)
        return true;
    else
	return false;
}

// Function plotter
// Inputs:
//       wave - An AudioWave object
//       graphType - An integer denoting the type of graph to create.
//       alg - An integer indicating which audio algorithm(s) to plot
//       fileName - A string indicating the name of the output file.
//       path - A path to the directory for outputting the plot
//       debug - A boolean flag that controls debug output.
// Outputs: None
// Purpose:  To graph a given data file.
void plotter(AudioWave wave, int graphType, int alg, string fileName, string path, bool debug)
{
    ofstream outFile;         // Stream pointer for data output
    ofstream debugFile;       // Stream pointer for debug output.
    ifstream infile;          // Will be used to edit the sourceFile if needed.
     
    string filePrefix;        // The prefix for plot files
 
    /*
    switch(graphType)
    {
        case 0:
        {
            outFileName = plotFileName + "_boxGraph";
            break;
        }
        default:
        {
            cout << "Unsupported graph type." << endl;
            break;
        }
    }*/

    filePrefix = path + "/Plots/" + wave.getFileName() + "_";
    switch(alg)
    { 
        case 0: // Plot all algorithms
        {
            for (int i = 0; i < 6; i++)
            {
                graphAlg(wave, filePrefix, i, fileName, path, debug);
            }

            break;
        }
        case 1: // Graph Audio wave
        {
            graphAlg(wave, filePrefix, 0, fileName, path, debug);
            break;
        }
        case 2: // Graph FFT
        {
            graphAlg(wave, filePrefix, 1, fileName, path, debug);
            break;
        }
        case 3: // Graph Zero cross
        {
            graphAlg(wave, filePrefix, 2, fileName, path, debug);
            break;
        }
        case 4:
        {
            graphAlg(wave, filePrefix, 3, fileName, path, debug);
            break;
        }
        case 5:
        {
            graphAlg(wave, filePrefix, 4, fileName, path, debug);
 
            break;
        }
        case 6:
        {
            graphAlg(wave, filePrefix, 5, fileName, path, debug);

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

// Function graphAlg
// Inputs:
//       wave - An AudioWave object
//       filePrefix - A string indicating the prefix for the plot file.
//       alg - An integer indicating the algorithm to graph.
//       fileName - A string indicating the name for data output.
//       path - A string indicating the path for output files.
//       debug - A boolean flag that controls debug output.
// Outputs: None
// Purpose: Plots the results of an algorithm to file.
void graphAlg(AudioWave wave, string filePrefix, int alg, string fileName, string path, bool debug)
{
    string title;                       // Will hold the title of the plot
    string xlabel;                      // Will hold the label for the x-axis
    string ylabel;                      // Will hold the label for the y-axis
    string tempOutFile;                 // Will hold a modified name for the output file.
    string sourceFile;                  // Will hold the name of the file containing the data.
    string plotCommand;                 // Will contain the command for gnuplot
    string fullTitle[2];                // Will hold the full title for each plot.
    string fullOutFile[2];              // Will hold the full output path for the plot
    
    ofstream outFile;                   // Stream pointer for data output.

    title = wave.getFileName();
    tempOutFile = filePrefix;

    

    plotCommand = "gnuplot -c 'gnuScript.txt'";

    // Graph the left channel data
    switch(alg)
    {
        case 0:  // Graphing audio wave
        {
            fullTitle[0] = title + " Left Channel Audio Wave";
            fullTitle[1] = title + " Right Channel Audio Wave";
            fullOutFile[0] = tempOutFile + "LeftAudioWave.png";
            fullOutFile[1] = tempOutFile + "RightAudioWave.png";
            sourceFile = wave.getSourceFile(0,0);
            ylabel = "Audio Wave";
            break;
        }
        case 1: // Graphing FFT
        {
            fullTitle[0] = title + " Left Channel FFT";
            fullTitle[1] = title + " Right Channel FFT";
            fullOutFile[0] = tempOutFile + "LeftFFT.png";
            fullOutFile[1] = tempOutFile + "RightFFT.png";
            sourceFile = wave.getSourceFile(0,1);
            ylabel = "FFT";
            break;
        }
        case 2: // Graphing zero cross
        {
            fullTitle[0] = title + " Left Channel Zero Cross";
            fullTitle[1] = title + " Right Channel Zero Cross";
            fullOutFile[0] = tempOutFile + "LeftZeroCross.png";
            fullOutFile[1] = tempOutFile + "RightZeroCross.png";
            sourceFile = wave.getSourceFile(0,2);
            ylabel = "Zero Cross Level";
            break;
        }
        case 3: // Graphing spectral flux
        {
            fullTitle[0] = title + " Left Channel Spectral Flux";
            fullTitle[1] = title + " Right Channel Spectral Flux";
            fullOutFile[0] = tempOutFile + "LeftSpectralFlux.png";
            fullOutFile[1] = tempOutFile + "RightSpectralFlux.png";
            sourceFile = wave.getSourceFile(0,3);
            ylabel = "Spectral Flux";
            break;
        }
        case 4: // Graphing cepstrum
        {
            fullTitle[0] = title + " Left Channel Cepstrum";
            fullTitle[1] = title + " Right Channel Cepstrum";
            fullOutFile[0] = tempOutFile + "LeftCepstrum.png";
            fullOutFile[1] = tempOutFile + "RightCepstrum.png";
            sourceFile = wave.getSourceFile(0,4);
            ylabel = "Cepstrum";
            break;
        }
        case 5: // Graphing spectrum centroid
        {
            fullTitle[0] = title + " Left Channel Spectrum Centroid";
            fullTitle[1] = title + " Right Channel Spectrum Centroid";
            fullOutFile[0] = tempOutFile + "LeftSpectrumCentroid.png";
            fullOutFile[1] = tempOutFile + "RightSpectrumCentroid.png";
            sourceFile = wave.getSourceFile(0,5);
            ylabel = "Spectrum Centroid";
            break;
        }
        default:
        {
            cout << "Invalid algorithm." << endl;
            break;
        }
    }
 
    xlabel = "Left Channel";

    generateScript(fullTitle[0], xlabel, ylabel, fullOutFile[0], sourceFile, 1);

    outFile.open((path + "/" + fileName).c_str(), ios::app);
    outFile << timestamp() << ":  Plotting " << fullTitle[0] << "..." << endl;

    if (debug)
        cout << timestamp() << ":  Plotting " << fullTitle[0] << "..." << endl;

    system(plotCommand.c_str());

    // Graph the right channel
    if (wave.getChannels() == 2)
    {
        switch(alg)
        {
            case 0:
            {
                sourceFile = wave.getSourceFile(1,0);
                break;
            }
            case 1:
            { 
                sourceFile = wave.getSourceFile(1,1);
                break;
            }
            case 2:
            {
                sourceFile = wave.getSourceFile(1,2);
                break;
            }
            case 3:
            {
                sourceFile = wave.getSourceFile(1,3);
                break;
            }
            case 4:
            {
                sourceFile = wave.getSourceFile(1,4);
                break;
            }
            case 5:
            {
                sourceFile = wave.getSourceFile(1,5);
                break;
            }
            default:
            {
                cout << "Invalid algorithm." << endl;
                break;
            }
        }

        xlabel = "Right Channel";

        generateScript(fullTitle[1], xlabel, ylabel, fullOutFile[1], sourceFile, 2);

        outFile << timestamp() << ":  Plotting " << fullTitle[1] << "..." << endl;
        
        if (debug)
            cout << timestamp() << ":  Plotting " << fullTitle[1] << "..." << endl;

        system(plotCommand.c_str());
    }

    outFile.close();

    return;
}

// Functon generateScript
// Inputs:
//       title - A string containing the title of the graph.
//       xlabel - A string containing the x label for the graph.
//       ylabel - A string containing the y label for the graph.
//       outFileName - A string containing the name of the file to output the graph to.
//       sourceFile - A string containing the name of the source data file
//       channel - An integer describing which audio channel we are graphing
// Outputs: None
// Purpose:  Automates the generation of the gnuplot script file.
void generateScript(string title, string xlabel, string ylabel, string outFileName, string sourceFile, int channel)
{
    ofstream outFile;

    outFile.open("gnuScript.txt",ios::out);
 
    outFile << "set terminal png \n";
    outFile << "set output '" << outFileName << "'\n";
    outFile << "set title '" << title << "'\n";
    outFile << "set ylabel '" << ylabel << "'\n";
    outFile << "set xlabel '" << xlabel << "'\n";
    outFile << "plot '" << sourceFile << "' using " << channel << " with boxes \n";

    outFile.close();

    return;
}

// Function timestamp
// Inputs: None
// Ouputs: 
//       currentTime - A string containing the current system timestamp
// Purpose: The timestamp function returns a string reflecting the current system timestamp.
string timestamp()
{
    string currentTime;
    string temp;

    currentTime = "";
    temp = "";

    auto timeNow = chrono::system_clock::to_time_t(chrono::system_clock::now());

    temp = ctime(&timeNow);

    for (std::string::size_type i = 0; i < temp.size()-1; i++)
        currentTime += temp[i];

    return currentTime;
}

// Function sortDist
// Inputs:
//       v1 - The first vector to sort
//       v2 - The second vector to sort
// Outputs:
//       isSorted - A boolean value describing if v1[x] < v2[x]
// Purpose:  To sort a list of vectors from greatest to least euclidean distance
bool sortDist (const vector<double>& v1, const vector<double>& v2)
{
    return v1[v1.size()-1] < v2[v2.size()-1];
}

// Function sign
// Inputs:
//       test - A double containing the number to test
// Outputs: 
//       result - An integer describing the sign of the test number
// Purpose: The sign function determines the sign of a given number
int sign(double test)
{
    int result = 0;

    if (test > 0)
        result = 1;

    return result;
}

// Function normalize
// Inputs:
//       wave - An AudioWave object containing the audio wave being analyzed.
//       outputFile - A string describing the name of the file for output.
//       normals - A 2D vector of doubles that will contain the normalized vector
//       path - A string describing the output directory
//       debug - A boolean flag that controls the debug output.
// Outputs: None
// Purpose:  This is a function that normalizes a vector
void normalize(AudioWave wave, vector<vector<double> > &normals, string outputFile, string path, bool debug)
{
    ofstream outFile;     // A stream pointer for data output.
    ofstream debugFile;   // A stream pointer for debug output.

    double mag;           // Will hold the magnitude of the vector.
    double tempMag;       // Will hold the intermediate calculation of the magnitude.
    int step;             // Will control the size of the step in the summation.

    mag = 0;
    tempMag = 0;
    step = wave.getFrames();

    outFile.open((path + "/" + outputFile).c_str(), ios::app);
    outFile << timestamp() << ":  Calculating normals..." << endl;
    outFile.close();

    // Clear out the normals vector(s)
    for (int i = 0; i < normals.size(); i++)
        normals[i].clear();

    if (debug)
    {
        debugFile.open((path + "/normals.txt").c_str(), ios::app);

        debugFile << "Frames = " << wave.getFrames() << endl;
    }

    for (int i = 0; i < wave.getChannels(); i++)
    {
        for (int j = 0; j < wave.getChannelSize(i+1); j += step)
        {
            tempMag = 0;
            int bound = 0;

            if ((j + step) >= wave.getChannelSize(i+1))
                bound = (j + step) - wave.getChannelSize(i+1);
            else
                bound = j + step;

            // Calculate the inside of the magnitude
            for (int k = j; k <= bound; k++)
            {
                double n1 = real(wave.getChannelData(i,k));
                double n2 = real(wave.getChannelData(i,k));

                if (isnan(n1))
                    n1 = 1;
                if (isnan(n2))
                    n2 = 1;

                tempMag += n1 * n2;
            }

            // Calculate the magnitude
            mag = sqrt(abs(tempMag));

            // Calculate the normals of the windoow
            for (int k = j; k <= bound; k++)
            {
                double n = real(wave.getChannelData(i,k));

                if(isnan(n))
                    n = 1;

                double norm = n / mag;

                if (isnan(norm))
                    norm = 0;

                normals[i].push_back(norm);
            }
        
            if ( (step >= 1) && ((i + (wave.getFrames() - 1)) < (wave.getChannelSize(i+1) - 1)))
                step = wave.getFrames() - 1;
            else
                step = 1;
        }
    }

    outFile.open((path + "/" + outputFile).c_str(), ios::app);
    outFile << timestamp() << ":  Finished calculating normals." << endl;
    outFile.close();

    if (debug)
    {
        for (int i = 0; i < normals.size(); i++)
        {
            if (i == 0)
            {
                debugFile << "Left Channel contains " << normals[i].size() << " normals." << endl << endl;
                debugFile << "Normals:" << endl << endl;
            }
            else if (i == 1)
            {
                debugFile << "Right Channel contains " << normals[i].size() << " normals." << endl << endl;
                debugFile << "Normals:" << endl << endl << "\t";
            }

            debugFile << "[" << endl;

            for (int j = 0; j < normals[i].size() - 1; j++)
            {
                debugFile << normals[i].at(j) << " ";

                if (((i % 20) == 0) && (i != 0))
                    debugFile << endl << "\t";
            }

            debugFile << endl << "]" << endl << endl;
        }
    }

    debugFile.close();

    return;
}
