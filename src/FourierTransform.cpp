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
#include "../include/Utilities.h"

typedef std::complex<double> Complex;
typedef std::vector<Complex> list;

// Function fft
// Inputs:
//       wave - An AudioWave object representing the audio wave.
//    x - A vector of complex numbers describing an audio signal.
//       debug - A boolean flag that controls debug output
//       resultDirectory - A string containing the name of the user specified output file.
// Outputs:  None
// Purpose:  fft is a C++ implementation of the Cooley-Tukey Fast Fourier
//           Transform (FFT) algorithm.  Fourier transformations are used
//           primarily in signal processing to indicate the frequency in 
//           a signal, and its proportion throughout said signal.
void fft(AudioWave &wave, string outputFile, string resultDirectory, bool debug)
{

    ofstream outFile;                                     // Will hold standard output.
    ofstream debugFile;                                   // Will hold debug output.

    vector<vector<complex<double> > > fft;                // Will hold the full fft
    vector<complex<double> > channelWave;                 // Will hold the waves for the channels.

    unsigned int N;
    unsigned int k;
    unsigned int n;
    unsigned int m;

    double thetaT = 3.14159265358979323846264338328L;
    Complex phiT;
    Complex T;

    outFile.open((resultDirectory + "/" + outputFile).c_str(), ios::app);

    if (debug)
        debugFile.open((resultDirectory + "/fastFourierDebug.txt").c_str(), ios::app);

    // Get the FFT of each channel
    for (int i = 0; i < wave.getChannels(); i++)
    {
        if (i == 0)
        {
            outFile << timestamp() << ":  Getting FFT of left channel..." << endl;
            channelWave = wave.getLeftChannel();

            if (debug)
                debugFile << "Left Channel Size = " << channelWave.size() << endl;
        }
        else if (i == 1)
        {
            if (wave.getChannels() > 1 && wave.getRightSize() > 0)
            {
                outFile << timestamp() << ":  Getting FFT of the right channel...." << endl;
                channelWave = wave.getRightChannel();

                if (debug)
                    debugFile << "Right Channel Size = " << channelWave.size() << endl;
            }
        }

        if (channelWave.size() > 0)
        {
            N = channelWave.size() - 1;
            k = N;
            thetaT /= N;
            phiT = Complex(cos(thetaT), -sin(thetaT));

            if (debug)
            {
                if (i == 0)
                    debugFile << timestamp() << "Starting left channnel FFT..." << endl;
                else if (i == 1)
                    debugFile << timestamp() << "Starting right channel FFT..." << endl;

                debugFile << "\tN = " << N << endl;
                debugFile << "\tk = " << k << endl;
                debugFile << "\tthetaT = " << thetaT << endl;
                debugFile << "\tphiT = " << phiT << endl << endl;

                debugFile << "\tResults:  " << endl;
            }

            // DFT
            while (k > 1)
            {
                debugFile << "\t\tK = " << k << endl;

                n = k;

                k >>= 1;

                phiT = phiT * phiT;

                T = 1.0L;

                for (unsigned int j = 0; j < k; j++)
                {
                    for (unsigned int a = j; a < N; a += n)
                    {
                        unsigned int b = a + k;

                        if (b > channelWave.size() - 1)
                            b = channelWave.size() - 1;

                        Complex t = channelWave[a] - channelWave[b];
                        channelWave[a] += channelWave[b];
                        channelWave[b] = t * T;
                    }

                    T *= phiT;
                }
            }

            // Decimate
            m = (unsigned int)log2(N);

            for (unsigned int a = 0; a < N; a++)
            {
                unsigned int b = a;

                b = (((b & 0xaaaaaaaa) >> 1) | ((b & 0x55555555) >> 1));
                b = (((b & 0xcccccccc) >> 2) | ((b & 0x33333333) >> 2));
                b = (((b & 0xf0f0f0f0) >> 4) | ((b & 0x0f0f0f0f) >> 4));
                b = (((b & 0xff00ff00) >> 8) | ((b & 0x00ff00ff) >> 8));
                b = ((b >> 16) | (b << 16)) >> (32 - m);

                if (b > a)
                {
                    Complex t = channelWave[a];
                    channelWave[a] = channelWave[b];
                    channelWave[b] = t;
                }
            }
        }
       
        if (i == 0)
        {
            outFile << timestamp() << ":  Left Channel FFT computed." << endl;
            wave.setLeftFFT(channelWave);
        }
        else if (i == 1)
        {
            if (wave.getRightSize() > 0)
            {
                outFile << timestamp() << ":  Right Channel FFT computed." << endl;
                wave.setRightFFT(channelWave);
            }
            else
                outFile << timestamp() << "Invalid right channel.  FFT not computed." << endl;
        } 
    }
   
    outFile.close();
 

    if (debug)
        debugFile.close();

    return;
}


/*
void FastFourier(vector<vector<complex<double> > > &fft, vector<complex<double> > x, int N, int &call, string resultDirectory, bool debug)
{
    string fileName;                                // Contains the results directory path.
    ofstream outFile;                               // Used for outputting results.
    const double PI = 3.145926535897932386;         // Used for calculations.
    Complex t;                                      // Used by fft

    fileName = resultDirectory + "/fastFourierTransform.txt";

    if (debug)
    {
        outFile.open(fileName.c_str(), ios::app);

        outFile << "FAST FOURIER FUNCTION CALLED WITH N = " << N << endl;
    }

    // Recursive base step
    if (N <= 1) 
    {
        if (debug)
            outFile << "Recursive step returning from call:  " << call << endl;

        call++;
        
        return;
    }

    if (debug)
    {
        outFile << "BASE STEP COMPLETE" << endl;
    }

    // Split complex set between even and odd elements
    for (int i = 0; i < (N / 2); i += 2)
    {
        int t1 = i * 2;
        int t2 = i * 2 + 1;
        cout << "i = " << i << endl;
        cout << "N / 2 = " << (N/2) << endl;
        cout << "x.size = " << x.size() << endl;
        if (t1 < x.size() - 1)
            fft[0].push_back(x[t1]);

        if (t2 < x.size() - 1)
            fft[1].push_back(x[t2]);

        if (debug)
            outFile << "Split Loop ran ( " << i << " ) times!" << endl;
    }

    // Divide and conquer recursion
    FastFourier(fft, fft[0], (N/2), call, resultDirectory, debug);
    FastFourier(fft, fft[1], (N/2), call, resultDirectory, debug);

    for (int i = 0; i < (N/2); ++i)
    {
        // t is a complex number calculated from polar coord of (magnitude, phase angle)
        if (i < fft[1].size())
        {
            t = std::polar(1.0, -2 * PI * i / N) * fft[1].at(i);

            if (debug)
                outFile << "Caculated t" << endl;
        }

        if (i < fft[0].size() - 1)
        {
            // Replaces elements in x, adding complex to the original element.
            x.at(i) = fft[0].at(i) + t;
            x.at(i + N/2) = fft[0].at(i) - t;

            if (debug)
            {
                outFile << "Replaced element in x " << endl;
                outFile << "Merging Loop ran ( " << i << " ) times!" << endl;
            }
        }
    }

    if (debug)
        outFile.close();

    cout << "Finished FFT on " << N << " elements." << endl;

    return;
}
*/
// Function inverseFT
// Inputs:
//    x - A vector of complex numbers representing the fft of the audio signal.
//    debug - A boolean flag that controls the debug output.
//    fileName - A string containing the name of a user specified output file.
// Outputs:  None
// Purpose:  The inverseFT function regenerates the audio wave based on the fft input.
void inverseFT(vector<complex<double> >& x, string fileName, bool debug)
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
