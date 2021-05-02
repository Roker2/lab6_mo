TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        CustomException.cpp \
        GaussMethod.cpp \
        Matrix.cpp \
        Resolver.cpp \
        SquareMatrix.cpp \
        main.cpp

HEADERS += \
    Appxomate.h \
    CustomException.h \
    GaussMethod.h \
    Matrix.h \
    Resolver.h \
    SquareMatrix.h
