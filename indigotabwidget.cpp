#include "indigotabwidget.h"
#include <QDebug>

IndigoTabWidget::IndigoTabWidget(QWidget *parent) :
    QTabWidget(parent)
{

}

void IndigoTabWidget::addTab( QWidget * child, const QString & label ){

    QTabWidget::addTab(child, label);

}

void IndigoTabWidget::addTab ( QWidget * child, const QIcon & icon, const QString & label ){

    QIcon ricon = icon;
    QSize sz;

    for (int var = 0; var < ricon.availableSizes().count(); ++var) {
        if (ricon.availableSizes().at(var).width() > sz.width())
        sz = ricon.availableSizes().at(var);
    }
    QPixmap pix = ricon.pixmap(sz);
    QTransform trans;

    if (this->tabPosition() == QTabWidget::East)
    trans.rotate(-90);
    else
    trans.rotate(+90);

    pix = pix.transformed(trans);
    ricon = QIcon(pix);

    // use normal addTab function
    QTabWidget::addTab(child, ricon, label);
}


