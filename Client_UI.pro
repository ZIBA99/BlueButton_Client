QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# for root dir sources
TR_DIR = translation
SRC_DIR = src

# for .ui format files
CUI_DIR = ui

# ============================================= for MVC source
MODEL_DIR = $${SRC_DIR}/models
VIEWS_DIR = $${SRC_DIR}/views
CONTR_DIR = $${SRC_DIR}/controllers


SOURCES += \
    src/main.cpp \
    src/views/AdminComplaintsAndImprovementsWidget.cpp \
    src/views/AdminGeneralInquiryManagementWidget.cpp \
    src/views/CentralManagement.cpp \
    src/views/MainAdmin.cpp \
    src/views/MainJoinMember.cpp \
    src/views/MainUser.cpp \
    src/views/MainLogin.cpp \
    src/views/UserEducationCommunicationWidget.cpp \
    src/views/UserEducationInfoApplicationWidget.cpp \
    src/views/UserGeneralInquiryWidget.cpp \
    src/views/UserProductComplaintWidget.cpp \
    src/views/UserProductWidget.cpp \
    src/views/UserSelfHelpWidget.cpp
    # $${VIEWS_SOURCES} \
    # $${MODEL_DIR}/*.cpp \
    # $${MODEL_DIR}/entity/*.cpp \
    # $${MODEL_DIR}/repository/*.cpp \
    # $${MODEL_DIR}/service/*.cpp \
    # $${UTILS_DIR}/*.cpp \
    # $${CONTR_DIR}/*.cpp

HEADERS += \
    src/views/AdminComplaintsAndImprovementsWidget.h \
    src/views/AdminGeneralInquiryManagementWidget.h \
    src/views/CentralManagement.h \
    src/views/MainAdmin.h \
    src/views/MainJoinMember.h \
    src/views/MainLogin.h \
    src/views/MainUser.h \
    src/views/UserEducationCommunicationWidget.h \
    src/views/UserEducationInfoApplicationWidget.h \
    src/views/UserGeneralInquiryWidget.h \
    src/views/UserProductComplaintWidget.h \
    src/views/UserProductWidget.h \
    src/views/UserSelfHelpWidget.h

INCLUDEPATH += \
    $${VIEWS_DIR}


FORMS += \
    ui/centralmanagement.ui \
    ui/admincomplaintsandimprovementswidget.ui \
    ui/admingeneralinquirymanagementwidget.ui \
    ui/usereducationcommunicationwidget.ui \
    ui/usereducationinfoapplicationwidget.ui \
    ui/usergeneralinquirywidget.ui \
    ui/userproductcomplaintwidget.ui \
    ui/userselfhelpwidget.ui \
    ui/userproductwidget.ui \
    ui/main_admin.ui \
    ui/main_joinmember.ui \
    ui/main_login.ui\
    ui/main_user.ui

TRANSLATIONS += \
    $${TR_DIR}/Client_UI_en_US.ts

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
