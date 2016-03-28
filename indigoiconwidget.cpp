#include "indigoiconwidget.h"

IndigoIconWidget::IndigoIconWidget(QWidget *parent)
    : QWidget(parent)
{

}



IndigoIconWidget::IndigoIconWidget(QIcon icon, int iconSize, QWidget *parent)
    : QWidget(parent)
{
    setIcon(icon, iconSize);
}



IndigoIconWidget::IndigoIconWidget(QString filePath, int iconSize, QWidget *parent)
    : QWidget(parent)
{
    setIcon(filePath, iconSize);
}



void IndigoIconWidget::setIcon(QIcon icon, int iconSize){

    int_iconSize = iconSize;
    pxm_icon = icon.pixmap(icon.actualSize(QSize(int_iconSize, int_iconSize)));

    setFixedSize(iconSize, iconSize);
    update();

}



void IndigoIconWidget::setIcon(QString filePath, int iconSize){

    QIcon icon = QIcon(filePath);
    setIcon(icon, iconSize);

}



void IndigoIconWidget::paintEvent(QPaintEvent *){


    QPainter painter(this);

    painter.drawPixmap(0,0,width(), height(), pxm_icon);

}
