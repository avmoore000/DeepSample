/* 
 *  File:    audioHandler.h
 *  Author:  Hue Truong, Andrew Moore, and Alex Reno
 *
 *  Created: February 23, 2020, 7:16 PM
 */

/**************************************Change Log *******************************************/

// Created this header file, will contain prototypes for all algorithms. - A.M. Feb 23 2020

/**************************************End Change Log ***************************************/

/**************************************To Do List ******************************/
/**************************************End To Do List **************************/

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <complex>
#include <vector>
#include <ctype.h>
#include <float.h>
#include <sndfile.h>
using namespace std;

#ifndef audioHandler
#define audioHandler

void loadAudio(string,vector<complex<double> >&,vector<complex<double> >&,int,bool);
static void convertSound(string,vector<complex<double> >&,vector<complex<double> >&,int,bool,bool);

#endif

