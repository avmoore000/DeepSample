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

/**************************************End Change Log ***************************/

/**************************************To Do List ******************************/

// Enable the main function to pass on multiple size arrays, eliminate hard coded test.

/**************************************End To Do List **************************/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <complex>
#include <vector>
#include <list>
#include "../include/AudioSegmentation.h"
#include "../include/FourierTransform.h"
#include "../include/audioHandler.h"
using namespace std;

void zeroCrossingTest(vector<complex<double> >, bool, string);


/*
 * 
 */
int main(int argc, char** argv) 
{
    string inputFile;  // Will hold the location of user input file.
    string outputFile; // Will hold the location to output file

    ofstream outFile;  // Pointer to the output file
    ifstream inFile; // Pointer to the user input file.

    bool debug; // Toggles debug mode.

    const complex<double> i(1.0,2.0); // Generate waves for testing

    vector <complex<double> > data; // Container to hold the wave representations.

    if (argc <= 1)
    {
        cout << "Program Use:  " << endl;
	cout << "./DeepSample [inputFile] [outputFile] [debugMode {0,1}]" << endl;
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
		    inputFile = argv[i];
		    break;
		}
		case 2:
		{
		    outputFile = argv[i];
		    break;
		}
		case 3:
		{
		    debug = atoi(argv[i]);
		    break;
		}
		default:
		    cout << "Error with arguments." << endl;
            }
        }
    }

    outFile.open(outputFile,ios::out);

    
    // Generate sample data

    loadAudio(inputFile, "testFile");

    for (int i = 0; i < 100; i++)
    {
	    complex<double> num;
	    if ((i % 3) == 0)
	    {
                num = polar(-static_cast<double>(i), 0.0);
            }
	    else
	        num = polar(static_cast<double>(i),0.0);
	    
	    data.push_back(num);
    }

    outFile << "Vector size:  " << data.size() << endl << endl;

    outFile.close();

    fft(data,debug,outputFile);

    zeroCrossingTest(data,debug,outputFile);

    return 0;
}

void zeroCrossingTest(vector<complex<double> > data, bool debug, string fileName)
{
    // f1 array will hold the results of zero-crossing tests
    float f1[data.size()];
    float zeroCross[data.size()];
    int bx = data.size();
    ofstream output;
    output.open(fileName, ios::app);

    float test[5];

    // Initialize the f1 array
    for (int i = 0; i < bx; i++)
    {
	    f1[i] = -5;
    }

    zeroCrossing(data,f1,bx,debug,fileName);

    output << "Zero Crossing Results" << endl << endl;
    if (debug)
    {
        output << "Signal Array:  " << endl;
        output << "[" << endl;

        for (int i = 0; i < bx-1; i++)
        {
            output << data[i] << " ";

	    if ((i != 0) && ((i%10) == 0))
	        output << endl;
        }
        output << endl << "]" << endl << endl;
    }
    
    output << "ZeroCrossTest array:  " << endl;
    output << "[" << endl;

    for (int i = 0; i < bx; i++)
    {
        output << f1[i] << " ";

	if ((i != 0) && ((i % 10) == 0))
	{
	    output << endl;
	}

    }
    
    output << endl << "]" << endl;

    output.close();
    
    return;
}
