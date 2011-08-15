#ifndef YSCLIENT
#define YSCLIENT

#include <map>
#include <iostream>

#include "ys_proto/sockets/socketYS.h"

//#include "ys_proto/apps/apps.h"  // and so:
#include "ys_proto/types/includeAll.h"

#include "checkpoint_check/Vec.h"
#include "checkpoint_check/readPoly.h"
#include "checkpoint_check/Racer.h"

class YSclient //: public Apps
{
    public:
        YSclient(char* checkpoints_file);
        void connect();

    protected:
        Racer* newracer;
        CheckPoints* cp;
        map<int, Racer*> racers;

        theader getheadbuffer(char* buffer);
        int receivedmanager(char* buffer, theader headbuffer);

    private:
        SocketYS s;
        int alogin(tlogin* login);
        int amap(tmap* map);
        int aysversion(tint* inte);
        int amissileOpt(tint* inte);
        int aweaponOpt(tint* inte);
        int ashowUserOpt(tint* inte);
        int aweather(tweather* weather);
        int aendairlist();
        int aairList(tairList* airList);
        int aairDisplayOption(tairDisplayOpt* airDisplayOpt);
        int amessage(tmessage* message);
        int aflight(tflight* flight, tflight2* flight2);
        int adamage(tdamage* damage);
        int auserlist(tuserlist* userlist);
        int aground(tground* ground);
        int aleft(tleft* left, int is_ground);
        int adefault(char* buffer, int size);
};
#endif
