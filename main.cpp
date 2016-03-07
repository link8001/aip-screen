#include <QApplication>
#include <QString>
#include <QPixmap>
#include <QDesktopWidget>
#include <QWSServer>
#include <em335x_rtc.h>

#define DEFAULT_NAME "/mnt/nfs/screenshot.PNG"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWSServer::setCursorVisible(false);//隐藏鼠标

    EM335X_RTC rtc;
    rtc_time t;
    char str[30];
    t = rtc.get_rtc();

    sprintf(str,"/mnt/nfs/%d%02d%02d%02d%02d%02d.png",t.tm_year,t.tm_mon,t.tm_mday,t.tm_hour,t.tm_min,t.tm_sec);
    QString fileName = str;
    if (argc > 1)
        fileName = argv[1];

    QPixmap scrPic = QPixmap::grabWindow(QApplication::desktop()->winId());
    bool ret = scrPic.save(fileName, "png");

    if (ret)
        qDebug("Screenshot is saved to: %s", fileName.toLatin1().data());
    else
        qCritical("Failed to save file: %s", fileName.toLatin1().data());

    return 0;
}

