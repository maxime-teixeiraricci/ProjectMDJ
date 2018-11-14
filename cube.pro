QT       += core gui widgets

TARGET = cube
TEMPLATE = app

SOURCES += main.cpp \
    mesh.cpp \
    obj_loader.cpp \
    gameobject.cpp \
    collider.cpp \
    timer_manager.cpp \
    gravity.cpp \
    inputmapping.cpp \
    camera.cpp

SOURCES += \
    mainwidget.cpp \
    geometryengine.cpp

HEADERS += \
    mainwidget.h \
    geometryengine.h \
    mesh.h \
    gameobject.h \
    collider.h \
    timer_manager.h \
    gravity.h \
    inputmapping.h \
    camera.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/cube
INSTALLS += target

DISTFILES += \
    cube.png \
    cube.obj \
    cube.obj \
    cube.obj \
    ../ProjectMDJ/PaletteTest.png
