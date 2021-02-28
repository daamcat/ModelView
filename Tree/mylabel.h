#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>

class QResizeEvent;
class QString;

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    MyLabel(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event);

private:
    QString m_originalText;
    QWidget *m_parent;
};

#endif // MYLABEL_H


