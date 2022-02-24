// Because we are having multiple files with name MainWindow, one in folder /tree/ and one in /table/,
// we remove #ifndef MAINWINDOW_H and #define MAINWINDOW_H from these files.

#pragma once

#include <QMainWindow>

#include "myitemmodel.h"

class QModelIndex;
class QFileSystemModel;
class QStandardItem;

namespace tree
{


namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    tree::Ui::MainWindow *ui;

    QFileSystemModel *m_model;
    MyItemModel *m_itemModel;

    void setFileInfoModel();
    void setCostumModel();

private slots:
    void slotPushButtonDebugClicked();
    void slotResizeColumnToContents(const QModelIndex &index);
    void slotHeaderDataChanged(Qt::Orientation orientation, int first, int last);
    void slotItemChanged(QStandardItem * item);
};

} // namespace tree

