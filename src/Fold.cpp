/* 
 *  File:    Fold.cpp
 *  Author:  Andrew Moore, Hue Truong, and Alex Reno
 *
 *  Created: March 27, 2020, 12:30 PM
 */

/**************************************Change Log *******************************/

/**************************************End Change Log ***************************/

/**************************************To Do List ******************************/
/**************************************End To Do List **************************/

#include "../include/Fold.h"
#include <sys/stat.h>

// Function Fold
// Inputs:
// Outputs: None
// Purpose:  This is the constructor for a Fold object.
Fold::Fold() 
{
}

// Function ~Fold
// Inputs: None
// Outputs: None
// Purpose: This is the destructor for Fold object.
Fold::~Fold()
{
    dataFolds.clear();
}

// Function pushFold
// Input:
//      newData -  A vector of doubles representing a channel of data
// Outputs: None
// Purpose:  Add a fold to the dataFolds vector
void Fold::pushFold(vector<double> newData)
{
    dataFolds.push_back(newData);
}

// Function getFold
// Input:  
//      index - An integer indicating which fold to retrieve
// Output:
//       dataFold -  An N-d vector of doubles representing a data fold.
// Purpose:  Returns a dataFold
vector<double> Fold::getFold(int index)
{
    return dataFolds.at(index);
}

// Function getSize
// Input:
// Ouput:
//      size - The size of the dataFold member
// Purpose:  Return the size of the dataFold member
int Fold::getSize()
{
    return dataFolds.size();
}
/******************** Initializers ********************/
