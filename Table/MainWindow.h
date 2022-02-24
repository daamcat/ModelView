// Because we are having multiple files with name MainWindow, one in folder /tree/ and one in /table/,
// we remove #ifndef MAINWINDOW_H and #define MAINWINDOW_H from these files.

#pragma once

#include <QMainWindow>

namespace table
{
namespace Ui
{
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  table::Ui::MainWindow *ui;
};

} // namespace table

