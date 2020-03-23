#include <iostream>
#include <string>
#include "../include/Utilities.h"
using namespace std;

int main()
{
    string file = "testSpectrum.txt";
    string path = ".";
    int type = 0;
    int channel = 2;
    int alg = 1;

    plotter(file,path,type,channel,alg);

    return 0;
}
