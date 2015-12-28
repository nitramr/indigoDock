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

    m_layout->addWidget(m_scrollArea);
    m_layout->addWidget(m_toolbar);

    setLayout(m_layout);

    PanelList = m_dropzone->PanelList;

    // watch active tab change event
    connect(m_toolbar, SIGNAL(tabMoved(int,int)), m_dropzone, SLOT(movePanel(int,int)));
    connect(m_dropzone, SIGNAL(resize()), this, SLOT(updateSize()));
    connect(m_dropzone, SIGNAL(panelRemoved(int)), m_toolbar, SLOT(removeTab(int)));
    connect(m_dropzone, SIGNAL(panelAdded(QIcon,int)), m_toolbar, SLOT(insertTab(QIcon, int)));

}



void IndigoDock::addIndigoPanel(IndigoPanel *panel, int tabIndex){

    m_dropzone->addPanel(panel, tabIndex);

    this->connect(panel, SIGNAL(mouseReleased()), m_dropzone, SLOT(dropPanel()));
    this->connect(panel, SIGNAL(mouseMove()), m_dropzone, SLOT(hoverZone()));
    this->connect(panel, SIGNAL(isFloating(int)), m_dropzone, SLOT(removePanel(int)));
    this->connect(panel, SIGNAL(panelClosed(int)), m_toolbar, SLOT(hideTab(int)));
    this->connect(panel, SIGNAL(panelShown(int)), m_toolbar, SLOT(showTab(int)));

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




