QT       += core gui network sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    login.cpp\
    mysockets.cpp\
    accountant.cpp\
    database.cpp\
    exepediture.cpp\
    soldcheckpage.cpp\
    stockwindow.cpp\
    report.cpp\
    search.cpp\
    settings.cpp


HEADERS += \
    login.h\
    mysockets.h\
    accountant.h\
    database.h\
    exepediture.h\
    soldcheckpage.h\
    stockwindow.h\
    report.h\
    search.h\
    settings.h

FORMS += \
    login.ui\
    accountant.ui\
    exepediture.ui\
    soldcheckpage.ui\
    stockwindow.ui\
    report.ui\
    search.ui\
    settings.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
