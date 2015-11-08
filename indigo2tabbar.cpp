#include "indigo2tabbar.h"
#include <QDebug>

Indigo2Tabbar::Indigo2Tabbar(QWidget *parent) :
    QTabWidget(parent)
{

    this->setObjectName("indigoTab");

    // watch active tab change event
    tabBar()->installEventFilter(this);
}

void Indigo2Tabbar::addTab( QWidget * child, const QString & label ){

      QTabWidget::addTab(child, label);
      activeWidget = this->widget(currentIndex());

}

void Indigo2Tabbar::addTab ( QWidget * child, const QIcon & icon, const QString & label ){

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

    activeWidget = this->widget(currentIndex());

}


bool Indigo2Tabbar::eventFilter(QObject *o, QEvent *e)
{
    if (o == tabBar() && e->type() == QEvent::MouseButtonRelease) {

        int index = currentIndex();

        activeWidget = this->widget(currentIndex());
        qDebug() << "TabIndexChange" << activeWidget << " index: " << index << endl;

    }
    return QTabWidget::eventFilter(o, e);
}
