//cepstrum function
//
//Purpose: cepstrum is an C++ implementation of the logarithmic tranformation
//         of a fourier transform of a signal spectrum. 
//         

#include <cmath>
#include <complex>
#include "FourierTransform.h"
#include "cepstrum.h"

//Raw implementation of the cepstrum equation
//Need to preprocess with Hamming window
void cepstrum(vector<complex<double>>& x){

//HAMMING WINDOW
for(int i = 0; i < x.size();i++){
    timeDomain[i] = (float) (( 0.53836 - ( 0.46164 * Math.cos( TWOPI * (double)i  / (double)( SEGMENTATION_LENGTH - 1 ) ) ) ) * frameBuffer[i]);
}//Not sure if .53836 & 0.46164 are constants

}
