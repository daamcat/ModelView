#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>

class TableModelPrimitive : public QAbstractTableModel
{
  Q_OBJECT
public:
  TableModelPrimitive(QObject* parent = nullptr);
  int rowCount(const QModelIndex& parent = QModelIndex()) const override;
  int columnCount(const QModelIndex& parent = QModelIndex()) const override;
  QVariant data(const QModelIndex& index , int role = Qt::ItemDataRole::DisplayRole) const override;
};

class TableModel2 : public TableModelPrimitive
{
  Q_OBJECT
public:
  TableModel2(QObject* parent = nullptr);
  int rowCount(const QModelIndex& parent = QModelIndex()) const override;
  int columnCount(const QModelIndex& parent = QModelIndex()) const override;
  QVariant data(const QModelIndex& index , int role = Qt::ItemDataRole::DisplayRole) const override;

private:
  QVector<QVector<QString>> m_items;
};



#endif // TABLEMODEL_H
