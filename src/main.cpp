#include "MainJoinMember.h"
#include "MainLogin.h"
#include "MainUser.h"
#include "MainAdmin.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Client_UI_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainLogin l;  // mainwindow.h에 정의된 클래스
    //MainUser u;   // mainuser.h에 정의된 클래스
    //MainAdmin ad;
    //MainJoinMember j;
    l.show();
    //u.show();
    //ad.show();
    //j.show();

    return a.exec();
}
