#include <QStandardItem>
#include <QFont>
#include <QBrush>

#include "myitemmodel.h"

MyItemModel::MyItemModel()
{
    setModelToTreeView();


}

void MyItemModel::setModelToTreeView()
{
    m_items.clear();

    //#########################
    // Item 1
    //#########################
    QStandardItem *standardItem1 = new QStandardItem();
    double itemValue = 5.67;
    standardItem1->setData(itemValue);
    QFont sansFont("Helvetica [Cronyx]", 22);
    standardItem1->setFont(sansFont);
    standardItem1->setText("This is a double");
    QBrush brush;
    brush.setStyle(Qt::BrushStyle::CrossPattern);
    brush.setColor(Qt::yellow);
    standardItem1->setForeground(brush);
    standardItem1->setBackground(QBrush(Qt::GlobalColor::darkRed));

    //###########
    // Item 1 - child 1
    //###########
    QStandardItem *standardItemChild = new QStandardItem();
    int itemValueChild = 8;
    standardItemChild->setData(itemValueChild);
    sansFont = QFont("Helvetica [Cronyx]", 16);
    standardItemChild->setFont(sansFont);
    standardItemChild->setText("This is a child int1");
    brush.setStyle(Qt::BrushStyle::Dense1Pattern);
    brush.setColor(Qt::black);
    standardItemChild->setForeground(brush);

    standardItem1->setChild(0,0,standardItemChild);

    //###########
    // Item 1 - child 2
    //###########
    QStandardItem *standardItemChild2 = new QStandardItem();
    int itemValueChild2 = 8;
    standardItemChild2->setData(itemValueChild2);
    sansFont = QFont("Helvetica [Cronyx]", 16);
    standardItemChild2->setFont(sansFont);
    standardItemChild2->setText("This is a child int2");
    brush.setStyle(Qt::BrushStyle::Dense1Pattern);
    brush.setColor(Qt::blue);
    standardItemChild2->setForeground(brush);

    standardItemChild->setChild(0,1,standardItemChild2);

    //#########################
    // Item 2
    //#########################
    QStandardItem *standardItem2 = new QStandardItem;
    QString valueStr = "Harchi";
    standardItem2->setData(valueStr);
    sansFont = QFont("Helvetica [Cronyx]", 27);
    sansFont.setBold(true);
    standardItem2->setFont(sansFont);
    standardItem2->setText("This is a string");
    brush.setStyle(Qt::BrushStyle::VerPattern);
    brush.setColor(Qt::green);
    standardItem2->setForeground(brush);
    standardItem2->setBackground(QBrush(Qt::GlobalColor::darkCyan));

    //###########
    // Item 2 - child 1
    //###########
    QStandardItem *standardItemChild3 = new QStandardItem;
    standardItemChild3->setData(itemValueChild);
    sansFont = QFont("Helvetica [Cronyx]", 16);
    standardItemChild3->setFont(sansFont);
    standardItemChild3->setText("This is a child int3");
    brush.setStyle(Qt::BrushStyle::Dense1Pattern);
    brush.setColor(Qt::black);
    standardItemChild3->setForeground(brush);

    standardItem2->setChild(1,1,standardItemChild3);


    m_items.push_back(standardItem1);
    m_items.push_back(standardItem2);

    this->appendColumn(m_items);

    this->insertColumn(1);

    this->setHeaderData(0,Qt::Orientation::Horizontal,"Col 1");
    this->setHeaderData(1,Qt::Orientation::Horizontal,"Col 2");
}

void MyItemModel::setModelToTableView()
{
    m_items.clear();

    //#########################
    // Item 1
    //#########################
    QStandardItem *standardItem1 = new QStandardItem();
    double itemValue = 5.67;
    standardItem1->setData(itemValue);
    QFont sansFont("Helvetica [Cronyx]", 22);
    standardItem1->setFont(sansFont);
    standardItem1->setText("This is a double");
    QBrush brush;
    brush.setStyle(Qt::BrushStyle::CrossPattern);
    brush.setColor(Qt::yellow);
    standardItem1->setForeground(brush);
    standardItem1->setBackground(QBrush(Qt::GlobalColor::darkRed));

    //#########################
    // Item 2
    //#########################
    QStandardItem *standardItem2 = new QStandardItem;
    QString valueStr = "Harchi";
    standardItem2->setData(valueStr);
    sansFont = QFont("Helvetica [Cronyx]", 27);
    sansFont.setBold(true);
    standardItem2->setFont(sansFont);
    standardItem2->setText("This is a string");
    brush.setStyle(Qt::BrushStyle::VerPattern);
    brush.setColor(Qt::green);
    standardItem2->setForeground(brush);
    standardItem2->setBackground(QBrush(Qt::GlobalColor::darkCyan));


    //#########################
    // Adding to the model
    //#########################
    m_items.push_back(standardItem1);
    m_items.push_back(standardItem2);

    this->appendColumn(m_items);
}

//int MyItemModel::rowCount(const QModelIndex &parent) const
//{
//    // In a tree, number of rows are the number of items directly connected to the root item:
//    return m_items.size();
//}

//QVariant MyItemModel::data(const QModelIndex &index, int role) const
//{
//    // With reimplementation of data(), the view will ignore all the formatting of the cells.
//    if (index.isValid() == false || index.row() >= m_items.size())
//    {
//        return QVariant();
//    }

//    if (role == Qt::ItemDataRole::DisplayRole)
//    {
//        if (index.column() == 0)
//        {
//            return m_items.at(index.row())->data(Qt::ItemDataRole::DisplayRole);
//        }
//        else
//        {
//            return m_items.at(index.row())->data();
//        }
//    }

//    else if (role == Qt::ItemDataRole::BackgroundColorRole)
//    {
//        return QColor(Qt::red);
//    }
//    else
//    {
//        return QVariant();
//    }
//}


void MyItemModel::changeItem()
{

}
