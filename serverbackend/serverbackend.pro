QT -= gui
QT += network
QT += sql

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        adminclass.cpp \
        databasesclass.cpp \
        main.cpp\
        myserver.cpp\
        myclient.cpp\
        mytask.cpp \
        shopactivityclass.cpp \
        validateuser.cpp
HEADERS += \
        adminclass.h \
        databasesclass.h \
        myserver.h\
        myclient.h\
        mytask.h \
        shopactivityclass.h \
        validateuser.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
