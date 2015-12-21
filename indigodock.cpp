#include "indigodock.h"


IndigoDock::IndigoDock(QWidget *parent) : QWidget(parent)
{


    QString styleSheetScroll( "QScrollArea {"
                                "border: 0px solid transparent;"
                            "}"
            );


    m_layout = new QHBoxLayout();
    m_layout->setSpacing(0);
    m_layout->setMargin(0);
    m_layout->setAlignment(Qt::AlignRight);

    m_toolbar = new  IndigoTabBar;

    m_dropzone = new IndigoDropZone;

    m_scrollArea = new QScrollArea;
    m_scrollArea->setStyleSheet( styleSheetScroll);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setWidget(m_dropzone);

   // m_layout->addStretch(1);
    m_layout->addWidget(m_scrollArea);
    m_layout->addWidget(m_toolbar);

    setLayout(m_layout);

    // watch active tab change event
    connect(m_toolbar, SIGNAL(moveTab(int,int)), this, SLOT(movePanel(int,int)));
    connect(m_dropzone, SIGNAL(resize()), this, SLOT(updateSize()));
    connect(m_dropzone, SIGNAL(panelRemoved(int)), this, SLOT(removeTab(int)));
    connect(m_dropzone, SIGNAL(panelAdded(QIcon,int)), this, SLOT(addTab(QIcon,int)));

}



void IndigoDock::addIndigoPanel(IndigoPanel *panel, int tabIndex){

    addPanel(panel, tabIndex);

    this->connect(panel, SIGNAL(mouseReleased()), m_dropzone, SLOT(dropPanel()));
    this->connect(panel, SIGNAL(mouseMove(int)), m_dropzone, SLOT(hoverZone(int)));
    this->connect(panel, SIGNAL(isFloating(int)), m_dropzone, SLOT(removePanel(int)));

}



void IndigoDock::movePanel(int oldIndex, int newIndex){

    m_dropzone->movePanel(oldIndex, newIndex);

}



void IndigoDock::addPanel(IndigoPanel * panel, int index){

    m_dropzone->addPanel(panel, index);

}



void IndigoDock::removeTab(int index){

     m_toolbar->removeTab(index);

}



void IndigoDock::addTab(QIcon icon, int index){

    if(index == -1){
        m_toolbar->addTab(icon);
    }else m_toolbar->insertTab(index, icon);
}



void IndigoDock::updateSize(){
    m_scrollArea->setFixedWidth(m_dropzone->width());
}



void IndigoDock::updateTabPosition(Qt::DockWidgetArea area){

    switch(area){
    case Qt::LeftDockWidgetArea:{
        if(m_toolbar->tabPosition() == IndigoTabBar::East){
            IndigoTabBar *tab = static_cast<IndigoTabBar*>(m_layout->takeAt(1)->widget());

            m_toolbar->setTabPosition(IndigoTabBar::West);
            m_layout->setAlignment(Qt::AlignLeft);
            m_layout->insertWidget(0, tab);
        }
        break;
    }
    case Qt::RightDockWidgetArea:{
        if(m_toolbar->tabPosition() == IndigoTabBar::West){
            IndigoTabBar *tab = static_cast<IndigoTabBar*>(m_layout->takeAt(0)->widget());
            m_toolbar->setTabPosition(IndigoTabBar::East);
            m_layout->setAlignment(Qt::AlignRight);
            m_layout->insertWidget(1,tab);
        }
        break;
    }
    default:

        break;

    }

}




