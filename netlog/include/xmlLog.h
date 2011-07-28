#ifndef XMLLOG
#define XMLLOG


#include <iostream>
#include <fstream>

#include "ys_proto/types/ys/includeAll.h"

using namespace std;

class XmlLog
{
    private:
        ofstream file;
    public:
        XmlLog();
        void close();
        ostream &log();
        void flush();
};
#endif
