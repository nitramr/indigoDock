#include "indigodock.h"

IndigoDock::IndigoDock(QWidget *parent) : QWidget(parent)
{
    init();

}

void IndigoDock::init(){

    // Setup Tabbar
    m_indigoTab = new IndigoTabbar;
    m_indigoTab->setTabPosition(IndigoTabbar::East);
    m_indigoTab->setMovable(true);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setSpacing(0);
    layout->setMargin(0);
    setLayout(layout);


    layout->addWidget(m_indigoTab);



}

void IndigoDock::addIndigoPanel(IndigoPanel *panel, int tabIndex){

    m_indigoTab->addIndigoPanel(panel, tabIndex );


    // Add some invalid content to test exceptions
    QWidget * widget = new QWidget();
    m_indigoTab->addTab(widget,QIcon(":/icons/icons/open.png") ,"");


}

void IndigoDock::updateTabWidget(Qt::DockWidgetArea area){

        switch(area){
        case Qt::LeftDockWidgetArea:{
            m_indigoTab->setTabPosition(IndigoTabbar::West);
            break;
        }
        case Qt::RightDockWidgetArea:{
             m_indigoTab->setTabPosition(IndigoTabbar::East);
            break;
        }
        default:

            break;

        }

}


