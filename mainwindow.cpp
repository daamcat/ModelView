#include "mainwindow.h"
#include "myitemmodel.h"
#include "ui_mainwindow.h"
#include "mytreeview.h"

#include <QFileSystemModel>
#include <QPushButton>
#include <QDataWidgetMapper>
#include <QLineEdit>
#include <QHeaderView>
#include <QStandardItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //setFileInfoModel();
    setCostumModel();


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setFileInfoModel()
{
    // QFileSystemModel inherits QAbstractItemModel and provides a data model for local filesystem. QAbstractItemModel is suitable for hierarchical structures.
    // Data can be inserted, removed, modified, etc.
    m_model = new QFileSystemModel();
    //m_model->setRootPath(QDir::currentPath());
    m_model->setRootPath(QString("C:/Users/Damon/Desktop"));

    // Assuming a widget for each column (can be row too), QDataWidgetMapper maps the widgets to columns of item model.
    //QDataWidgetMapper *mapper = new QDataWidgetMapper();

    ui->treeView->setModel(m_model);
    ui->treeView->setAnimated(false);

    //QLineEdit *lineEdit = new QLineEdit();

    //mapper->setModel(m_model);
    //mapper->addMapping(lineEdit,1);
    //mapper->toFirst();

    // QHeaderView provides header row/column for item view:
    QHeaderView headerView(Qt::Orientation::Horizontal);
    // Header data comes normally with model too.

    connect(ui->pushButtonDebug,&QPushButton::clicked,this,&MainWindow::slotPushButtonDebugClicked);
    connect(ui->treeView,&QTreeView::expanded,this,&MainWindow::slotResizeColumnToContents);
    connect(ui->treeView,&QTreeView::collapsed,this,&MainWindow::slotResizeColumnToContents);
}

void MainWindow::setCostumModel()
{
    m_model = new QFileSystemModel();

    MyItemModel *itemModel = new MyItemModel();
    ui->treeView->setModel(itemModel);

    connect(itemModel,&MyItemModel::headerDataChanged,this,&MainWindow::slotHeaderDataChanged);
    connect(itemModel,&MyItemModel::itemChanged,this,&MainWindow::slotItemChanged);

}

void MainWindow::slotHeaderDataChanged(Qt::Orientation orientation, int first, int last)
{
    ui->labelDebug->setText("Header data changed");
}

void MainWindow::slotItemChanged(QStandardItem * item)
{
    ui->labelDebug->setText(QString("Standard item changed into: ") + QString(item->text()));
}


void MainWindow::slotPushButtonDebugClicked()
{
    // Clear the view:
    //ui->treeViewFiles->setModel(nullptr);
    //ui->treeViewFiles->setEnabled(false);

    // Access header data
    int columnNumber = 2;
    QString str = m_model->headerData(columnNumber,Qt::Orientation::Horizontal).toString();

    // using m_model->setHeaderData() to modify the model in here is not possible and will return false!


    ui->labelDebug->setText(str);

}

void MainWindow::slotResizeColumnToContents(const QModelIndex &index)
{
    int columnNumber = index.column();
    ui->labelDebug->setText(index.data().toString());
    ui->treeView->resizeColumnToContents(columnNumber);
}
