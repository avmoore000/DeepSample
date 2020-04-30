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
#include <string>
#include <sstream>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include "../include/DeepSample.h"

using namespace std;
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
    string command;                            // Command for calling sample generator.

    ostringstream converter;                   // For converting directory entries to strings
    bool debug;                                // Flag that controls debug output.
    bool plot;                                 // Flag that controls plotting functionality.
    bool fullPrecision;                        // The precision for output.
    bool save;                                 // Toggle saving
    int channels;                              // Holds the number of channels in the file.
    int graphType;                             // Specifies the type of graph to plot.

    fs::path p;                                 // Will hold an iterable directory path.

    command = "./SampleGenerator ";

    if (argc <= 1)
    {
        cout << endl << endl << "Program Use:" << endl << endl;
        cout << "./SampleGeneration [path] [inputDirectory] [fileName] [channels {1,2}]"
             << endl << "   [fullPrecision {0,1} [debug {0,1}] [plot {0,1}] [graphType {1} [save {0,1}]" << endl << endl;
        cout << "\tpath" << endl << endl << "\t\tUser specified directory where results"
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
        cout << "\tgraphType" << endl << endl << "\t\tThe type of graph to plot." << endl << endl;
        cout << "\t\t1 = Box" << endl << endl;
        cout << "\tsave" << endl << endl << "\t\tToggle Saving" << endl << endl << "\t\t1 = Save"
             << endl << "\t\t2 = No Save" << endl << endl;

    }
    else
    {
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
                }
            }
        }
    }

    p = inputDirectory;

    if (fs::is_directory(inputDirectory))
    {
        for (auto &entry: boost::make_iterator_range(fs::directory_iterator(p)))
        {
            converter << entry;

            command += path + " " + converter.str() + " " + fileName + " ";
            command += to_string(channels) + " " + to_string(fullPrecision);
            command += " " + to_string(debug) + " " + to_string(plot) + " " + to_string(graphType);
            command += " " + to_string(save);

            cout << command << endl << endl;

            system(command.c_str());

            converter.str("");
            converter.clear();
            command = "./SampleGenerator ";
        }
    }
    
    return 0;
}
