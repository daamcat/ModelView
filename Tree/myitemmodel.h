#ifndef MYITEMMODEL_H
#define MYITEMMODEL_H

#include <QStandardItemModel>

class MyItemModel : public QStandardItemModel
{
    Q_OBJECT
public:
    MyItemModel();

    // For read-only models, reimplement rowCount(), data() and headerData() functions:
    //int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    //QVariant data(const QModelIndex &index, int role = Qt::ItemDataRole::DisplayRole) const override;
    //QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::ItemDataRole::DisplayRole) const override;




    void changeItem();

private:
    void setModelToTreeView();
    void setModelToTableView();


    QList<QStandardItem*> m_items;
};

#endif // MYITEMMODEL_H
