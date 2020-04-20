/*
 *  File:     FourierTransform.cpp
 *  Author:   Hue Truong, Andrew Moore, and Alex Reno
 *  Created:  February 10, 2020  12:00 AM
 *
 */

/**************************************Change Log *******************************/

//  Added comments to function headers - A.M. Feb 23 2020
//  Added debug information to functions - A.M. Feb 23 2020
//  Changed FFT method to an in place calculation - A.M. 30 Mar 2020
//  Standardized function argument list - A.M. 30 Mar 202

/**************************************End Change Log ***************************/

/**************************************To Do List ******************************/
/**************************************End To Do List **************************/


#include "../include/FourierTransform.h"
#include "../include/Utilities.h"

typedef std::complex<double> Complex;
typedef std::vector<Complex> list;

// Function fft
// Inputs:
//       wave - An AudioWave object.
//       save - A boolean flag specifiying whether to save data to file.
//       fileName - A string indicating the file for data output.
//       path - A string indicating the path for output files.
//       debug - A boolean flag that controls debug output.
// Outputs:  None
// Purpose:  fft is a C++ implementation of the Cooley-Tukey Fast Fourier
//           Transform (FFT) algorithm.  Fourier transformations are used
//           primarily in signal processing to indicate the frequency in 
//           a signal, and its proportion throughout said signal.
void fft(AudioWave &wave, string fileName, string path, bool debug)
{

    ofstream outFile;                                     // A stream pointer for data output
    ofstream debugFile;                                   // A stream pointer for debug output

    vector<vector<complex<double> > > fft;                // A vector to hold the FFT
    vector<complex<double> > channelWave;                 // A vector to hold the channel data.

    unsigned int N;
    unsigned int k;
    unsigned int n;
    unsigned int m;

    double thetaT = 3.14159265358979323846264338328L;
    Complex phiT;
    Complex T;


    // Temporarily disable debug
    debug = 0;

    outFile.open((path + "/" + fileName).c_str(), ios::app);

    if (debug)
        debugFile.open((path + "/Debug/fastFourierDebug.txt").c_str(), ios::app);

    // Get the FFT of each channel
    for (int i = 0; i < wave.getChannels(); i++)
    {
        if (i == 0)
        {
            outFile << timestamp() << ":  Getting FFT of left channel..." << endl;
            channelWave = wave.getLeftChannel();

            if (debug)
            {
                debugFile << "Left Channel Size = " << channelWave.size() << endl;

                cout << timestamp() << ":  Getting FFT of left channel..." << endl;
            }
        }
        else if (i == 1)
        {
            if (wave.getChannels() > 1 && wave.getRightSize() > 0)
            {
                outFile << timestamp() << ":  Getting FFT of the right channel...." << endl;
                channelWave = wave.getRightChannel();

                if (debug)
                {
                    debugFile << "Right Channel Size = " << channelWave.size() << endl;

                    cout << timestamp() << ":  Getting FFT of right channel..." << endl;
                }
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
                {
                    debugFile << timestamp() << "Starting left channnel FFT..." << endl;
                    debugFile << "Left Channel DFT Results" << endl << endl;
                }
                else if (i == 1)
                {
                    debugFile << timestamp() << "Starting right channel FFT..." << endl;
                    debugFile << "Right Channel DFT Results" << endl << endl;
                }

                debugFile << "\tN = " << N << endl;
                debugFile << "\tk = " << k << endl;
                debugFile << "\tthetaT = " << thetaT << endl;
                debugFile << "\tphiT = " << phiT << endl << endl;

                debugFile << "\tResults:  " << endl;
            }

            // DFT
            while (k > 1)
            {
                if (debug)
                    debugFile <<"\tK = " << k << endl;

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

                        // Correct for NAN results
                        if (isnan(real(channelWave[a])))
                            channelWave[a] = (0,0);
                        
                        if (isnan(real(channelWave[b])))
                            channelWave[b] = (0,0);
                        if (debug)
                            debugFile << "channelWave(" << a << "," << b << ") = ("
                                      << channelWave[a] << "," << channelWave[b] << ")" << endl;
                    }

                    T *= phiT;
                }
            }

            // Decimate
            m = (unsigned int)log2(N);

            if (debug)
            {
                debugFile << endl << endl << "Decimation Results:" << endl << endl;

                if (i == 0)
                    debugFile << "Left Channel:  " << endl << endl;
                else
                    debugFile << "Right Channel:  " << endl << endl;
            }

            for (unsigned int a = 0; a < N; a++)
            {
                unsigned int b = a;

                b = (((b & 0xaaaaaaaa) >> 1) | ((b & 0x55555555) << 1));
                b = (((b & 0xcccccccc) >> 2) | ((b & 0x33333333) << 2));
                b = (((b & 0xf0f0f0f0) >> 4) | ((b & 0x0f0f0f0f) << 4));
                b = (((b & 0xff00ff00) >> 8) | ((b & 0x00ff00ff) << 8));
                b = ((b >> 16) | (b << 16)) >> (32 - m);

                if (b > a)
                {
                    Complex t = channelWave[a];
                    channelWave[a] = channelWave[b];
                    channelWave[b] = t;

                    if (debug)
                    {
                       debugFile << "\tchannelWave(" << a << "," << b << ") = ("
                                 << channelWave[a] << "," << channelWave[b] << ")" << endl;      
                    } 
                    
                }
            }
        }
       
        if (i == 0)
        {
            outFile << timestamp() << ":  Left Channel FFT computed." << endl;
            wave.setLeftFFT(channelWave);

            if (debug)
                cout << timestamp() << ":  Left Channel FFT computed." << endl;
        }
        else if (i == 1)
        {
            if (wave.getRightSize() > 0)
            {
                outFile << timestamp() << ":  Right Channel FFT computed." << endl;
                wave.setRightFFT(channelWave);

                if (debug)
                   cout << timestamp() << ":  Right Channel FFT computed." << endl;
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


// Function inverseFT
// Inputs:
//    x - A vector of complex numbers representing the fft of the audio signal.
//    debug - A boolean flag that controls the debug output.
//    fileName - A string containing the name of a user specified output file.
// Outputs:  None
// Purpose:  The inverseFT function regenerates the audio wave based on the fft input.
void inverseFT(vector<double>& x, string fileName, bool debug)
{
    //Loops through and conjoins complex numbers
    for(int i = 0; i < x.size(); i++)
    {
       x.at(i) = real(std::conj(x.at(i)));
    }

    //Pushes conjoined vector to fourier
    FourierTransform(x);

    //Loops through and conjoins complex numbers again
    for(int i = 0; i < x.size(); i++)
    {
       x.at(i) = real(std::conj(x.at(i)));
    }

    //scales number to (element / ectorsize)th its original size
    double size = x.size();

    for(int i = 0; i < x.size(); i++)
    {
        x.at(i) /= size;
    }
}
