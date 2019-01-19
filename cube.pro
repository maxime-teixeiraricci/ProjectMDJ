QT       += core gui widgets opengl gamepad

TARGET = cube
TEMPLATE = app


SOURCES += main.cpp \
    mesh.cpp \
    gameobject.cpp \
    timer_manager.cpp \
    inputmapping.cpp \
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
    colorblockcomponent.cpp \
    invisibiltycomponent.cpp \
    meshrenderer.cpp

SOURCES += \
    mainwidget.cpp

HEADERS += \
    mainwidget.h \
    mesh.h \
    gameobject.h \
    timer_manager.h \
    inputmapping.h \
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
    colorblockcomponent.h \
    invisibiltycomponent.h \
    meshrenderer.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/cube
INSTALLS += target

DISTFILES += \
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
