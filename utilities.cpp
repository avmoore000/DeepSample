/* 
 * File:   AudioSegmentation.cpp
 * Author: Andrew Moore
 *
 * Created on February 9, 2020, 3:17 PM
 */

/**************************************Change Log *******************************/

// Created source file for audio segmentation algorithms - A.M. Feb 09 2020
// Added zeroCrossing function implementation - A.M. Feb 09 2020
// Added getSign function implementation - A.M. Feb 09 2020

/**************************************End Change Log ***************************/

/**************************************To Do List ******************************/

// Create function implementation for Spectral Flux
// Create function implementation for cepstral analysis
// Create function implementation for complex cepstra analysis

/**************************************End To Do List **************************/
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <complex>
#include <fstream>
#include "AudioSegmentation.h"

using namespace std;

// Function zeroCrossing
// Inputs:  
//        *data - A pointer to the user generated waves
//        zeroCross - A pointer to the array that will store the zero cross results.
//        nx - the size of each data point in the dataset
//        debug - a flag to enable or disable debug messages.
// Outputs:  None
// Purpose:  The zeroCrossing function is an implementation of the zero crossing signal
// analysis algorithm.  It counts the positive and negative changes within the signal
// and records the results in an array of zeros and ones that is passed by the user.
void printer(string fileName)
{
	ofstream outFile;  // Points to user specified output file

	stringstream stringBuilder;  // This will be used to create the output strings

}
    int j = 0;

    // Strings used to build output file.
    stringstream stringBuilder;
    string iteration = "";
    string realI = "";
    string realI1 = "";
    string s1 = "";
    string s2 = "";
    string zcA = "";

    string l1 = "";
    string l2 = "";
    string l3 = "";
    string l4 = "";
    string l5 = "";
    string l6 = "";

    for (int i = 0; i < 100; i++)
        outFile << "*";

    outFile << endl << endl << "ZeroCross Algorithm" << endl << endl;
    cout << endl << endl << "ZeroCross Algorithm" << endl << endl;


    // Allocate space in memory based on the size of the data points.
//    memset(zeroCross, 0, nx*sizeof(float));

//    zeroCross = (float*) malloc(nx*sizeof(float));

    if (debug)
    {
        outFile << "NX = " << nx << endl << endl;
        outFile << "Zero Crossing calculations:  " << endl << endl;
    }

    // Loop through the data
    for (int i = 0; i < nx-1; i++)
    {
        sign1 = getSign(real(data[i]),debug, fileName);
        sign2 = getSign(real(data[i+1]),debug, fileName);;

        // If the signs are not equal, there has been a change in signal.
        if (sign1 != sign2)
            zeroCross[i+1] = 1;

        if (debug)
        {
	    stringBuilder << setiosflags(ios_base::left) << setw(10) << to_string(i+1) + "  ";
	    iteration += stringBuilder.str();
	    stringBuilder.str("");
	    stringBuilder << setiosflags(ios_base::left) << setw(10) << to_string(real(data[i])) + "  ";
	    realI += stringBuilder.str();
            stringBuilder.str("");
	    stringBuilder << setiosflags(ios_base::left) << setw(10) << to_string(real(data[i+1])) + "  ";
	    realI1 += stringBuilder.str();
	    stringBuilder.str("");
	    stringBuilder << setiosflags(ios_base::left) << setw(10) << to_string(sign1) + "  ";
	    s1 += stringBuilder.str();
	    stringBuilder.str("");
	    stringBuilder << setiosflags(ios_base::left) << setw(10) << to_string(sign2) + "  ";
	    s2 += stringBuilder.str();
	    stringBuilder.str("");
	    stringBuilder << setiosflags(ios_base::left) << setw(10) << to_string(zeroCross[i+1]) + "  ";
	    zcA += stringBuilder.str();
	    stringBuilder.str("");

            if ((i != 0) && ((i%4) == 0))
            {
		l1 = "Iteration:";
		l2 = "Real I [" + to_string(j) + " - " + to_string(i+1) + " ]:";
		l3 = "Real I+1 [" + to_string(j) + " - " + to_string(i+1) + "]:";
		l4 = "Sign 1 [" + to_string(j) + " - " + to_string(i+1) + "]:";
		l5 = "Sign 2 [" + to_string(j) + " - " + to_string(i+1) +  "]:";
	        l6 = "zeroCross [" + to_string(j) + " - " + to_string(i+1) + "]:";
	        
	        outFile << l1 << setiosflags(ios_base::left) << setw(30-l1.length()) << " " 
			<< resetiosflags(ios_base::left) << setiosflags(ios_base::right) << iteration << endl << endl;
		outFile << l2 << resetiosflags(ios_base::right) << setiosflags(ios_base::left) << setw(30-l2.length()) << " "
			<< resetiosflags(ios_base::left) << setiosflags(ios_base::right) << realI << endl << endl;
		outFile << l3 << resetiosflags(ios_base::right) << setiosflags(ios_base::left) << setw(30-l3.length()) << " "
			<< resetiosflags(ios_base::left) << setiosflags(ios_base::right) << realI1 << endl << endl;
		outFile << l4 << resetiosflags(ios_base::right) << setiosflags(ios_base::left) << setw(30-l4.length()) << " "
			<< resetiosflags(ios_base::left) << setiosflags(ios_base::right) << s1 << endl << endl;
	        outFile << l5 << resetiosflags(ios_base::right) << setiosflags(ios_base::left) << setw(30-l5.length()) << " "
			<< resetiosflags(ios_base::left) << setiosflags(ios_base::right) << s2 << endl << endl;
                outFile << l6 << resetiosflags(ios_base::right) << setiosflags(ios_base::right) << setw(30-l6.length()) << " "
			<< resetiosflags(ios_base::right) << zcA << endl << endl;

		iteration = "";
		realI = "";
		realI1 = "";
		s1 = "";
		s2 = "";
		zcA = "";
		j = i+1;
	    }
	    else
            {
                j = 0;
	    }
        }
    }

    outFile << "ZeroCross Algorithm Complete. " << endl << endl;
    cout << "ZeroCross Algorithm Complete." << endl << endl;
    
    for (int i = 0; i < 100; i++)
        outFile << "*";
    outFile << endl << endl;

    outFile.close();

}

// Function getSign
// Inputs
//    data - A float containing the current data point.
//    debut - A flag to enable or disable debug messages.
// Outputs:
//    sign - A boolean stating whether the signal has changed from positive to negative or vice versa.
// Purpose: Determines if a sign change has occured.
bool getSign(complex<double> data, bool debug, string fileName)
{
    bool sign = 0;

    if (real(data) > 0)
        sign = 1;
    else
        sign = 0;

    return sign;
}
