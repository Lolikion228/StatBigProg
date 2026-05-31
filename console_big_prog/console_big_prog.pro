TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        ../big_prog/chisq.cpp \
        ../big_prog/distribution.cpp \
        ../big_prog/mod.cpp \
        ../big_prog/poisgen.cpp \
        ../big_prog/poisgen1.cpp \
        ../big_prog/poisgen2.cpp \
        ../big_prog/probdist.cpp \

HEADERS += \
        ../big_prog/chisq.h \
        ../big_prog/distribution.h \
        ../big_prog/mod.h \
        ../big_prog/poisgen.h \
        ../big_prog/poisgen1.h \
        ../big_prog/poisgen2.h \
        ../big_prog/probdist.h \

