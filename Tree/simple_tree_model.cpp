#include "treemodel.h"
#include <QApplication>
#include <QTreeView>
#include <QFile>
#include <QDir>
#include <QDebug>


/*
Ref:
https://doc.qt.io/qt-5/qtwidgets-itemviews-simpletreemodel-example.html
*/


int simple_tree_model(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString fileName = QDir::currentPath() + "/testData/TreeSample2.txt";
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    TreeModel model(file.readAll());
    file.close();

    TreeModel model2("Salam");
    QTreeView w;
    w.setModel(&model);
    w.expandAll();
    w.setWindowTitle("View1");
    w.show();

    QTreeView w2;
    w2.setModel(&model);
    w2.expandAll();
    w2.setWindowTitle("View2");
    w2.show();

    return a.exec();
}
