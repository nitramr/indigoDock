#include "indigotabbar.h"
#include <QDebug>
#include <QWheelEvent>

IndigoTabbar::IndigoTabbar(QWidget *parent) :
    QTabWidget(parent)
{

    this->setObjectName("indigoTab");

    this->tabBar()->setFocusPolicy(Qt::NoFocus);
    this->tabBar()->setIconSize(QSize(32,32));
    this->setStyleSheet("QTabWidget::pane { /* The tab widget frame */"
                        "border: 0px solid transparent;"
                        "}"
                        "QTabBar::tab {"
                        "text-align: center;"
                        "border: 0px solid transparent;"
                        "border-radius: 0px;"
                        "width: 32px;"
                        "height: 32px;"
                        "padding: 0px;"
                        "}"
                        "QTabBar::tab:selected {"
                        "background-color: rgb(153,153,153);"
                        "}"
                       );

    // watch active tab change event
    connect(this->tabBar(), SIGNAL(currentChanged(int)), this, SLOT(setActiveTab(int)));

}

void IndigoTabbar::addTab( QWidget * child, const QString & label ){

      QTabWidget::addTab(child, label);

          m_activeWidget = this->widget(currentIndex());


}

void IndigoTabbar::addTab ( QWidget * child, const QIcon & icon, const QString & label ){

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
    pix = pix.scaledToWidth( 32 );
    pix = pix.scaledToHeight( 32 );
    ricon = QIcon(pix);

    // use normal addTab function
    QTabWidget::addTab(child, ricon, label);


        m_activeWidget = this->widget(currentIndex());

}


void IndigoTabbar::setActiveTab(int index){
    m_activeWidget = this->widget(index);
    //qDebug() << "TabIndexChange" << m_activeWidget << " index: " << index << endl;
}
