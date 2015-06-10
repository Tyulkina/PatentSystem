#include "./header/patentsystem.h"

#include <QtGui>
#include <QApplication>
#include <QSplashScreen>
#include <QPixmap>
#include <QTimer>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

   // QSplashScreen splash (QPixmap("icons/Splash.png"));
  //  splash.show();
    PatentSystem w;
   // w.setWindowIcon(QIcon(QDir::currentPath() + "/Bulldog.ico"));
  //  QTimer::singleShot(1000,&splash,SLOT(close()));
   // QTimer::singleShot(1000,&w,SLOT(show()));
    w.show();
    return a.exec();
}
