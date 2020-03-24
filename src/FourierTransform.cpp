/*
 *  File:     FourierTransform.cpp
 *  Author:   Hue Truong, Andrew Moore, and Alex Reno
 *  Created:  February 10, 2020  12:00 AM
 *
 */

/**************************************Change Log *******************************/

//  Added comments to function headers - A.M. Feb 23 2020
//  Added debug information to functions - A.M. Feb 23 2020

/**************************************End Change Log ***************************/

/**************************************To Do List ******************************/
/**************************************End To Do List **************************/


#include "../include/FourierTransform.h"

typedef std::complex<double> Complex;
typedef std::vector<Complex> list;

// Function fft
// Inputs:
//    x - A vector of complex numbers describing an audio signal.
//    debug - A boolean flag that controls debug output
//    fileName - A string containing the name of the user specified output file.
// Outputs:  None
// Purpose:  fft is a C++ implementation of the Cooley-Tukey Fast Fourier
//           Transform (FFT) algorithm.  Fourier transformations are used
//           primarily in signal processing to indicate the frequency in 
//           a signal, and its proportion throughout said signal.
void fft(vector<complex<double> > x, bool debug, string resultDirectory)
{
    string fileName;                             // Contains the results directory path
    ofstream outFile;                            // Used for outputting results
    vector <complex<double> > even;              // Holds the even elements of the wave
    vector <complex<double> > odd;               // Holds the odd elements of the wave
    const double PI = 3.14159265358979323846;     // Used in calculations
    const int N = x.size();                      // Used for recursion

    fileName = resultDirectory + "/fastFourierTransform.txt";
  
    if (debug)
        outFile.open(fileName.c_str(), ios::out);

    if (debug)
    {
	outFile << "FAST FOURIER FUNCTION CALLED" << endl;
    }
    
    //Recursive basis step
    if(N <= 1) return; 
    
    if (debug)
    {
        outFile << "BASE STEP COMPLETE" << endl;
    }

    //Split complex set between even and odd elements;
    for(int i = 0; i < (x.size() / 2); i = i + 2)
    {
        even.push_back(i);
        odd.push_back(i + 1);

	if (debug)
        {
	    outFile << "Split Loop ran ( " << i << " ) times!" << endl;
        }
    }
    
    //Divide and conquer recursion
    fft(even, debug, fileName); 
    fft(odd, debug, fileName);

    for (int i = 0; i < (x.size() / 2); ++i)
    {
        //t is a complex number calculated from polar coord of (magnitude, phase angle)
        
	if (i < odd.size())
	{
	    Complex t = std::polar(1.0, -2 * PI * i / N) * odd.at(i);

	    if (debug)
            {
		outFile << "Calculated t" << endl;
            }

	}

        if (i < even.size())
    	{	
            //Replaces elements in x, adding complex to the original element
            x.at(i) = even.at(i);
            x.at(i + N/2) = even.at(i);
	}

	if (debug)
        {
	    outFile << "Replaced element in x " << endl;
            outFile << "Merging Loop ran ( " << i << " ) times!" << endl;
        }
    }
   
    if (debug)
        outFile.close();

    return;
}

// Function inverseFT
// Inputs:
//    x - A vector of complex numbers representing the fft of the audio signal.
//    debug - A boolean flag that controls the debug output.
//    fileName - A string containing the name of a user specified output file.
// Outputs:  None
// Purpose:  The inverseFT function regenerates the audio wave based on the fft input.
void inverseFT(vector<complex<double> >& x, bool debug, string fileName)
{
    //Loops through and conjoins complex numbers
    for(int i = 0; i < x.size(); i++)
    {
       x.at(i) = std::conj(x.at(i));
    }

    //Pushes conjoined vector to fourier
    FourierTransform(x);

    //Loops through and conjoins complex numbers again
    for(int i = 0; i < x.size(); i++)
    {
       x.at(i) = std::conj(x.at(i));
    }

    //scales number to (element / ectorsize)th its original size
    double size = x.size();

    for(int i = 0; i < x.size(); i++)
    {
        x.at(i) /= size;
    }
}
