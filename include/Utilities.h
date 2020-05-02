/* 
 *  File:    Utilities.h
 *  Author:  Hue Truong, Andrew Moore, and Alex Reno
 *
 *  Created: February 9, 2020, 3:06 PM
 */

/**************************************Change Log *******************************************/

// Created this header file, will contain prototypes for all algorithms. - A.M. Feb 09 2020

/**************************************End Change Log ***************************************/

/**************************************To Do List ******************************/
/**************************************End To Do List **************************/

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <complex>
#include <chrono>
#include <ctime>
#include "AudioWave.h"
using namespace std;

#ifndef Utilities
#define Utilities

void graphAlg(AudioWave, string, int, string, string, bool);
void generateScript(int, string, string, string, double, double, string, string, int);
void genTrainSet(vector<vector<double> >, vector<vector<double> >&, int);
void normalize(AudioWave, vector<vector<double> >&, string, string, bool);
void plotter(AudioWave, int, int, string, string, bool);
void printer(string,vector<string>,int,int,int);
void realify(AudioWave, vector<vector<double> >&, string, string, bool);
string createString(int,int);
string createString(bool,int);
string createString(double,int);
string timeStamp();
bool fileExists(string);
bool sortDist(const vector<double>&, const vector<double>&);
int sign(double);

#endif

