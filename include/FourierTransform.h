/* 
 *  File:    FourierTransform.h
 *  Author:  Hue Truongm, Andrew Moore, and Alex Reno
 *
 *  Created: February 15, 2020, 12:19 PM
 */

/**************************************Change Log *******************************************/

// Created this header file, will contain prototypes for all algorithms. - A.M. Feb 15 2020

/**************************************End Change Log ***************************************/

/**************************************To Do List ******************************/
/**************************************End To Do List **************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <complex>
#include <cmath>
#include "AudioWave.h"
using namespace std;

#ifndef FourierTransform
#define FourierTransform

void fft(AudioWave &, string, string, bool);
void inverseFT(vector<complex<double> >, string, bool);

#endif

