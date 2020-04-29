#include "treemodel.h"
#include <QApplication>
#include <QTreeView>
#include <QFile>
#include <QDir>

/*
Ref:
https://doc.qt.io/qt-5/qtwidgets-itemviews-simpletreemodel-example.html
*/


int simple_tree_model(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString fileName = QString(SOURCE_DIR)+"/testData/TreeSample2.txt";
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    TreeModel model(file.readAll());
    file.close();

    TreeModel model2("Salam");
    QTreeView w;
    w.setModel(&model);

    w.show();
    return a.exec();
}
