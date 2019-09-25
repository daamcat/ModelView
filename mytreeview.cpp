#include "mytreeview.h"

#include <QHeaderView>
#include <QMenu>
#include <QAction>

MyTreeView::MyTreeView(QWidget *parent)
{
    // With Qt::CustomContextMenu the signal customContextMenuRequested()is emitted and the user requests a context menu.
    setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);

    connect(this , &MyTreeView::customContextMenuRequested , this , &MyTreeView::slotContextMenuRequested);





}


void MyTreeView::slotContextMenuRequested(QPoint point)
{
    QModelIndex modelIndex = this->indexAt(point);
    // WARNING: This point is with respect to MyTreeView object local coordinates. When showing a context menu, it must be mapped into global coordinates.

    QMenu *menu = new QMenu(this);
    QString displayRole = modelIndex.data(Qt::ItemDataRole::DisplayRole).toString();
    menu->addAction(new QAction(displayRole,this));

    // What is viewPort? Imagine you have a big image and you zoom in. You will have horizontal and vertical scrollbars, since not the whole widget is visible.
    // The visible part of the image is shown in a widget. This widget is called "viewPort".
    QPoint pointInGlobalCoordinate = this->viewport()->mapToGlobal(point);
    menu->popup(pointInGlobalCoordinate);

}
