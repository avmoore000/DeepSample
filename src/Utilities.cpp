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
    ofstream outFile;                // Points to user specified output file
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
//       sourceFile - A string containing the name of the file to plot
//       plotFileName - A string containing the name of the file to save plots to.
//       path - A path to the directory for outputting the plot
//       graphType - An integer denoting the type of graph to create.
//       channel - An integer describing which channel is being plotted.
//       alg - An integer describing which audio algorithm is being worked with.
// Outputs: None
// Purpose:  To graph a given data file.
void plotter(string sourceFile, string plotFileName, int graphType, int alg, int channels, string path)
{
    ifstream infile;          // Will be used to edit the sourceFile if needed.
    string plotCommand;       // Will contain the command for gnuplot
    string outFileName;       // Will hold the name of the output file
    string tempOutFile;       // Will hold a modified name for the output file.
    string xlabel;            // Will hold the label for the x-axis
    string ylabel;            // Will hold the label for the y-axis
    string title;             // Will hold the title of the plot
    string mode;              // Holds the mode of the gnuplot terminal
    
    mode = "set terminal png";
    plotCommand = "gnuplot -c 'gnuScript.txt'";

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
    }

    switch(alg)
    { 
        case 0: // Zero crossing algorithm
        {

            // Graph the left channel zero crossing
            title = "Left Channel Zero Crossing";
            xlabel = "Left Channel";
            ylabel = "Zero Cross Level";
            tempOutFile = path + "/LeftChannel/" + outFileName + "_ZeroCross.png";

            generateScript(title, xlabel, ylabel, tempOutFile, sourceFile, 1);

            cout << "Calling gnuplot" << endl;
            system(plotCommand.c_str());
        
            // Graph the right channel zero crossing
            if (channels == 2)
            {
                title = "Right Channel Zero Crossing";
                xlabel = "Right Channel";
                ylabel = "Zero Cross Level";
                tempOutFile = path + "/RightChannel/" + outFileName + "_ZeroCross.png";

                generateScript(title, xlabel, ylabel, tempOutFile, sourceFile, 2);

                cout << "Calling gnuplot" << endl;
                system(plotCommand.c_str());
            }

            break;
        }
        case 1: // Spectrum flux algorithm
        {
            // Graph the left channels of the spectral flux

            title = "Left Channel Spectral Flux";
            xlabel = "Left Channel";
            ylabel = "Spectral Flux";
            tempOutFile = path + "/LeftChannel/" + outFileName + "_SpectralFlux.png";

            generateScript(title, xlabel, ylabel, tempOutFile, sourceFile, 1);

            cout << "Calling gnuplot" << endl;
            system(plotCommand.c_str()); 

            // Graph the right channels spectral flux
            if (channels == 2)
            {
                title = "Right Channel Spectral Flux";
                xlabel = "Right Channel";
                ylabel = "Spectral Flux";
                tempOutFile = path + "/RightChannel/" + outFileName + "_SpectralFlux.png";

                generateScript(title, xlabel, ylabel, tempOutFile, sourceFile, 2);

                system(plotCommand.c_str());
            }
             
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
//       data - A vector of complex doubles describing an audiowave.
//       frames - An integer describing the number of frames to break wave into.
//       normals - A vector of doubles that will contain the normalized vector
//       channel - An integer describing the channel we are normalizing.
//       debug - A flag that controls debug output.
//       path - A string describing the output directory
// Outputs: None
// Purpose:  This is a function that normalizes a vector
void normalize(vector<complex<double> > data, vector<double> &normals, int frames, int channel, string path, bool debug)
{
    double mag;           // Will hold the magnitude of the vector
    double tempMag;       // Will hold the intermediate calculation of the magnitude.
    int step;             // Used to calculate beginning of next frame.
    string fileName;      // Will contain the file and path for debug output
    ofstream outfile;     // Stream pointer for debug output

    // Clear out the normals vector
    normals.clear();

    if (debug)
    {
        fileName = path + "/normals.txt";

        outfile.open(fileName.c_str(), ios::app);

        outfile << "Frames = " << frames << endl;

        if (channel == 1)
            outfile << "Left Channel Normals:" <<  endl;
        else if (channel == 2)
            outfile << "Right Channel Normals:" << endl;
    }

    mag = 0;
    step = frames;

    for (int i = 0; i <= data.size() - 1; i += step)
    {
        tempMag = 0;
        int bound = 0;

        if ((i+step) >= data.size())
            bound = (i + step) - data.size();
        else 
            bound = i+step;

        // Calculate the inside of the magnitude
        for (int j = i; j <= bound; j++)
        {
            tempMag += real(data[j]) * real(data[j]);
        }

        // Calculate the magnitude
        mag = sqrt(abs(tempMag));

        // Calculate normals of the window
        for (int j = i; j <= bound; j++)
        {
            double norm = real(data[j]) / mag;

            if (isnan(norm))
                norm = 0;
            normals.push_back(norm);
        }

        if ( (step >= 1) && ((i + frames-1) < data.size() -1))
            step = frames-1;
        else if (step != 1)
            step = 1;
    }

    if (debug)
    {
        outfile << "Total Elements = " << normals.size() << endl;
   
        outfile << "[" << endl;

        for (int i = 0; i <= normals.size() - 1; i++)
        {
            outfile << normals[i] << " ";
 
            if (((i % 10) == 0) && (i != 0))
                outfile << endl;
        }

        outfile << endl << "]" << endl << endl;
 
        for (int i = 0; i < 100; i++)
            outfile << "*";

        outfile << endl << endl;

        outfile.close();
    }

    return;
}
