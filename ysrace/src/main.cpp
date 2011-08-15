#include "ysclient.h"
#include "checkpoint_check/readPoly.h"
#include "checkpoint_check/Racer.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    CheckPoints* cp = read_file((char*)"cp1.txt");
//    cout << *cp << endl;


    Racer racer("Vins", "f-16", 2, cp);

    if (argc < 2)
    {
        printf("Wrong number of parameters.\n Usage: ysrace CHECKPOINTS_FILE.race");
        return -1;
    }

    YSclient ysc(argv[1]);
    ysc.connect();


    return 0;


}


