QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ./controller/controller.cc \
    main.cpp \
    ./model/model.cc \
    ./views/mywindow.cc \
    ./parser/objectsparser.cc \
    ./store/sqlitestore.cc

HEADERS += \
    ./controller/controller.h \
    ./model/model.h \
    ./views/mywindow.h \
    ./parser/objectsparser.h \
    ./parser/parser.h \
    ./store/sqlitestore.h \
    ./store/store.h \
    ./model/types.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
