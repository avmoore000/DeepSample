/* 
 *  File:    Utilities.h
 *  Author:  Hue Truong and Andrew Moore
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
using namespace std;

#ifndef Utilities
#define Utilities

void printer(string,vector<string>,int,int,int);;
string createString(int,int);
string createString(bool,int);
string createString(double,int);
void normalize(vector<complex<double > >,vector<double>&,int,int,bool,string);

#endif

