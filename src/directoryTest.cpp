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
        cout << "\tdebug" << endl << endl << "\t\tToggle debug output.  Warning: Debug mode causes"
             << " large files and" << endl << "\t\t slows down execution." << endl << endl
             << "\t\t1 = On" << endl << "\t\t\t2 = Off" << endl << endl;

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
                case 6:
                {
                    debug = atoi(argv[i]);
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

            
            if (mkdir((path + "/ConvertedAudio").c_str(), 0777) == -1)
            {
                if (debug)
                    cout << ":  ConvertedAudio directory could not be created." << endl;
            }
            else
            {
                if (debug)
                    cout << ":  ConvertedAudio directory created at " << path << "/Convertedaudio" << endl;
            }

            if (mkdir((path + "/Cepstrum").c_str(), 0777) == -1)
            {
                if (debug)
                    cout << ":  Cepstrum directory could not be created." << endl;
            }
            else
            {
                if (debug)
                    cout << ":  Cepstrum directory created at " << path << "/Cepstrum" << endl;
            }

            if (mkdir((path + "/FFT").c_str(), 0777) == -1)
            {
                if (debug)
                    cout << ":  FFT directory could not be created." << endl;
            }
            else
            {
                if (debug)
                    cout << ":  FFT directory created at " << path << "/FFT" << endl;
            }

            if (mkdir((path + "/SpectrumFlux").c_str(), 0777) == -1)
            {
                if (debug)
                    cout << ":  Spectrum Flux directory could not be created." << endl;
            }
            else
            {
                if (debug)
                    cout << ":  Spectrum Flux directory created at " << path << "/SpectrumFlux" << endl;
            }

            if (mkdir((path + "/ZeroCross").c_str(), 0777) == -1)
            {
                if (debug)
                    cout << ":  ZeroCross directory could not be created." << endl;
            }
            else
            {
                if (debug)
                    cout << ":  ZeroCross directory created at " << path << "/ZeroCross" << endl;
            }

            if (mkdir((path + "/SpectrumCentroid").c_str(), 0777) == -1)
            {
                if (debug)
                    cout << ":  SpectrumCentroid directory could not be created." << endl;
            }
            else
            {
                if (debug)
                    cout << ":  SpectrumCentroid directory created at " << path << "/SpectrumCentroid" << endl;
            }

            if (mkdir((path + "/Databases").c_str(), 0777) == -1)
            {
                if (debug)
                    cout << ":  Databases directory could not be created." << endl;
            }
            else
            {
                if (debug)
                    cout << ":  Databases directory created at " << path << "/Databases" << endl;
            }

            if (plot)
            {
                if (mkdir((path + "/Plots").c_str(), 0777) == -1)
                {
                    if (debug)
                        cout << ":  Plots directory could not be created." << endl;
                }
                else
                {
                    if (debug)
                        cout << ":  Plots directory created at " << path << "/Plots" << endl;
                }
            }

            if (debug)
            {
                if (mkdir((path + "/Debug").c_str(), 0777) == -1)
                {
                    cout << ":  Debug directory could not be created." << endl;
                }
                else
                {
                    cout << ":  Debug directory created at " << path << "/Debug" << endl;
                }
            }
        } // Finished making directories

    } // End generation

    return 0;
}
