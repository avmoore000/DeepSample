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
#include <stdio.h>
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
    string outputFileName;                     // Prefix for the output file
    string filePath;                           // Path for the algorithm outputs
    string sFluxDir;                           // Directory for individual spectrum flux files
    string zCrossDir;                          // Directory for individual zero cross results
    string cepstrumDir;                        // Directory for individual cepstrum results
    string fftDir;                             // Directory for individual fft results
    string audioDir;                           // Directory for individual converted audio files
    string plotPath;                           // Contains a user specified location for plotting data.
    string plotFileName;                       // Contains the name of the file to save plots to.
    string resultsFileName;                    // The name of the current results file

    ostringstream convertor;                   // Used to convert directory entries to strings

    ofstream outFile;                          // Pointer to the output file used for runtime data
    ofstream resultsFile;                      // Pointer to the output file used for audio segmentation data
    ofstream database;                         // Pointer to the main database for the current segmentation algorithm.
    ifstream inFile;                           // Pointer to the user input file

    bool debug;                                // Toggles debug mode
    bool plot;                                 // Toggles graph plotting
    int channels;		               // Number of channels in sound file.
    int test;                                  // Specifies which tests are being run.

    double spectralFluxResults[2];             // Will hold the results of the spectral flux algorithm

    fs::path p;                                // Will contain an iterable file path

    vector <complex<double> > leftChannel;     // Container to hold the left side of the wave.
    vector<complex<double> > rightChannel;     // Container to hold the right side of the wave.
    vector<string> fileNames;                  // Will contain the names of the audio files for the current dataset.
    vector<string> scrubbedFileNames;          // Will contain the names of the files without the directory paths.

    outputFileName = "";

    if (argc <= 1)
    {
        cout << endl << endl << "Program Use:  " << endl << endl;
	cout << "./SampleGeneration [resultsDirectory] [inputDirectory] [outputFileName] [channels {1,2}] [debugMode {0,1}] [plot {0,1}]" << endl << endl;
        cout << "resultsDirectory: User specified directory where results will be stored.  If directory does not exist it will be created." << endl;
        cout << "inputDirectory:  Directory containing audio files for analysis" << endl;
        cout << "outputFileName:  Name of the output file prefix" << endl;
        cout << "channels:  1 = Mono 2 = Stereo" << endl;
        cout << "debugMode:  Toggles debug output.  Warning: Debug mode causes output of large files and slows down execution." << endl;
        cout << "plot: Toggles plotting of data graphs.  If selected, a directory called Plots will be created." << endl << endl;
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
                    outputFileName = argv[i];
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
                    plot = atoi(argv[i]);

                    cout << endl << "Please enter the directory to save plots to:  " ;
                    cin >> plotPath;
                    cout << endl;
                    break;
                }
		default:
		    cout << "Error with arguments." << endl;
            }
        }
    }

    // Create a directory for results
    if(mkdir(filePath.c_str(), 0777) == -1)
        cout << filePath << " directory already exists.  Will be using it as results directory." << endl;
    else
    {
        cout << "Results directory created at " << filePath << endl;

        sFluxDir = filePath + "/SpectrumFlux/";
        zCrossDir = filePath + "/ZeroCross/";
        cepstrumDir = filePath + "/Cepstrum/";
        
        mkdir(sFluxDir.c_str(), 0777);
        mkdir(zCrossDir.c_str(),0777);
        mkdir(cepstrumDir.c_str(),0777);
    } 

    if (debug)
    {
        fftDir = filePath + "/FFT/";
        mkdir(fftDir.c_str(),0777);

        audioDir = filePath + "/AudioDir/";
        mkdir(audioDir.c_str(),0777);
    }
    
    // Create plots directory
    if (plot)
        if (mkdir(plotPath.c_str(),0777) == -1)
            cout << "Error creating directory. " << plotPath << " already exists." << endl;
        else
            cout << "Plots directory created at " << plotPath << endl;

    // Open the file for data output
    outFile.open((filePath + "/" + outputFileName + "_output.txt").c_str(),ios::out);

    outFile << "SampleGenerator run with the following arguments:" << endl << endl;
    outFile << "\tResults Directory:  " << filePath << endl;
    outFile << "\tInput Directory:  " << inputDirectory << endl;
    outFile << "\tOutputfile Prefix:  " << outputFileName << endl;
    outFile << "\tChannels:  " << channels << endl;
    outFile << "\tDebug:  " << debug << endl;
    outFile << "\tPlot:  " << plot << endl << endl;

    

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

            string tempName = "";

            for (int i = converted.size()-1; i > 0; i--)
            {
                if (converted[i] != '/')
                    tempName += converted[i];
                else
                    break;
            }

            converted = "";

            for (int i = tempName.size()-1; i >= 0; i--)
            {
                 converted += tempName[i];
            }
       
            scrubbedFileNames.push_back(converted);

            cout << "File Name = " << converted << endl;
        }
    }
    else
        cout << "Invalid input directory." << endl;

    // Run algorithms for each file in the input directory
    for (int i = 0; i < fileNames.size(); i++)
    {
        cout << "Performing analysis of " << fileNames[i] << endl;

        outFile << timestamp() << ": Performing analysis of " << scrubbedFileNames[i] << endl;
    
        outFile << timestamp() << ": Loading audio file..." << endl;

        loadAudio(fileNames[i], leftChannel, rightChannel, audioDir, scrubbedFileNames[i], channels, filePath, debug);

        outFile << timestamp() << ": Audio file loaded." << endl;

        outFile << timestamp() << ": Performing FFT of left channel..." << endl;

        auto start = high_resolution_clock::now();
        fft(leftChannel, filePath, debug);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        outFile << timestamp() << ": FFT of left channel completed in " << duration.count() << " microseconds." << endl;

        if (channels == 2)
        {
            outFile << timestamp() << ": Performing FFT of right channel..." << endl;

            start = high_resolution_clock::now();
            fft(rightChannel, filePath, debug);
            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);

            outFile << timestamp() << ": FFT of right channel completed in " << duration.count() << " microseconds." << endl;
        }

        if (debug)
        {
            resultsFile.open((fftDir + scrubbedFileNames[i] + "_fftResults.txt").c_str(),ios::out);

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
        vector<float> dataPoints;                                        // Will contain the data points for each channel.
        vector<vector<float> > zeroCrossResults(2,dataPoints);           // Will contain the results of the zero cross algorithm.

        outFile << timestamp() << ": Beginning zero cross algorithm..." << endl;

        start = high_resolution_clock::now();
        zeroCross(leftChannel, rightChannel, zeroCrossResults, channels, filePath, debug);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        
        dataPoints.clear();
       
        outFile << timestamp() << ": Zero cross algorithm completed in " << duration.count() << " microseconds." << endl;

        outFile << timestamp() << ": Updating zero cross database at " << outputFileName;


        if (channels == 1)
        {
            outFile << "_zeroCrossMono.txt..." << endl;
            resultsFile.open((zCrossDir + scrubbedFileNames[i] + "_zeroCrossMono.txt").c_str(),ios::out);
            database.open((filePath + "/zeroCrossMonoDatabase.txt").c_str(), ios::app);
        }
        else if (channels == 2)
        {
            outFile << "_zeroCrossStereo.txt..." << endl;
            resultsFile.open((zCrossDir + scrubbedFileNames[i] + "_zeroCrossStereo.txt").c_str(),ios::out);
            database.open((filePath + "/zeroCrossStereoDatabase.txt").c_str(),ios::app);
        }

        for (int i = 0; i < zeroCrossResults.size(); i++)
        {
            if (zeroCrossResults[i].size() > 0)
            {
                for (int j = 0; j < zeroCrossResults[i].size(); j++)
                {
                    resultsFile << zeroCrossResults[i][j] << " ";
                    database << zeroCrossResults[i][j] << " ";
                }

                resultsFile << endl;
                database << endl;
            }
        }

        resultsFile << endl;
        database << endl;

        resultsFile.close();
        database.close();

        outFile << timestamp() << ": Finished updating zero cross database." << endl;

        // Plot the zero cross results if that is an option
        if (plot)
        {
            ofstream tempOutFile;
            string tempOutFileName;
            vector<double> tempData;

            tempOutFileName = filePath + "/" + scrubbedFileNames[i] + "_zeroCross";

            cout << "TempFile located at:  " << tempOutFileName << endl;

            tempOutFile.open(tempOutFileName.c_str(), ios::out);
            
            if (channels == 1)
            {
                for (int i = 0; i < zeroCrossResults[0].size(); i++)
                    tempOutFile << zeroCrossResults[0][i] << endl;
            }
            else if (channels == 2)
            {
                for (int i = 0; i < zeroCrossResults[0].size(); i++)
                {
                    tempOutFile << zeroCrossResults[0][i] << " " << zeroCrossResults[1][i] << endl;
                }
            }
           
            if (channels == 1) 
                plotFileName = scrubbedFileNames[i] + "_zeroCrossMono";
            else
                plotFileName = scrubbedFileNames[i] + "_zeroCrossingStereo";

            plotter(tempOutFileName, plotFileName, 0, 0, channels, plotPath);

            if (remove(tempOutFileName.c_str()) == 0)
                cout << "Temporary file deleted" << endl;
            else 
                cout << "Failed to delete temp file." << endl;

          
        }

        zeroCrossResults.clear();

        outFile << timestamp() << ": Beginning spectrum flux algorithm..." << endl;

        start = high_resolution_clock::now();
        spectralFlux(leftChannel, rightChannel, spectralFluxResults, channels, filePath, debug);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);

        outFile << timestamp() << ": Spectrum flux algorithm completed in " << duration.count() << " microseconds." << endl;

        outFile << timestamp() << ": Updating spectrum flux database at " << outputFileName;

        if (channels == 1)
        {
            outFile << "_spectrumFluxMono.txt..." << endl;

            resultsFileName = sFluxDir + scrubbedFileNames[i] + "_spectrumFluxMono.txt";
            resultsFile.open(resultsFileName.c_str(),ios::out);
            database.open((filePath + "/spectrumFluxMonoDatabase.txt").c_str(),ios::app);
        }
        else if (channels == 2)
        {
            outFile << "_spectrumFluxStereo.txt..." << endl;

            resultsFileName = sFluxDir + scrubbedFileNames[i] + "_spectrumFluxStereo.txt";
            resultsFile.open(resultsFileName.c_str(),ios::out);
            database.open((filePath + "/spectrumFluxStereoDatabase.txt").c_str(),ios::app);
        }

        resultsFile << spectralFluxResults[0];
        database << spectralFluxResults[0];

        if (channels == 2)
        {
            resultsFile << " " << spectralFluxResults[1];
            database << spectralFluxResults[0];
        }

        resultsFile << endl;
        database << endl;

        resultsFile.close();
        database.close();

        if (plot)
        {
            outFile << timestamp() << ": Plotting results of spectrum flux algorithm..." << endl;

            if (channels == 1)
                plotFileName = scrubbedFileNames[i] + "_spectrumFluxMono";
            else
                plotFileName = scrubbedFileNames[i] + "_spectrumFluxStereo";

            plotter(resultsFileName, plotFileName, 0, 1, channels, plotPath);

            outFile << timestamp() << ": Finished plotting results." << endl;
        }

        outFile << timestamp() << ": Beginning cepstrum algorithm..." << endl;

        start = high_resolution_clock::now();
        //cepstrum();
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);

        outFile << timestamp() << ": Cepstrum algorithm completed in " << duration.count() << " microseconds." << endl;

        outFile << timestamp() << ": Updating cepstrum database at " << outputFileName;

        if (channels == 1)
        {
            outFile << "_cepstrumMono.txt..." << endl;
            resultsFile.open((filePath + "/" + outputFileName + "_cepstrumMono.txt").c_str(),ios::app);
        }
        else if (channels == 2)
        {
            outFile << "_cepstrumStereo.txt..." << endl;
            resultsFile.open((filePath + "/" + outputFileName + "_cepstrumStereo.txt").c_str(),ios::app);
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
