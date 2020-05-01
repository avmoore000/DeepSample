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
#include "../include/DeepSample.h"

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

    string audioDir;                           // Directory for converted audio files.
    string fileName;                           // Name for output file
    string inputDirectory;                     // Location of input files
    string path;                               // Path for file output.
    string resultsDirectory;                   // Name of directory for storing results.

    ostringstream converter;                   // Used for converting directory entries to strings

    ofstream outFile;                          // Stream pointer for data output.
    ofstream database;                         // Stream pointer for database output.
    
    ifstream inFile;                           // Stream pointer for data input.

    bool debug;                                // Flag that controls debug output.
    bool plot;                                 // Flag that controls plotting functionality.
    bool startGeneration;                      // Starts the sample generation.
    bool fullPrecision;                        // The precision for output.
    bool save;                                 // Toggle saving
    int channels;                              // Holds the number of channels in the file.
    int test;                                  // Specifies which tests are being run.
    int graphType;                             // Specifies the type of graph to plot.

    fs::path p;                                // Will hold an iterable directory path.

    vector<string> audioNames;                 // Names of all audio files to analyze.
    vector<string> scrubbedAudioNames;         // Names of file without path information.

    if (argc <= 1)
    {
        cout << endl << endl << "Program Use:" << endl << endl;
        cout << "./SampleGeneration [path] [inputDirectory] [fileName] [channels {1,2}] [fullPrecision {0,1}]"
             << endl << "   [debug {0,1}] [plot {0,1}] [graphType {1}], [save {0,1}]" << endl << endl;
        cout << "\tresultsDirectory" << endl << endl << "\t\tUser specified directory where results"
             << " will be stored.  If directory" << endl << "\t\tdoes not exist it will be created." 
             << endl << endl;
        cout << "\tinputDirectory" << endl << endl << "\t\tDirectory containing audio files for "
             << "analysis." << endl << endl;
        cout << "\tfileName" << endl << endl << "\t\tName of the output file prefix." << endl << endl;
        cout << "\tchannels" << endl << endl << "\t\t1 = Mono" << endl << "\t\t2 = Stereo" << endl << endl;
        cout << "\tfullPrecison" << endl << endl << "\t\tSet the precision for decimal output." << endl << endl;
        cout << "\tdebug" << endl << endl << "\t\tToggle debug output.  Warning: Debug mode causes"
             << " large files and" << endl << "\t\t slows down execution." << endl << endl
             << "\t\t1 = On" << endl << "\t\t2 = Off" << endl << endl;
        cout << "\tplot" << endl << endl << "\t\tToggle plotting." << endl << endl 
             << "\t\t1 = Plot" << endl << "\t\t2 = No Plot" << endl << endl;
        cout << "\tgraphType" << endl << endl << "\t\tSelect the type of graph to plot." << endl << endl;
        cout << "\t\t 1 = Box Graph" << endl << endl;
        cout << "\tsave" << endl << endl << "\t\tToggle Saving" << endl << endl << "\t\t1 = Save"
             << endl << "\t\t2 = No Save" << endl << endl;

        startGeneration = false;
    }
    else
    {
        startGeneration = true;

        for (int i = 1; i < argc; i++)
        {
            switch(i)
            {
                case 1:
                {
                    path = argv[i];
                    break;
                }
                case 2:
                {
                    inputDirectory = argv[i];
                    break;
                }
                case 3:
                {
                    fileName = argv[i];
                    break;
                }
                case 4:
                {
                    channels = atoi(argv[i]);
                    break;
                }
                case 5:
                {
                    fullPrecision = atoi(argv[i]);
                    break;
                }
                case 6:
                {
                    debug = atoi(argv[i]);
                    break;
                }
                case 7:
                {
                    plot = atoi(argv[i]);
                    break;
                }
                case 8:
                {
                    graphType = atoi(argv[i]);
                    break;
                }
                case 9:
                {
                    save = atoi(argv[i]);
                    break;
                }
                default:
                {
                    cout << "Error with arguments." << endl;
                    startGeneration = false;
                }
            }
        }
    }

    if (startGeneration)
    {

        // Create directories for results
        if(mkdir((path.c_str()),0777) == -1)
            cout << path << " directory already exists. Will be using it to store results." << endl;
        else
        {
            cout << "Results directory created at " << path << endl;

            outFile.open((path + "/" + fileName).c_str(), ios::app);

            outFile << "Sample Generator run with the following arguments:" << endl << endl;
            outFile << "\tpath:  " << path << endl;
            outFile << "\tinputDirectory:  " << inputDirectory << endl;
            outFile << "\tfileName:  " << fileName << endl;
            outFile << "\tchannels:  " << channels << endl;
            outFile << "\tdebug:  " << debug << endl;
            outFile << "\tplot:  " << plot << endl << endl;

            outFile << timestamp() << ":  Results directory created at " << path << endl;
            
            if (mkdir((path + "/ConvertedAudio").c_str(), 0777) == -1)
            {
                outFile << timestamp() << ":  ConvertedAudio directory could not be created." << endl;

                if (debug)
                    cout << timestamp() << ":  ConvertedAudio directory could not be created." << endl;
            }
            else
            {
                outFile << timestamp() << ":  ConvertedAudio directory created at " << path << "/ConvertedAudio" << endl;

                if (debug)
                    cout << timestamp() << ":  ConvertedAudio directory created at " << path << "/Convertedaudio" << endl;
            }

            if (mkdir((path + "/Cepstrum").c_str(), 0777) == -1)
            {
                outFile << timestamp() << ":  Cepstrum directory could not be created." << endl;
 
                if (debug)
                    cout << timestamp() << ":  Cepstrum directory could not be created." << endl;
            }
            else
            {
                outFile << timestamp() << ":  Cepstrum directory created at " << path << "/Cepstrum" << endl;

                if (debug)
                    cout << timestamp() << ":  Cepstrum directory created at " << path << "/Cepstrum" << endl;
            }

            if (mkdir((path + "/FFT").c_str(), 0777) == -1)
            {
                outFile << timestamp() << ":  FFT directory could not be created." << endl;

                if (debug)
                    cout << timestamp() << ":  FFT directory could not be created." << endl;
            }
            else
            {
                outFile << timestamp() << ":  FFT directory created at " << path << "/FFT" << endl;

                if (debug)
                    cout << timestamp() << ":  FFT directory created at " << path << "/FFT" << endl;
            }

            if (mkdir((path + "/SpectrumFlux").c_str(), 0777) == -1)
            {
                outFile << timestamp() << ":  SpectrumFlux directory could not be created." << endl;;

                if (debug)
                    cout << timestamp() << ":  Spectrum Flux directory could not be created." << endl;
            }
            else
            {
                outFile << timestamp() << ":  SpectrumFlux directory created at " << path << "/SpectrumFlux" << endl;

                if (debug)
                    cout << timestamp() << ":  Spectrum Flux directory created at " << path << "/SpectrumFlux" << endl;
            }

            if (mkdir((path + "/ZeroCross").c_str(), 0777) == -1)
            {
                outFile << timestamp() << ":  ZeroCross directory could not be created." << endl;

                if (debug)
                    cout << timestamp() << ":  ZeroCross directory could not be created." << endl;
            }
            else
            {
                outFile << timestamp() << ":  ZeroCross directory created at " << path << "/ZeroCross" << endl;

                if (debug)
                    cout << timestamp() << ":  ZeroCross directory created at " << path << "/ZeroCross" << endl;
            }

            if (mkdir((path + "/SpectrumCentroid").c_str(), 0777) == -1)
            {
                outFile << timestamp() << ":  SpectrumCentroid directory could not be created." << endl;
            
                if (debug)
                    cout << timestamp() << ":  SpectrumCentroid directory could not be created." << endl;
            }
            else
            {
                outFile << timestamp() << ":  SpectrumCentroid directory created at " << path << "/SpectrumCentroid" <<endl;

                if (debug)
                    cout << timestamp() << ":  SpectrumCentroid directory created at " << path << "/SpectrumCentroid" << endl;
            }

            if (mkdir((path + "/Databases").c_str(), 0777) == -1)
            {
                outFile << timestamp() << ":  Databases directory could not be created." << endl;

                if (debug)
                    cout << timestamp() << ":  Databases directory could not be created." << endl;
            }
            else
            {
                outFile << timestamp() << ":  Databases directory created at " << path << "/Databases" << endl;

                if (debug)
                    cout << timestamp() << ":  Databases directory created at " << path << "/Databases" << endl;
            }

            if (plot)
            {
                if (mkdir((path + "/Plots").c_str(), 0777) == -1)
                {
                    outFile << timestamp() << ":  Plots directory could not be created." << endl;

                    if (debug)
                        cout << timestamp() << ":  Plots directory could not be created." << endl;
                }
                else
                {
                    outFile << timestamp() << ":  Plots directory created at " << path << "/Plots" << endl;
 
                    if (debug)
                        cout << timestamp() << ":  Plots directory created at " << path << "/Plots" << endl;
                }
            }

            if (debug)
            {
                if (mkdir((path + "/Debug").c_str(), 0777) == -1)
                {
                    outFile << timestamp() << ":  Debug directory could not be created." << endl;
 
                    cout << timestamp() << ":  Debug directory could not be created." << endl;
                }
                else
                {
                    outFile << timestamp() << ":  Debug directory created at " << path << "/Debug" << endl;
     
                    cout << timestamp() << ":  Debug directory created at " << path << "/Debug" << endl;
                }
            }
        } // Finished making directories

        // Grab the audio file names from the input directory

        p = inputDirectory;
  
        if (fs::is_directory(inputDirectory))
        {
            outFile << timestamp() << ":  Retrieving audio files from " << inputDirectory << "..." << endl;

            if (debug)
                cout << timestamp() << ":  Retrieving audio files from " << inputDirectory << "..." << endl << endl;

            for (auto &entry: boost::make_iterator_range(fs::directory_iterator(p)))
            {
                converter << entry;

                string temp = converter.str();
                string converted = "";

                // Loop through and grab the current file name, removing the quotes
                for (int i = 0; i < temp.size(); i++)
                {
                    if (temp[i] != '\"')
                        converted += temp[i];
                }

                audioNames.push_back(converted);
                converter.str("");
                converter.clear();

                string tempName = "";

                // Get just the audio file name, will return a backwards string
                for (int i = converted.size() - 1; i > 0; i--)
                {
                    if (converted[i] != '/')
                        tempName += converted[i];
                    else
                        break;
                }

                converted = "";

                // Reverse the backwards audio file name.
                for (int i = tempName.size() - 1; i >= 0; i--)
                    converted += tempName[i];

                scrubbedAudioNames.push_back(converted);

                if (debug)
                    cout << "\tFile Name = " << converted << endl;
            }

            outFile << endl << "\tTotal Audio Samples:  " << audioNames.size() << endl << endl;

            if (debug)
                cout << "\tTotal Audio Samples:  " << audioNames.size() << endl << endl;

            outFile << timestamp() << ":  Audio files retrieved." << endl;

            if (debug)
                cout << endl << timestamp() << ":  Audio files retrieved." << endl;
        } // Finished grabbing audio file names
        else
        {
            outFile << timestamp() << ":  Error retrieving audio files. " << inputDirectory << " is not"
                    << " a valid directory." << endl;

            if (debug)
                cout << timestamp() << ":  Error retrieving audio files.  " << inputDirectory << " is not"
                     << " a valid directory." << endl;

            startGeneration = false;
        }

        if (startGeneration)
        {
            outFile << timestamp() << ":  Processing Audio Files..." << endl << endl;
            outFile.close();

            if (debug)
                cout << timestamp() << ":  Processing Audio Files..." << endl << endl;

            // Run algorithms for each file in the audio sample directory
            for (int i = 0; i < audioNames.size(); i++)
            {
                outFile.open((path + "/" + fileName).c_str(), ios::app);
                outFile << "Sample [" << (i + 1) << "]" << endl;
                outFile << timestamp() << ":  Performing analysis of " << scrubbedAudioNames[i] << endl;
		outFile << timestamp() << ":  Loading audio file..." << endl;
                outFile.close();

                AudioWave wave("test", channels);  // An AudioWave object

                if (debug)
                {
                    cout << "Sample [" << (i + 1) << " / " << (audioNames.size()) << "]" << endl;
                    cout << timestamp() << ":  Performing analysis of " << scrubbedAudioNames[i] << endl;
                    cout << timestamp() << ":  Loading audio file..." << endl;
                }

                loadAudio(wave, audioNames[i],"ConvertedAudio", scrubbedAudioNames[i], 
                          channels, fullPrecision, path, debug);

                outFile.open((path + "/" + fileName).c_str(), ios::app);
                outFile << timestamp() << ":  Audio file loaded." << endl;
                outFile << timestamp() << ":  Performing FFT..." << endl;
                outFile.close();

                if (debug)
                {
                    cout << timestamp() << ":  Audio file loaded." << endl;
                    cout << timestamp() << ":  Performing FFT..." << endl;
                }

                auto start = high_resolution_clock::now();
                fft(wave, fileName, path, debug);
                auto stop = high_resolution_clock::now();
                auto FFTDuration = duration_cast<microseconds>(stop - start);

                outFile.open((path + "/" + fileName).c_str(), ios::app);
                outFile << timestamp() << ":  FFT completed." << endl;
                outFile << timestamp() << ":  Performing Zero Cross..." << endl;
                outFile.close();

                if (debug)
                {
                    cout << timestamp() << ":  FFT completed." << endl;
                    cout << timestamp() << ":  Performing Zero Cross..." << endl;
                }

                start = high_resolution_clock::now();
                zeroCross(wave, fileName, path, debug);
                stop = high_resolution_clock::now();
                auto ZeroDuration = duration_cast<microseconds>(stop - start);

                outFile.open((path + "/" + fileName).c_str(), ios::app);
                outFile << timestamp() << ":  Zero Cross complete." << endl;
                outFile << timestamp() << ":  Performing Spectrum Flux..." << endl;
                outFile.close();

                if (debug)
                {
                    cout << timestamp() << ":  Zero Cross complete." << endl;
                    cout << timestamp() << ":  Performing Spectrum Flux..." << endl;
                }

                start = high_resolution_clock::now();
                spectralFlux(wave, fileName, path, debug);
                stop = high_resolution_clock::now();
                auto SFDuration = duration_cast<microseconds>(stop - start);

                outFile.open((path + "/" + fileName).c_str(), ios::app);
                outFile << timestamp() << ":  Spectrum Flux complete." << endl;
                outFile << timestamp() << ":  Performing Cepstrum..." << endl;
                outFile.close();

                if (debug)
                {
                    cout << timestamp() << ":  Spectrum Flux complete." << endl;
                    cout << timestamp() << ":  Performing Cepstrum..." << endl;
                }

		vector<double> rawL;
		vector<double> rawR;
		vector<double> cepstrumResult;
                vector<complex<double> > tempV;

		tempV = wave.getLeftChannel();

		for (int i = 0; i < tempV.size(); i++)
                {
                    rawL.push_back(real(tempV[i]));
		}

		if (wave.getChannels() == 2)
                {
                    tempV = wave.getRightChannel();

		    for (int i = 0; i < tempV.size(); i++)
	            {
		        rawR.push_back(real(tempV[i]));
		    }
		}

                start = high_resolution_clock::now();
                cepstrumResult = rCepstrum(rawL, 2.0);
                stop = high_resolution_clock::now();
                auto cDuration = duration_cast<microseconds>(stop - start);

		for (int i = 0; i < cepstrumResult.size()-1; i++)
		    wave.pushCepstrum(0,cepstrumResult[i]);

		if (wave.getChannels() == 2)
		{
		    cepstrumResult.clear();
		    start = high_resolution_clock::now();
		    cepstrumResult = rCepstrum(rawR, 2.0);
		    stop = high_resolution_clock::now();
		    cDuration += duration_cast<microseconds>(stop - start);

		    for (int i = 0; i < cepstrumResult.size()-1; i++)
		        wave.pushCepstrum(1, cepstrumResult[i]);
		}
                outFile.open((path + "/" + fileName).c_str(), ios::app);
                outFile << timestamp() << ":  Cepstrum complete." << endl;
                outFile << timestamp() << ":  Performing Spectrum Centroid..." << endl;
                outFile.close();

                if (debug)
                {
                    cout << timestamp() << ":  Cepstrum complete." << endl;
                    cout << timestamp() << ":  Performing Spectrum Centroid..." << endl;
                }

                start = high_resolution_clock::now();
                spectralCentroid(wave, fileName, path, debug);
                stop = high_resolution_clock::now();
                auto SCDuration = duration_cast<microseconds>(stop - start);

                outFile.open((path + "/" + fileName).c_str(), ios::app);
                outFile << timestamp() << ":  Spectrum Centroid complete." << endl;
                outFile.close();

                if (debug)
                    cout << timestamp() << ":  Spectrum Centroid complete." << endl;

                // If plotting, plot
                if (plot)
                {
                    // Generate Y maximums and minimums

                    outFile.open((path + "/" + fileName).c_str(), ios::app);
                    outFile << timestamp() << ":  Generating Y maximums..." << endl;

                    wave.setYMaximums();

                    outFile << timestamp() << ":  Y maximums generated." << endl;
                    outFile << timestamp() << ":  Generating Y minimums..." << endl;

                    wave.setYMinimums();

                    outFile << timestamp() << ":  Y minimums generated." << endl;

                    // Set up source files for plotting  

                    outFile << timestamp() << ":  Setting up source files for plotting..." << endl;
                    outFile.close();

                    if (debug)
                        cout << timestamp() << ":  Setting up source files for plotting..." << endl;

                    wave.setSourceFiles();
                    
                    outFile.open((path + "/" + fileName).c_str(), ios::app);
                    outFile << timestamp() << ":  Source files set up." << endl;

                    // Plot the data

                    outFile << timestamp() << ":  Plotting Data..." << endl << endl;
                    outFile.close();

                    if (debug)
                        cout << timestamp() << ":  Plotting Data..." << endl << endl;

                    plotter(wave, graphType, 0, fileName, path, debug);

                    outFile.open((path + "/" + fileName).c_str(), ios::app);
                    outFile << timestamp() << ":  Plotting complete." << endl;
                    outFile.close();

                    if (debug) 
                        cout << timestamp() << ":  Plotting complete." << endl;                 
                } 
                // Done with plotting

                // If saving, create/update the database files
                if (save)
                {
                    outFile.open((path + "/" + fileName).c_str(), ios::app);
                    outFile << timestamp() << ":  Creating/Updating databases..." << endl;

                    if (debug)
                        cout << timestamp() << ":  Creating/Updating databases..." << endl;

                    int tChannel = wave.getChannels();
                    vector<complex<double> > tempFFT;
                    string audioName = "\u03bc " + wave.getFileName();

                    for (int i = 0; i < wave.getChannels(); i++)
                    {
                        // Fourier Transform Database

                        if (tChannel == 1) // Create/update monoFFT database
                        {
                            outFile << timestamp() << ":  Creating / updating monoFFT database..." << endl;
 
                            if (debug)
                                cout << timestamp() << ":  Creating / updating monoFFT database..." << endl;

                            database.open((path + "/Databases/monoFFT.txt").c_str(), ios::app);
                        }
                        else if (tChannel == 2) // Create/update stereoFFT database
                        {
                            outFile << timestamp() << ":  Creating / updating stereoFFT database..." << endl;
 
                            if (debug)
                                cout << timestamp() << ":  Creating / updating stereoFFT database..." << endl;

                            database.open((path + "/Databases/stereoFFT.txt").c_str(), ios::app);
                        }

                        if (i == 0) // Get leftChannel FFT
                        {
                            // Output the name of the audio file
                            database << audioName << endl;
                            tempFFT = wave.getLeftFFT();
                        }
                        if (i == 1) // Get rightChannel FFT
                            tempFFT = wave.getRightFFT();

                        for (int j = 0; j < tempFFT.size(); j++)
                            database << real(tempFFT[j]) << " ";
                        
                        database << endl;
                        database.close();
                        tempFFT.clear();
                       
                        outFile << timestamp() << ":  FFT database created / updated." << endl;

                        if (debug)
                            cout << timestamp() << ":  FFT database created / updated." << endl;
 
                        // End Fourier Transform Database

                        // Zero Cross Database

                        if (tChannel == 1) // Create/update monoZeroCross database
                        {
                            outFile << timestamp() << ":  Creating / updating monoZeroCross database..." << endl;

                            if (debug)
                                cout << timestamp() << ":  Creating / updating monoZeroCross database..." << endl;

                            database.open((path + "/Databases/monoZeroCross.txt").c_str(), ios::app);
                        }
                        else if (tChannel == 2) // Create/update stereoZeroCross database
                        {
                            outFile << timestamp() << ":  Creating / updating stereoZeroCross database..." << endl;

                            if (debug) 
                                cout << timestamp() << ":  Creating / updating stereoZeroCross database..." << endl;

                            database.open((path + "/Databases/stereoZeroCross.txt").c_str(), ios::app);
                        }

                        database << audioName << endl;

                        bool end = 0;

                        for (int j = 0; j < tChannel; j++)
                        {
                            for (int k = 0; k < wave.getZSize(j+1); k++)
                                database << wave.getZeroDataPoint(j+1,k) << " ";

                            database << endl;
                        }

                        database << endl;
                        database.close();

                        outFile << timestamp() << ":  ZeroCross database created / updated." << endl;

                        if (debug)
                            cout << timestamp() << ":  ZeroCross database created / updated." << endl;
                        
                        // End Zero Cross Database

                        // Cepstrum Database

                        if (tChannel == 1) // Create/update monoCepstrum database
                        {
                            outFile << timestamp() << ":  Creating / updating monoCepstrum database..." << endl;
                   
                            if (debug)
                                cout << timestamp() << ":  Creating / updating monoCepstrum database..." << endl;

                            database.open((path + "/Databases/monoCepstrum.txt").c_str(), ios::app);
                        }
                        else if (tChannel == 2) // Create/update stereoCepstrum database
                        {
                            outFile << timestamp() << ":  Creating / updating stereoCepstrum database..." << endl;
 
                            if (debug)
                                cout << timestamp() << ":  Creating / updating stereoCepstrum database..." << endl;

                            database.open((path + "/Databases/stereoCepstrum.txt").c_str(), ios::app);
                        } 
                         
                        database << audioName << endl;

                        for (int j = 0; j < tChannel; j++)
                        {
                            for (int k = 1; k < wave.getCSize(j+1); k++)
                                database << wave.getCepstrumDataPoint(j,k) << " ";

                            database << endl;
                            
                        }

                        database << endl;
                        database.close();

                        outFile << timestamp() << ":  Cepstrum database created / updated." << endl;
                
                        if (debug)
                            cout << timestamp() << ":  Cepstrum database created / updated." << endl;
                       
                        // End Cepstrum Database

                        // Spectrum Flux Database
    
                        if (tChannel == 1)
                        {
                            outFile << timestamp() << ":  Creating / updating monoSpectrumFlux database..." << endl;
            
                            if (debug)
                                cout << timestamp() << ":  Creating / updating monoSpectrumFlux database..." << endl;

                            database.open((path + "/Databases/monoSpectrumFlux.txt").c_str(), ios::app);
                            database << audioName << endl;
                            database << wave.getSpectrumFDataPoint(0) << endl << endl;
                            database.close();
                        }
                        if (tChannel == 2)
                        {
                            outFile << timestamp() << ":  Creating / updating stereoSpectrumFlux database..." << endl;

                            if (debug)
                                cout << timestamp() << ":  Creating / updating stereoSpectrumFlux database..." << endl;
 
                            database.open((path + "/Databases/stereoSpectrumFlux.txt").c_str(), ios::app);
                            if (i == 0)
                            {
                                database << audioName << endl;
                                database << wave.getSpectrumFDataPoint(0) << endl;
                                database.close();
                            }
                            else if (i == 1)
                            {
                                database << wave.getSpectrumFDataPoint(1) << endl << endl;
                                database.close();
                            }
                        }

                        outFile << timestamp() << ":  Spectrum Flux database created / updated." << endl;

                        if (debug)
                            cout << timestamp() << ":  Spectrum Flux database created / updated." << endl;

                        // End Spectrum Flux

                        // Spectrum Centroid Database
                        if (tChannel == 1)
                        {
                            outFile << timestamp() << ":  Creating / updating monoSpectrumCentroid database..." << endl;
        
                            if (debug)
                                cout << timestamp() << ":  Creating / updating monoSpectrumCentroid database..." << endl;
                            database.open((path + "/Databases/monoSpectrumCentroid.txt").c_str(), ios::app);
                            database << audioName << endl;
                            database << wave.getSpectrumCDataPoint(0) << endl << endl;
                            database.close();
                        }
                        else if (tChannel == 2)
                        {
                            outFile << timestamp() << ":  Creating / updating stereoSpectrumCentroid database..." << endl;
 
                            if (debug)
                                cout << timestamp() << ":  Creating / updating stereoSpectrumCentroid database..." << endl;

                            database.open((path + "/Databases/stereoSpectrumCentroid.txt").c_str(), ios::app);
                            if (i == 0)
                            {
                                database << audioName << endl;
                                database << wave.getSpectrumCDataPoint(0) << endl;
                                database.close;
                            }
                            else if (i == 1)
                            {
                                database << wave.getSpectrumCDataPoint(1) << endl << endl;
                                database.close();
                            }
                        }

                        outFile << timestamp() << ":  Spectrum Centroid database created / updated." << endl;

                        if (debug)
                            outFile << timestamp() << ":  Spectrum Centroid database created / updated." << endl;
                    }
                }
                // Done with saving, creating/updating databases.

                outFile << timestamp() << ":  Databases created / updated." << endl;
                outFile.close();
 
                if (debug)
                    cout << timestamp() << ":  Databases created / updated." << endl;              
               
                outFile.open((path + "/" + fileName).c_str(), ios::app);
                outFile << timestamp() << ":  Audio Algorithms completed for sample " << (i+1) << "." << endl << endl;
                outFile << "\tTiming Data:" << endl << endl;
                outFile << "\tFFT:  Completed in " << FFTDuration.count() << " \u03bc" << "s" << endl;
                outFile << "\tZeroCross:  Completed in " << ZeroDuration.count() << " \u03bc" << "s" << endl;
                outFile << "\tSpectrumFlux:  Completed in " << SFDuration.count() << " \u03bc" << "s" <<endl;
                outFile << "\tCepstrum:  Completed in " << cDuration.count() << " \u03bc" << "s" << endl;
                outFile << "\tSpectrumCentroid:  Completed in " << SCDuration.count() << " \u03bc" << "s" << endl << endl;
                outFile.close();

                if (debug)
                {
                    cout << timestamp() << ":  Spectrum Centroid complete." << endl;
                    cout << timestamp() << ":  Audio Algorithms completed for sample " << (i+1) << "." << endl << endl;
                    cout << "\tTiming Data:" << endl << endl;
                    cout << "\tFFT:  Completed in " << FFTDuration.count() << " \u03bc" << "s" << endl;
                    cout << "\tZeroCross: Completed in " << ZeroDuration.count() << " \u03bc" << "s" << endl;
                    cout << "\tSpectrumFlux:  Completed in " << SFDuration.count() << " \u03bc" << "s" << endl;
                    cout << "\tCepstrum:  Completed in " << cDuration.count() << " \u03bc" << "s" << endl;
                    cout << "\tSpectrumCentroid:  Completed in " << SCDuration.count() << " \u03bc" << "s" << endl << endl;
                }

            } // Finished algorithm loop

            outFile.open((path + "/" + fileName).c_str(), ios::app);
            outFile << timestamp() << ":  Finished processing audio files." << endl << endl;
            outFile.close();

            if (debug)
                cout << timestamp() << ":  Finished processing audio files." << endl << endl;

            
        } // End second generation
    } // End generation

    // Clean up trash files
    if (remove("*.txt") != 0)
        cout << "Couldn't clean up files." << endl;

    return 0;
}
