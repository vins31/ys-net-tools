#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
//#include <fstream>
//#include <iostream>
//#include <time.h>

#include "ysclient.h"


//active certains outils de debuggage (macros TRACE, etc).
#ifdef _DEBUG
#define DBG_PRINTF(a) printf a
#else
#define DBG_PRINTF(a)
#endif


//#include "tests.h"




int main(int argc, char *argv[])
{

    #ifdef __linux
    printf("Compiling on Linux\n\n");
    // GCC defines: __linux ; __linux__ ; _gnu_linux__ ; linux ;
    #else
    printf("Compiling on Windows\n\n");
    // VC++ defines _WIN32
    #endif


// ------------------- Tests ---------------




    YSclient ysc;
    ysc.connect();


    return 0;


}


