#ifndef EM335X_RTC_H
#define EM335X_RTC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/ioctl.h>
#include <linux/rtc.h>
#include <linux/ioctl.h>

class EM335X_RTC
{
public:
    EM335X_RTC();

    int set_rtc(rtc_time rtc_tm);
    rtc_time get_rtc();

};

#endif // EM335X_RTC_H
