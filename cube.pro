QT       += core gui widgets

TARGET = cube
TEMPLATE = app

SOURCES += main.cpp \
    mesh.cpp \
    obj_loader.cpp \
<<<<<<< HEAD
    gameobject.cpp \
    scenegraph.cpp
=======
    collider.cpp
>>>>>>> 4e2c101fd295eb628b99824aa97134f85c1e2110

SOURCES += \
    mainwidget.cpp \
    geometryengine.cpp

HEADERS += \
    mainwidget.h \
    geometryengine.h \
    mesh.h \
<<<<<<< HEAD
    gameobject.h \
    scenegraph.h
=======
    collider.h
>>>>>>> 4e2c101fd295eb628b99824aa97134f85c1e2110

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
