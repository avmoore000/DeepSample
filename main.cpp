/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: huetruong and Andrew Moore
 *
 * Created on February 1, 2020, 2:55 PM
 */

/**************************************Change Log *******************************/

// Added a change log and to do list section - A.M. Feb 09 2020
// Added the portaudio library for handling the audio file inputs - A.M. Feb 09 2020
// Added in the code for generating the waves, and sedning to the fourier transform function.  - H.T. & A.M. Feb 15 2020
// Converted complex numbers from float to double template - A.M. Feb 15 2020
// Edited zerocrossing test to accept vector data - A.M. - Feb 15 2020

/**************************************End Change Log ***************************/

/**************************************To Do List ******************************/

// Enable the main function to pass on multiple size arrays, eliminate hard coded test.

/**************************************End To Do List **************************/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <complex>
#include <vector>
#include <list>
#include "portaudio/include/portaudio.h"
#include "AudioSegmentation.h"
#include "FourierTransform.h"
using namespace std;

void zeroCrossingTest(vector<complex<double>>, bool);


/*
 * 
 */
int main(int argc, char** argv) 
{
    // Get filename for data location
//    string fileName = argv[1];
    // Store data location from user input
  //  ifstream audioFile;

//    audioFile.open(fileName, ios::in);


    // Generate files for testing
    const complex<double> i(1.0, 2.0);
    
    vector <complex<double>> data;
    // Generate sample data
    for (int i = 0; i < 100; i++)
    {
	    complex<double> num;
	    if ((i % 3) == 0)
	    {
                num = polar(-static_cast<double>(i), 0.0);
            }
	    else
	        num = polar(static_cast<double>(i),0.0);
	    
	    data.push_back(num);
    }

    cout << "Vector size:  " << data.size() << endl;
    fastFourierTransform(data);

    zeroCrossingTest(data,1);
    
    return 0;
}

void zeroCrossingTest(vector<complex<double>> data, bool debug)
{
    // f1 array will hold the results of zero-crossing tests
    float f1[data.size()];
    float zeroCross[data.size()];
    int bx = data.size();

    float test[5];
    // Initialize the f1 array
    for (int i = 0; i < bx; i++)
    {
	    f1[i] = -5;
    }

    if (debug)
    {
        cout << "Signal Array:  " << endl;
        cout << "[";

        
	for (int i = 0; i < bx; i++)
        {
            cout << data[i] << " ";
        }
        
        cout << "]" << endl;
    }

    zeroCrossing(data,f1,bx,1);

    if (debug)
    {
        cout << "Zero Crossing Results:  " <<endl<<endl;
        cout << "Signal Array:  " << endl;
        cout << "[";
        for (int i = 0; i < bx-1; i++)
        {
            //cout << data[i] << " ";
        }
        cout << "]" << endl;

        cout << "F array:  " << endl;
        cout << "[";

        for (int i = 0; i < bx; i++)
        {
            cout << f1[i] << " ";
        }
        cout << "]" << endl;
    }

    return;
}
