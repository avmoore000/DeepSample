/* 
 *  File:    spectrumFlux.h
 *  Author:  Andrew Moore and Hue Truong
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
using namespace std;

#ifndef spectrumFlux
#define spectrumFlux

// Audio segmentation algorithms
void spectralFlux(vector<complex<double> >,vector<complex<double> >,double[],int,bool,string);

// Helper utilities

#endif

