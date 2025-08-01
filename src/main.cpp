#include "JoinMemberMainWindow.h"
#include "LoginMainWindow.h"
#include "UserMainWindow.h"
// #include "AdminMainWindow.h"


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

    // //아래는 Layout
    // LoginMainWindow l;  // mainwindow.h에 정의된 클래스
    UserMainWindow u;   // mainuser.h에 정의된 클래스
    // AdminMainWindow ad;


    // //아래는 Layout
    // l.show();
    u.show();
    // ad.show();
    // j.show();

    // //User Widgets
    // userP.show();
    // userEIA.show();
    // userEC.show();
    // userSH.show();
    // userPC.show();

    // //Admin Widgets
    // AdminCM.show();
    // AdminCI.show();
    // AdminGIM.show();

    return a.exec();
}
