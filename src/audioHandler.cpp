/* 
 *  File:    audioHandler.cpp
 *  Author:  Andrew Moore  and Hue Truong
 *
 *  Created: February 9, 2020, 1:46 PM
 */

/**************************************Change Log *******************************/

// Created initial audio handling function.  - A.M. Feb 09 2020.

/**************************************End Change Log ***************************/

/**************************************To Do List ******************************/
/**************************************End To Do List **************************/

#include "../include/audioHandler.h"

#define BLOCKSIZE 4096

#ifdef DBL_DECIMAL_DIG
        #define OP_DBL_Digs (DBL_DECIMAL_DIG)
#else
        #ifdef DECIMAL_DIG
                #define OP_DBL_Digs (DECIMAL_DIG)
        #else
                #define OP_DBL_Digs (DBL_DIG + 3)
        #endif
#endif

static void
convertToText (string infileName, string outFileName, int channels, int fullPrecision)
{
    SNDFILE *infile = NULL;  
    SF_INFO sfinfo;     
    float buf [BLOCKSIZE];
    sf_count_t frames;
    int k, m, readcount;
    ofstream outFile;

    outFile.open(outFileName, ios::app);
   
    if((infile = sf_open(infileName.c_str(), SFM_READ, &sfinfo)) == NULL)
        cout << "Error opening audio file." << endl;

    frames = BLOCKSIZE / channels;

    while ((readcount = sf_readf_float (infile, buf, frames)) > 0)
    {      
        cout << "Reading the input file" << endl; 
        for (k = 0 ; k < readcount ; k++)
        {       
            for (m = 0 ; m < channels ; m++)
            {
                if (fullPrecision)
                    outFile << OP_DBL_Digs-1 << ", " << buf[k * channels + m];
                else
                    outFile << buf[k*channels+m];
                    //fprintf (outFile, " % 12.10f", buf [k * channels + m]);
            }
            outFile << endl;
        } 
    }

    outFile.close(); 

        return;
} /* convert_to_text */

int loadAudio(string infileName, string outFileName)
{
    cout << "Audio loader called." << endl;
    convertToText(infileName, outFileName, 2, 1);
    return 0;
}
