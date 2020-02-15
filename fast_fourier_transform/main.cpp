//fourierTransform Function

//Purpose: fourierTransform is an C++ implementation of the Cooley-Tukey Fast Fourier
//         Transform (FFT) algorithm. Fourier transformations are used primarily in signal
//         processing to indicate the frequency in signal, and its proportion throughout
//         said signal.
//

#include <complex>
#include <iostream>
#include <cmath>
#include <vector>

using std::vector;
typedef std::complex<double> Complex;
typedef std::vector<Complex> list;

void FourierTransform(list& x){ //Implemented in a recursive format
    std::cout << "FUNCTION CALLED" << std::endl;
    const double PI = 3.141592653589793238460;
    const int N = x.size();
    
    //Recursive basis step
    if(N <= 1) return; 
    
    std::cout << "BASE STEP COMPLETE" << std::endl;

    list even;
    list odd;
    
    //Split complex set between even and odd elements;
    for(int i = 0; i < (N / 2); i = i + 2){
        even.push_back(i);
        odd.push_back(i + 1);
        std::cout << "Split Loop ran (" << i + 1 << ") times!" << std::endl;
    }
    
    //Divide and conquer recursion
    FourierTransform(even); 
    FourierTransform(odd);
    
    for (size_t i = 0; i < (N/2); ++i){
        //t is a complex number calculated from polar coord of (magnitude, phase angle)
        Complex t = std::polar(1.0, -2 * PI * i / N) * odd.at(i); 
        
        //Replaces elements in x, adding complex to the original element
        x.at(i) = even.at(i) + t;
        x.at(i + N/2) = even.at(i) - t;
        //x[k    ] = even[k] + t;
        //x[k+N/2] = even[k] - t;
        std::cout << "Merging Loop ran (" << i + 1 << ") times!" << std::endl;
    }
}

int main(){
    const Complex i(1.0, 2.0);
    const Complex j(0.0, 1.0);

    list data;
    data.push_back(i);
    data.push_back(j);
    FourierTransform(data);
   
    return 0;
}

