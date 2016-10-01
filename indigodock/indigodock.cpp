/*******************************************************
 *
 * Copyright (C) 2016  Martin Reininger
 *
 * This file is part of IndigoDock.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 *******************************************************/


#include "indigodock.h"


IndigoDock::IndigoDock(QWidget *parent) : QDockWidget(parent)
{


    QString styleSheetScroll( "QScrollArea {"
                              "border: 0px solid transparent;"
                              "}"
                              );

    int_padding = 2;
    int_placeholderHeight = int_padding;
    int_minPanelHeight = 50;
    int_minPanelWidth = 100;
    int_minHeight = int_minPanelHeight + 2*int_padding;
    int_minWidth = int_minPanelWidth + 2*int_padding;
    int_scrollSpeed = 150; // milliseconds
    bool_singleMode = false;


    wdg_toolbar = new IndigoTabBar;


    wdg_placeholder = new QWidget();
    wdg_placeholder->setAutoFillBackground( true );
    wdg_placeholder->setBackgroundRole(QPalette::Highlight);


    lyt_dropzone = new QBoxLayout(QBoxLayout::TopToBottom);
    lyt_dropzone->setContentsMargins(int_padding, int_padding, int_padding, int_padding);
    lyt_dropzone->setSpacing(int_padding);
    lyt_dropzone->addStretch(1);


    wdg_dropzone = new QWidget();
    wdg_dropzone->setLayout(lyt_dropzone);
    wdg_dropzone->setMinimumWidth(int_minWidth);
    wdg_dropzone->setMinimumHeight(int_minHeight);
    wdg_dropzone->setBackgroundRole(QPalette::Base);


    wdg_scrollArea_dz = new QScrollArea;
    wdg_scrollArea_dz->setStyleSheet( styleSheetScroll);
    wdg_scrollArea_dz->setWidgetResizable(true);
    wdg_scrollArea_dz->setWidget(wdg_dropzone);
    wdg_scrollArea_dz->setMinimumWidth(wdg_dropzone->minimumWidth() + 20); //scrollbar fix
    wdg_scrollArea_dz->setMinimumHeight(wdg_dropzone->minimumHeight() + 20); //scrollbar fix


    wdg_scrollArea_tb = new QScrollArea;
    wdg_scrollArea_tb->setStyleSheet( styleSheetScroll);
    wdg_scrollArea_tb->setWidgetResizable(true);
    wdg_scrollArea_tb->setWidget(wdg_toolbar);
    wdg_scrollArea_tb->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    wdg_scrollArea_tb->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    wdg_scrollArea_tb->setBackgroundRole(QPalette::Base);


    wdg_mainSplitter = new QSplitter();
    wdg_mainSplitter->setOrientation(Qt::Horizontal);
    wdg_mainSplitter->setHandleWidth(0);
    wdg_mainSplitter->addWidget(wdg_scrollArea_dz);
    wdg_mainSplitter->addWidget(wdg_scrollArea_tb);


    setWidget(wdg_mainSplitter);
    setMouseTracking(true);
    setAutoFillBackground( true );
    setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));
    setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea | Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
    setAccessibleName("IndigoDock");
    setObjectName("IndigoDock");


    connect(this, SIGNAL(dockLocationChanged(Qt::DockWidgetArea)), this, SLOT(updateTabPosition(Qt::DockWidgetArea)));
    connect(wdg_toolbar, SIGNAL(tabMoved(int,int)), this, SLOT(movePanel(int,int)));
    connect(wdg_toolbar, SIGNAL(tabClicked(int)), this, SLOT(scrollToPanel(int)));

}



void IndigoDock::hideTab(int index){
    wdg_toolbar->hideTab(index);
}



void IndigoDock::showTab(int index){
    wdg_toolbar->showTab(index);
}



void IndigoDock::addWidget(QWidget *widget){

    insertWidget(-1,widget);

}



void IndigoDock::insertWidget(int index, QWidget *widget){

    int count = lyt_dropzone->count();

    if(count > 0){

        if(index < 0 || index > count -1) index = count -1;

        lyt_dropzone->insertWidget(index, widget); // index fix because stretch element as last object
    }else{
        lyt_dropzone->addWidget(widget); // should never happen because of spacer widget
    }

}


/**
 * Add Panel in Splitter
 * @brief Indigo2DropZone::addPanel
 * @param panel
 */
void IndigoDock::addIndigoPanel (IndigoPanel *panel, IndigoPanel::IndigoDockState dockState, int tabIndex){

    // add panel to PanelList
    if(tabIndex == -1){
        lst_PanelList.append(panel);
    }else lst_PanelList.insert(tabIndex, panel);


    // add panel to DropZone
    insertWidget(tabIndex, panel);


    // Panel settings
    if(dockState == IndigoPanel::Docked || dockState == IndigoPanel::HiddenDocked){
        panel->setDockState(dockState);
    }else panel->setDockState(IndigoPanel::Docked);

    panel->installEventFilter(this);
    panel->setOrientation(m_orientation);
    // panel->setMinimumSize(QSize(int_minPanelWidth, int_minPanelHeight));


    updatePanels();

    wdg_toolbar->insertTab(panel->Icon(), panel->Index(), panel->Caption());

}



void IndigoDock::removePanel(int index){

    lst_PanelList.removeAt(index);

    updatePanels();
    wdg_toolbar->removeTab(index);
}



void IndigoDock::updatePanels(){


    int i = 0;

    IndigoPanel * panel;
    foreach(panel, lst_PanelList){

        if(panel->dockState() == IndigoPanel::Docked || panel->dockState() == IndigoPanel::HiddenDocked){

            panel->setIndex(i);
        }

          i++;
    }

    // toggle single mode
    toggleSingleMode();

    // Calculate spacer
    updateMinHeight();

}



void IndigoDock::updateMinHeight(){


    int i = 0;
    int int_hiddenPanels = 0;
    int lastPanelSize = 0;
    int totalPanelSize = 0;


    IndigoPanel * panel;
    foreach(panel, lst_PanelList){

        switch(panel->dockState()){

        case IndigoPanel::Docked:{

            switch(m_orientation){
            case Qt::Vertical:
                lastPanelSize = panel->height() + int_padding;
                totalPanelSize += panel->height() + int_padding;
                break;
            case Qt::Horizontal:
                lastPanelSize = panel->width() + int_padding;
                totalPanelSize += panel->width() + int_padding;
                break;
            }

            break;
        }

        default:{
           int_hiddenPanels ++;
            break;
        }

        }

          i++;
    }


    // hide dock if all panels are hidden
    if(int_hiddenPanels == lst_PanelList.size()){

        qDebug() << "Hide Dock" << endl;
       // hide();

    }else{


        int minSize = 0;
        int spacer = 0;

        switch(m_orientation){
        case Qt::Vertical:

            minSize = totalPanelSize;
            spacer = wdg_scrollArea_dz->height() - lastPanelSize;

            if(spacer < 0) spacer = 0;

            // set fixed height based on content
            wdg_dropzone->setMaximumWidth(QWIDGETSIZE_MAX);
            wdg_dropzone->setFixedHeight(minSize + spacer);

            break;
        case Qt::Horizontal:

            minSize = totalPanelSize;
            spacer = wdg_scrollArea_dz->width() - lastPanelSize;

            if(spacer < 0) spacer = 0;

            // set fixed width based on content
            wdg_dropzone->setFixedWidth(minSize + spacer);
            wdg_dropzone->setMaximumHeight(QWIDGETSIZE_MAX);


            break;
        }

        // reset size limit
        setMaximumSize(QSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX));

        update();
    }
}



void IndigoDock::toggleSingleMode(){



    // Switch single panel mode
    if(lst_PanelList.size() <= 1){

        bool_singleMode = true;
        wdg_scrollArea_tb->hide();

    }else{

        bool_singleMode = false;
        wdg_scrollArea_tb->show();     

    }

    emit singleMode(bool_singleMode);
    qDebug() << "emit: Dock singleMode" << bool_singleMode << endl;


}



void IndigoDock::movePanel(int oldIndex, int newIndex){

    // Take out
    IndigoPanel * pan = lst_PanelList.takeAt(oldIndex);
    pan->setParent(this);

    // Put in
    lst_PanelList.insert(newIndex, pan);
    insertWidget(newIndex, pan);

    // update panels
    updatePanels();
}



void IndigoDock::scrollToPanel(int PanelIndex){

    IndigoPanel *panel = lst_PanelList.at(PanelIndex);

    if (!panel) return;

    panel->show();

    updateMinHeight();

    this->show();

    int offset = int_padding;
    QPoint panPos = wdg_dropzone->mapFromGlobal(panel->mapToGlobal( QPoint( 0, 0 ) ));
    QPropertyAnimation *animation;

    switch(m_orientation){
    case Qt::Horizontal:
        animation = new QPropertyAnimation(wdg_scrollArea_dz->horizontalScrollBar(), "value");
        animation->setDuration(int_scrollSpeed);
        animation->setStartValue(wdg_scrollArea_dz->horizontalScrollBar()->value());
        animation->setEndValue(panPos.x() - offset);
        animation->start();
        break;
    case Qt::Vertical:
        animation = new QPropertyAnimation(wdg_scrollArea_dz->verticalScrollBar(), "value");
        animation->setDuration(int_scrollSpeed);
        animation->setStartValue(wdg_scrollArea_dz->verticalScrollBar()->value());
        animation->setEndValue(panPos.y() - offset);
        animation->start();
        break;
    default:

        qDebug() << "IndigoDock::scrollToPanel() supports only horizontal / vertical orientation" << endl;

        break;
    }

}



void IndigoDock::scrollToPanel(QString PanelName){

    IndigoPanel * panel;
    foreach(panel, lst_PanelList){

       if(panel->dockState() == IndigoPanel::Docked || panel->dockState() == IndigoPanel::HiddenDocked){
           if(panel->objectName() == PanelName){

               this->scrollToPanel(panel->Index());
               return;
           }
       }
    }

}



void IndigoDock::addPlaceholder (int index){


    switch(m_orientation){
    case Qt::Vertical:
        wdg_placeholder->setFixedHeight(int_placeholderHeight);
        wdg_placeholder->setMaximumWidth(QWIDGETSIZE_MAX);
        break;
    case Qt::Horizontal:
        wdg_placeholder->setMaximumHeight(QWIDGETSIZE_MAX);
        wdg_placeholder->setFixedWidth(int_placeholderHeight);
        break;
    }

    if(index == -1) index = lyt_dropzone->count()-2;

    insertWidget(index, wdg_placeholder);

    wdg_placeholder->show();

}



void IndigoDock::removePlaceholder (){

    wdg_placeholder->setParent(this);
    wdg_placeholder->hide();

}



void IndigoDock::updateTabPosition(Qt::DockWidgetArea area){

    qDebug() << "updateTabPosition()" << area <<  this->accessibleName() << this << endl;

    switch(area){
    case Qt::LeftDockWidgetArea:{

        m_orientation = Qt::Vertical;

        calculateSize();

        wdg_mainSplitter->setOrientation(Qt::Horizontal);
        wdg_mainSplitter->addWidget(wdg_scrollArea_tb);
        wdg_mainSplitter->addWidget(wdg_scrollArea_dz);

        break;
    }
    case Qt::RightDockWidgetArea:{

        m_orientation = Qt::Vertical;

        calculateSize();

        wdg_mainSplitter->setOrientation(Qt::Horizontal);
        wdg_mainSplitter->addWidget(wdg_scrollArea_dz);
        wdg_mainSplitter->addWidget(wdg_scrollArea_tb);


        break;
    }
    case Qt::TopDockWidgetArea:{

        m_orientation = Qt::Horizontal;

        calculateSize();

        wdg_mainSplitter->setOrientation(Qt::Vertical);
        wdg_mainSplitter->addWidget(wdg_scrollArea_tb);
        wdg_mainSplitter->addWidget(wdg_scrollArea_dz);


        break;
    }
    case Qt::BottomDockWidgetArea:{

        m_orientation = Qt::Horizontal;

        calculateSize();

        wdg_mainSplitter->setOrientation(Qt::Vertical);
        wdg_mainSplitter->addWidget(wdg_scrollArea_dz);
        wdg_mainSplitter->addWidget(wdg_scrollArea_tb);


        break;
    }
    default:

        break;

    }

    // toggle single mode
    toggleSingleMode();

}



void IndigoDock::calculateSize(){

    switch (m_orientation){

    case Qt::Vertical:

        setFeatures(DockWidgetClosable|DockWidgetMovable|DockWidgetFloatable);

        // Toolbar
        wdg_toolbar->setTabOrientation(m_orientation);

        // Toolbar ScrollArea
        wdg_scrollArea_tb->setMinimumSize(QSize(wdg_toolbar->width(), wdg_toolbar->width()));
        wdg_scrollArea_tb->setMaximumSize(wdg_toolbar->maximumSize());

        lyt_dropzone->setDirection(QBoxLayout::TopToBottom);

        wdg_scrollArea_dz->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        wdg_scrollArea_dz->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        break;

    case Qt::Horizontal:

        setFeatures(DockWidgetVerticalTitleBar|DockWidgetClosable|DockWidgetMovable|DockWidgetFloatable);

        // Toolbar
        wdg_toolbar->setTabOrientation(m_orientation);

        // Toolbar ScrollArea
        wdg_scrollArea_tb->setMinimumSize(QSize(wdg_toolbar->height(), wdg_toolbar->height()));
        wdg_scrollArea_tb->setMaximumSize(wdg_toolbar->maximumSize());

        lyt_dropzone->setDirection(QBoxLayout::LeftToRight);

        wdg_scrollArea_dz->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        wdg_scrollArea_dz->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        break;

    default:
        break;


    }


    foreach(IndigoPanel *pan, lst_PanelList)
    {
        pan->setOrientation(m_orientation);
    }

    // qDebug() << "Toolbar Size: Height" << wdg_toolbar->height() << "Width" << wdg_toolbar->width() << "MaxSize"<< wdg_toolbar->maximumSize()<< endl;

    wdg_dropzone->setMinimumWidth(int_minWidth);
    wdg_dropzone->setMinimumHeight(int_minHeight);

}



void IndigoDock::hoverDock(IndigoPanel * pan){

    if (!pan || isHidden()) return;

    QPoint cursor = this->mapFromGlobal(QCursor::pos());

    if (wdg_dropzone->rect().contains(cursor) ) {

            int index = -1;


            IndigoPanel * panel;
            foreach(panel, lst_PanelList )
            {

                if(panel->dockState() == IndigoPanel::Docked || panel->dockState() == IndigoPanel::HiddenDocked){

                    // calculate IndigoPanel position on DropZone
                    QPoint childPosBegin = this->mapFromGlobal(panel->mapToGlobal( QPoint( 0, 0 ) ));

                    QRect panRect = QRect(childPosBegin, QPoint(childPosBegin.x() + panel->width(), childPosBegin.y()+panel->height()+2*int_padding + int_placeholderHeight));


                    // Check if mouse is over an IndigoPanel and get Index
                    if (panRect.contains(cursor) ) {

                        index = panel->Index();

                    }
                }
            }


            //set Panel Index of floating panel
            pan->setIndex(index);

            this->addPlaceholder(index);

    }else{
        this->removePlaceholder();
    }


}



void IndigoDock::dropPanel(IndigoPanel *panel){

    if (!panel || isHidden()) return;

    QPoint cursor = this->mapFromGlobal(QCursor::pos());

    if (wdg_dropzone->rect().contains(cursor) ) {

        this->removePlaceholder();

        addIndigoPanel(panel, IndigoPanel::Docked, panel->Index());

    }
}



void IndigoDock::clear(){

    lst_PanelList.clear();
    wdg_toolbar->clear();

    while ( IndigoPanel* pan = findChild<IndigoPanel*>() )
        pan->setParent(0);

}



void IndigoDock::updatePanelSize(){

    IndigoPanel * panel;
    foreach(panel, lst_PanelList){
        qDebug() << "Panel SizeHintHeight" << panel->sizeHint().height() << endl;

        panel->setMinimumSize(int_minPanelWidth, int_minPanelHeight);
    }

}


/**********************
 *
 * Events
 *
 * *******************/


void IndigoDock::resizeEvent(QResizeEvent *e){

    QWidget::resizeEvent(e);
    updateMinHeight();

}



bool IndigoDock::eventFilter(QObject *object, QEvent *event)
{

    switch( event->type() )
    {
    case QEvent::Hide:
    case QEvent::Resize:
    {
        updateMinHeight();
        break;
    }

    default:
        break;
    }


    return QWidget::eventFilter(object, event);
}


/**********************
 *
 * Properties
 *
 * *******************/


QList<IndigoPanel*> IndigoDock::getPanels(){
    return lst_PanelList;

}



Qt::Orientation IndigoDock::Orientation(){

    return m_orientation;

}



void IndigoDock::setMinimumPanelHeight(int height){

    int_minPanelHeight = height;
    int_minHeight = int_minPanelHeight + 2*int_padding;


    wdg_dropzone->setMinimumHeight(int_minHeight);
    wdg_scrollArea_dz->setMinimumHeight(wdg_dropzone->minimumHeight() + 20); //scrollbar fix

}



void IndigoDock::setMinimumPanelWidth(int width){

    int_minPanelWidth = width;
    int_minWidth = int_minPanelWidth + 2*int_padding;

    wdg_dropzone->setMinimumWidth(int_minWidth);
    wdg_scrollArea_dz->setMinimumWidth(wdg_dropzone->minimumWidth() + 20); //scrollbar fix

}



void IndigoDock::setMinimumPanelSize(QSize size){

    setMinimumPanelWidth(size.width());
    setMinimumPanelHeight(size.height());

}



QSize IndigoDock::minimumPanelSize(){

   return QSize(int_minPanelWidth, int_minPanelHeight);

}



void IndigoDock::setMovableTabs(bool allow){

    wdg_toolbar->setMovableTabs(allow);

}



bool IndigoDock::movableTabs(){

    return wdg_toolbar->movableTabs();

}



void IndigoDock::setPanelPadding(int padding){

    int_padding = padding;

    lyt_dropzone->setSpacing(int_padding);
    lyt_dropzone->setContentsMargins(int_padding, int_padding, int_padding, int_padding);

}



int IndigoDock::panelPadding(){

    return int_padding;

}
