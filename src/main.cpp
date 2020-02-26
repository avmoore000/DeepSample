/* 
 *  File:   main.cpp
 *  Author: Hue Truong and Andrew Moore
 *
 *  Created February 1, 2020, 2:55 PM
 *
 */

/**************************************Change Log *******************************/

// Added a change log and to do list section - A.M. Feb 09 2020
// Added the portaudio library for handling the audio file inputs - A.M. Feb 09 2020
// Added in the code for generating the waves, and sedning to the fourier transform function.  - H.T. & A.M. Feb 15 2020
// Converted complex numbers from float to double template - A.M. Feb 15 2020
// Edited zerocrossing test to accept vector data - A.M. - Feb 15 2020
// Added in the chrono library for tracking completion time of algorithms - A.M. - Feb 26 2020

/**************************************End Change Log ***************************/

/**************************************To Do List ******************************/

// Enable the main function to pass on multiple size arrays, eliminate hard coded test.

/**************************************End To Do List **************************/

//#include <cstdlib>
#include <iostream>
#include <fstream>
#include <complex>
#include <vector>
#include <string>
#include <chrono>
#include <sys/stat.h>
#include "../include/AudioSegmentation.h"
#include "../include/FourierTransform.h"
#include "../include/audioHandler.h"
using namespace std;
using namespace std::chrono;

void zeroCrossingTest(vector<complex<double> >, bool, string, string);;


/*
 * 
 */
int main(int argc, char** argv) 
{
    string inputFile;                  // Location of user input file
    string outputFile;                 // Location to output file
    string filePath;                   // Path for the algorithm outputs

    ofstream outFile;                  // Pointer to the output file
    ifstream inFile;                   // Pointer to the user input file

    bool debug;                        // Toggles debug mode

    vector <complex<double> > data;    // Container to hold the wave representations

    if (argc <= 1)
    {
        cout << "Program Use:  " << endl;
	cout << "./DeepSample [resultsDirectory] [inputFile] [outputFile] [debugMode {0,1}]" << endl;
	return 0;
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            switch (i)
            {
                case 1:
                {
                    filePath = argv[i];
                    break;
                }
                case 2:
		{
		    inputFile = argv[i];
		    break;
		}
		case 3:
		{
		    outputFile = argv[i];
		    break;
		}
		case 4:
		{
		    debug = atoi(argv[i]);
		    break;
		}
		default:
		    cout << "Error with arguments." << endl;
            }
        }
    }

    // Create a directory for results
    if(mkdir(filePath.c_str(), 0777) == -1)
        cout << "Error creating directory." << endl;
    else
        cout << "Results directory created." << endl;

    // Open the file for output
    outFile.open((filePath + "/" + outputFile).c_str(),ios::out);
    
    // Load audio file
    loadAudio(inputFile,data,debug);

    outFile << "Vector size:  " << data.size() << endl << endl;

    outFile.close();

    auto start = high_resolution_clock::now(); 
    fft(data,debug,filePath);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    outFile << "FFT completed in " << duration.count() << " ms." << endl << endl;

    zeroCrossingTest(data,debug,outputFile,filePath);

    return 0;
}

void zeroCrossingTest(vector<complex<double> > data, bool debug, string fileName, string filePath)
{
    float zeroCross[data.size()];      // Hold the results of the zero-crossing test
    ofstream output;                   // Points to the file to output results
   
    output.open((filePath + "/" + fileName).c_str(), ios::app);

    // Initialize the zeroCrossing array
    for (int i = 0; i < data.size(); i++)
    {
	    zeroCross[i] = 0;
    }

    auto start = high_resolution_clock::now();
    zeroCrossing(data,zeroCross,data.size(),debug);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Zero Crossing Algorithm completed in " << duration.count() << " ms." << endl;
    output << "Zero Crossing Algorithm completed in " << duration.count() << " ms." << endl << endl;

    if (debug)
    {
        output << "Zero Crossing Results" << endl << endl;

        output << "Signal Array:  " << endl;
        output << "[" << endl;

        for (int i = 0; i < data.size()-1; i++)
        {
            output << data[i] << " ";

	    if ((i != 0) && ((i%10) == 0))
	        output << endl;
        }
        output << endl << "]" << endl << endl;
    
        output << "ZeroCrossTest array:  " << endl;
        output << "[" << endl;

        for (int i = 0; i < data.size(); i++)
        {
            output << zeroCross[i] << " ";

            if ((i > 0) && ((i % 50) == 0))
	    {
	        output << endl;
	    }

        }
    
        output << endl << "]" << endl;
    }

    output.close();
    
    return;
}
