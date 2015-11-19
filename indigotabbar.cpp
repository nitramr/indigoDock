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


void IndigoTabbar::addIndigoPanel(IndigoPanel *panel, int tabIndex ){

    IndigoDropZone * zone = new IndigoDropZone(0);
    zone->addPanel(panel);

    static const QIcon &icon = panel->Icon();

    // new tab
    if (tabIndex == -1){

        this->connect(panel, SIGNAL(mouseReleased()), zone, SLOT(dropPanel()));
        this->connect(panel, SIGNAL(mouseMove()), zone, SLOT(hoverZone()));


        addTab ( zone, icon, "" );


    // exsisting tab
    }else{

        if(tabIndex >= 0 && tabIndex <= this->count() - 1){

            QWidget * widget = this->widget(tabIndex);

            IndigoDropZone *zone = qobject_cast<IndigoDropZone*>(widget);
            if(!zone) return;

            zone->addPanel(panel);

            this->connect(panel, SIGNAL(mouseReleased()), zone, SLOT(dropPanel()));
            this->connect(panel, SIGNAL(mouseMove()), zone, SLOT(hoverZone()));

           // m_activeWidget = this->widget(currentIndex()); // not need for exsisting tabs
        }

    }



}


void IndigoTabbar::setActiveTab(int index){
    m_activeWidget = this->widget(index);
    //qDebug() << "TabIndexChange" << m_activeWidget << " index: " << index << endl;
}


void IndigoTabbar::setTabPosition(TabPosition tabPos){


    // Rotate icons in right direction
    for(int i=0;i<count();i++)
    {
        QIcon icon = this->tabBar()->tabIcon(i);

        icon = rotateIcon(icon, tabPos);

        this->tabBar()->setTabIcon(i, icon);

    }

    // set new tab position
    QTabWidget::setTabPosition(tabPos);

}


/******************
 *
 * Helper
 *
 * ***************/

QIcon IndigoTabbar::rotateIcon(const QIcon &icon, TabPosition tabPos){

    QSize sz;

    for (int var = 0; var < icon.availableSizes().count(); ++var) {
        if (icon.availableSizes().at(var).width() > sz.width())
        sz = icon.availableSizes().at(var);
    }
    QPixmap pix = icon.pixmap(sz);
    QTransform trans;

    switch(this->tabPosition()){
    case QTabWidget::East:{
        switch(tabPos){
            case QTabWidget::West:{
                trans.rotate(180);
                break;
            }
            case QTabWidget::North:{
                trans.rotate(-90);
                break;
            }
            default:
                break;
        }


        break;
    }
    case QTabWidget::West:{
        switch(tabPos){

            case QTabWidget::East:{
                trans.rotate(180);
                break;
            }
            case QTabWidget::North:{
                trans.rotate(+90);
                break;
            }
            default:
                break;
        }
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
