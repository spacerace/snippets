#define __USE_SYSTICK_AS_CLOCKSOURCE__
//#define __USE_RTC_AS_CLOCKSOURCE__
//#define __USE_TIMER_AS_CLOCKSOURCE__

#ifdef __USE_SYSTICK_AS_CLOCKSOURCE__
#warning using systick as a clocksource is a bad idea, it is highly recommended to use either the RTC or a  different timer! 
#endif

#ifdef __USE_RTC_AS_CLOCKSOURCE__
#error NOT IMPLEMENTED YET
#endif

#ifdef __USE_TIMER_AS_CLOCKSOURCE__
#warning why not using your RTC for a clock?
#error NOT IMPLEMENTED YET
#endif

#include "stm32f10x.h"
#include "clock.h"

static void clock_increment_day();

static volatile struct clock_data {
        uint32_t uptime;
        uint32_t ticks_per_sec;
        uint32_t unix_timestamp;
        int h;
        int m;
        int s;
        int ms;
        int day;
        int month;
        int year;
} clock;

void reset_clock() {
        /* unix timestamp begins with "epoch". epoch is defined to be 1.1.1970 00:00:00 UTC */
        clock.ticks_per_sec = 1000;
        clock.unix_timestamp = 0;
        clock.h = 0;
        clock.m = 0;
        clock.s = 0;
        clock.ms = 0;
        clock.day = 1;
        clock.month = 1;
        clock.year = 1970;
        
        clock.uptime = 0;
        return;
}

void init_clock() {
        reset_clock();
       
        return;
}

uint32_t _clock() {
        return clock.uptime;
}

uint32_t get_unixtime() {
        return clock.unix_timestamp;
}

void get_time(int *h, int *m, int*s, int *ms) {
        *h = clock.h;
        *m = clock.m;
        *s = clock.s;
        *ms = clock.ms;
        
        return;
}

void handle_clock_tick() {
        clock.uptime++;
        clock.ms++;
        if(clock.ms >= 1000) {
                clock.ms = 0;
                clock.s++;
                if(clock.s >= 60) {
                        clock.s = 0;
                        clock.m++;
                        if(clock.m >= 60) {
                                clock.m = 0;
                                clock.h++;
                                if(clock.h >= 24) {
                                        clock.h = 0;
                                        clock_increment_day();
                                }
                        }
                }
        }
}

/* here we could do some date calculation */ 
static void clock_increment_day() {
        return;
}


// ???
