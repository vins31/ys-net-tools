#ifndef ACTIVITY_MESS
#define ACTIVITY_MESS

#if defined (Win32)
#  include <windows.h>
#  define psleep(sec) Sleep ((sec) * 1000)
#elif defined (__linux)
#  include <unistd.h>
#  define psleep(sec) sleep ((sec))
#endif

void * send_activity_message(void * p_data);

#endif
