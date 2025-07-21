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
    src/views/admin/AdminComplaintPage.cpp \
    src/views/admin/AdminDefaultPage.cpp \
    src/views/admin/AdminInquiryPage.cpp \
    src/views/admin/AdminMainWindow.cpp \
    src/views/login/JoinMemberMainWindow.cpp \
    src/views/login/LoginMainWindow.cpp \
    src/views/user/UserEducationChatPage.cpp \
    src/views/user/UserEducationMainPage.cpp \
    src/views/user/UserInquiryPage.cpp \
    src/views/user/UserMainWindow.cpp \
    src/views/user/UserProductComplaintPage.cpp \
    src/views/user/UserProductPage.cpp \
    src/views/CentralManagement.cpp \
    src/views/user/UserSelfHelpPage.cpp \
    src/views/user/UserDefaultPage.cpp \
    src/views/admin/AminEuducationChatPage.cpp \
    src/contollers/ClientSocket.cpp
    # $${VIEWS_SOURCES} \
    # $${MODEL_DIR}/*.cpp \
    # $${MODEL_DIR}/entity/*.cpp \
    # $${MODEL_DIR}/repository/*.cpp \
    # $${MODEL_DIR}/service/*.cpp \
    # $${UTILS_DIR}/*.cpp \
    # $${CONTR_DIR}/*.cpp


HEADERS += \
    src/views/user/UserDefaultPage.h \
    src/views/admin/AdminComplaintPage.h \
    src/views/admin/AdminDefaultPage.h \
    src/views/admin/AdminInquiryPage.h \
    src/views/admin/AdminMainWindow.h \
    src/views/login/JoinMemberMainWindow.h \
    src/views/login/LoginMainWindow.h \
    src/views/user/UserEducationChatPage.h \
    src/views/user/UserEducationMainPage.h \
    src/views/user/UserInquiryPage.h \
    src/views/user/UserMainWindow.h \
    src/views/user/UserProductComplaintPage.h \
    src/views/user/UserProductPage.h \
    src/views/CentralManagement.h \
    src/views/user/UserSelfHelpPage.h \
    src/views/admin/AminEuducationChatPage.h \
    src/contollers/ClientSocket.h


INCLUDEPATH += \
    $${SRC_DIR} \
    $${VIEWS_DIR} \
    $${VIEWS_DIR}/login \
    $${VIEWS_DIR}/user \
    $${VIEWS_DIR}/admin


FORMS += \
    ui/admin/amin_euducation_chat_page.ui \
    ui/user/user_default_page.ui \
    ui/admin/admin_default_page.ui \
    ui/admin/admin_complaint_page.ui \
    ui/admin/admin_inquiry_page.ui \
    ui/admin/admin_main_window.ui \
    ui/central_management.ui \
    ui/login/join_member_main_window.ui \
    ui/login/login_main_window.ui \
    ui/user/user_education_chat_page.ui \
    ui/user/user_education_main_page.ui \
    ui/user/user_general_inquiry_page.ui \
    ui/user/user_main_window.ui \
    ui/user/user_product_complaint_page.ui \
    ui/user/user_product_page.ui \
    ui/user/user_self_help_page.ui

TRANSLATIONS += \
    $${TR_DIR}/Client_UI_en_US.ts

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
