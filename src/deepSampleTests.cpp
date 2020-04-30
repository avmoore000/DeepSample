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
// Added the Spectrum Centroid test - A.R. - 22 Apr 2020
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

    AudioWave w("test",2);

    waves.push_back(w);

    if (argc <= 1)
    {
        cout << endl << endl << "Program Use:  " << endl << endl;
	cout << "./DeepSample [resultsDirectory] [inputFile] [outputFile] [channels {1,2}]"
             << endl << "   [debugMode {0,1}] tests{0,1,2,3,4,5,6,7}" << endl << endl;
        cout << "\tresultsDirectory:"
             << endl << endl << "\t     User specified directory where results will be stored.  If directory" 
             << endl << "\t     does not exist it will be created" << endl << endl; 
        cout << "\tinputFile:"
             << endl << endl << "\t     Audio file for analysis." << endl << endl;
        cout << "\toutputFile:"
             << endl << endl << "\t     File name for main output file." << endl << endl;
        cout << "\tchannels:"
             << endl << endl << "\t     1 = Mono " << endl;
        cout << "\t     2 = Stereo" << endl << endl;
        cout << "\tdebugMode:"
             << endl << endl << "\t     Toggles debug output.  Warning: Debug mode causes output of large"
             << endl << "\t     files and slows down execution." << endl << endl;
        cout << "\ttests:" << endl << endl;
        cout << "\t     0: Run all tests." << endl;
        cout << "\t     1: Audio Loader test." << endl;
        cout << "\t     2: Run the FFT test." << endl;
        cout << "\t     3: Run only zero-cross test." << endl;
        cout << "\t     4: Run only spectrum flux test." << endl;
        cout << "\t     5: Run only cepstrum test." << endl;
        cout << "\t     6: Run only spectrum centroid test." << endl;
        cout << "\t     7: Run only ANNI test." << endl;
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
    outFile << endl << "Running DeepSampleTest with the following options:" << endl << endl;
    outFile << "\tfilePath:  " << filePath << endl;
    outFile << "\tinputFile:  " << inputFile << endl;
    outFile << "\tchannels:  " << channels << endl;
    outFile << "\tdebug:  " << debug << endl;
    outFile << "\ttest:  " << test << endl << endl;
    outFile.close();

    switch(test)
    {
        case 1:        // Load Audio test
        {
            if (debug)
                cout << timestamp() << ":  Starting Audio Loader Test..." << endl;

            audioTest(waves[0], inputFile, "", "", channels, 1, outputFile, filePath, debug);

            if (debug)
                cout << timestamp() << ":  Audio Loader Test complete." << endl;

            break;
        }
        case 2:        // Run FFT test
        {
            if (debug)
            {
                cout << timestamp() << ":  Doing prep work for FFT Test..." << endl;
                cout << timestamp() << ":  Loading Audio..." << endl;
            }

                loadAudio(waves[0], inputFile, "", "", channels, 1, filePath, debug);

            if (debug)
            {
                cout << timestamp() << ":  Audio loaded." << endl;
                cout << timestamp() << ":  Prep work complete." << endl;
                cout << timestamp() << ":  Starting FFT Test..." << endl;
            }

            fftTest(waves[0], outputFile, filePath, debug);

            if (debug)
                cout << timestamp() << ":  FFT Test complete." << endl;

            break; 
        }
        case 3:        // Run zero crossing test
        {
            if (debug)
            {
                cout << timestamp() << ":  Doing prep work for Zero Cross Test..." << endl;
                cout << timestamp() << ":  Loading Audio..." << endl;
            }

                loadAudio(waves[0], inputFile, "", "", channels, 1, filePath, debug);     

            if (debug)
            {
                cout << timestamp() << ":  Audio loaded." << endl;
                cout << timestamp() << ":  Prep work complete." << endl;
                cout << timestamp() << ":  Starting Zero Cross Test..." << endl;
            }

            zeroCrossingTest(waves[0], outputFile, filePath, debug); 

            if (debug)
                cout << timestamp() << ":  Zero Cross Test complete." << endl;

            break;
        }
        case 4:        // Run spectrum flux test
        {
            if (debug)
            {
                cout << timestamp() << ":  Doing prep work for Spectrum Flux Test..." << endl;
                cout << timestamp() << ":  Loading Audio..." << endl;
            }
          
                loadAudio(waves[0], inputFile, "", "", channels, 1, filePath, debug);

            if (debug)
            {
                cout << timestamp() << ":  Audio loaded." << endl;
                cout << timestamp() << ":  Prep work complete." << endl;
                cout << timestamp() << ":  Starting Spectrum Flux Test..." << endl;
            }

            spectrumFluxTest(waves[0], outputFile, filePath, debug);

            if (debug)
                cout << timestamp() << ":  Spectrum Flux Test complete." << endl;

            break;
        }
        case 5:        // Run cepstrum test
        {
            if (debug)
            {
                cout << timestamp() << ":  Doing prep work for Cepstrum Test..." << endl;
                cout << timestamp() << ":  Loading Audio..." << endl;
            }

                loadAudio(waves[0], inputFile, "", "", channels, 1, filePath, debug);

            if (debug)
            {
                cout << timestamp() << ":  Audio loaded." << endl;
                cout << timestamp() << ":  Prep work complete." << endl;
                cout << timestamp() << ":  Starting Cepstrum Test..." << endl;
            }

            cepstrumTest(waves[0], outputFile, filePath, debug);


            if (debug)
                cout << timestamp() << ":  Cepstrum Test complete." << endl;

            break;
        }
        case 6:        // Run spectrum centroid test
        {
            if (debug)
            {
                cout << timestamp() << ":  Doing prep work for Spectrum Centroid Test..." << endl;
                cout << timestamp() << ":  Loading Audio..." << endl;
            }
          
                loadAudio(waves[0], inputFile, "", "", channels, 1, filePath, debug);

            if (debug)
            {
                cout << timestamp() << ":  Audio loaded." << endl;
                cout << timestamp() << ":  Prep work complete." << endl;
                cout << timestamp() << ":  Starting Spectrum Centroid Test..." << endl;
            }

            spectrumCentroidTest(waves[0], outputFile, filePath, debug);

            if (debug)
                cout << timestamp() << ":  Spectrum Centroid Test complete." << endl;

            break;
        }
        case 7:  // Run ANNI test (runs all tests)
        case 0:
        {
            // Do the prep work for ANNI
            if (debug)
            {
                if (test == 5)
                    cout << timestamp() << ":  Doing prep work for ANNI Test..." << endl;

                cout << timestamp() << ":  Loading Audio..." << endl;
            }
                loadAudio(waves[0], inputFile, "", "", channels, 1, filePath, debug);

            if (debug)
            {
                cout << timestamp() << ":  Audio Loaded." << endl;
                cout << timestamp() << ":  Generating FFT..." << endl;
            }

            // Generate the FFT
            fftTest(waves[0], outputFile, filePath, debug);
            
            if (debug)
            {
                cout << timestamp() << ":  FFT generation complete." << endl;
                cout << timestamp() << ":  Generating Zero Cross..." << endl;
            }

            // Generate zero cross
            zeroCrossingTest(waves[0], outputFile, filePath, debug);     

            if (debug)
            {
                cout << timestamp() << ":  Zero Cross generation complete." << endl;
                cout << timestamp() << ":  Generating Spectrum Flux..." << endl;
            }

            // Generate spectrum flux
            spectrumFluxTest(waves[0], outputFile, filePath, debug);

            if (debug)
            {
                cout << timestamp() << ":  Spectrum Flux generation complete." << endl;
                cout << timestamp() << ":  Generating Cepstrum..." << endl;
            }

            // Generate cepstrum
            cepstrumTest(waves[0], outputFile, filePath, debug);

            if (debug)
            {
                cout << timestamp() << ":  Cepstrum generation complete." << endl;
                cout << timestamp() << ":  Generating Spectrum Centroid..." << endl;
            }

            // Generate spectrum centroid
            spectrumCentroidTest(waves[0], outputFile, filePath, debug);

            if (debug)
            {
                cout << timestamp() << ":  Spectrum Centroid generation complete." << endl;
                cout << timestamp() << ":  Prep work complete." << endl;
                cout << timestamp() << ":  Starting ANNI Test..." << endl;
            }

            anniTest(waves[0], outputFile, filePath, debug);

            if (debug)
                cout << timestamp() << ":  ANNI Test complete." << endl;

            break;
        }
        default:       // Invalid test option
        {
            cout << "Error, unsupported test." << endl << endl;
            break;
        }
    }
 
    return 0;
}
