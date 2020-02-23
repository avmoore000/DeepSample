#include <fstream>
#include <iostream>

using namespace std;

void inputraw(){
    string userInput;

    cout << ".raw file to be manipulated: " << endl;
    cin >> userInput;

    ifstream c(userInput, std::ios_base::binary);

    if(c.good());

    char ch; 
    c.read(&ch, sizeof(ch));
}

int main(){
    inputraw();
}