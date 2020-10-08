#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main()
{
    ofstream fr("largeFileRandom2.txt");
    srand(time(0));
    string toFile="";
    for(int i=0;i<rand()%2000+1000;i++)
    {
        toFile+=(char)(rand()%93+33);
    }
    fr<<toFile;
    fr.close();
}
