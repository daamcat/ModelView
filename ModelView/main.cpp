#include <QApplication>

#include "simple_tree_model.cpp"
#include "simple_table_model.cpp"





int main(int argc, char *argv[])
{
    //int exec = simple_tree_model(argc,argv);
    int exec = simple_table_model(argc,argv);

    return exec;
}

