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
    dropZoneInitHeight = m_dropzone->height();

    m_scrollArea = new QScrollArea;
    m_scrollArea->setStyleSheet( styleSheetScroll);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setWidget(m_dropzone);
    m_scrollArea->setMinimumWidth(m_dropzone->minimumWidth() + 20); //scrollbar fix
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_layout->addWidget(m_scrollArea);
    m_layout->addWidget(m_toolbar);

    setLayout(m_layout);

    // watch active tab change event
    connect(m_toolbar, SIGNAL(tabMoved(int,int)), m_dropzone, SLOT(movePanel(int,int)));
    connect(m_toolbar, SIGNAL(scrollToPanel(int)), this, SLOT(scrollToPanel(int)));
    connect(m_dropzone, SIGNAL(panelRemoved(int)), m_toolbar, SLOT(removeTab(int)));
    connect(m_dropzone, SIGNAL(panelAdded(QIcon,int)), m_toolbar, SLOT(insertTab(QIcon, int)));
    connect(m_dropzone, SIGNAL(contentResize()), this, SLOT(resizeScrollPanel()));

}



void IndigoDock::addIndigoPanel(IndigoPanel *panel, int tabIndex){

    m_dropzone->addPanel(panel, tabIndex);

    this->connect(panel, SIGNAL(mouseReleased()), m_dropzone, SLOT(dropPanel()));
    this->connect(panel, SIGNAL(mouseMove()), m_dropzone, SLOT(hoverZone()));
    this->connect(panel, SIGNAL(isFloating(int)), m_dropzone, SLOT(removePanel(int)));
    this->connect(panel, SIGNAL(panelClosed(int)), m_toolbar, SLOT(hideTab(int)));
    this->connect(panel, SIGNAL(panelShown(int)), m_toolbar, SLOT(showTab(int)));

}


QList<IndigoPanel*> IndigoDock::getPanelList(){

    return m_dropzone->PanelList;

}


void IndigoDock::scrollToPanel(int PanelIndex){

    QRect panRect = m_dropzone->getPanelRect(PanelIndex);

    // m_scrollArea->verticalScrollBar()->setValue(panRect.y());

    QPropertyAnimation *animation = new QPropertyAnimation(m_scrollArea->verticalScrollBar(), "value");
    animation->setDuration(100);
    animation->setStartValue(m_scrollArea->verticalScrollBar()->value());
    animation->setEndValue(panRect.y());
    animation->start();

}


void IndigoDock::scrollToPanel(QString PanelName){

    QList<IndigoPanel*> PanelList = getPanelList();

    for( int i=0; i<PanelList.size(); ++i )
    {
        if(PanelList.at(i)->dockState() == IndigoPanel::Docked || PanelList.at(i)->dockState() == IndigoPanel::HiddenDocked){

            if(PanelList.at(i)->objectName() == PanelName){

                this->scrollToPanel(i);
            }
        }
    }


}


void IndigoDock::resizeScrollPanel(){
    // Update DropZone height

    int dzHeight = m_dropzone->minHeight;
    int dzPanel = m_dropzone->lastPanelHeight;
    int spacer = m_scrollArea->height() - dzPanel;

    if(dzHeight < dzPanel) dzHeight = dzPanel;

    m_dropzone->setFixedHeight(dzHeight + spacer);
}


void IndigoDock::resizeEvent(QResizeEvent *e){

  Q_UNUSED(e)
  resizeScrollPanel();
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




