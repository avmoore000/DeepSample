/* 
 *  File:    spectrumCentroid.h
 *  Author:  Andrew Moore, Hue Truong, and Alex Reno
 *
 *  Created: April 8, 2020, sometime after 3:00 PM
 */

/**************************************Change Log *******************************************/

// Created this header file by copying the one from spectrumFlux - A.R. Apr 8 2020

/**************************************End Change Log ***************************************/

/**************************************To Do List ******************************/
/**************************************End To Do List **************************/

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <complex>
#include <cmath>
#include <string>
#include "FourierTransform.h"
using namespace std;

#ifndef spectrumCentroid
#define spectrumCentroid

// Audio segmentation algorithms
void spectralCentroid(AudioWave&, string, string, bool);

// Helper utilities

#endif

