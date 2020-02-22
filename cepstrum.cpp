//cepstrum function
//
//Purpose: cepstrum is an C++ implementation of the logarithmic tranformation
//         of a fourier transform of a signal spectrum. 
//         

#include <cmath>
#include <complex>
#include <vector>
#include "FourierTransform.h"
#include "cepstrum.h"

//Hamming Window
vector<complex<double>> windowHamming(vector<complex<double>> n){
       vector<complex<double>> newn;
       //arbitrary N; fixed window size;
        double N = 200;

    //Applies the hamming window to every element in the vector list
    for(int i = 0; i <= n.size(); i++){
        newn.at(i) = 0.54 - 0.46 * cos((2 * M_PI * n.at(i)) / N - 1.0); //Formula
    }
    return newn;
}

void cepstrum(vector<complex<double>> x){

    vector<complex<double>> absfft = abs(FourierTransform(x)); //absolute value of fft
    vector<complex<double>> log = log(absfft); //log of the absolute value

    vector<complex<double>> final = inverseFT(log); //applies inverse Fourier Transform

    return final;
}