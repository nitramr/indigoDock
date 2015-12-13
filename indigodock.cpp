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

    m_toolbar = new  IndigoTabBar;

    m_dropzone = new IndigoDropZone; 

    m_scrollArea = new QScrollArea;
    m_scrollArea->setStyleSheet( styleSheetScroll);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setWidget(m_dropzone);
   // m_scrollArea->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));

    m_layout->addStretch(1);
    m_layout->addWidget(m_scrollArea);
    m_layout->addWidget(m_toolbar);

    //layout->setSizeConstraint(QLayout::SetFixedSize);

    //setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding));

    setLayout(m_layout);



    // watch active tab change event
    connect(m_toolbar, SIGNAL(moveTab()), this, SLOT(movePanel()));
    connect(m_dropzone, SIGNAL(resize()), this, SLOT(updateSize()));


}



void IndigoDock::addIndigoPanel(IndigoPanel *panel, int tabIndex){

    addPanel(panel, tabIndex);

    this->connect(panel, SIGNAL(mouseReleased()), m_dropzone, SLOT(dropPanel()));
    this->connect(panel, SIGNAL(mouseMove(int)), m_dropzone, SLOT(hoverZone(int)));
    this->connect(panel, SIGNAL(isFloating(int)), this, SLOT(removePanel(int)));
    this->connect(panel, SIGNAL(isDock()), this, SLOT(redockPanel()));
}



void IndigoDock::movePanel(){

    int oldIndex = m_toolbar->oldTabIndex();
    int newIndex = m_toolbar->newTabIndex();

    qDebug() << "TabIndexOld:" << oldIndex << "TabIndexNew:" << newIndex << endl;


    IndigoPanel * pan = m_panelList.takeAt(oldIndex);
    m_panelList.insert(newIndex, pan);
    updatePanels();

    m_dropzone->movePanel(newIndex, pan->objectName());


}



void IndigoDock::addPanel(IndigoPanel * panel, int index){

    if(index == -1){
        m_panelList.append(panel);
    }else m_panelList.insert(index, panel);

    m_dropzone->addPanel(panel, index);

    QIcon icon = panel->Icon();

    if(index == -1){
        m_toolbar->addTab(icon);
    }else m_toolbar->insertTab(index, icon);

    updatePanels();
}



void IndigoDock::removePanel(int index){
     m_panelList.removeAt(index);
     m_toolbar->removeTab(index);
     updatePanels();
}



void IndigoDock::redockPanel(){
    IndigoPanel *pan = qobject_cast<IndigoPanel *>(sender());
    if (!pan) return;

    addPanel(pan);
}



void IndigoDock::updatePanels(){

    // update panel index
    for( int i=0; i<m_panelList.count(); ++i )
    {
        m_panelList.at(i)->setIndex(i);
    }

}

void IndigoDock::updateSize(){
    m_scrollArea->setFixedWidth(m_dropzone->width());
}



void IndigoDock::updateTabPosition(Qt::DockWidgetArea area){

        switch(area){
        case Qt::LeftDockWidgetArea:{
            m_toolbar->setTabPosition(IndigoTabBar::West);

            break;
        }
        case Qt::RightDockWidgetArea:{
             m_toolbar->setTabPosition(IndigoTabBar::East);
            break;
        }
        default:

            break;

        }

}




