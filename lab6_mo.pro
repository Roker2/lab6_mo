TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Calculator/Calculator.cpp \
        Calculator/DerivativeCalculator.cpp \
        Calculator/Func.cpp \
        Calculator/FuncFragmentator.cpp \
        Calculator/Priority.cpp \
        Calculator/Tests.cpp \
        Calculator/Token.cpp \
        Calculator/Translator.cpp \
        CustomException.cpp \
        GaussMethod.cpp \
        Matrix.cpp \
        Resolver.cpp \
        SimplexMethod/SimplexMethod.cpp \
        SimplexMethod/StepFive.cpp \
        SimplexMethod/StepFour.cpp \
        SimplexMethod/StepOne.cpp \
        SimplexMethod/StepSix.cpp \
        SimplexMethod/StepThree.cpp \
        SquareMatrix.cpp \
        main.cpp

HEADERS += \
    Approximate.h \
    Calculator/Calculator.h \
    Calculator/DerivativeCalculator.h \
    Calculator/Func.h \
    Calculator/FuncFragmentator.h \
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
    SimplexMethod/SimplexMethod.h \
    SimplexMethod/StepFive.h \
    SimplexMethod/StepFour.h \
    SimplexMethod/StepOne.h \
    SimplexMethod/StepSix.h \
    SimplexMethod/StepThree.h \
    SquareMatrix.h
