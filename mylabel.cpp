#include "mylabel.h"

#include <QFont>
#include <QFontMetrics>
#include <QResizeEvent>
#include <QString>

MyLabel::MyLabel(QWidget *parent) : QLabel(parent),
    m_parent(parent)
{
    QString text = "hala hala hala hala hala";
    m_originalText = text + text + text + text;
    this->setText(m_originalText);
}




void MyLabel::resizeEvent(QResizeEvent *event)
{
    int labelWidth = this->size().width();
    QFont font = this->font();
    QFontMetrics fontMetrics(font);

    QString adjustedText = fontMetrics.elidedText(m_originalText, Qt::TextElideMode::ElideRight, labelWidth - 50);
    this->setText(adjustedText);
    QLabel::resizeEvent(event);
}
