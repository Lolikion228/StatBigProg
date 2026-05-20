QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DrawTimeDialog.cpp \
    DrawTimeParams.cpp \
    HistGenParams.cpp \
    PDistGenParams.cpp \
    SetHistDrawParamsDialog.cpp \
    SetHistGenParamsDialog.cpp \
    SetPDistDrawParamsDialog.cpp \
    SetPDistGenParamsDialog.cpp \
    basicview.cpp \
    chisq.cpp \
    distribution.cpp \
    document.cpp \
    funcs.cpp \
    main.cpp \
    mainwindow.cpp \
    mod.cpp \
    mysample.cpp \
    poisgen.cpp \
    poisgen1.cpp \
    poisgen2.cpp \
    probdist.cpp \
    utils.cpp

HEADERS += \
    DrawTimeDialog.h \
    DrawTimeParams.h \
    HistGenParams.h \
    PDistGenParams.h \
    SetHistDrawParamsDialog.h \
    SetHistGenParamsDialog.h \
    SetPDistDrawParamsDialog.h \
    SetPDistGenParamsDialog.h \
    basicview.h \
    chisq.h \
    distribution.h \
    document.h \
    funcs.h \
    mainwindow.h \
    mod.h \
    mysample.h \
    poisgen.h \
    poisgen1.h \
    poisgen2.h \
    probdist.h \
    utils.h

FORMS += \
    DrawTimeDialog.ui \
    SetHistDrawParamsDialog.ui \
    SetHistGenParamsDialog.ui \
    SetPDistDrawParamsDialog.ui \
    SetPDistGenParamsDialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
