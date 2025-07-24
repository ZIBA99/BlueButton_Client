QT       += core gui network

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
    src/controllers/ClientSocket.cpp \
    src/models/entity/Entity.cpp \
    src/models/entity/Product.cpp \
    src/models/service/ProductManager.cpp \
    src/views/admin/AdminMainWindow.cpp \
    src/views/login/JoinMemberMainWindow.cpp \
    src/views/login/LoginMainWindow.cpp \
    src/views/user/DoubleClickButton.cpp \
    src/views/user/ProductWidget.cpp \
    src/views/user/UserMainWindow.cpp
    # $${VIEWS_SOURCES} \
    # $${MODEL_DIR}/*.cpp \
    # $${MODEL_DIR}/entity/*.cpp \
    # $${MODEL_DIR}/repository/*.cpp \
    # $${MODEL_DIR}/service/*.cpp \
    # $${UTILS_DIR}/*.cpp \
    # $${CONTR_DIR}/*.cpp


HEADERS += \
    src/models/entity/Entity.h \
    src/models/entity/Product.h \
    src/models/service/ProductManager.h \
    src/utils/CustomErrorCodes.h \
    src/views/admin/AdminMainWindow.h \
    src/views/login/JoinMemberMainWindow.h \
    src/views/login/LoginMainWindow.h \
    src/controllers/ClientSocket.h \
    src/views/user/DoubleClickButton.h \
    src/views/user/ProductWidget.h \
    src/views/user/UserMainWindow.h


INCLUDEPATH += \
    $${SRC_DIR} \
    $${VIEWS_DIR} \
    $${VIEWS_DIR}/login \
    $${VIEWS_DIR}/user \
    $${VIEWS_DIR}/admin


FORMS += \
    src/views/user/product_widget.ui \
    src/views/admin/admin_main_window.ui \
    src/views/user/user_main_window.ui \
    src/views/login/join_member_main_window.ui \
    src/views/login/login_main_window.ui

TRANSLATIONS += \
    $${TR_DIR}/Client_UI_en_US.ts

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
