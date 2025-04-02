QT       += core gui \
    quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

 QT += multimedia

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gamewidget.cpp \
    levelselect.cpp \
    main.cpp \
    mainmenu.cpp



HEADERS += \
    gamewidget.h \
    levelselect.h \
    mainmenu.h



FORMS += \
    levelselect.ui \
    mainmenu.ui



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    zhuyebeijing.qrc \

