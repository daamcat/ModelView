#include "treeitem.h"

TreeItem::TreeItem(const QVector<QVariant> &data, TreeItem *parentItem):
    m_itemData(data),
    m_parentItem(parentItem)
{


}

TreeItem::~TreeItem()
{
    qDeleteAll(m_childItems);
}

void TreeItem::appendChild(TreeItem *child)
{
    m_childItems.push_back(child);
}

TreeItem* TreeItem::getChildItem(int row)
{
    if (row>=0 && row<childCount())
    {
        return m_childItems.at(row);
    }
    return nullptr;
}

int TreeItem::childCount() const
{
    return m_childItems.size();
}

int TreeItem::columnCount() const
{
    return m_itemData.size();
}

QVariant TreeItem::data(int column) const
{
    if (column < 0 || column >= columnCount())
    {
        return QVariant();
    }
    return m_itemData.at(column);
}

int TreeItem::row() const
{
    if (!m_parentItem)
        // If the item has no parent, it is root item, and its row is zero. Model will never ask for this!
    {
        return 0;
    }
    return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));
}

TreeItem* TreeItem::getParentItem()
{
    return m_parentItem;
}

void TreeItem::setData(const QVector<QVariant> &data)
{
  m_itemData = data;
}

