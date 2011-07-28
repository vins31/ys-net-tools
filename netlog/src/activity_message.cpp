#include "ys_proto/apps/activity_message.h"
#include "ys_proto/serialization/header.h"
#include "ys_proto/sockets/socketYS.h"


void * send_activity_message(void * p_data)
{
    SocketYS* s = (SocketYS*) p_data;
    char buffer[8];
    packtheader(4,17, buffer);
    while (1)
    {
        psleep (30);
        s->sends(buffer, 8);
    }

    return NULL;
}
