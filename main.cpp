#include "mainwindow.h"
#include <QApplication>

#include "simple_tree_model.cpp"






int main(int argc, char *argv[])
{
    //MainWindow w;

    int exec = simple_tree_model(argc,argv);


    return exec;
}

