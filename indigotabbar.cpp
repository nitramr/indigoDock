#include "indigotabbar.h"
#include <QDebug>
#include <QWheelEvent>
#include <QStyle>

IndigoTabBar::IndigoTabBar(QWidget *parent) :
    QTabBar(parent)
{

    int_iconScale = 32;
    QColor c_bg = /*QColor( 153, 153, 153 );*/this->palette().color(QPalette::Base);

    QString styleSheetTab(  "QTabBar{"
                                "border: 0px solid transparent;"
                            "}"
                            "QTabBar::tab {"
                                "alignment: left;"
                                "text-align: center;"
                                "border: 0px solid transparent;"
                                "border-radius: 0px;"
                                "width: %1 px;"
                                "height: %1 px;"
                                "padding: 0px;"
                                "margin: 0px;"
                            "}"
                            "QTabBar::tab:hover {"
                                "background-color: rgb(%2,%3,%4);"
                            "}"
            );

    this->setStyleSheet( styleSheetTab.arg(int_iconScale).arg(c_bg.red()).arg(c_bg.green()).arg(c_bg.blue()) );
    this->setMovable(true);
    this->setShape(QTabBar::RoundedEast);
    this->setFocusPolicy(Qt::NoFocus);
    this->setIconSize(QSize(int_iconScale,int_iconScale));
    this->setExpanding(false);
    this->setSelectionBehaviorOnRemove(QTabBar::SelectPreviousTab);
    this->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding));

}



void IndigoTabBar::mousePressEvent(QMouseEvent*event){

    QTabBar::mousePressEvent(event);
    int_oldIndex = this->currentIndex();
}




void IndigoTabBar::mouseReleaseEvent(QMouseEvent*event){

    int_newIndex = this->currentIndex();
    emit moveTab();

    QTabBar::mouseReleaseEvent(event);

}


int IndigoTabBar::oldTabIndex(){

    return int_oldIndex;
}



int IndigoTabBar::newTabIndex(){

    return int_newIndex;
}



void IndigoTabBar::addTab(QIcon &icon){

    icon = rotateIcon(icon);

    QTabBar::addTab(icon, "");

}



void IndigoTabBar::insertTab(int index, QIcon &icon){

    icon = rotateIcon(icon);

    QTabBar::insertTab(index, icon, "");
}



void IndigoTabBar::setTabPosition(Orientation tabOrientation){


    // Rotate icons in right direction
    for(int i=0;i<this->count();i++)
    {
        QIcon icon = this->tabIcon(i);

        icon = rotateIcon(icon, tabOrientation);

        this->setTabIcon(i, icon);

    }

    // set new tab position
    switch(tabOrientation){
        case IndigoTabBar::East:{
            this->setShape(QTabBar::RoundedEast);
            break;
        }
        case IndigoTabBar::West:{
            this->setShape(QTabBar::RoundedWest);
            break;
        }
        case IndigoTabBar::North:{
            this->setShape(QTabBar::RoundedNorth);
            break;
        }
        case IndigoTabBar::South:{
            this->setShape(QTabBar::RoundedSouth);
            break;
        }
        default:
            this->setShape(QTabBar::RoundedEast);
            break;
    }

}



/******************
 *
 * Helper
 *
 * ***************/

QIcon IndigoTabBar::rotateIcon(const QIcon &icon, Orientation tabOrientation){

    QSize sz;

    for (int var = 0; var < icon.availableSizes().count(); ++var) {
        if (icon.availableSizes().at(var).width() > sz.width())
        sz = icon.availableSizes().at(var);
    }
    QPixmap pix = icon.pixmap(sz);
    QTransform trans;

    switch(this->shape()){
    case QTabBar::RoundedEast:{
        switch(tabOrientation){
            case IndigoTabBar::West:{
                trans.rotate(180);
                break;
            }
            case IndigoTabBar::North:{
                trans.rotate(-90);
                break;
            }
            case IndigoTabBar::South:{
                trans.rotate(+90);
                break;
            }
            default:
                break;
        }


        break;
    }
    case QTabBar::RoundedWest:{
        switch(tabOrientation){

            case IndigoTabBar::East:{
                trans.rotate(180);
                break;
            }
            case IndigoTabBar::North:{
                trans.rotate(+90);
                break;
            }
            case IndigoTabBar::South:{
                trans.rotate(-90);
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
    pix = pix.scaledToWidth( int_iconScale );
    pix = pix.scaledToHeight( int_iconScale );

    return QIcon(pix);
}

