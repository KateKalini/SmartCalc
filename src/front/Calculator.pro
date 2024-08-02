QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    MainWindow.cpp \
    main.cpp \
    ../back/s21_calculate.c \
    ../back/s21_stack.c \
    ../back/s21_credit_calc.c \
    ../back/s21_debit_calc.c \
    qcustomplot.cpp

HEADERS += \
    ../back/s21_stack.h \
    ../back/s21_calculate.h \
    ../back/s21_credit_calc.h \
    ../back/s21_debit_calc.h \
    MainWindow.h \
    qcustomplot.h

FORMS += \
    MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
