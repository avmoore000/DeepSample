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
using namespace std;

#ifndef ANN
#define ANN

// Neural network functions
void ANNI(vector<vector<float> >, double[], string, int, string, bool);

// Helper utilities
double euclideanDistance(vector<double>, vector<double>, string, bool);
int getBestMatch(vector<vector<float> >, vector<float>, int, string, bool);
int getBestMatch(vector<vector<double> >, vector<double>, int, string, bool);
void randomDatabase(vector<vector<double> >, vector<vector<double> >&, string,bool);
void trainCodeBooks(vector<vector<double> >, vector<vector<double> >&, int, double, int, int, string, bool);

#endif

