/* 
 *  File:    audioSegmentation.h
 *  Author:  Andrew Moore and Hue Truong
 *
 *  Created: February 9, 2020, 3:06 PM
 */

/**************************************Change Log *******************************************/

// Created this header file, will contain prototypes for all algorithms. - A.M. Feb 09 2020
// Added in the function prototypes for cepstrum and hamming window - A.M. Feb 23 2020

/**************************************End Change Log ***************************************/

/**************************************To Do List ******************************/
/**************************************End To Do List **************************/

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <complex>
#include <cmath>
#include <string>
#include "FourierTransform.h"
using namespace std;

#ifndef AudioSegmentation
#define AudioSegmentation

// Audio segmentation algorithms
void zeroCrossing(vector<complex<double> >,float[],int,bool);
void spectrumFlux(vector<complex<double> >,float[],int,bool);
vector<complex<double> > cepstrum(vector<complex<double> >);

// Helper utilities
vector<complex <double> > windowHamming(vector<complex<double> >);
bool getSign(complex<double>,bool,string);

#endif

