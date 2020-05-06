/* 
 *  File:    Fold.h
 *  Author:  Andrew Moore, Hue Truong, and Alex Reno
 *
 *  Created: May 5, 2020, 10:00 PM
 */

/**************************************Change Log *******************************/

/**************************************End Change Log ***************************/

/**************************************To Do List ******************************/
/**************************************End To Do List **************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
#include <string>
using namespace std;

#ifndef Fold_H
#define Fold_H

// Class Fold
class Fold
{
    public:

        Fold();                                                // Class constructor
        ~Fold();                                               // Class destructor


        // Update

        void pushFold(vector<double>);                         // Push a value to dataFolds

        // Getters

        vector<double> getFold(int);                           // Return a fold from dataFolds
        int getSize();                                         // Return the size of the fold
      
    private:

        // Data members

        vector<vector<double> > dataFolds;                     // The data folds.
};
#endif
