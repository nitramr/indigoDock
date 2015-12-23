#include "indigotabbar.h"
#include <QDebug>
#include <QWheelEvent>
#include <QStyle>

IndigoTabBar::IndigoTabBar(QWidget *parent) :
    QTabBar(parent)
{

    int_iconScale = 32;

    QString styleSheetTab(  "IndigoTabBar{"
                                "border: 0px solid transparent;"
                            "}"
                            "IndigoTabBar::tab {"
                                "alignment: left;"
                                "text-align: center;"
                                "border: 0px solid transparent;"
                                "border-radius: 0px;"
                                "width: %1 px;"
                                "height: %1 px;"
                                "padding: 0px;"
                                "margin: 0px;"
                            "}"
                           /* "IndigoTabBar::tab:disabled{"
                                "width: 0 px;"
                                "height: 0 px;"
                                "margin: 0 px;"
                                "padding: 0 px;"
                                "border: none;"
                            "}"*/
            );

    this->setAccessibleName("IndigoTabBar");
    this->setStyleSheet( styleSheetTab.arg(int_iconScale));
    this->setMovable(true);
    this->setShape(QTabBar::RoundedEast);
    this->m_tabOrientation = IndigoTabBar::East;
    this->setFocusPolicy(Qt::NoFocus);
    this->setIconSize(QSize(int_iconScale,int_iconScale));
    this->setExpanding(false);
    this->setDrawBase(false);
    this->setUsesScrollButtons(true);
    this->setSelectionBehaviorOnRemove(QTabBar::SelectPreviousTab);
    this->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding));


}



void IndigoTabBar::mousePressEvent(QMouseEvent*event){

    QTabBar::mousePressEvent(event);
    int_oldIndex = this->currentIndex();
}



void IndigoTabBar::mouseReleaseEvent(QMouseEvent*event){

    int_newIndex = this->currentIndex();

    QTabBar::mouseReleaseEvent(event);

    if(int_newIndex != int_oldIndex)
        emit tabMoved(int_oldIndex, int_newIndex);



}



void IndigoTabBar::paintEvent(QPaintEvent *event)
{
    QTabBar::paintEvent(event);

   /* QStylePainter p(this);

    for(int i = 0; i < this->count(); ++i)
    {


        QStyleOptionTabV3 tab;
        initStyleOption(&tab, i);

        if (!(tab.state & QStyle::State_Enabled)) {
            tab.palette.setCurrentColorGroup(QPalette::Disabled);
            QRect tabRect(tab.rect.x(), tab.rect.y(), 0,0);
            p.drawRect(tabRect);
            continue;
        }


        //p.drawControl(QStyle::CE_TabBarTab, tab);

        //p.drawItemPixmap(tab.rect, 0, tab.icon.pixmap(int_iconScale,int_iconScale));
    }
*/


}



void IndigoTabBar::addTab(QIcon icon, int index){

    if(index == -1){
        icon = rotateIcon(icon);
        QTabBar::addTab(icon, "");
    }else insertTab(index, icon);

}



void IndigoTabBar::insertTab(int index, QIcon &icon){

    icon = rotateIcon(icon);

    QTabBar::insertTab(index, icon, "");
}



void IndigoTabBar::removeTab(int index){
    QTabBar::removeTab(index);
}



void IndigoTabBar::hideTab(int index){

    this->setTabEnabled(index,false);    
    //this->resize(this->sizeHint());

}


void IndigoTabBar::showTab(int index){

    this->setTabEnabled(index,true);
    //this->resize(this->sizeHint());

}


IndigoTabBar::Orientation IndigoTabBar::tabPosition(){
    return m_tabOrientation;
}



void IndigoTabBar::setTabPosition(Orientation tabOrientation){


    // Rotate icons in right direction
    for(int i=0;i<this->count();i++)
    {
        QIcon icon = this->tabIcon(i);

        icon = rotateIcon(icon, tabOrientation);

        this->setTabIcon(i, icon);

    }

    m_tabOrientation = tabOrientation;

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

