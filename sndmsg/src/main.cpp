#include <stdio.h>
#include <string.h>


#include "msgclient.h"






int main(int argc, char *argv[])
{

    #ifdef __linux
    printf("sndmsg Linux version\n\n");
    // GCC defines: __linux ; __linux__ ; _gnu_linux__ ; linux ;
    #else
    printf("sndmsg Windows version\n\n");
    // VC++ defines _WIN32
    #endif


// ------------------- Tests ---------------


    if (argc < 3)
    {
        printf("Wrong number of parameters.\n Usage: sndmsg ys-version \"message\"");
        return -1;
    }

    int version = atoi(argv[1]);
    char* message = argv[2];

    MSGclient ysc;
    return ysc.sndmsg(version, message);


    return 1;


}



