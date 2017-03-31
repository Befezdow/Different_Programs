#include "binarytree.h"
#include "binarywriter.h"
#include "symbolscounter.h"
#include "binaryreader.h"
#include <netinet/in.h>
#include <cstring>

using namespace std;

void codeFile(ifstream& inStream, ofstream& outStream)
{
    if (!inStream.is_open())
    {
        throw "codeFile: In stream is'n open";
    }
    if (!outStream.is_open())
    {
        throw "codeFile: Out stream is'n open";
    }
    vector<int> symbolsCount=SymbolsCounter::getSymbolsCount(inStream);
    BinaryTree tree(symbolsCount);
    map<char,string> encoding=tree.getEncoding();
    BinaryWriter writer;
    writer.setEncoding(encoding);
    writer.attach(&outStream);
    inStream.clear();
    inStream.seekg(0,ios::beg);
    outStream.write("HUFF",4);
    for (int i=0;i<256;i++)
    {
        unsigned int num=htonl(symbolsCount[i]);
        outStream.write((char*)&num, 4);
    }
    char c;
    while (true)
    {
        c=inStream.get();
        if (inStream.eof())
        {
            writer.flush();
            break;
        }
        else
        {
            try
            {
                writer.write(c);
            }
            catch (const char* str)
            {
                throw str;
            }
        }
    }
    writer.detach();
    return;
}

void decodeFile(ifstream& inStream, ofstream& outStream)
{
    if (!inStream.is_open())
    {
        throw "codeFile: In stream is'n open";
    }
    if (!outStream.is_open())
    {
        throw "codeFile: Out stream is'n open";
    }
    char str[4];
    inStream.read(str,4);
    if (str[0]!='H' || str[1]!='U' || str[2]!='F' || str[3]!='F')
    {
        throw "decodeFile: Unknown format";
    }
    vector<int> symbolsCount(256);
    unsigned int num;
    unsigned long long sym=0;
    for (int i=0;i<256;++i)
    {
        inStream.read((char*)&num, 4);
        symbolsCount[i]=ntohl(num);
        sym+=symbolsCount[i];
    }
    BinaryTree tree(symbolsCount);
    BinaryReader reader;
    reader.setReadTree(&tree);
    reader.attach(&inStream);
    for (unsigned long long i=0;i<sym;++i)
    {
        try
        {
            outStream<<reader.read();
        }
        catch (const char* str)
        {
            throw str;
        }
    }
    return;
}

int main(int argc, char *argv[])
{
    if (argc!=4)
    {
        cerr<<"main: Incorrect count of arguments"<<endl;
        return 1;
    }
    if (!strcmp(argv[2],"-c"))
    {
        ifstream inFile;
        inFile.open(argv[1]);
        if (!inFile)
        {
            cerr<<"main: InFile open error"<<endl;
            return 1;
        }

        ofstream outFile;
        outFile.open(argv[3],ios::binary);
        if (!outFile)
        {
            cerr<<"main: OutFile open error"<<endl;
            return 1;
        }
        try
        {
            codeFile(inFile,outFile);
        }
        catch (const char* str)
        {
            cerr<<"Interception of error:"<<endl;
            cerr<<str<<endl;
            terminate();
        }
        inFile.close();
        outFile.close();
    }
    else if (!strcmp(argv[2],"-d"))
    {
        ifstream inFile2;
        inFile2.open(argv[1],ios::binary);
        if (!inFile2)
        {
            cerr<<"main: InFile2 open error"<<endl;
            return 1;
        }

        ofstream outFile2;
        outFile2.open(argv[3]);
        if (!outFile2)
        {
            cerr<<"main: OutFile2 open error"<<endl;
            return 1;
        }
        try
        {
            decodeFile(inFile2,outFile2);
        }
        catch (const char* str)
        {
            cerr<<"Interception of error:"<<endl;
            cerr<<str<<endl;
            terminate();
        }
        inFile2.close();
        outFile2.close();
    }
    else
    {
        cerr<<"main: Unknown key"<<endl;
        return 1;
    }
    return 0;
}
