#include "iconwidget.h"

IconWidget::IconWidget(QWidget *parent)
    : QWidget(parent)
{

}



IconWidget::IconWidget(QIcon icon, int iconSize, QWidget *parent)
    : QWidget(parent)
{
    setIcon(icon, iconSize);
}



IconWidget::IconWidget(QString filePath, int iconSize, QWidget *parent)
    : QWidget(parent)
{
    setIcon(filePath, iconSize);
}



void IconWidget::setIcon(QIcon icon, int iconSize){

    int_iconSize = iconSize;
    pxm_icon = icon.pixmap(icon.actualSize(QSize(int_iconSize, int_iconSize)));

    setFixedSize(iconSize, iconSize);
    update();

}



void IconWidget::setIcon(QString filePath, int iconSize){

    QIcon icon = QIcon(filePath);
    setIcon(icon, iconSize);

}



void IconWidget::paintEvent(QPaintEvent *){


    QPainter painter(this);

    painter.drawPixmap(0,0,width(), height(), pxm_icon);

}
