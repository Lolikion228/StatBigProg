QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    HistGenParams.cpp \
    PDistGenParams.cpp \
    SetPDistDrawParamsDialog.cpp \
    SetPDistGenParamsDialog.cpp \
    basicview.cpp \
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
    sethistdrawparamsdialog.cpp \
    sethistgenparamsdialog.cpp \
    utils.cpp

HEADERS += \
    HistGenParams.h \
    PDistGenParams.h \
    SetPDistDrawParamsDialog.h \
    SetPDistGenParamsDialog.h \
    basicview.h \
    document.h \
    funcs.h \
    mainwindow.h \
    mod.h \
    mysample.h \
    poisgen.h \
    poisgen1.h \
    poisgen2.h \
    probdist.h \
    sethistdrawparamsdialog.h \
    sethistgenparamsdialog.h \
    utils.h

FORMS += \
    SetPDistDrawParamsDialog.ui \
    SetPDistGenParamsDialog.ui \
    mainwindow.ui \
    sethistdrawparamsdialog.ui \
    sethistgenparamsdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
