/* 
 *  File:    ANN.h
 *  Author:  Andrew Moore, Hue Truong, and Alex Reno
 *
 *  Created: March 8, 2020, 12:00 PM
 */

/**************************************Change Log *******************************************/

// Created this header file, will contain prototypes for all algorithms. - A.M., H.T., and A. Feb 29 2020

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
#include <algorithm>
#include <time.h>
#include "AudioWave.h"
using namespace std;

#ifndef ANN
#define ANN

// Neural network functions
void ANNI(string, int, double, int, int, int, int, string, bool);
void learningVectorQuantization(vector<vector<double> >, vector<vector<double> >, vector<string>, vector<string>, int, double, int, string, string, bool);

// Helper utilities
void lvqHelper(string, string, string,int, double, int, int, int, string, bool);
double euclideanDistance(vector<double>, vector<double>, string, bool);
int getBestMatch(vector<vector<double> >, vector<double>, string, string, bool);
void prepareFolds(bool,int, int, int, int, string, vector<vector<double> > &, vector<string>&, string, bool);
void randomDatabase(vector<vector<double> >, vector<vector<double> >&, string,bool);
void trainCodeBooks(vector<vector<double> >, vector<vector<double> >&, int, double, int, string, string, bool);

#endif

