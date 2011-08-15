#include "ysclient.h"
#include "checkpoint_check/readPoly.h"
#include "checkpoint_check/Racer.h"
#include <iostream>
#include <string.h>
using namespace std;

int main(int argc, char *argv[])
{
    CheckPoints* cp = read_file((char*)"cp1.txt");
//    cout << *cp << endl;


    Racer racer("Vins", "f-16", 2, cp);


    if (argc < 3)
    {
        printf("Wrong number of parameters.\n Usage: ysrace CHECKPOINTS_FILE.race NUMBER_OF_LAPS");
        return -1;
    }

    YSclient ysc(argv[1], atoi(argv[2]));
    ysc.connect();


    return 0;


}


