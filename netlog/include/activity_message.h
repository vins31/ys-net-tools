#ifndef ACTIVITY_MESS
#define ACTIVITY_MESS

#if defined (__linux)
#  include <unistd.h>
#  define psleep(sec) sleep ((sec))
#else
#  include <windows.h>
#  define psleep(sec) Sleep ((sec) * 1000)    
#endif

void * send_activity_message(void * p_data);

#endif
