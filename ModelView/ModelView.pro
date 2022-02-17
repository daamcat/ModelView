
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = ModelView
TEMPLATE = app


# Adds the Tree project path to the header file include lookup path
INCLUDEPATH += $$PWD/../Tree
INCLUDEPATH += $$PWD/../Table

SOURCES += main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Adds Tree.lib to the linker
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Tree/release/ -lTree
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Tree/debug/ -lTree

# Adds the Table.lib to the linker
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Table/release/ -lTable
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Table/debug/ -lTable

# Copy a folder to build directory:
# (ref linux: https://dragly.org/2013/11/05/copying-data-files-to-the-build-directory-when-working-with-qmake/)
# (ref win: https://stackoverflow.com/questions/19066593/copy-a-file-to-build-directory-after-compiling-project-with-qt)
# $$PWD/../ is parent folder of source folder.
# shell_path is needed in windows, otherwise QMAKE_EXTRA_TARGETS issues makefile error.
copydata.commands = $(COPY_DIR) \"$$shell_path($$PWD/../\\Tests\\testData)\" \"$$shell_path($$OUT_PWD\\testData)\"
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

