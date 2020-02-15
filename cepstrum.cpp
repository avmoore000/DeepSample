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
const double PI = 3.14159265359;

//HAMMING WINDOW
for(int i = 0; i < x.size(); i++){
    timeDomain[i] = (float) (( 0.53836 - ( 0.46164 * cos( (2 * PI) * (double)i  / (double)( x.size() - 1 ) ) ) ) * frameBuffer[i]);
}//Not sure if .53836 & 0.46164 are constants

}
