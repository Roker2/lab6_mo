TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Calculator/Calculator.cpp \
        Calculator/DerivativeCalculator.cpp \
        Calculator/Func.cpp \
        Calculator/Priority.cpp \
        Calculator/Tests.cpp \
        Calculator/Token.cpp \
        Calculator/Translator.cpp \
        CustomException.cpp \
        GaussMethod.cpp \
        Matrix.cpp \
        Resolver.cpp \
        SquareMatrix.cpp \
        main.cpp

HEADERS += \
    Appxomate.h \
    Calculator/Calculator.h \
    Calculator/DerivativeCalculator.h \
    Calculator/Func.h \
    Calculator/Priority.h \
    Calculator/Property.h \
    Calculator/Tests.h \
    Calculator/Token.h \
    Calculator/TokenType.h \
    Calculator/Translator.h \
    Calculator/global.h \
    CustomException.h \
    GaussMethod.h \
    Matrix.h \
    Resolver.h \
    SquareMatrix.h
