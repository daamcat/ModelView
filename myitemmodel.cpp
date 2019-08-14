#include <QStandardItem>
#include <QFont>
#include <QBrush>

#include "myitemmodel.h"

MyItemModel::MyItemModel()
{

    this->setHeaderData(0,Qt::Orientation::Horizontal,"Col 1");
    QList<QStandardItem*> items;

    QStandardItem *standardItem = new QStandardItem();
    double itemValue = 5.67;
    standardItem->setData(itemValue);
    QFont sansFont("Helvetica [Cronyx]", 22);
    standardItem->setFont(sansFont);
    standardItem->setText("This is a double");
    QBrush brush;
    brush.setStyle(Qt::BrushStyle::CrossPattern);
    brush.setColor(Qt::yellow);
    standardItem->setForeground(brush);
    standardItem->setBackground(QBrush(Qt::GlobalColor::darkRed));

    QStandardItem *standardItemChild = new QStandardItem();
    int itemValueChild = 8;
    standardItemChild->setData(itemValueChild);
    sansFont = QFont("Helvetica [Cronyx]", 16);
    standardItemChild->setFont(sansFont);
    standardItemChild->setText("This is a child int1");
    brush.setStyle(Qt::BrushStyle::Dense1Pattern);
    brush.setColor(Qt::black);
    standardItemChild->setForeground(brush);

    standardItem->setChild(0,0,standardItemChild);

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



    items.push_back(standardItem);

    QStandardItem *standardItem2 = new QStandardItem();
    QString valueStr = "Harchi";
    standardItem2->setData(itemValue);
    sansFont = QFont("Helvetica [Cronyx]", 27);
    sansFont.setBold(true);
    standardItem2->setFont(sansFont);
    standardItem2->setText("This is a string");
    brush.setStyle(Qt::BrushStyle::VerPattern);
    brush.setColor(Qt::green);
    standardItem2->setForeground(brush);
    standardItem2->setBackground(QBrush(Qt::GlobalColor::darkCyan));


    QStandardItem *standardItemChild3 = new QStandardItem();
    standardItemChild3->setData(itemValueChild);
    sansFont = QFont("Helvetica [Cronyx]", 16);
    standardItemChild3->setFont(sansFont);
    standardItemChild3->setText("This is a child int3");
    brush.setStyle(Qt::BrushStyle::Dense1Pattern);
    brush.setColor(Qt::black);
    standardItemChild3->setForeground(brush);

    standardItem2->setChild(1,1,standardItemChild3);


    items.push_back(standardItem2);

    this->appendColumn(items);

    this->insertColumn(1);


    this->setHeaderData(0,Qt::Orientation::Horizontal,"Col1");
    this->setHeaderData(1,Qt::Orientation::Horizontal,"Col2");




}
