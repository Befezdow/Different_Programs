#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

int main()
{
    ifstream in;
    ofstream out;
    in.open("heCat.txt");
    out.open("heCatOut.txt");
    if (!in.is_open() || !out.is_open())
    {
        return 1;
    }
    string strBuffer;
    while (!in.eof())
    {
        unsigned char c=(unsigned char)in.get();
        if (((c>191 && c<224) || c==168) && strBuffer.size()>2)
        {
            cout<<"qwerty"<<endl;
            out<<strBuffer<<endl;
            strBuffer.clear();
            strBuffer+=c;
        }
        else
        {
            strBuffer+=c;
        }
    }
    
    if (strBuffer.size()!=0)
    {
        out<<strBuffer<<endl;
    }
    in.close();
    out.close();
    
    return 0;
}