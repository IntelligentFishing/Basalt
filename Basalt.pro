QT += widgets
CONFIG += c++11 console
CONFIG -= app_bundle


INCLUDEPATH += /usr/local/include/yaml-cpp \
/usr/include/eigen3 \
interface/include \
methods/include

LIBS += /usr/local/lib/libyaml-cpp.a \
/usr/local/lib/libopencv*


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
    interface/src/mainwindow.cpp \
    interface/src/newproject.cpp \
    methods/src/common.cpp \
    methods/src/dataloader.cpp \
    methods/src/flda.cpp \
    methods/src/fldapanel.cpp \
    methods/src/kernel.cpp \
    methods/src/kfda.cpp \
    interface/src/loadproject.cpp \
    main.cpp \
    methods/src/kfdapanel.cpp \
    interface/src/createprojectfile.cpp \
    interface/src/createnewproject.cpp


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    interface/Forms/mainwindow.ui \
    interface/Forms/newproject.ui \
    methods/Forms/fldapanel.ui \
    interface/Forms/loadproject.ui \
    methods/Forms/kfdapanel.ui \
    interface/Forms/createnewproject.ui


HEADERS += \
    interface/include/mainwindow.h \
    interface/include/newproject.hpp \
    methods/include/common.hpp \
    methods/include/dataloader.hpp \
    methods/include/flda.hpp \
    methods/include/fldapanel.hpp \
    methods/include/kernel.hpp \
    methods/include/kfda.hpp \
    methods/include/RedSVD-h \
    interface/include/loadproject.hpp \
    methods/include/kfdapanel.hpp \
    interface/include/createprojectfile.hpp \
    interface/include/createnewproject.hpp

