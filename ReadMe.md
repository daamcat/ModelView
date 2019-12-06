# My Notes on Model-View

## 06.12.2019
My reimplementation of the function `QAbstractItemModel::data()` looks like this:

```c_cpp
QVariant MyItemModel::data(const QModelIndex &index, int role) const
{
    // With reimplementation of data(), the view will ignore all the formatting of the cells.
    if (index.isValid() == false || index.row() >= m_items.size())
    {
        return QVariant();
    }

    if (role == Qt::ItemDataRole::DisplayRole)
    {
        if (index.column() == 0)
        {
            return m_items.at(index.row())->data(Qt::ItemDataRole::DisplayRole);
        }
        else
        {
            return m_items.at(index.row())->data();
        }
    }

    else if (role == Qt::ItemDataRole::BackgroundColorRole)
    {
        return QColor(Qt::red);
    }
    else
    {
        return QVariant();
    }
}

```
 
