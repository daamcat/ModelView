#ifndef TREEMODEL_H
#define TREEMODEL_H

/*
Ref:
[1] https://doc.qt.io/qt-5/qtwidgets-itemviews-simpletreemodel-example.html

*/

#include<QAbstractItemModel>
#include "treeitem.h"

enum class NodeColumns
{
  path,
  comment,
  type,
  value,
  defaultValue,
  minRead,
  minWrite,
  minFull,
  minValue,
  maxValue
};


// From which class we subclass, depends on how we want to represent the data. For lists: QAbstractListModel, for tables: QAbstractTableModel, for trees: QAbstractItemModel
class TreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit TreeModel(const QString &data, QObject *parent = nullptr);
    // Keyword "explicit" to avoid unwanted conversion.
    ~TreeModel();

    // Given the index and the role, returns the data.
    QVariant data(const QModelIndex &index, int role) const override;
    // Keyword "override" means this function belongs to the parent class and has been overwritten.
    // Keyword "const" means the function is not allowed to change the object.

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    // Keyword "override" means this function belongs to the parent class and has been overwritten.
    // Keyword "const" means the function is not allowed to change the object.

    // Given the section and role, returns the data for the header.
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::ItemDataRole::DisplayRole) const override;

    // Given the row, column and parent index, returns the index:
    // Views and delegates use this function to get indexes and to read the data.
    // The goal is to return child item index, given its parent plus row plus column.
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;

    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

private:
    void setupModelData(const QStringList &lines, TreeItem *parent);
    void setupModelData2(const QStringList &lines, TreeItem *parent);

    TreeItem *m_rootItem;


};

#endif // TREEMODEL_H
