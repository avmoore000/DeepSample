/* 
 *  File:    cepstrum.h
 *  Author:  Andrew Moore, Hue Truong, and Alex Reno
 *
 *  Created: February 29, 2020, 3:06 PM
 */

/**************************************Change Log *******************************************/

// Created this header file, will contain prototypes for all algorithms. - A.M. and H.T. Feb 29 2020
// Added in the function prototypes for cepstrum and hamming window - A.M. and H.T. Feb 29 2020

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

#ifndef cepstrum
#define cepstrum

// Audio segmentation algorithms
vector<double> Rcepstrum(vector<complex<double> >&, double);

// Helper utilities
vector<double> windowHamming(vector<complex<double> >, double);
bool getSign(complex<double>, bool, string);

#endif

