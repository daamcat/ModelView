#ifndef MYTREEVIEW_H
#define MYTREEVIEW_H


#include <QTreeView>

class MyTreeView : public QTreeView
{
public:
    MyTreeView(QWidget *parent = nullptr);

private slots:
    void slotContextMenuRequested(QPoint point);
};

#endif // MYTREEVIEW_H
