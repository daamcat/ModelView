#include "treemodel.h"

/*
Ref:
https://doc.qt.io/qt-5/qtwidgets-itemviews-simpletreemodel-example.html

*/

#include <QVector>
#include <iostream>

TreeModel::TreeModel(const QString &data, QObject *parent) : // Whatever comes after "colon" is called "initialization list":
    QAbstractItemModel (parent) // Base class constructors are automatically called if they have no argument. But if we want to call base class's constructor, that must be done in initialization list.
{
    const QVector<QVariant> rootData = {tr("root"), tr(">root"), tr("Summary")};
    m_rootItem = new TreeItem(rootData);
    QStringList dataSplitted = data.split('\n');
    setupModelData2(dataSplitted, m_rootItem);



    /*
    const QVector<QVariant> root = {tr("Title"), tr("Summary")};
    m_rootItem = new TreeItem(root);
    setupModelData(data.split('\n'), m_rootItem);
    */
}
TreeModel::~TreeModel()
{
    delete m_rootItem;
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        // We use the indexes, only when they are valid.
    {
        // From documentation: If you don't have value to return, return an invalid QVariant, and NOT zero!
        return QVariant();
    }
    if (role != Qt::ItemDataRole::DisplayRole)
    {
        return QVariant();
    }

    // Model indexes provide TEMPORARY references to their pieces of information, and can be used to retrieve data from model:
    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    return item->data(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    // Each data item has properties (selectable or not, editable or not, enabled or not,...). These properties can be specified with enum Qt::ItemFlags.
    // Given the model index, we return the flags
    if (!index.isValid())
    {
        return Qt::ItemFlag::NoItemFlags;
    }

    // ItemFlags is typedef of QFlags<ItemFlag>.
    return QAbstractItemModel::flags(index) | Qt::ItemFlag::ItemIsEditable;
}

bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  if (!index.isValid() || role != Qt::ItemDataRole::EditRole)
  {
    return false;
  }

  // Access the item from index:
  TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

  QVector<QVariant> columnData;
  for (int i = 0; i<item->columnCount();i++)
  {
    if (i == index.column())
    {
      columnData << value.toString();
    }
    else
    {
      columnData << item->data(i).toString();
    }
  }
  item->setData(columnData);

  emit dataChanged(index,index,{role});
  return true;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // Horizontal header: section = column number
    // Vertical header: section = row number
    if (orientation == Qt::Orientation::Horizontal && role == Qt::ItemDataRole::DisplayRole)
    {
        return m_rootItem->data(section);
    }

    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    // First make sure with the given info, there is an index:
    if (this->hasIndex(row,column,parent) == false)
    {
        return QModelIndex();
    }

    // First find parent TreeItem, having model index of the parent:
    TreeItem *parentItem;
    if (parent.isValid())
    {
        parentItem = static_cast<TreeItem*>(parent.internalPointer());
    }
    else
        // If the parent index is not valid, the parent item is root item:
    {
        parentItem = m_rootItem;
    }

    // Now, having parent item, we can get its child item:
    TreeItem* childItem = parentItem->getChildItem(row);

    // Now having the child item, we want its model index:
    if (childItem)
    {
        return this->createIndex(row,column,childItem);
    }
    else
    {
        return QModelIndex();
    }
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return QModelIndex();
    }

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->getParentItem();
    if (parentItem == m_rootItem)
    {
        // We always return invalid index as parent of top-level item [1]:
        return QModelIndex();
    }

    return this->createIndex(parentItem->row(),0,parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() >0)
        // We know that our model has only one column
    {
        return 0;
    }

    // Obtain parent item from parent model index:
    TreeItem *parentItem;
    if (!parent.isValid())
    {
        parentItem = m_rootItem;
    }
    else
    {
        parentItem = static_cast<TreeItem*>(parent.internalPointer());
    }

    return parentItem->childCount();
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        TreeItem *parentItem = static_cast<TreeItem*>(parent.internalPointer());
        return parentItem->columnCount();
    }

    return m_rootItem->columnCount();
}

void TreeModel::setupModelData(const QStringList &lines, TreeItem *parent)
{
    QVector<TreeItem*> parents;
    QVector<int> indentations;
    parents << parent;
    indentations << 0;

    int number = 0;

    while (number < lines.count()) {
        int position = 0;
        while (position < lines[number].length()) {
            if (lines[number].at(position) != ' ')
                break;
            position++;
        }

        const QString lineData = lines[number].mid(position).trimmed();

        if (!lineData.isEmpty()) {
            // Read the column data from the rest of the line.
            const QStringList columnStrings = lineData.split('\t', QString::SkipEmptyParts);
            QVector<QVariant> columnData;
            columnData.reserve(columnStrings.count());
            for (const QString &columnString : columnStrings)
                columnData << columnString;

            if (position > indentations.last()) {
                // The last child of the current parent is now the new parent
                // unless the current parent has no children.

                if (parents.last()->childCount() > 0) {
                    parents << parents.last()->getChildItem(parents.last()->childCount()-1);
                    indentations << position;
                }
            } else {
                while (position < indentations.last() && parents.count() > 0) {
                    parents.pop_back();
                    indentations.pop_back();
                }
            }

            // Append a new item to the current parent's list of children.
            parents.last()->appendChild(new TreeItem(columnData, parents.last()));
        }
        ++number;
    }
}

QString TreeModel::enumToString(NodeTypes type)
{
  switch (type)
  {
  case NodeTypes::nodeTypeGroup:
    return "nodeTypeGroup";
  case NodeTypes::nodeTypeString:
    return "nodeTypeString";
  case NodeTypes::nodeTypeInt64:
    return "nodeTypeInt64";
  case NodeTypes::nodeTypeBool:
    return "nodeTypeBool";
  case NodeTypes::nodeTypeDouble:
    return "nodeTypeDouble";
  default:
    return "nodeTypeUnknown";
  }
}

NodeTypes TreeModel::stringToEnum(QString string)
{
    if (string == "nodeTypeGroup")
        return NodeTypes::nodeTypeGroup;
    else if (string == "nodeTypeString")
        return NodeTypes::nodeTypeString;
    else if (string == "nodeTypeInt64")
        return NodeTypes::nodeTypeInt64;
    else if (string == "nodeTypeDouble")
        return NodeTypes::nodeTypeDouble;
    else if (string == "nodeTypeBool")
        return NodeTypes::nodeTypeBool;
    else
        return NodeTypes::nodeTypeUnknown;
}

void TreeModel::setupModelData2(const QStringList &lines, TreeItem *parent)
{
  QVector<TreeItem*> nodes;
  nodes << parent;

  for (QString line : lines)
  {
    // First remove the "\r" from the end of line:
    line = line.simplified();
    QStringList lineSplitted = line.split(';');

    //##################
    // Read the data from the node (line)
    //##################
    NodeTypes nodeType = NodeTypes::nodeTypeUnknown;
    if (lineSplitted.size() >= 2)
    {
        nodeType = stringToEnum(lineSplitted.at(1));
    }

    QString nodeValue;
    if (lineSplitted.size() == 4 &&
            nodeType != NodeTypes::nodeTypeUnknown &&
            nodeType != NodeTypes::nodeTypeGroup)
    {
        nodeValue = lineSplitted.at(3);
    }

    QStringList nodeNames = lineSplitted.at(0).split('>');
    QString parentNodeName;
    QString nodePath = ">root";
    QString parentNodePath = "";
    for (int i = 1; i<nodeNames.size()-1; i++)
      // Sweeps the node names from "root" to the end node name in a line,...
      // (The first string is empty string)
    {
      QString parentNodeName = nodeNames.at(i);
      QString nodeName = nodeNames.at(i+1);
      nodePath = nodePath + ">" + nodeName;
      parentNodePath = parentNodePath + ">" + parentNodeName;
      if (nodeName == "" || parentNodeName == "")
      {
          continue;
      }

      TreeItem *parentItem = nullptr;
      // Find parent node:
      for (TreeItem* item : nodes)
      {
        if (item->data(1).toString() == parentNodePath)
        {
          // Parent found!
          parentItem = item;
          break;
        }
      }

      // Check if the node itself exists:
      TreeItem *nodeItself = nullptr;
      for (TreeItem* item : nodes)
      {
        if (item->data(1).toString() == nodePath)
        {
          // Node found!
          nodeItself = item;
          break;
        }
      }

      if (!nodeItself)
      {
        QVector<QVariant> columnData;
        if (i == nodeNames.size()-2 && nodeType != NodeTypes::nodeTypeGroup)
        {
            columnData << nodeName <<nodePath << nodeValue;
            std::cout<<nodeName.toStdString()<<" , "<<nodeValue.toStdString()<<std::endl;
        }
        else
        {
            columnData << nodeName <<nodePath << QVariant();
        }
        TreeItem *treeItem = new TreeItem(columnData,parentItem);
        parentItem->appendChild(treeItem);
        nodes<<treeItem;
      }
    }
  }
}
