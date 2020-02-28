/* 
 *  File:   TestSuite.cpp
 *  Author: Hue Truong and Andrew Moore
 *
 *  Created February 27, 2020, 12:28 PM
 *
 */

/**************************************Change Log *******************************/

// Added a change log and to do list section - A.M. Feb 09 2020
// Implemented a 2D vector to contain zeroCross results

/**************************************End Change Log ***************************/

/**************************************To Do List ******************************/

/**************************************End To Do List **************************/

#include "../include/TestSuite.h"

using namespace std;
using namespace std::chrono;

// Function zeroCrossingTest
// Inputs:
//       leftChannel - A vector of complex doubles describing the left side of the audio wave.
//       rightChannel - A vector of complex doubles describing the right side of the audio wave.
//       channels - An integer describing the number of channels in the audio file.
//       debug - A boolean flag that controls debug output
//       fileName - A string containing the filname of hte output file
//       filePath - A string containg the directory for file output
// Outputs: None
// Purpose:  This is a test function for the zero crossing algorithm.
void zeroCrossingTest(vector<complex<double> > leftChannel,vector<complex<double> > rightChannel,int channels,bool debug,string fileName,string filePath)
{
    int m = 2;                                             // Specify number of rows in vector
    int n = leftChannel.size();                            // Specify number of columns of vector
    vector<float> dataPoints(n,0);                         // A vector that will contain the data points for each channel	
    vector<vector<float> > zeroCross(2,dataPoints);        // Holds the datapoints for both waves in a 2D vector 
    string outputFileName;                                 // Name of the file to output to
    ofstream output;                                       // Points to the file to output results

    outputFileName = filePath + "/" + fileName;
  
    output.open(outputFileName.c_str(), ios::app);

    auto start = high_resolution_clock::now();
    zeroCrossing(leftChannel,rightChannel,zeroCross,channels,debug,filePath);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Zero Crossing Algorithm completed in " << duration.count() << " ms." << endl;
    output << "Zero Crossing Algorithm completed in " << duration.count() << " ms." << endl << endl;

    if (debug)
    {
        output << "Zero Crossing Results" << endl << endl;

        output << "Left Channel Signal Array:  " << endl;
        output << "[" << endl;

        for (int i = 0; i < leftChannel.size()-1; i++)
        {
            output << leftChannel[i] << " ";

	    if ((i != 0) && ((i%10) == 0))
	        output << endl;
        }
        output << endl << "]" << endl << endl;

        if (channels == 2)
        {
            output << "Right Channel Signal Array:  " << endl << "[" << endl;

            for (int i = 0; i < rightChannel.size(); i++)
            {
                output << rightChannel[i] << " ";

                if ((i != 0) && ((i%10) == 0))
                    output << endl;
            }

            output << endl << "]" << endl << endl;
        }
    
        output << "ZeroCrossTest Left Channel:  " << endl;
        output << "[" << endl;

        for (int i = 0; i < leftChannel.size(); i++)
        {
            output << zeroCross[0][i] << " ";
          
            if ((i > 0) && ((i % 50) == 0))
                output << endl;
        }
        output << endl << "]";

        if (channels == 2)
        { 
            output << endl << endl << "ZeroCrossTest Right Channel:" << endl << "[" << endl;

            for (int i = 0; i < zeroCross.size(); i++)
            {
                for (int j = 0; j < leftChannel.size(); j++)
                {
                    output << zeroCross[i][j] << " ";

                    if ((j > 0) && ((j % 50) == 0))
                        output << endl;
                }
            }
        }
    
        output << endl << "]" << endl << endl;
    }

    output.close();
    
    return;
}
