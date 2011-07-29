#include "ys_proto/apps/apps.h"
#include "ys_proto/serialization/includeAll.h"

#include <string.h>
//#include <stdio.h>
#include "ys_proto/debug.h"
#include "ys_proto/serialization/unpack.h"
#include <pthread.h>

//TODO: WEATHER

theader Apps::getheadbuffer(char* buffer)
{
    return unpacktheader(buffer);
}

int Apps::receivedmanager(char* buffer, theader headbuffer)
{

    int carryOn = 0;

    switch (headbuffer.kind)
    {
        case 1:
        {
            // Login
            tlogin login;
            unpacktlogin(buffer, headbuffer.size, &login);
            carryOn = alogin(&login);
            break;
        }
        case 4:
        {
            // Map name
            tmap map;
            unpacktmap(buffer, headbuffer.size, &map);
            carryOn = amap(&map);
            break;
        }
        case 5:
        {
//            // ground or player joined
//            debugChar(buffer, headbuffer.size);
//            //debugDec(buffer, headbuffer.size);
//            debugHex(buffer, headbuffer.size);
//            char input[50] = "i,i,i,f,f,f,f,f,f,c64";
//
//            while (input[0]!='n')
//            {
//                display_unpack(input, buffer);
//                if (headbuffer.size == 120)
//                    strcpy(input, "n");
//                else
//                    scanf("%s",input);
//                    //strcpy(input, "i,i,i,f,f,f,f,f,f,c64,i,i,i,f,i,i,c56");
//            }
            tground ground;
            unpacktground(buffer, headbuffer.size, &ground);
            carryOn = aground(&ground);
            break;
        }
        case 11:
        {
            // flight data
            tflight flight;
            //debugHex(buffer, 22);
            //char input[50] = "i,i,s,f,f,f";
//            display_unpack(input, buffer);
            unpacktflight(buffer, headbuffer.size, &flight);
            carryOn = aflight(&flight);
            break;
        }
        case 13:
        {
            // has left the flight
            tleft left;
            unpacktacknowledge(buffer, headbuffer.size, (tacknowledge*)&left);
            carryOn = aleft(&left, 0);
            break;
        }
        case 16:
        {
            // Finnished to send the aircraft list
            carryOn = aendairlist();
            break;
        }
        case 19:
        {
            //ground left
            tleft left;
            unpacktacknowledge(buffer, headbuffer.size, (tacknowledge*)&left);
            carryOn = aleft(&left, 1);
            break;
        }
        case 22:
        {
            // Damages
            //debugHex(buffer, headbuffer.size);
            tdamage damage;
            unpacktdamage(buffer, headbuffer.size, &damage);
            carryOn = adamage(&damage);
            break;
        }
        case 29:
        {
            //YS version
            tint inte;
            unpacktint(buffer, headbuffer.size, &inte);
            carryOn = aysversion(&inte);
            break;
        }
        case 31:
        {
            // Missile option
            tint inte;
            unpacktint(buffer, headbuffer.size, &inte);
            carryOn = amissileOpt(&inte);
            break;
        }
        case 32:
        {
            // Chat message
            tmessage message;
            unpacktmessage(buffer, headbuffer.size, &message);
            carryOn = amessage(&message);
            break;
        }
        case 33:
        {
            // Weather
            tweather weather;
            unpacktweather(buffer, headbuffer.size, &weather);
            carryOn = aweather(&weather);
            break;
        }
        case 36:
        {
            //User list 37 ???
            tuserlist userlist;
            unpacktuserlist(buffer, headbuffer.size, &userlist);
            carryOn = auserlist(&userlist);
            break;
        }
        case 39:
        {
            // Weapon option
            tint inte;
            unpacktint(buffer, headbuffer.size, &inte);
            carryOn = aweaponOpt(&inte);
            break;
        }
        case 41:
        {
            // Show username option
            tint inte;
            unpacktint(buffer, headbuffer.size, &inte);
            carryOn = ashowUserOpt(&inte);
            break;
        }
        case 43:
        {
            // Radar alt and displau users options
            tairDisplayOpt airDisplayOpt;
            unpacktairDisplayOpt(buffer, headbuffer.size, &airDisplayOpt);
            carryOn = aairDisplayOption(&airDisplayOpt);
            break;
        }
        case 44:
        {
            // Aircraft list
            tairList airList;
            unpacktairList(buffer, headbuffer.size, &airList);
            //tairList airList;
            //unpacktairList(buffer, headbuffer.size, &airList);
            carryOn = aairList(&airList);
            break;
        }
        default:
        {
            carryOn = adefault(buffer, headbuffer.size);
            break;
        }
    }
    return carryOn;

}

