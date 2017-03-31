#include "symbolscounter.h"
#include <iostream>
#include <iomanip>

using namespace std;

vector<int>
SymbolsCounter::getSymbolsCount(ifstream& file)
{
    if (!file.is_open())
    {
        cerr<<"SymbolsCounter::getSymbolsCount: Stream open error"<<endl;
        return vector<int>();
    }
    vector<int> sym(256);
    for (int i=0;i<256;++i)
    {
        sym[i]=0;
    }
    while (!file.eof())
    {
        int c=file.get();
        if (!file) break;
        if (c>255 || c<0)
        {
            cerr<<"SymbolsCounter::getSymbolsCount: Unknown symbol"<<endl;
            continue;
        }
        sym[c]++;
    }
    return sym;
}

void
SymbolsCounter::printSymbols(vector<int> vec)
{
    if (vec.empty())
    {
        cerr<<"SymbolsCounter::printSymbols: Vector is empty"<<endl;
        return;
    }
    int j=1;
    for (int i=0;i<256;++i)
    {
        cout<<setw(3)<<left<<i<<": "<<setw(5)<<left<<vec[i];
        if (j%8==0)
        {
            cout<<endl;
        }
        j++;
    }
    return;
}
