/* 
 *  File:    FourierTransform.h
 *  Author:  Hue Truong & Andrew Moore
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

using namespace std;

#ifndef FourierTransform
#define FourierTransform

void fft(vector<complex<double> >, bool, string);
void inverseFT(vector<complex<double> >, bool, string);

#endif

