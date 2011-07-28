#include "ys_proto/output/xmlLog.h"

using namespace std;

XmlLog::XmlLog()
{
    file.open("log.xml", ios::out | ios::app);
    if (!file.is_open())
    {
        cerr << "failed to open the file" << endl;
    }
}

void XmlLog::close()
{
    file.close();
}

void XmlLog::flush()
{
    file.flush();
}

ostream &XmlLog::log()
{
    return file;
}



