/*! 
 *  File:    TestSuite.h
 *  Author:  Hue Truong, Andrew Moore, and Alex Reno
 *
 *  Created: February 27, 2020, 12:33 PM
 */

/**************************************Change Log *******************************************/

// Created this header file, will contain prototypes for the test suite functions - A.M. Feb 27 2020
// Added Spectrum Centroid test - A.R. Apr 22 2020

/**************************************End Change Log ***************************************/

/**************************************To Do List ******************************/
/**************************************End To Do List **************************/

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>
#include "zeroCrossing.h"
#include "spectrumFlux.h"
#include "spectrumCentroid.h"
#include "ANN.h"
#include "audioHandler.h"
#include "AudioWave.h"
#include "Utilities.h"

using namespace std;
using namespace std::chrono;

#ifndef TestSuite
#define TestSuite

void audioTest(AudioWave&, string, string, string, int, bool, string, string, bool);
void fftTest(AudioWave&, string, string, bool);
void zeroCrossingTest(AudioWave&, string, string, bool);
void spectrumFluxTest(AudioWave&, string, string, bool);
void cepstrumTest(AudioWave&, string, string, bool);
void spectrumCentroidTest(AudioWave&, string, string, bool);
void anniTest(AudioWave&, string, string, bool);

#endif

