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

    vector<AudioWave> waves;                   // Will hold all generated waves.
    vector<string> audioNames;                 // Names of all audio files to analyze.
    vector<string> scrubbedAudioNames;         // Names of file without path information.

    if (argc <= 1)
    {
        cout << endl << endl << "Program Use:" << endl << endl;
        cout << "./SampleGeneration [resultsDirectory] [inputDirectory] [fileName] [channels {1,2}]"
             << endl << "   [debugMode {0,1}] [plot {0,1}]" << endl << endl;
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
             << "\t\t1 = On" << endl << "\t\t\t2 = Off" << endl << endl;
        cout << "\tplot" << endl << endl << "\t\tToggle plotting." << endl << endl 
             << "\t\t1 = Plot" << endl << "\t\t2 = No Plot" << endl << endl;
        cout << "\tsave" << endl << endl << "\t\tToggle Saving" << endl << endl << "\t\t1 = Save"
             << endl << "\t\t2= No Save" << endl << endl;

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

    if (plot)
    {
        cout << "What type of graph?" << endl;
        cout << "\t1. Box Plot" << endl;
        cout << "Enter Selection:  ";
        cin >> graphType;
        cout << endl;
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

            outFile << "\tTotal Audio Samples:  " << audioNames.size() << endl << endl;

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

                AudioWave wave("test", 2);  // An AudioWave object

                if (debug)
                {
                    cout << "Sample [" << (i + 1) << "]" << endl;
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

                fft(wave, fileName, path, debug);

                outFile.open((path + "/" + fileName).c_str(), ios::app);
                outFile << timestamp() << ":  FFT complete." << endl;
                outFile << timestamp() << ":  Performing Zero Cross..." << endl;
                outFile.close();

                if (debug)
                {
                    cout << timestamp() << ":  FFT complete." << endl;
                    cout << timestamp() << ":  Performing Zero Cross..." << endl;
                }

                zeroCross(wave, fileName, path, debug);

                outFile.open((path + "/" + fileName).c_str(), ios::app);
                outFile << timestamp() << ":  Zero Cross complete." << endl;
                outFile << timestamp() << ":  Performing Spectrum Flux..." << endl;
                outFile.close();

                if (debug)
                {
                    cout << timestamp() << ":  Zero Cross complete." << endl;
                    cout << timestamp() << ":  Performing Spectrum Flux..." << endl;
                }

                spectralFlux(wave, fileName, path, debug);

                outFile.open((path + "/" + fileName).c_str(), ios::app);
                outFile << timestamp() << ":  Spectrum Flux complete." << endl;
                outFile << timestamp() << ":  Performing Cepstrum..." << endl;
                outFile.close();

                if (debug)
                {
                    cout << timestamp() << ":  Spectrum Flux complete." << endl;
                    cout << timestamp() << ":  Performing Cepstrum..." << endl;
                }

                // cepstrum()

               outFile.open((path + "/" + fileName).c_str(), ios::app);
               outFile << timestamp() << ":  Cepstrum complete." << endl;
               outFile << timestamp() << ":  Performing Spectrum Centroid..." << endl;
               outFile.close();

               if (debug)
               {
                   cout << timestamp() << ":  Cepstrum complete." << endl;
                   cout << timestamp() << ":  Performing Spectrum Centroid..." << endl;
               }

               // spectrumCentroid()

               outFile.open((path + "/" + fileName).c_str(), ios::app);
               outFile << timestamp() << ":  Spectrum Centroid complete." << endl;
               outFile << timestamp() << ":  Audio Algorithms completed for sample " << (i+1) << "." << endl << endl;
               outFile.close();

               if (debug)
               {
                   cout << timestamp() << ":  Spectrum Centroid complete." << endl;
                   cout << timestamp() << ":  Audio Algorithms completed for sample " << (i+1) << "." << endl << endl;
               }

               waves.push_back(wave);

            } // Finished algorithm loop

            outFile.open((path + "/" + fileName).c_str(), ios::app);
            outFile << timestamp() << ":  Finished processing audio files." << endl;
            outFile.close();

            if (debug)
                cout << timestamp() << ":  Finished processing audio files." << endl << endl;

            
            // Set up the source files for the audio waves
            if (plot)
            {
                outFile.open((path + "/" + fileName).c_str(), ios::app);
                outFile << timestamp() << ":  Setting up source files for plotting..." << endl;
                outFile.close();

                if (debug)
                    cout << timestamp() << ":  Setting up source files for plotting..." << endl;

                for (int i = 0; i < waves.size(); i++)
                {
                    waves[i].setSourceFiles();
                }

                outFile.open((path + "/" + fileName).c_str(), ios::app);
                outFile << timestamp() << ":  Source files set up." << endl;
                outFile.close();

                if (debug)
                    cout << timestamp() << ":  Source files set up." << endl;
   
            // Plot the results if plot is selected
                outFile.open((path + "/" + fileName).c_str(), ios::app);
                outFile << timestamp() << ":  Plotting Data..." << endl << endl;
                outFile.close();

                if (debug)
                    cout << timestamp() << ":  Plotting Data..." << endl;

                // Loop through the wave objects.
                for (int i = 0; i < waves.size(); i++)
                {
                    // Call plotter with a 0 for alg in order to plot all graphs
                    plotter(waves[i], graphType, 0, fileName, path, debug);

                } // End plot loop

                outFile.open((path + "/" + fileName).c_str(), ios::app);
                outFile << timestamp() << ":  Plotting complete." << endl;
                outFile.close();

                if (debug)
                    cout << timestamp() << ":  Plotting complete." << endl;
            } // End plot

            // Create database files for training ANNI
            

           outFile.open((path + "/" + fileName).c_str(), ios::app);
           outFile << timestamp() << ":  Creating databases from results..." << endl;
           outFile.close();

           if (debug)
               cout << timestamp() << ":  Creating databases from results..." << endl;

           for (int i = 0; i < waves.size(); i++)
           {
               // Create FFT database
               
               // Create ZeroCross database

               // Create Cepstrum database
 
               // Create Spectrum Flux database
 
               // Create Spectrum Centroid database

           }// End database loop

        outFile.open((path + "/" + fileName).c_str(), ios::app);
        outFile << timestamp() << ":  Databases created." << endl;
        outFile.close();

        if (debug)
            cout << timestamp() << ":  Databases created." << endl;

        } // End second generation
    } // End generation

    outFile.open((path + "/" + fileName).c_str(), ios::app);
    outFile << timestamp() << ":  SampleGenerator completed." << endl;
    outFile.close();

    if (debug)
        cout << timestamp() << ":  SampleGenerator completed." << endl << endl;

    return 0;
}
