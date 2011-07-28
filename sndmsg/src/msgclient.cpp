#include "msgclient.h"
#include "ys_proto/serialization/includeAll.h"

using namespace std;

MSGclient::MSGclient()
{

}

int MSGclient::sndmsg(int version, char* message)
{
    int res = s.connects((char *)"127.0.0.1",7915);

    if (res)
    {
        printf("Connected\n");
        tlogin login;
        strcpy(login.username, "sndmsg");
        login.YSversion = version;
        s.sendsYS(packtlogin(&login),0);

        tmessage* mess = (tmessage*)malloc(sizeof(*mess));
        mess->u = 0;
        mess->message = message;
        s.sendsYS(packtmessage(mess));
    }
    return 1;

}


int MSGclient::alogin(tlogin* login)
{
    return 1;
}

int MSGclient::amap(tmap* map)
{
    return 1;
}

int MSGclient::aysversion(tint* inte)
{
    printf("YS version: %d\n", inte->val);
    tacknowledge ack;
    ack.id = 9;
    ack.info = 0;
    return s.sendsYS(packtacknowledge(&ack));
}

int MSGclient::amissileOpt(tint* inte)
{
    return 1;
}

int MSGclient::aweaponOpt(tint* inte)
{
    return 1;
}

int MSGclient::ashowUserOpt(tint* inte)
{
    return 1;
}

int MSGclient::aweather(tweather* weather)
{
    return 1;
}

int MSGclient::aendairlist()
{
    return 1;
}

int MSGclient::aairList(tairList* airList)
{
    return 1;
}


int MSGclient::aairDisplayOption(tairDisplayOpt* airDisplayOpt)
{
    return 1;
}

int MSGclient::amessage(tmessage* message)
{
    return 1;
}

int MSGclient::aflight(tflight* flight)
{
    return 1;
}

int MSGclient::adamage(tdamage* damage)
{
    return 1;
}

int MSGclient::auserlist(tuserlist* userlist)
{
    return 1;
}

int MSGclient::aground(tground* ground)
{
    return 1;
}

int MSGclient::aleft(tleft* left, int is_ground=0)
{
    return 1;
}

int MSGclient::adefault(char* buffer, int size)
{
    return 1;
}


