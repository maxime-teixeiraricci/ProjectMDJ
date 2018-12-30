QT       += core gui widgets opengl

TARGET = cube
TEMPLATE = app


SOURCES += main.cpp \
    mesh.cpp \
    gameobject.cpp \
    collider.cpp \
    timer_manager.cpp \
    inputmapping.cpp \
    camera.cpp \
    transform.cpp \
    component.cpp \
    playercomponent.cpp \
    mapmaker.cpp \
    gravitycomponent.cpp \
    boxcollidercomponent.cpp \
    collidercomponent.cpp \
    rotationcomponent.cpp \
    starcollectcomponent.cpp \
    switchcomponent.cpp \
    colorblockcomponent.cpp

SOURCES += \
    mainwidget.cpp

HEADERS += \
    mainwidget.h \
    mesh.h \
    gameobject.h \
    collider.h \
    timer_manager.h \
    inputmapping.h \
    camera.h \
    transform.h \
    component.h \
    playercomponent.h \
    mapmaker.h \
    gravitycomponent.h \
    boxcollidercomponent.h \
    collidercomponent.h \
    rotationcomponent.h \
    starcollectcomponent.h \
    switchcomponent.h \
    colorblockcomponent.h

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
