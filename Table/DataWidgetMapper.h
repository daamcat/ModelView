#ifndef DATAWIDGETMAPPER_H
#define DATAWIDGETMAPPER_H


#include <QDataWidgetMapper>

class DataWidgetMapper : public QDataWidgetMapper
{
  Q_OBJECT
public:
  DataWidgetMapper(QObject* parent = nullptr);
};

#endif // DATAWIDGETMAPPER_H
