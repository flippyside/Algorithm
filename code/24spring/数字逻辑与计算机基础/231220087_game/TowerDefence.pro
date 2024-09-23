QT       += core gui concurrent
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QT += multimedia

SOURCES += \
    Basic/enemy.cpp \
    Basic/globalattribute.cpp \
    Basic/role.cpp \
    Basic/scenemap.cpp \
    Basic/tower.cpp \
    Render/Settlement.cpp \
    Render/inputmanager.cpp \
    Render/menu.cpp \
    Render/render.cpp \
    Render/stageselect.cpp \
    Render/tdgame.cpp \
    Tool/Special.cpp \
    Tool/affix.cpp \
    Tool/archive.cpp \
    Tool/bullet.cpp \
    Tool/enemywave.cpp \
    Tool/fightSystem.cpp \
    Tool/healthsystem.cpp \
    game.cpp \
    main.cpp \
    mainscene.cpp \
    mainwindow.cpp \
    maps.cpp \
    pause.cpp

HEADERS += \
    Basic/Json/null.h \
    Basic/enemy.h \
    Basic/globalattribute.h \
    Basic/role.h \
    Basic/scenemap.h \
    Basic/tower.h \
    Render/Settlement.h \
    Render/inputmanager.h \
    Render/menu.h \
    Render/render.h \
    Render/stageselect.h \
    Render/tdgame.h \
    Tool/Special.h \
    Tool/affix.h \
    Tool/archive.h \
    Tool/bullet.h \
    Tool/enemywave.h \
    Tool/fightSystem.h \
    Tool/healthsystem.h \
    Tool/template.h \
    game.h \
    mainscene.h \
    mainwindow.h \
    maps.h \
    pause.h

FORMS += \
    mainwindow.ui

RESOURCES += resources.qrc \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    res/background/map1.jpeg \
    res/background/map88.png \
    res/enemy/pinkocto.png \
    res/path/path_stone.jpg \
    res/path/rt1.png \
    res/path/rt2.jpg \
    res/tower/omori.png


