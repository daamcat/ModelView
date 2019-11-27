#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "myitemmodel.h"



namespace Ui {
class MainWindow;
}

class QModelIndex;
class QFileSystemModel;
class QStandardItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

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

#endif // MAINWINDOW_H
