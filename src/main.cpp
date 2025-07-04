#include "MainJoinMember.h"
#include "MainLogin.h"
#include "MainUser.h"
#include "MainAdmin.h"
#include "UserProductWidget.h"
#include "UserEducationInfoApplicationWidget.h"
#include "UserEducationCommunicationWidget.h"
#include "UserSelfHelpWidget.h"
#include "UserProductComplaintWidget.h"
#include "CentralManagement.h"
#include "AdminComplaintsAndImprovementsWidget.h"
#include "AdminGeneralInquiryManagementWidget.h"

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

    //아래는 Layout
    MainLogin l;  // mainwindow.h에 정의된 클래스
    MainUser u;   // mainuser.h에 정의된 클래스
    MainAdmin ad;
    MainJoinMember j;

    //User Widgets
    UserProductWidget userP;
    UserEducationInfoApplicationWidget userEIA;
    UserEducationCommunicationWidget userEC;
    UserSelfHelpWidget userSH;
    UserProductComplaintWidget userPC;

    //Admin Widgets
    CentralManagement AdminCM;
    AdminComplaintsAndImprovementsWidget AdminCI;
    AdminGeneralInquiryManagementWidget AdminGIM;

    //아래는 Layout
    l.show();
    u.show();
    ad.show();
    j.show();

    //User Widgets
    userP.show();
    userEIA.show();
    userEC.show();
    userSH.show();
    userPC.show();

    //Admin Widgets
    AdminCM.show();
    AdminCI.show();
    AdminGIM.show();

    return a.exec();
}
