TEMPLATE = subdirs
SUBDIRS += ModelView \
     Tree \
     Table
    #TableTest

ModelView.depends = Tree
ModelView.depends = Table

