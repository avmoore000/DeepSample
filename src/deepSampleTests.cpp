/*! 
 *  File:   main.cpp
 *  Author: Hue Truong, Andrew Moore, and Alex Reno
 *
 *  Created February 1, 2020, 2:55 PM
 *
 */

/*!*************************************Change Log *******************************/

// Added a change log and to do list section - A.M. Feb 09 2020
// Added the portaudio library for handling the audio file inputs - A.M. Feb 09 2020
// Added in the code for generating the waves, and sedning to the fourier transform function.  - H.T. & A.M. Feb 15 2020
// Converted complex numbers from float to double template - A.M. Feb 15 2020
// Edited zerocrossing test to accept vector data - A.M. - Feb 15 2020
// Added in the chrono library for tracking completion time of algorithms - A.M. - Feb 26 2020
// Added seperate vectors for left and right waves - A.M. - Feb 27 2020

/*!*************************************End Change Log ***************************/

/*!*************************************To Do List ******************************/


/*!*************************************End To Do List **************************/

#include <iostream>
#include <fstream>
#include <complex>
#include <vector>
#include <string>
#include <chrono>
#include <sys/stat.h>
#include "../include/FourierTransform.h"
#include "../include/audioHandler.h"
#include "../include/TestSuite.h"
using namespace std;
using namespace std::chrono;

int main(int argc, char** argv) 
{
    string inputFile;                          //!< Location of user input file
    string outputFile;                         //!< Location to output file
    string filePath;                           //!< Path for the algorithm outputs

    ofstream outFile;                          //!< Pointer to the output file
    ifstream inFile;                           //!< Pointer to the user input file

    bool debug;                                //!< Toggles debug mode
    int channels;		               //!< Number of channels in sound file.
    int test;                                  //!< Specifies which tests are being run.

    vector <complex<double> > leftChannel;     //!< Container to hold the left side of the wave.
    vector<complex<double> > rightChannel;     //!< Container to hold the right side of the wave.

    if (argc <= 1)
    {
        cout << endl << endl << "Program Use:  " << endl << endl;
	cout << "./DeepSample [resultsDirectory] [inputFile] [outputFile] [channels {1,2}] [debugMode {0,1}] tests{0,1,2,3,4}" << endl << endl;
        cout << "resultsDirectory: User specified directory where results will be stored.  If directory does not exist it will be created." << endl;
        cout << "inputFile:  Audio file for analysis." << endl;
        cout << "outputFile: File name for main output file." << endl;
        cout << "channels:  1 = Mono 2 = Stereo" << endl;
        cout << "debugMode:  Toggles debug output.  Warning: Debug mode causes output of large files and slows down execution." << endl << endl;
        cout << "tests:" << endl << endl;
        cout << "0: Run all tests." << endl;
        cout << "1: Run only zero-cross test." << endl;
        cout << "2: Run only spectrum flux test." << endl;
        cout << "3: Run only cepstrum test." << endl;
        cout << "4: Run only ANNI test." << endl;
        cout << endl;
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
                    channels = atoi(argv[i]);
                    break;
                }
		case 5:
		{
		    debug = atoi(argv[i]);
		    break;
		}
                case 6:
                {
                    test = atoi(argv[i]);
                    break;
                }
		default:
		    cout << "Error with arguments." << endl;
            }
        }
    }

    // Create a directory for results
    if(mkdir(filePath.c_str(), 0777) == -1)
        cout << "Error creating directory.  " << filePath << " already exists." << endl;
    else
        cout << "Results directory created at " << filePath << endl;

    // Open the file for output
    outFile.open((filePath + "/" + outputFile).c_str(),ios::out);

    if ((test == 0) || (test == 1) || (test == 2) || (test == 3))
    {
        // Load the audio file.
        loadAudio(inputFile,leftChannel,rightChannel,channels,debug,"","","");

        outFile << "Left Channel Size:  " << leftChannel.size() << endl;
        outFile << "Right Channel Size:  " << rightChannel.size() << endl << endl;

        outFile.close();

        // Get FFT of the left channel
        auto startL = high_resolution_clock::now(); 
        fft(leftChannel,debug,filePath);
        auto stopL = high_resolution_clock::now();
        auto durationL = duration_cast<microseconds>(stopL - startL);

        outFile.open((filePath + "/" + outputFile).c_str(), ios::app);

        outFile << "FFT of left channel completed in " << durationL.count() << " ms." << endl;

        // Get the FFT of the right channel if working with stereo
        if (channels == 2)
        {
            auto startR = high_resolution_clock::now();
            fft(rightChannel,debug,filePath);
            auto stopR = high_resolution_clock::now();
            auto durationR = duration_cast<microseconds>(stopR - startR);

            outFile << "FFT of the right channel completed in " << durationR.count() << " ms." << endl;
        }

        cout << endl;

        outFile.close();

        switch(test)
        {
            case 0:
            {
                zeroCrossingTest(leftChannel,rightChannel,channels,debug,outputFile,filePath);
                spectrumFluxTest(leftChannel,rightChannel,channels,debug,outputFile,filePath);
                cepstrumTest(leftChannel,rightChannel,channels,debug,outputFile,filePath);
                anniTest(filePath,outputFile,inputFile,channels,debug);

                break;
            }
            case 1:
            {
                zeroCrossingTest(leftChannel,rightChannel,channels,debug,outputFile,filePath);

                break;
            }
            case 2:
            {
                spectrumFluxTest(leftChannel,rightChannel,channels,debug,outputFile,filePath);

                break;
            }
            case 3:
            {
                cepstrumTest(leftChannel,rightChannel,channels,debug,outputFile,filePath);

                break;
            }
            default:
            {
                cout << "Error, unsupported test." << endl << endl;

                break;
            }
        }
    }
    else if (test == 4)
        anniTest(filePath,outputFile,inputFile,channels,debug);

    return 0;
}