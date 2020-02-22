/* 
 * File:   audioSegmentation.h
 * Author: Andrew Moore
 *
 * Created on February 9, 2020, 3:06 PM
 */

/**************************************Change Log *******************************************/

// Created this header file, will contain prototypes for all algorithms. - A.M. Feb 09 2020

/**************************************End Change Log ***************************************/

/**************************************To Do List ******************************/
/**************************************End To Do List **************************/

#include <vector>
#include <complex>
#include <string>
using namespace std;
#ifndef AudioSegmentation
#define AudioSegmentation

void zeroCrossing(vector<complex<double>>,float[],int,bool, string);
bool getSign(complex<double>,bool,string);

#endif

