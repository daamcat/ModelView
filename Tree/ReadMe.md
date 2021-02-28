# My Notes on Model-View

In order to choose the right class to subclass, we need to ask some major questions:
1. Do we want a read-only model or read-write model.
2. What kind of items are we going to show? Simple list of strings, Simple table, tree view?
In Qt, the standard class for model is `QAbstractItemModel`. In order to be able to use `QAbstractItemModel`, you need to reimplement some functions. But there are several other classes which have default implementations of these functions in order to ease the use of the classes. For example, I chose `QStandardItemModel` class because I wanted to show tree models. Using `QStandardItemModel`, we don't need to reimplement anything in order to see the model. If our model is a tree model, subclassing `QAbstractItemModel` is a demanding task with need of many function members to be reimplemented.






## 06.12.2019
My reimplementation of the function `QAbstractItemModel::data()` looks like this below:

```cpp
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
    else
    {
        return QVariant();
    }
}
```

![alt text](https://github.com/daamcat/ModelView/blob/master/images/table_simple_data_no_delegate.PNG)

Then I add one `if-else` condition to the function for the case the role is `BackgroundColorRole`:

```cpp
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

We see how the background color of the cells in view changes into red:

![alt text](https://github.com/daamcat/ModelView/blob/master/images/table_BackgroundColorRole_added_data_no_delegate.PNG)

 
 07.05.2020
 We have a working read-only model-view. We want to make it read-write:
 1. Add a reimplementation of the function `Qt::ItemFlags QAbstractItemModel::flags(const QModelIndex &index) const`. 
 For each the model must be able to return the flags of the item. The item being selectable, editable, etc is identified through these flags (Qt::ItemFlags).
 Write the last line of the function so that `Qt::ItemFlag::ItemIsEditable` is between the returned flags:
```cpp
return QAbstractItemModel::flags(index) | Qt::ItemFlag::ItemIsEditable;
```

Now run the code and double-click on an arbitrary cell. You will see that you can type in the place of the cell.
But even if you type something new, nothing will happen. In the next step, we want the model to be updated after we change the content of a cell.
2. Add a reimplementation of the function `bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::ItemDataRole::EditRole) override`.
This function provides us the possibility of setting the new value in the model. The crucial point is how to access the data item using modelindex input argument.
At the end of editing the data in model, we need to send a signal that data was changed. This is `dataChanged()` signal. To see what this signal does, create an extra tree view and set your model to it. By running the code, you can see two views for a single model. If you double click on a cell in a view and change its value, you expect all views to be updated. This will not happen without emitting the signal `dataChanged()`.


