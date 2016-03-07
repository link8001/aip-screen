/*******************************************************************************
 * Copyright (c) 2015,青岛艾普智能仪器有限公司
 * All rights reserved.
 *
 * version:     1.0
 * author:      link
 * date:        2015.11.10
 * brief:       RTC功能
*******************************************************************************/
#include "em335x_rtc.h"

EM335X_RTC::EM335X_RTC()
{

}
/******************************************************************************
  * version:    1.0
  * author:     link
  * date:       2015.11.10
  * brief:      设置系统时间
******************************************************************************/
int EM335X_RTC::set_rtc(rtc_time rtc_tm)
{
    int 				ret;
    int  				rtc_fd;
    time_t 				t1;

    rtc_tm.tm_year -= 1900;                     //年从1900开始
    rtc_tm.tm_mon -= 1;                         //月从0开始


    rtc_fd = open("/dev/rtc0", O_RDWR, 0);      //打开RTC
    if (rtc_fd == -1)
    {
        printf("/dev/rtc0 open error\n");
        return -1;
    }

    t1 = timelocal( (tm*)&rtc_tm );             //设置系统时间
    stime( &t1 );


    ret = ioctl(rtc_fd, RTC_SET_TIME, &rtc_tm); //设置RCT时间
    if (ret == -1)
    {
        printf("rtc ioctl RTC_SET_TIME error\r\n");
        return -1;
    }

    close(rtc_fd);                              //关闭RTC

    return 0;
}
/******************************************************************************
  * version:    1.0
  * author:     link
  * date:       2015.11.10
  * brief:      获取系统时间
******************************************************************************/
rtc_time EM335X_RTC::get_rtc()
{
    int 				ret;
    struct rtc_time 	rtc_tm;
    int  				rtc_fd;


    rtc_fd = open("/dev/rtc0", O_RDWR, 0);      //打开RTC
    if (rtc_fd == -1)
    {
        printf("/dev/rtc0 open error\n");
    }

    ret = ioctl(rtc_fd, RTC_RD_TIME, &rtc_tm);  //读取时间
    if(ret < 0)
    {
        printf("RTC_RD_TIME failed %d", ret);
    }

    rtc_tm.tm_year += 1900;                     //年从1900开始
    rtc_tm.tm_mon += 1;                         //月从１开始

    close(rtc_fd);                              //关闭RTC

    return rtc_tm;
}
/******************************************************************************
                                    END
******************************************************************************/
