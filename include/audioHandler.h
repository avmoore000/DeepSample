/* 
 *  File:    audioHandler.h
 *  Author:  Andrew Moore
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
#include <ctype.h>
#include <float.h>
#include <sndfile.h>
using namespace std;

#ifndef audioHandler
#define audioHandler

int loadAudio(string, string);
static void convertToText(SNDFILE*, string, int, int);

#endif

