#define __SCHEDULER_MILLIS_C__

#include "scheduler_millis.h"

void scheduler_milis_atom()
{
    static unsigned long mil_cur = millis();
    static unsigned long mil_pre = mil_cur;
    static uint16_t cnt_for_10msec = 0, cnt_for_100msec = 0, cnt_for_sec = 0;
    mil_cur = millis();

    scheduler_1msec = 0;
    scheduler_10msec = 0;
    scheduler_100msec = 0;
    scheduler_1sec = 0;

    // accounting for rollover(overflow) with subtraction!
    if ((unsigned long)(mil_cur - mil_pre) >= INTERVAL_ATOM)
    {
        uint16_t tocnt  = (unsigned long)(mil_cur - mil_pre) / INTERVAL_ATOM;
        //Serial.printf("xxxxx %u\n", tocnt);
        
        cnt_for_10msec  = cnt_for_10msec + tocnt;
        cnt_for_100msec = cnt_for_100msec + tocnt;
        cnt_for_sec     = cnt_for_sec + tocnt;

        scheduler_1msec = 1;

        if (cnt_for_10msec > ((INTERVAL_10MSEC / INTERVAL_ATOM) - 1))
        {
            scheduler_10msec = 1;
            cnt_for_10msec = 0;
        }

        if (cnt_for_100msec > ((INTERVAL_100MSEC / INTERVAL_ATOM) - 1))
        {
            scheduler_100msec = 1;
            cnt_for_100msec = 0;
        }

        if (cnt_for_sec > ((INTERVAL_1SEC / INTERVAL_ATOM) - 1))
        {
            scheduler_1sec = 1;
            cnt_for_sec = 0;
        }

        mil_pre = mil_cur;
    }
}
