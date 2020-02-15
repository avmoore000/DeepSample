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
#include "FourierTransform.h"
using std::vector;
typedef std::complex<double> Complex;
typedef std::vector<Complex> list;

void fastFourierTransform(vector<complex<double>> x)
{
//void FourierTransform(list& x){ //Implemented in a recursive format
    std::cout << "FUNCTION CALLED" << std::endl;
    const double PI = 3.141592653589793238460;
    const int N = x.size();
    
    //Recursive basis step
    if(N <= 1) return; 
    
    std::cout << "BASE STEP COMPLETE" << std::endl;

    /*
    list even;
    list odd;
    */

    vector <complex<double>> even;
    vector <complex<double>> odd;
    
    //Split complex set between even and odd elements;
    for(int i = 0; i < (x.size() / 2); i = i + 2){
        even.push_back(i);
        odd.push_back(i + 1);
        std::cout << "Split Loop ran (" << i << ") times!" << std::endl;
    }
    
    //Divide and conquer recursion
    fastFourierTransform(even); 
    fastFourierTransform(odd);

    for (int i = 0; i < (x.size() / 2); ++i){
        //t is a complex number calculated from polar coord of (magnitude, phase angle)
        
	if (i < odd.size())
	{
	    Complex t = std::polar(1.0, -2 * PI * i / N) * odd.at(i);
            std::cout << "Calculated t" << endl;
	}

        if (i < even.size())
    	{	
            //Replaces elements in x, adding complex to the original element
            x.at(i) = even.at(i);
            x.at(i + N/2) = even.at(i);
	}

	std::cout<<"Replaced element in x " << endl;

        //x[k    ] = even[k] + t;
        //x[k+N/2] = even[k] - t;
        std::cout << "Merging Loop ran (" << i << ") times!" << std::endl;
    }
}


void inverseFT(vector<complex<double>>& x){
    //Loops through and conjoins complex numbers
    for(int i = 0; i < x.size(); i++){
       x.at(i) = std::conj(x.at(i));
    }

    //Pushes conjoined vector to fourier
    FourierTransform(x);

    //Loops through and conjoins complex numbers again
    for(int i = 0; i < x.size(); i++){
       x.at(i) = std::conj(x.at(i));
    }

    //scales number to (element / ectorsize)th its original size
    double size = x.size();
    for(int i = 0; i < x.size(); i++){
        x.at(i) /= size;
    }
}
