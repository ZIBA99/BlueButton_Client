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
    src/views/admin/AdminComplaintsAndImprovementsWidget.cpp \
    src/views/admin/AdminGeneralInquiryManagementWidget.cpp \
    src/views/admin/MainAdmin.cpp \
    src/views/login/MainJoinMember.cpp \
    src/views/login/MainLogin.cpp \
    src/views/user/MainUser.cpp \
    src/views/user/UserEducationCommunicationWidget.cpp \
    src/views/user/UserEducationInfoApplicationWidget.cpp \
    src/views/user/UserGeneralInquiryWidget.cpp \
    src/views/user/UserProductComplaintWidget.cpp \
    src/views/user/UserProductWidget.cpp \
    src/views/user/UserSelfHelpWidget.cpp \
    src/views/CentralManagement.cpp
    # $${VIEWS_SOURCES} \
    # $${MODEL_DIR}/*.cpp \
    # $${MODEL_DIR}/entity/*.cpp \
    # $${MODEL_DIR}/repository/*.cpp \
    # $${MODEL_DIR}/service/*.cpp \
    # $${UTILS_DIR}/*.cpp \
    # $${CONTR_DIR}/*.cpp

HEADERS += \
    src/views/admin/AdminComplaintsAndImprovementsWidget.h \
    src/views/admin/AdminGeneralInquiryManagementWidget.h \
    src/views/admin/MainAdmin.h \
    src/views/login/MainJoinMember.h \
    src/views/login/MainLogin.h \
    src/views/user/MainUser.h \
    src/views/user/UserEducationCommunicationWidget.h \
    src/views/user/UserEducationInfoApplicationWidget.h \
    src/views/user/UserGeneralInquiryWidget.h \
    src/views/user/UserProductComplaintWidget.h \
    src/views/user/UserProductWidget.h \
    src/views/user/UserSelfHelpWidget.h \
    src/views/CentralManagement.h

INCLUDEPATH += \
    $${SRC_DIR} \
    $${VIEWS_DIR} \
    $${VIEWS_DIR}/login \
    $${VIEWS_DIR}/user \
    $${VIEWS_DIR}/admin


FORMS += \
    ui/admin/admin_complain_page.ui \
    ui/admin/admin_general_inquiry_management_widget.ui \
    ui/admin/admin_main_window.ui \
    ui/central_management.ui \
    ui/login/join_member_main_window.ui \
    ui/login/login_main_window.ui \
    ui/user/user_education_communication_widget.ui \
    ui/user/user_education_info_application_widget.ui \
    ui/user/user_general_inquiry_widget.ui \
    ui/user/user_main_window.ui \
    ui/user/user_product_complaint_widget.ui \
    ui/user/user_product_widget.ui \
    ui/user/user_self_help_widget.ui

TRANSLATIONS += \
    $${TR_DIR}/Client_UI_en_US.ts

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
