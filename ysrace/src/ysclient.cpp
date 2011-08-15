#include "ysclient.h"
#include "ys_proto/serialization/includeAll.h"
//#include "ys_proto/debug.h"
#include "activity_message.h"
//#include "checkpoint_check/readPoly.h"
#include "checkpoint_check/Racer.h"
#include <iostream>

#include <pthread.h>

using namespace std;


YSclient::YSclient(char* checkpoints_file, int laps)
{
     cp   = read_file(checkpoints_file); //manque un new ?
     this->laps = laps;
//     cout << *cp  << std::endl;
//     Racer newracer("Vins", "f-16", 2, cp);
//     cout << "Done!" << endl;
//     cout << newracer << endl;
//     Racer* newracer = new Racer(ground->name2, ground->name, 1, cp);
     //cout << *cp  << std::endl;

}

void YSclient::connect()
{
    int res = s.connects((char *)"127.0.0.1",7915);
    if (res)
    {
        printf("Connected\n");
        tlogin login;
        strcpy(login.username, "ysrace");
        login.YSversion = 20110207;
        s.sendsYS(packtlogin(&login),0);
        pthread_t thread_activity_message;
        pthread_create(&thread_activity_message, NULL, send_activity_message, (void *)&s);

        while (1)
        {
            int size = s.recvsYS();
            if (size<0)
            {
                perror("Failed to receive data.\n");
            }
            else
            {
                int res = receivedmanager(s.buffer, s.head);
                if (!res)
                {
                    printf("Failed to receive\n");
                    break;
                }
            }
            //s.freebuffer();

            //printf("res: %d\n", res);
        }
        int rest = pthread_cancel(thread_activity_message);
        printf("Fin thread %d.", rest);

    }


}


