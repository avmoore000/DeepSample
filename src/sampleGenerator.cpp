/* 
 *  File:   sampleGeneration.cpp
 *  Author: Hue Truong, Andrew Moore, and Alex Reno
 *
 *  Created February 1, 2020, 2:55 PM
 *
 */

/**************************************Change Log *******************************/

// Added a change log and to do list section - A.M. Feb 09 2020

/**************************************End Change Log ***************************/

/**************************************To Do List ******************************/


/**************************************End To Do List **************************/

#include <iostream>
#include <fstream>
#include <complex>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <ctime>
#include <sys/stat.h>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include "../include/FourierTransform.h"
#include "../include/audioHandler.h"
#include "../include/Utilities.h"
#include "../include/AudioAlgorithms.h"
using namespace std;
using namespace std::chrono;
namespace fs = boost::filesystem;

struct path_leaf_string
{
    std::string operator()(const boost::filesystem::directory_entry& entry) const
    {
        return entry.path().leaf().string();
    }
};

int main(int argc, char** argv) 
{
    string inputDirectory;                     // Location of user input files
    string outputFilePrefix;                   // Prefix for the output file
    string filePath;                           // Path for the algorithm outputs

    ostringstream convertor;                  // Used to convert directory entries to strings

    ofstream outFile;                          // Pointer to the output file used for runtime data
    ofstream resultsFile;                      // Pointer to the output file used for audio segmentation data
    ifstream inFile;                           // Pointer to the user input file

    bool debug;                                // Toggles debug mode
    int channels;		               // Number of channels in sound file.
    int test;                                  // Specifies which tests are being run.

    double spectralFluxResults[2];             // Will hold the results of the spectral flux algorithm

    fs::path p;                                // Will contain an iterable file path

    vector <complex<double> > leftChannel;     // Container to hold the left side of the wave.
    vector<complex<double> > rightChannel;     // Container to hold the right side of the wave.
    vector<string> fileNames;                  // Will contain the names of the audio files for the current dataset.

    if (argc <= 1)
    {
        cout << endl << endl << "Program Use:  " << endl << endl;
	cout << "./SampleGeneration [resultsDirectory] [inputDirectory] [outputFilePrefix] [channels {1,2}] [debugMode {0,1}] tests{0,1,2,3,4}" << endl << endl;
        cout << "resultsDirectory: User specified directory where results will be stored.  If directory does not exist it will be created." << endl;
        cout << "inputDirectory:  Directory containing audio files for analysis" << endl;
        cout << "outputFilePrefix: File prefix for main output file." << endl;
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
		    inputDirectory = argv[i];
		    break;
		}
		case 3:
		{
		    outputFilePrefix = argv[i];
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

    // Open the file for data output
    outFile.open((filePath + "/" + outputFilePrefix + "_output.txt").c_str(),ios::out);

    outFile << "SampleGenerator run with the following arguments:" << endl << endl;
    outFile << "\tResults Directory:  " << filePath << endl;
    outFile << "\tInput Directory:  " << inputDirectory << endl;
    outFile << "\tOutputfile Prefix:  " << outputFilePrefix << endl;
    outFile << "\tChannels:  " << channels << endl;
    outFile << "\tDebug:  " << debug << endl << endl;

    p = inputDirectory;

    if (fs::is_directory(inputDirectory))
    {
        // Step through results directory and create data from each file
        for (auto &entry : boost::make_iterator_range(fs::directory_iterator(p)))
        {
            convertor << entry;

            string temp = convertor.str();
            string converted = "";

            for (int i = 0; i < temp.size(); i++)
            {
                if (temp[i] != '\"')
                    converted += temp[i];
            }
            fileNames.push_back(converted);
            convertor.str("");
            convertor.clear();
        }
    }
    else
        cout << "Invalid input directory." << endl;

    // Run algorithms for each file in the input directory
    for (int i = 0; i < fileNames.size(); i++)
    {
        cout << "Performing analysis of " << fileNames[i] << endl;

        outFile << timestamp() << ": Performing analysis of " << fileNames[i] << endl;
    
        outFile << timestamp() << ": Loading audio file..." << endl;

        loadAudio(fileNames[i], leftChannel, rightChannel, channels, debug, filePath);

        outFile << timestamp() << ": Audio file loaded." << endl;

        outFile << "\tLeft channel size:  " << leftChannel.size() << endl;

        if (channels == 2)
            outFile << "\tRight channel size:  " << rightChannel.size() << endl;

        outFile << timestamp() << ": Performing FFT of left channel..." << endl;

        auto start = high_resolution_clock::now();
        fft(leftChannel, debug, filePath);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        outFile << timestamp() << ": FFT of left channel completed in " << duration.count() << " microseconds." << endl;

        if (channels == 2)
        {
            outFile << timestamp() << ": Performing FFT of right channel..." << endl;

            start = high_resolution_clock::now();
            fft(rightChannel, debug, filePath);
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);

            outFile << timestamp() << ": FFT of right channel completed in " << duration.count() << " microseconds." << endl;
        }

        if (debug)
        {
            resultsFile.open((filePath + "/" + outputFilePrefix + "_fftResults.txt").c_str(),ios::app);

            for (int i = 0; i < leftChannel.size(); i++)
            {
                resultsFile << leftChannel[i] << " ";

                if ((i%10) == 0)
                    resultsFile << endl;
            }

            for (int i = 0; i < rightChannel.size(); i++)
            {
                resultsFile << rightChannel[i] << " ";

                if ((i%10) == 0)
                    resultsFile << endl;
            }

            resultsFile.close();
        }
        // Get the zero cross of the current file

        // Do the prep work for the algorithm
        vector<float> dataPoints(leftChannel.size(),0);                  // Will contain the data points for each channel.
        vector<vector<float> > zeroCrossResults(2,dataPoints);           // Will contain the results of the zero cross algorithm.

        outFile << timestamp() << ": Beginning zero cross algorithm..." << endl;

        start = high_resolution_clock::now();
        zeroCross(leftChannel,rightChannel,zeroCrossResults,channels,debug,filePath);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        
        dataPoints.clear();
       
        outFile << timestamp() << ": Zero cross algorithm completed in " << duration.count() << " microseconds." << endl;

        outFile << timestamp() << ": Updating zero cross database at " << outputFilePrefix;


        if (channels == 1)
        {
            outFile << "_zeroCrossMono.txt..." << endl;
            resultsFile.open((filePath + "/" + outputFilePrefix + "_zeroCrossMono.txt").c_str(),ios::app);
        }
        else if (channels == 2)
        {
            outFile << "_zeroCrossStereo.txt..." << endl;
            resultsFile.open((filePath + "/" + outputFilePrefix + "_zeroCrossStereo.txt").c_str(),ios::app);
        }

        for (int i = 0; i < zeroCrossResults.size(); i++)
        {
            if (zeroCrossResults[i].size() > 0)
            {
                for (int j = 0; j < zeroCrossResults[i].size(); j++)
                    resultsFile << zeroCrossResults[i][j] << " ";

                resultsFile << endl;
            }
        }

        resultsFile << endl;
        resultsFile.close();
        zeroCrossResults.clear();

        outFile << timestamp() << ": Finished updating zero cross database." << endl;

        outFile << timestamp() << ": Beginning spectrum flux algorithm..." << endl;

        start = high_resolution_clock::now();
        spectralFlux(leftChannel, rightChannel, spectralFluxResults, channels, debug, filePath);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);

        outFile << timestamp() << ": Spectrum flux algorithm completed in " << duration.count() << " microseconds." << endl;

        outFile << timestamp() << ": Updating spectrum flux database at " << outputFilePrefix;

        if (channels == 1)
        {
            outFile << "_spectrumFluxMono.txt..." << endl;
            resultsFile.open((filePath + "/" + outputFilePrefix + "_spectrumFluxMono.txt").c_str(),ios::app);
        }
        else if (channels == 2)
        {
            outFile << "_spectrumFluxStereo.txt..." << endl;
            resultsFile.open((filePath + "/" + outputFilePrefix + "_spectrumFluxStereo.txt").c_str(),ios::app);
        }

        resultsFile << spectralFluxResults[0];

        if (channels == 2)
            resultsFile << " " << spectralFluxResults[1];

        resultsFile << endl;

        resultsFile.close();

        outFile << timestamp() << ": Beginning cepstrum algorithm..." << endl;

        start = high_resolution_clock::now();
        //cepstrum();
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);

        outFile << timestamp() << ": Cepstrum algorithm completed in " << duration.count() << " microseconds." << endl;

        outFile << timestamp() << ": Updating cepstrum database at " << outputFilePrefix;

        if (channels == 1)
        {
            outFile << "_cepstrumMono.txt..." << endl;
            resultsFile.open((filePath + "/" + outputFilePrefix + "_cepstrumMono.txt").c_str(),ios::app);
        }
        else if (channels == 2)
        {
            outFile << "_cepstrumStereo.txt..." << endl;
            resultsFile.open((filePath + "/" + outputFilePrefix + "_cepstrumStereo.txt").c_str(),ios::app);
        }

        resultsFile << endl;

        resultsFile.close();

        outFile << endl;
        cout << endl;

        leftChannel.clear();
        rightChannel.clear();
        
    }

    return 0;
}
