/*! 
 *  File:    TestSuite.h
 *  Author:  Hue Truong, Andrew Moore, and Alex Reno
 *
 *  Created: February 27, 2020, 12:33 PM
 */

/**************************************Change Log *******************************************/

// Created this header file, will contain prototypes for the test suite functions - A.M. Feb 27 2020

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
#include "ANN.h"
#include "audioHandler.h"

using namespace std;
using namespace std::chrono;

#ifndef TestSuite
#define TestSuite

void zeroCrossingTest(vector<complex<double> >,vector<complex<double> >,int,bool,string,string);
void spectrumFluxTest(vector<complex<double> >,vector<complex<double> >,int,bool,string,string);
void cepstrumTest(vector<complex<double> >, vector<complex<double> >, int, bool, string, string);
void anniTest(string,string,string,int,bool);

#endif

