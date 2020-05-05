/* 
 *  File:   anniDriver.cpp
 *  Author: Andrew Moore
 *
 *  Created April 9, 2020, 3:30 PM
 *
 */

/**************************************Change Log *******************************/

// Added a change log and to do list section - A.M. Feb 09 2020

/**************************************End Change Log ***************************/

/**************************************To Do List ******************************/


/**************************************End To Do List **************************/

#include <iostream>
#include <string>
#include "../include/ANN.h"

using namespace std;

int main(int argc, char** argv) 
{

    string resultsPath;                        // Path for file output.
    string testPath;                           // A string containing the path to the test directory
    string trainPath;                          // A string containing the path to the training data.

    int folds;                                 // Contains the number of folds to seperated data into
    double learnRate;                          // The learning rate for the neural network.
    int epochs;                                // The number of epochs to train the network for
    int codeBooks;                             // The number of codebooks to generate
    int alg;                                   // The algorithm to run against.
    bool debug;                                // Flag that controls debug output.
    int channels;                              // Holds the number of channels in the file.


    if (argc <= 1)
    {
        cout << endl << endl << "Program Use:" << endl << endl;
        cout << "./DeepSample [trainPath] [testPath] [folds] [learnRate] [epochs] [codeBooks] [alg {0,1,2,3,4,5]"
             << endl << "       [channels {1,2}] [path] [debug {0,1}]" << endl << endl;
        cout << "\ttrainPath" << endl << endl << "\t\tA string indicating the path for the training data." 
             << endl << endl;
        cout << "\ttestPath" << endl << endl << "\t\tA string indicating the path to test file location."                                                << endl << endl;
        cout << "\tfolds" << endl << endl << "\t\tInteger indicating the number of folds to break"
             << " data into." << endl << endl;
        cout << "\tlearnRate" << endl << endl << "\t\tFloating point indicating the learning rate."
             << endl << endl;
        cout << "\tepochs" << endl << endl << "\t\tAn integer indicating the number of epochs to "
             << " train over." << endl << endl;
        cout << "\tcodeBooks" << endl << endl << "\t\tAn integer indicating the number of codebooks"
             << " to generate from dataset." << endl << endl;
        cout << "\talg" << endl << endl << "\t\tInteger indicating which algorithm to run agains" 
             << endl << endl << "\t\t0 - All algorithms" << endl << "\t\t1 - Fast Fourier Transform"
             << endl << "\t\t2 - Zero Cross" << endl << "\t\t3 - Spectrum Flux" << endl
             << "\t\t4 - Cepstrum" << endl << " \t\t5 - Spectrum Centroid" << endl << endl;
        cout << "\tchannels" << endl << endl << "\t\tAn integer indicating the number of channels"
             << " in the audio samples." << endl << endl;
        cout << "\tresultsPath" << endl << endl << "\t\tThe path for saving data output." << endl << endl;
        cout << "\tdebug" << endl << endl << "\t\tA flag that controls debug output." << endl << endl
             << "\t\t0 - No debug" << endl << "\t\t1 - Debug" << endl << endl;
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            switch(i)
            {
                case 1:
                {
                    trainPath = argv[i];
                    break;
                }
                case 2: 
                {
                    testPath = argv[i];
                    break;
                }
                case 3:
                {
                    folds = atoi(argv[i]);
                    break;
                }
                case 4:
                {
                    learnRate = stod(argv[i]);
                    break;
                }
                case 5:
                {
                    epochs = atoi(argv[i]);
                    break;
                }
                case 6:
                {
                    codeBooks = atoi(argv[i]);
                    break;
                }
                case 7:
                {
                    alg = atoi(argv[i]);
                    break;
                }
                case 8:
                {
                    channels = atoi(argv[i]);
                    break;
                }
                case 9:
                {
                    resultsPath = argv[i];
                    break;
                }
                case 10:
                {
                    debug = atoi(argv[i]);
                    break;
                }
                default:
                {
                    cout << "Error with arguments." << endl;
                }
            }
        }
    }

    cout << "Calling ANNI.." << endl;

    ANNI(trainPath, testPath, folds, learnRate, epochs, codeBooks, alg, channels, resultsPath, debug);
 
    return 0;
}
