TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Calculator/Calculator.cpp \
        Calculator/Func.cpp \
        Calculator/Property.cpp \
        Calculator/Translator.cpp \
        CustomException.cpp \
        GaussMethod.cpp \
        Matrix.cpp \
        main.cpp

HEADERS += \
    Appxomate.h \
    Calculator/Calculator.h \
    Calculator/Func.h \
    Calculator/Priority.h \
    Calculator/Property.h \
    Calculator/Translator.h \
    CustomException.h \
    GaussMethod.h \
    Matrix.h
