#include <iostream>
#include <fstream>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <bitset>
#include <algorithm>
using namespace std;
string ArturoHash(string inputString);
void readFile(char *argv[], int argc);
void testing();
unsigned long long ArturoHashTest(string inputString);
string toHex(unsigned long long input);
string toBinary(unsigned long long input);
const unsigned int k[64] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee ,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501 ,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be ,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821 ,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa ,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8 ,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed ,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a ,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c ,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70 ,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05 ,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665 ,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039 ,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1 ,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1 ,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};
int main(int argc, char *argv[])
{
    cout <<argc-1<<" arguments entered.\n";
    for(int i=1; i<argc; i++)
    {
        cout<<argv[i]<<"\n"<<endl;
    }
    cout<<"Ivesti (1) ar skaityti is failo (2) ar testuoti(3)?"<<endl;
    int ans;
    cin>>ans;
    string inputString;
    if(ans==1)
    {
        cin>>inputString;
        ArturoHash(inputString);
    }
    else if(ans==2)
    {
        readFile(argv,argc);
    }
    else if(ans==3)
    {
        testing();
    }
    return 0;
}
void testing()
{
    srand(time(0));
    string one="",two="",hashOne,hashTwo;
    int count=10,collisionCount=0;
    vector<double> percentageBinary;
    vector<double> percentageHex;
    for(int i=0; i<4; i++)
    {
        if(i==0)
        {
            count=10;
        }
        else if(i==1)
        {
            count=100;
        }
        else if(i==2)
        {
            count=500;
        }
        else if(i==3)
        {
            count=1000;
        }
        for(int j=0; j<25000; j++)
        {
            for(int k=0; k<count; k++)
            {
                one+=(char)(rand()%93+33);
                two+=(char)(rand()%93+33);
            }
            //cout<<one<<" "<<two<<endl;
            hashOne=ArturoHash(one);
            hashTwo=ArturoHash(two);
            if(hashOne==hashTwo)
            {
                cout<<"COLLISION at "<<count<<" symbols"<<endl;
                collisionCount++;
            }
            one="";
            two="";
            for(int k=0;k<count;k++)
            {
                one+=(char)(rand()%93+33);
            }
            two=one;
            while(two==one)
            {
                two[rand()%count]=(char)(rand()%93+33);
            }
            unsigned long long hashOneTest=ArturoHashTest(one),hashTwoTest=ArturoHashTest(two);
            //cout<<one<<" "<<two<<endl;
            string binaryExperiment1=toBinary(hashOneTest),binaryExperiment2=toBinary(hashTwoTest);
            string hexExperiment1=toHex(hashOneTest),hexExperiment2=toHex(hashTwoTest);
            //cout<<hexExperiment1<<" "<<hexExperiment2<<endl;
            double percentageBinaryCounter=0,percentageHexCounter=0;
            for(int i=0;i<binaryExperiment1.size();i++)
            {
                if(binaryExperiment1[i]!=binaryExperiment2[i])
                {
                    percentageBinaryCounter+=(double)100/binaryExperiment1.size();
                }
            }
            if(percentageBinaryCounter==0)
            {
                cout<<binaryExperiment1<<" "<<binaryExperiment2<<endl;
                cout<<one<<" "<<two<<endl;
                cout<<ArturoHash(one)<<" "<<ArturoHash(two)<<endl;
                cout<<ArturoHashTest(one)<<" "<<ArturoHashTest(two)<<endl;
                collisionCount++;

            }
            percentageBinary.push_back(percentageBinaryCounter);
            percentageBinaryCounter=0;
            for(int i=0;i<hexExperiment1.size();i++)
            {
                if(hexExperiment1[i]!=hexExperiment2[i])
                {
                    percentageHexCounter+=(double)100/hexExperiment1.size();
                }
            }
            percentageHex.push_back(percentageHexCounter);
            percentageHexCounter=0;
        }
    }
    double maxElement=*max_element(std::begin(percentageHex),std::end(percentageHex));
    double minElement=*min_element(std::begin(percentageHex),std::end(percentageHex));
    double sum=0;
    for(int i=0;i<percentageHex.size();i++)
    {
        sum+=percentageHex[i];
    }
    double average=(double)sum/percentageHex.size();
    sum=0;
    cout<<"Hex difference maximum and minimum percentages: "<<maxElement<<" "<<minElement<<endl;
    cout<<"Hex average: "<<average<<endl;
    maxElement=*max_element(std::begin(percentageBinary),std::end(percentageBinary));
    minElement=*min_element(std::begin(percentageBinary),std::end(percentageBinary));
    for(int i=0;i<percentageBinary.size();i++)
    {
        sum+=percentageBinary[i];
    }
    average=(double)sum/percentageBinary.size();
    cout<<"Binary difference maximum and minimum percentages: "<<maxElement<<" "<<minElement<<endl;
    cout<<"Binary average: "<<average<<endl;
    cout<<"Amount of collisions: "<<collisionCount<<endl;
}
string toBinary(unsigned long long input)
{
    unsigned long long i=0, temp;
    string output="";
    while(input>0)
    {
        temp=input%2;
        output+=to_string(temp);
        input/=2;
    }
    return output;
}
string toHex(unsigned long long input)
{
    stringstream stream;
    stream<<hex<<input<<dec;
    return stream.str();
}
string ArturoHash(string inputString)
{
    auto start=std::chrono::high_resolution_clock::now();
    int keys[]= {3,5,7,11,13,17,19,23};
    int largeKeys[]={564654616,654989715,42788378,73783783,74896637,785375786,7867682,7};
    unsigned long long sum=0x54e55;
    for(int i=0; i<inputString.size(); i++)
    {
        sum^=(sum<<keys[i%8])+inputString[i]+(sum>>keys[(i+1)%8]);
    }
    sum = ((sum >> 8) ^ sum) * k[0];//0x45d9f3b;
    sum = ((sum << 8) ^ sum) * k[1];//0x45d9f3b;
    sum = (sum >> 8) ^ sum;
    auto end=std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff=end-start;
    //cout<<std::hex<<sum<<std::dec<<endl;
    //std::cout<<"Hashavimas uztruko: "<<diff.count()<<endl;
    stringstream stream;
    for(int i=0;i<4;i++)
    {
        stream<<hex<<sum*k[i];
    }
//    while(stream.str().size()<64)
//    {
//        stream<<hex<<sum*k[stream.str().size()%16];
//    }
//    while(stream.str().size()>64)
//    {
//        stream.str().erase(stream.str().size()-1);
//    }
    //cout<<stream.str().size()<<endl;
    int i=0;
    string result;
    while(stream.str().size()<64)
    {
        stream<<hex<<sum*k[i%64];
        i++;
    }
    result=stream.str();
    while(result.size()>64)
    {
        result=result.substr(0,result.size()-1);
    }
    //cout<<result<<" "<<result.size()<<endl;
    return result;
}
unsigned long long ArturoHashTest(string inputString)
{
    auto start=std::chrono::high_resolution_clock::now();
    int keys[]= {3,5,7,11,13,17,19,23};
    int largeKeys[]={564654616,654989715,42788378,73783783,74896637,785375786,7867682,7};
    unsigned long long sum=0x54e55;
    for(int i=0; i<inputString.size(); i++)
    {
        sum^=(sum<<keys[i%8])+inputString[i]+(sum>>keys[(i+1)%8]);
    }
    sum = ((sum >> 8) ^ sum) * 0x45d9f3b;
    sum = ((sum << 8) ^ sum) * 0x45d9f3b;
    sum = (sum >> 8) ^ sum;
    sum*=k[0];
    for(int i=1;i<4;i++)
    {
        sum+=sum*k[i];
    }
    auto end=std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff=end-start;
    return sum;
}
void readFile(char *argv[], int argc)
{
    for(int i=1; i<argc; i++)
    {
        ifstream fd(argv[i]);
        string inputString="";
        if(fd)
        {
            ostringstream ss;
            ss<<fd.rdbuf();
            inputString=ss.str();
        }
        //cout<<inputString<<endl;
        ArturoHash(inputString);
    }

}
