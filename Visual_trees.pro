QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    avl_tree.cpp \
    crazycircle.cpp \
    customview.cpp \
    draw_tree.cpp \
    main.cpp \
    mainwindow.cpp \
    splay_tree.cpp \
    treap.cpp

HEADERS += \
    avl_tree.h \
    common_parts_trees.h \
    crazycircle.h \
    customview.h \
    draw_tree.h \
    mainwindow.h \
    splay_tree.h \
    treap.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
