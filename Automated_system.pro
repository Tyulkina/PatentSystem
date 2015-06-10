TEMPLATE = app
TARGET = Automated_system
QT += core \
    gui
QT += widgets
HEADERS += header/develop_information.h \
    header/ipc_class.h \
    header/patentsystem.h \
    header/ipc_form.h
SOURCES += src/develop_information.cpp \
    src/ipc_class.cpp \
    src/patentsystem.cpp \
    src/ipc_form.cpp \
    main.cpp
FORMS += develop_information.ui \
    ipc_form.ui \
    patentsystem.ui
RESOURCES += Resources.qrc
LIBS += "/usr/local/lib/liblink-grammar.so" \
    "/usr/lib/libpq.so"
LIBS += -L"/usr/local/lib" \
    -L"/usr/lib"
INCLUDEPATH += "/usr/local/include/link-grammar" \
    "/usr/include/postgresql"
