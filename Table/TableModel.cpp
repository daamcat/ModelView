#include "TableModel.h"

TableModelPrimitive::TableModelPrimitive(QObject* parent) : QAbstractTableModel (parent)
{
}

int TableModelPrimitive::rowCount(const QModelIndex &parent) const
{
  return 3;
}

int TableModelPrimitive::columnCount(const QModelIndex &parent) const
{
  return 4;
}

QVariant TableModelPrimitive::data(const QModelIndex &index, int role) const
{
  if (role != Qt::ItemDataRole::DisplayRole)
  {
    return QVariant();
  }
  return QString("Row %1 , Col %2")
      .arg(index.row())
      .arg(index.column());
}

TableModel2::TableModel2(QObject* parent) : TableModelPrimitive (parent)
{
  for (int i = 0; i < 3; i++)
  {
    QVector<QString> row_i;
    for (int j = 0; j < 4; j++)
    {
      row_i.push_back(QString("T2 Row %1 , T2 Col %2")
          .arg(i)
          .arg(j));
    }
    m_items.push_back(row_i);
  }
}

int TableModel2::rowCount(const QModelIndex &parent) const
{
  return m_items.length();
}

int TableModel2::columnCount(const QModelIndex &parent) const
{
  return m_items.at(0).length();
}

QVariant TableModel2::data(const QModelIndex &index, int role) const
{
  if (role != Qt::ItemDataRole::DisplayRole)
  {
    return QVariant();
  }
  return m_items.at(index.row()).at(index.column());
}

