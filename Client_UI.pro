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


# ====================== views
VIEWS_SOURCES += \
    $${VIEWS_DIR}/mainwindow.cpp
    # $${VIEWS_DIR}/test.cpp

VIEWS_HEADERS += \
    $${VIEWS_DIR}/mainwindow.h
    # $${VIEWS_DIR}/test.h

# ====================== models

# MODEL_SOURCES += \
#     $${MODEL_DIR}/*.cpp \
#     $${MODEL_DIR}/entity/*.cpp \
#     $${MODEL_DIR}/repository/*.cpp \
#     $${MODEL_DIR}/service/*.cpp

# MODEL_HEADERS += \
#     $${MODEL_DIR}/*.h \
#     $${MODEL_DIR}/entity/*.h \
#     $${MODEL_DIR}/repository/*.h \
#     $${MODEL_DIR}/service/*.h

# ====================== contorllers
# CONTR_HEADERS += \
#     $${CONTR_DIR}/*.cpp

# CONTR_SOURCES += \
#     $${CONTR_DIR}/*.cpp


# ============================================= for utils source
# UTILS_DIR = $${SRC_DIR}/utils

# UTILS_SOURCES += \
#     $${UTILS_DIR}/*.cpp

# UTILS_HEADERS += \
#     $${UTILS_DIR}/*.h

# ============================================= add all sources

SOURCES += \
    $${SRC_DIR}/main.cpp \
    $${VIEWS_SOURCES}
    # $${MODEL_DIR}/*.cpp \
    # $${MODEL_DIR}/entity/*.cpp \
    # $${MODEL_DIR}/repository/*.cpp \
    # $${MODEL_DIR}/service/*.cpp \
    # $${UTILS_DIR}/*.cpp \
    # $${CONTR_DIR}/*.cpp

HEADERS += \
    $${VIEWS_HEADERS}

INCLUDEPATH += \
    $${VIEWS_DIR}


FORMS += \
    $${CUI_DIR}/mainwindow.ui

TRANSLATIONS += \
    $${TR_DIR}/Client_UI_en_US.ts

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
