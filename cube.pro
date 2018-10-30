QT       += core gui widgets

TARGET = cube
TEMPLATE = app

SOURCES += main.cpp \
    mesh.cpp \
    obj_loader.cpp \
    gameobject.cpp \
    scenegraph.cpp \
    collider.cpp

SOURCES += \
    mainwidget.cpp \
    geometryengine.cpp

HEADERS += \
    mainwidget.h \
    geometryengine.h \
    mesh.h \
    gameobject.h \
    scenegraph.h \
    collider.h

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
