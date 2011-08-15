#include "ysclient.h"
#include "ys_proto/serialization/includeAll.h"

#include "ys_proto/debug.h"
#include <math.h>

#include <time.h>
//#pragma pack(2)

using namespace std;


// IDEA ---------
// ALL PACK FUNCTION IN SERIALIZE  COULD WRITE THE SIZE

int YSclient::alogin(tlogin* login)
{
    printf("Login: %s %d\n",login->username, login->YSversion);
    return 1;
}

int YSclient::amap(tmap* map)
{
    printf("Map: %s\n",map->map);
    //xmlLog->log() << "<map>" << map->map << "</map>" << endl;;
    int res1 = s.sendsYS(packaskweather());
    return s.sendsYS(packtmap(*map)) * res1;
    // put a free...
}

int YSclient::aysversion(tint* inte)
{
    printf("YS version: %d\n", inte->val);
    tacknowledge ack;
    ack.id = 9;
    ack.info = 0;
    return s.sendsYS(packtacknowledge(&ack));
}

int YSclient::amissileOpt(tint* inte)
{
    //printf("Missile option: %d\n", inte->val);
    tacknowledge ack;
    ack.id = 10;
    ack.info = 0;
    return s.sendsYS(packtacknowledge(&ack));
}

int YSclient::aweaponOpt(tint* inte)
{
    //printf("Weapon option: %d\n", inte->val);
    tacknowledge ack;
    ack.id = 11;
    ack.info = 0;
    return s.sendsYS(packtacknowledge(&ack));
}

int YSclient::ashowUserOpt(tint* inte)
{
    //printf("Show user option: %d\n", inte->val);
    //tacknowledge ack;
    //ack.id = 11;
    //return s.sendsYS(packtacknowledge(&ack));
    //FIXME: TO CHANGE
    return 1;
}

int YSclient::aweather(tweather* weather)
{
    //printf("Weather:\n");
    //printf("day: %d\noptions: %d\nvisib: %f\nwind: %f %f %f\n", weather->day, weather->options, weather->visibility, weather->windX, weather->windY, weather->windZ);
    //xmlLog->log() << "<weather day='" << weather->day << "' visibility='" << weather->visibility << "' windX='" << weather->windX << "' windY=" <<  weather->windY << "' windZ='" <<  weather->windZ << "' />" << endl;
    tacknowledge ack;
    ack.id = 4;
    ack.info = 0;
    return s.sendsYS(packtacknowledge(&ack));
}

int YSclient::aendairlist()
{
    tacknowledge ack;
    ack.id = 7;
    ack.info = 0;
    return s.sendsYS(packtacknowledge(&ack));
}

int YSclient::aairList(tairList* airList)
{
    //printf("Nb aircraft %d\n", airList->nbOfAircraft);
    //printsarray(airList->aircraft, airList->nbOfAircraft);
    //BEWARE THE AIRCRAFT LIST DISEAPEAR AFTER THE free(buffer2), EVEN IF WE MAKE A COPY OF THE STRUCT BECAUSE WE USED A POINTER FOR airList.aircraft
    return s.sendsYS(packtairList(airList));
}


int YSclient::aairDisplayOption(tairDisplayOpt* airDisplayOpt)
{
    //printf("Option: %s\n", airDisplayOpt->message);
    return s.sendsYS(packtairDisplayOpt(airDisplayOpt));
}

int YSclient::amessage(tmessage* message)
{
    printf("Message: %s\n", message->message);
    //xmlLog->log() << "<message>" << message->message << "</message>" << endl;
    //xmlLog->flush();
    return 1;
}

int YSclient::aflight(tflight* flight, tflight2* flight2)
{
//    printf("ID: %d x: %f   z: %f   y: %f\n", flight->ID, flight2->x, flight2->z, flight2->y);
     map<int,Racer*>::iterator racer = racers.find(flight->ID);

    if (racer != racers.end())
    {
        if ( (abs(flight2->x) < 100000) && (abs(flight2->z) < 100000) && (abs(flight2->y) < 100000))
        {
            float speed = 0.19438612860586*sqrt(flight2->xSpeed * flight2->xSpeed + flight2->ySpeed * flight2->ySpeed + flight2->zSpeed * flight2->zSpeed);
            int d = racers[flight->ID]->check(flight2->x, flight2->z, flight2->y, speed, time (NULL));
//            cout << newracer->check(flight->x, flight->z, flight->y, speed, time (NULL)) << endl;
            // FIXME: USE TRY/CATCH WITH DICO !!!
            if (d > 0)
            {
                printf ("check %d at time=%d\n", racers[flight->ID]->nextCP(), time(NULL));
                tmessage* mess2 = (tmessage*)malloc(sizeof(*mess2));
                mess2->u = 0;
                mess2->message = (char*)malloc(200);
                sprintf (mess2->message, "%s went trougth gate %d at %.2f kt", racers[flight->ID]->name().c_str(), racers[flight->ID]->nextCP(), speed);
                s.sendsYS(packtmessage(mess2));
                printf ("speed: %fkt  - time: %.0f\n", speed, time(NULL));
                if ( (racers[flight->ID]->nextCP()) == 1 && (speed>200) )
                {
                    tmessage* mess3 = (tmessage*)malloc(sizeof(*mess3));
                    mess3->u = 0;
                    mess3->message = (char*)malloc(200);
                    sprintf (mess3->message, "2s penalty for %s, you had to go below 200kt at the first gate!", racers[flight->ID]->name().c_str());
                    s.sendsYS(packtmessage(mess3));
                    printf("2s penalty!!\n");
                }
            }
            if (d == -1)
            {
                    cout  <<racers[flight->ID]->name() << " missed a check-point !" << endl;
            }
            else if (d == 2)
            {
                cout <<  racers[flight->ID]->name() << " finished the lap " << racers[flight->ID]->lapNumber()-1 << endl;
            }
            else if (d == 3)
            {
                tmessage* mess = (tmessage*)malloc(sizeof(*mess));
                mess->u = 0;
                mess->message = (char*)malloc(300);

                sprintf (mess->message, "%s finished in %.2f s ; Top speed %d kt", racers[flight->ID]->name().c_str(), racers[flight->ID]->time(), racers[flight->ID]->topSpeed());

                s.sendsYS(packtmessage(mess));
                cout << racers[flight->ID]->name() << " finished the race in " <<  racers[flight->ID]->time() << "s ; Top speed: "<< racers[flight->ID]->topSpeed() << "kt" << endl;
            }
            
//            cout << clock() << endl;
        }
    }
    else
    {
        cout << "Unkown pilot" << flight->ID << endl;
    }



    //cout << flight->stopWatch << endl;
    return 1;
}

int YSclient::adamage(tdamage* damage)
{
    printf("DAMAGE: killer: (%d,%d)  victim: (%d,%d) power: %d weapon: %d shot: %d, u1: %d, u2: %d\n", damage->killer, damage->killerID, damage->victim, damage->victimID, damage->power, damage->weapon, damage->shot, damage->u1, damage->u2);
    //xmlLog->log() << "<damage killer_id='" << damage->killer << "' killer_type='" << damage->killerID << "' victim_id='" << damage->victim << "' victim_type='" << damage->victimID << "' power='" << damage->power << "' weapon='" << damage->weapon << "' shot='" << damage->shot << "' />"<<endl;
    return 1;
}

int YSclient::auserlist(tuserlist* userlist)
{
    return 1;
}

int YSclient::aground(tground* ground)
{
    //printf("Join %s %s type: %d iff: %d id:%d gro_id: %d flag: %d u1: %d u2: %f u3: %d u4: %d (x,y,z,r1,r2,r3)=(%f,%f,%f,%f,%f,%f)\n", ground->name2, ground->name, ground->type, ground->iff, ground->id, ground->gro_id, ground->flag, ground->u1, ground->u2, ground->u3, ground->u4, ground->x, ground->y, ground->z, ground->r1, ground->r2, ground->r3);
    tacknowledge ack;
    if (ground->type == 65537)
    {
        //printf("GROUNDJOIN %s %s type: %d iff: %d id:%d gro_id %d\n", ground->name2, ground->name, ground->type, ground->iff, ground->id, ground->gro_id);
        ack.id = 1;
        //debugHex((char*)&ground, 180);
    }
    else
    {
        printf("PLAYERJOIN %s %s type: %d iff: %d id:%d\n", ground->name2, ground->name, ground->type, ground->iff, ground->id);
        ack.id=0;
        racers[ground->id] = new Racer(ground->name2, ground->name, laps, cp);
    }
    ack.info = ground->id;
    return s.sendsYS(packtacknowledge(&ack));
}

int YSclient::aleft(tleft* left, int is_ground=0)
{

    tacknowledge ack;
    if (is_ground)
    {
        ack.id = 3;
        printf("GROUNDLEFT: %d has left %d.\n", left->id, left->u);
        tmessage* mess2 = (tmessage*)malloc(sizeof(*mess2));
        mess2->u = 0;
        mess2->message = (char*)malloc(200);
        sprintf (mess2->message, "Object %d was hit, 2s penalty?", left->id);
        //s.sendsYS(packtmessage(mess2));
        printf("2s penalty for pylon hit!!\n");
        //xmlLog->log() << "<groundLeft id='"<< left->id <<"' />" << endl;
    }
    else
    {
        ack.id = 2;
        printf("PLAYERLEFT: %d has left %d.\n", left->id, left->u);
        //xmlLog->log() << "<pilotLeft id='"<< left->id <<"' />" << endl;
        racers.erase(left->id);
    }
    ack.info = left->id;
    return s.sendsYS(packtacknowledge(&ack));
}

int YSclient::adefault(char* buffer, int size)
{
//    printf("\n ---- Hex ----- \n");
//    debugHex(buffer, size);
//    printf("\n ---- Dec ----- \n");
//    debugDec(buffer, size);
//    printf("\n ---- Char ----- \n");
//    debugChar(buffer, size);
//    printf("\n");
    return 1;
}
