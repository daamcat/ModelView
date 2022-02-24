#include <QApplication>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QStringList>
#include <QTableView>

#include "TableModel.h"
#include "MainWindow.h"


int simple_table_model(int argc , char* argv[])
{
  QApplication a(argc,argv);

  QString fileName = QDir::currentPath() + "/testData/SampleTable.txt";
  QFile file(fileName);
  file.open(QIODevice::ReadOnly);
  QTextStream in(&file);
  QStringList strStream;
  while (!in.atEnd())
  {
    strStream.append(in.readLine());
  }
  file.close();

  /*
  QTableView winn;
  //TableModelPrimitive model;
  TableModel2 model;
  winn.setModel(&model);
  winn.show();
  */
  table::MainWindow win;
  win.show();

  return a.exec();
}
