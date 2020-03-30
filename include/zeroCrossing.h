/* 
 *  File:    zeroCrossing.h
 *  Author:  Andrew Moore, Hue Truong, and Alex Reno
 *
 *  Created: February 29, 2020, 3:06 PM
 */

/**************************************Change Log *******************************************/

// Created this header file, will contain prototypes for all algorithms. - A.M. and H.T. Feb 29 2020

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
#include "AudioWave.h"
using namespace std;

#ifndef zeroCrossing
#define zeroCrossing

// zeroCrossing algorithms
void zeroCross(AudioWave&, string, string, bool);

// Helper utilities
void summation(vector<complex<double> >, vector<vector<float> >&, int, int, string, bool);

#endif

