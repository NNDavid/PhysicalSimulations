QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    doublependulum.cpp \
    doublependulum_solver.cpp \
    drawer.cpp \
    harmonic_oscillation.cpp \
    harmonicoscillator_solver.cpp \
    main.cpp \
    mainmenu.cpp \
    mass_on_spring.cpp \
    oscillating_support_pendulum.cpp \
    oscillatingsupportpendulum_solver.cpp \
    qsfml_doublependulum.cpp \
    qsfml_harmonicoscillation.cpp \
    qsfml_massonspring.cpp \
    qsfml_oscillatingsupportpendulum.cpp \
    qsfmlcanvas.cpp \
    simulationdata.cpp \
    solver.cpp \
    spring.cpp

HEADERS += \
    doublependulum.h \
    doublependulum_solver.h \
    drawer.h \
    harmonic_oscillation.h \
    harmonicoscillator_solver.h \
    mainmenu.h \
    mass_on_spring.h \
    oscillating_support_pendulum.h \
    oscillatingsupportpendulum_solver.h \
    qsfml_doublependulum.h \
    qsfml_harmonicoscillation.h \
    qsfml_massonspring.h \
    qsfml_oscillatingsupportpendulum.h \
    qsfmlcanvas.h \
    simulationdata.h \
    solver.h \
    spring.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -LC:/SFML-2.5.1/lib

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += C:/SFML-2.5.1/include
DEPENDPATH += C:/SFML-2.5.1/include
