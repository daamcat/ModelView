#ifndef TREEITEM_H
#define TREEITEM_H

/*
Ref:
https://doc.qt.io/qt-5/qtwidgets-itemviews-simpletreemodel-example.html
https://doc.qt.io/qt-5/model-view-programming.html
*/


#include <QVector>
#include <QVariant>

class TreeItem
{
public:
    explicit TreeItem(const QVector<QVariant> &data, TreeItem *parentItem = nullptr);
    // Keyword "explicit" to avoid unwanted conversion.
    // Each TreeItem has a parent item, which itself is another TreeItem.

    // Destructor declaration
    ~TreeItem();

    // How the data is displayed is separated from how it is accessed. This is the major reason behind concept of QModelIndex.
    // Each piece of information = one QModelIndex object
    // Smallest piece of our tree = one TreeItem object

    // ModelIndexes are used to retrieve or modify the data via the model. We think of an item of data. We want its modelIndex. We need 3 things:
    // row, column, modelIndex of parent data item.
    // For tables, we only need row and column: QModelIndex indexA = model->index(0, 0, QModelIndex());
    // For trees, we must have the parent index.

    // Each treeItem contains several columns of data. Hence, in DataItem structure, we assume only one column for each item. And, for addressing a data item, we just need its
    // row number and its parent item, and column number is not needed. This format is typical for trees.


    void appendChild(TreeItem *child);
    TreeItem* getChildItem(int row);

    // The "const" at the end of function member declaration? We get compiler error if we later try to change the value returned by these functions.
    // The idea behind "const" function members is not to allow the function members to modify the objects on which they are called.
    // Example: Inside these "const" functions, you can't call m_childItems.clear();
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const; // Each TreeItem has different columns.
    int row() const;
    TreeItem* getParentItem(); // Each TreeItem has a parent TreeItem.

private:
    QVector<TreeItem*> m_childItems;
    QVector<QVariant> m_itemData;
    TreeItem* m_parentItem;


};

#endif // TREEITEM_H
