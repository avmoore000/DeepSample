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
#include "fastFourierTransform.h"
using namespace std;

void zeroCrossingTest(bool debug);


/*
 * 
 */
int main(int argc, char** argv) 
{
    // Get filename for data location
    string fileName = argv[1];
    // Store data location from user input
    ifstream audioFile;

    audioFile.open(fileName, ios::in);


    // Generate files for testing
    const complex<float> i(1.0, 2.0);
    vector<complex<float>> test;
/*    list <float> data;
    data.push_back(i);
    data.push_back(2);
    FourierTransform(data);*/

    test.push_back(i);

    zeroCrossingTest(1);
    
    return 0;
}

void zeroCrossingTest(bool debug)
{
    float testArray[9] = {1,2,3,0,-1,-2,-3,0,1};
    float f1[9] = {-5,-5,-5,-5,-5,-5,-5,-5,-5};;
    int bx = 9;

    if (debug)
    {
        cout << "Signal Array:  " << endl;
        cout << "[";

        for (int i = 0; i < 9; i++)
        {
            cout << testArray[i] << " ";
        }
        
        cout << "]" << endl;
    }

    zeroCrossing(testArray,f1,bx,1);

    if (debug)
    {
        cout << "Zero Crossing Results:  " <<endl<<endl;
        cout << "Signal Array:  " << endl;
        cout << "[";
   
        for (int i = 0; i < 9; i++)
        {
            cout << testArray[i] << " ";
        }
        cout << "]" << endl;

        cout << "F array:  " << endl;
        cout << "[";

        for (int i = 0; i < 9; i++)
        {
            cout << f1[i] << " ";
        }
        cout << "]" << endl;
    }

    return;
}
