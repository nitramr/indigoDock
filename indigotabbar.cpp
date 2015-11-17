#include "indigotabbar.h"
#include <QDebug>
#include <QWheelEvent>
#include <QStyle>

IndigoTabbar::IndigoTabbar(QWidget *parent) :
    QTabWidget(parent)
{

    iconScale = 32;

    this->setObjectName("indigoTab");

    this->tabBar()->setFocusPolicy(Qt::NoFocus);
    this->tabBar()->setIconSize(QSize(iconScale,iconScale));

   // QPainter painter(this);
    //style()->drawControl(QStyle::CT_TabBarTab, QStyleOptionTab, painter,this->tabBar());
    QString styleSheet("QTabWidget::pane {"
                            "border: 0px solid transparent;"
                        "}"
                        "QTabWidget::tab-bar{"
                            "alignment: left;"
                        "}"
                        "QTabBar::tab {"
                            "text-align: center;"
                            "border: 0px solid transparent;"
                            "border-radius: 0px;"
                            "width: %1 px;"
                            "height: %1 px;"
                            "padding: 0px;"
                        "}"
                        "QTabBar::tab:selected {"
                            "background-color: rgb(153,153,153);"
                        "}"
                       );

    this->setStyleSheet( styleSheet.arg(iconScale) );

    // watch active tab change event
    connect(this->tabBar(), SIGNAL(currentChanged(int)), this, SLOT(setActiveTab(int)));



}

void IndigoTabbar::addTab( QWidget * child, const QString & label ){

      QTabWidget::addTab(child, label);

          m_activeWidget = this->widget(currentIndex());


}

void IndigoTabbar::addTab ( QWidget * child, const QIcon & icon, const QString & label ){

    // rotate icon if needed
    QIcon ricon = rotateIcon(icon);

    // use normal addTab function
    QTabWidget::addTab(child, ricon, label);


    m_activeWidget = this->widget(currentIndex());

}


void IndigoTabbar::setActiveTab(int index){
    m_activeWidget = this->widget(index);
    //qDebug() << "TabIndexChange" << m_activeWidget << " index: " << index << endl;
}

QIcon IndigoTabbar::rotateIcon(const QIcon &icon){

    QSize sz;

    for (int var = 0; var < icon.availableSizes().count(); ++var) {
        if (icon.availableSizes().at(var).width() > sz.width())
        sz = icon.availableSizes().at(var);
    }
    QPixmap pix = icon.pixmap(sz);
    QTransform trans;

    switch(this->tabPosition()){
    case QTabWidget::East:{
        trans.rotate(-90);
        break;
    }
    case QTabWidget::West:{
        trans.rotate(+90);
        break;
    }
    default:
        break;
    }

    pix = pix.transformed(trans);
    pix = pix.scaledToWidth( iconScale );
    pix = pix.scaledToHeight( iconScale );
    return QIcon(pix);
}
