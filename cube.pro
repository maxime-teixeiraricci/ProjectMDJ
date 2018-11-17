QT       += core gui widgets

TARGET = cube
TEMPLATE = app

SOURCES += main.cpp \
    mesh.cpp \
    gameobject.cpp \
    collider.cpp \
    timer_manager.cpp \
    gravity.cpp \
    inputmapping.cpp \
    camera.cpp \
    transform.cpp

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
    camera.h \
    transform.h

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
    ../ProjectMDJ/PaletteTest.png \
    cube.obj \
    skybox.obj \
    slope.obj \
    sphere.obj \
    Stage1.obj \
    SuzaneLOD0.obj \
    SuzaneLOD1.obj \
    SuzaneLOD2.obj \
    SuzaneLOD3.obj \
    SuzaneLOD4.obj
