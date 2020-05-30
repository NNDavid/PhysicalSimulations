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
    doublependulum/doublependulum.cpp \
    doublependulum/doublependulum_solver.cpp \
    harmonicoscillator/harmonic_oscillation.cpp \
    harmonicoscillator/harmonicoscillator_solver.cpp \
    main.cpp \
    mainmenu.cpp \
    massonspring/mass_on_spring.cpp \
    massonspring/massonspring_solver.cpp \
    oscillatingsupportpendulum/oscillating_support_pendulum.cpp \
    oscillatingsupportpendulum/oscillatingsupportpendulum_solver.cpp \
    doublependulum/qsfml_doublependulum.cpp \
    harmonicoscillator/qsfml_harmonicoscillation.cpp \
    massonspring/qsfml_massonspring.cpp \
    oscillatingsupportpendulum/qsfml_oscillatingsupportpendulum.cpp \
    qsfmlcanvas.cpp \
    simulationdata.cpp \
    spring.cpp

HEADERS += \
    doublependulum/doublependulum.h \
    doublependulum/doublependulum_solver.h \
    drawer.h \
    harmonicoscillator/harmonic_oscillation.h \
    harmonicoscillator/harmonicoscillator_solver.h \
    mainmenu.h \
    massonspring/mass_on_spring.h \
    massonspring/massonspring_solver.h \
    oscillatingsupportpendulum/oscillating_support_pendulum.h \
    oscillatingsupportpendulum/oscillatingsupportpendulum_solver.h \
    doublependulum/qsfml_doublependulum.h \
    harmonicoscillator/qsfml_harmonicoscillation.h \
    massonspring/qsfml_massonspring.h \
    oscillatingsupportpendulum//qsfml_oscillatingsupportpendulum.h \
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
