#ifndef __SCHEDULER_MILLIS_H__
#define __SCHEDULER_MILLIS_H__

#include "arduino_common_define.h"

#define INTERVAL_1MSEC (1)
#define INTERVAL_10MSEC (10)
#define INTERVAL_100MSEC (100)
#define INTERVAL_1SEC (1000)
#define INTERVAL_ATOM INTERVAL_1MSEC

#ifdef __SCHEDULER_MILLIS_C__
uint8_t scheduler_1msec, scheduler_10msec, scheduler_100msec, scheduler_1sec;
#else
extern uint8_t scheduler_1msec, scheduler_10msec, scheduler_100msec, scheduler_1sec;
#endif

void scheduler_milis_atom();

#endif /* __SCHEDULER_MILLIS_H__ */
