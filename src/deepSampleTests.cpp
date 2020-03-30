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
// Modified the program to use the new AudioWave class - A.M. - 29 Mar 2020
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
#include "../include/AudioWave.h"
#include "../include/Utilities.h"
using namespace std;
using namespace std::chrono;

int main(int argc, char** argv) 
{

    vector<AudioWave> waves;                    // A vector of audio wave objects.
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

   /* auto start = high_resolution_clock::now();  // Used for tracking start times
    auto stop = high_resolution_clock::now();   // Used for tracking end times.
    auto duration = duration_cast<milliseconds>(stop - start);  // Used to track duration.*/

    AudioWave w("test",2);

    waves.push_back(w);

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
        cout << "1: Run the FFT test." << endl;
        cout << "2: Run only zero-cross test." << endl;
        cout << "3: Run only spectrum flux test." << endl;
        cout << "4: Run only cepstrum test." << endl;
        cout << "5: Run only ANNI test." << endl;
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

    // Output initial run information
    outFile.open((filePath + "/" + outputFile).c_str(),ios::out);
    outFile << "Running DeepSampleTest with the following options:" << endl << endl;
    outFile << "\tfilePath:  " << filePath << endl;
    outFile << "\tinputFile:  " << inputFile << endl;
    outFile << "\tchannels:  " << channels << endl;
    outFile << "\tdebug:  " << debug << endl;
    outFile << "\ttest:  " << test << endl << endl;
    outFile.close();

    if ((test == 0) || (test == 1) || (test == 2) || (test == 3) || (test == 4))
    {
        // Load the audio file.

        outFile.open((filePath + "/" + outputFile).c_str(), ios::app);
        outFile << timestamp() << ":  Loading audio file..." << endl;
        outFile.close();

        auto start = high_resolution_clock::now();
        loadAudio(inputFile, waves[0], "", "", channels, "", debug);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        outFile.open((filePath + "/" + outputFile).c_str(), ios::app);
        outFile << timestamp() << ":  Finished loading audio file in " << duration.count() << "us."  << endl << endl;
        outFile << "\tLeft Channel Size:  " << waves[0].getLeftSize() << endl;
        outFile << "\tRight Channel Size:  " << waves[0].getRightSize() << endl << endl;
        outFile.close();
    }

    switch(test)
    {
        case 0:        // Run all tests
        {
            break;
        }
        case 1:        // Run FFT test
        {

            outFile.open((filePath + "/" + outputFile).c_str(), ios::app);
            outFile << timestamp() << ":  Starting FFT Test..." << endl;
            outFile.close();

            if (debug)
                cout << timestamp() << ":  Starting FFT Test..." << endl;
     
            auto start = high_resolution_clock::now();
            fft(waves[0], outputFile, filePath, debug);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            outFile.open((filePath + "/" + outputFile).c_str(), ios::app);
            outFile << timestamp() << ":  FFT Test completed in " << duration.count() << " us." << endl;
            outFile.close();

            if (debug)
                cout << timestamp() << ":  FFT Test completed in " << duration.count() << " us." << endl;

            break; 
        }
        case 2:        // Run zero crossing test
        {

            outFile.open((filePath + "/" + outputFile).c_str(), ios::app);
            outFile << timestamp() << ":  Starting Zero Crossing Test..." << endl;
            outFile.close();

            if (debug)
                cout << timestamp() << ":  Starting Zero Crossing Test..." << endl;

            auto start = high_resolution_clock::now();
            zeroCrossingTest(waves[0], outputFile, filePath, debug);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
 
            outFile.open((filePath + "/" + outputFile).c_str(), ios::app);
            outFile << timestamp() << ":  Zero Crossing Test completed in " << duration.count() << " us." << endl;
            outFile << endl << "\tZero Cross Database Contains " << waves[0].getZSize(0) << " channels." << endl;
            outFile << "\tLeft Channel Zero Cross Size:  " << waves[0].getZSize(1) << endl;
            outFile << "\tRight Channel Zero Cross Size:  " << waves[0].getZSize(2) << endl;
            outFile.close();

            if (debug)
                cout << timestamp() << ":  Zero Crossing Test completed in " << duration.count() << "us." << endl;
            break;
        }
        case 3:        // Run spectrum flux test
        {
            break;
        }
        case 4:        // Run cepstrum test
        {
            break;
        }
        default:       // Invalid test option
        {
            break;
        }
    }

        
/*
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
*/
    return 0;
}
