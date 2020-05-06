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
#include "Fold.h"
using namespace std;

#ifndef ANN
#define ANN

// Neural network functions
void ANNI(string, string, int, double, int, int, int, int, string, bool);
void learningVectorQuantization(vector<Fold>, vector<Fold>, vector<string>, vector<string>, string, int, int, int, double, int, string, string, bool);

// Helper utilities
void lvqHelper(string, string, string, string,int, double, int, int, int, string, bool);
double euclideanDistance(vector<double>, vector<double>, string, bool);
int getBestMatch(vector<vector<double> >, vector<double>, string, string, bool);
void prepareFolds(bool, int, int, int, int, string, vector<Fold> &, vector<string>&, string, bool);
void randomDatabase(vector<Fold>, vector<vector<double> >&, int alg, string,bool);
void trainCodeBooks(vector<Fold>, vector<vector<double> >&, int, int, double, int, string, string, bool);

#endif

