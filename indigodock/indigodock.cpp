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


    int_toolBarIndex = 0; // index of toolbar container in splitter -- unsed
    int_padding = 2;
    int_placeholderHeight = int_padding;
    int_minPanelHeight = 50;
    int_minPanelWidth = 100;
    int_minHeight = int_minPanelHeight + 2*int_padding;
    int_minWidth = int_minPanelWidth + 2*int_padding;



    wdg_toolbar = new IndigoTabBar;


    wdg_placeholder = new QWidget();
    wdg_placeholder->setAutoFillBackground( true );
    wdg_placeholder->setBackgroundRole(QPalette::Highlight);


    wdg_panelSplitter = new QSplitter();
    wdg_panelSplitter->setHandleWidth(int_padding);
    wdg_panelSplitter->setOrientation(Qt::Vertical);
    wdg_panelSplitter->installEventFilter(this);


    lyt_dropzone = new QBoxLayout(QBoxLayout::TopToBottom);
    lyt_dropzone->setMargin(int_padding);
    lyt_dropzone->setSpacing(0);
    lyt_dropzone->addWidget(wdg_panelSplitter);
    lyt_dropzone->addStretch(1);


    wdg_dropzone = new QWidget();
    wdg_dropzone->setLayout(lyt_dropzone);
    wdg_dropzone->setMinimumWidth(int_minWidth);
    wdg_dropzone->setMinimumHeight(int_minHeight);
    wdg_dropzone->setBackgroundRole(QPalette::Base);
   // wdg_dropzone->setBackgroundRole(QPalette::Highlight); // control color


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


QList<IndigoPanel*> IndigoDock::getPanels(){
    return lst_PanelList;

}



void IndigoDock::hideTab(int index){
    wdg_toolbar->hideTab(index);
}



void IndigoDock::showTab(int index){
    wdg_toolbar->showTab(index);
}



/**
 * Add Panel in Splitter
 * @brief Indigo2DropZone::addPanel
 * @param panel
 */
void IndigoDock::addIndigoPanel (IndigoPanel *panel, int tabIndex){

    // add panel to PanelList
    if(tabIndex == -1){
        lst_PanelList.append(panel);
    }else lst_PanelList.insert(tabIndex, panel);


    // add panel to DropZone
    if(tabIndex == -1){
        wdg_panelSplitter->addWidget(panel);
        wdg_panelSplitter->setCollapsible(wdg_panelSplitter->count()-1, false);

    }else{
        wdg_panelSplitter->insertWidget(tabIndex, panel);
        wdg_panelSplitter->setCollapsible(tabIndex, false);
    }


    panel->setDockState(IndigoPanel::Docked);
   // panel->setMinimumSize(QSize(int_minPanelWidth, int_minPanelHeight));

    updatePanels();

    wdg_toolbar->insertTab(panel->Icon(), panel->Index(), panel->Caption());

}



void IndigoDock::updatePanels(){

    // update panel index
    for( int i=0; i<lst_PanelList.count(); ++i )
    {

        if(lst_PanelList.at(i)->dockState() == IndigoPanel::Docked || lst_PanelList.at(i)->dockState() == IndigoPanel::HiddenDocked){
            lst_PanelList.at(i)->setIndex(i);
        }

    }

    updateMinHeight();
}



void IndigoDock::removePanel(int index){

    lst_PanelList.removeAt(index);
    wdg_toolbar->removeTab(index);
    updatePanels();

    // destroy Dock if empty
    if(lst_PanelList.size() == 0){

        emit dockDestroyed(); // remove dock from list in manager only
        qDebug() << "emit: dockDestroyed();" << endl;
        this->setParent(NULL);
        this->destroy();
       // this->close();
    }
}



void IndigoDock::movePanel(int oldIndex, int newIndex){

    // Take out
    IndigoPanel * pan = lst_PanelList.takeAt(oldIndex);
    pan->setParent(this);

    // Put in
    lst_PanelList.insert(newIndex, pan);
    wdg_panelSplitter->insertWidget(newIndex, pan);

    // update panels
    updatePanels();
}



void IndigoDock::scrollToPanel(int PanelIndex){

    IndigoPanel *panel = lst_PanelList.at(PanelIndex);

    if (!panel) return;

    this->show();

    updateMinHeight();


    int offset = int_padding;

    QPoint panPos = wdg_dropzone->mapFromGlobal(panel->mapToGlobal( QPoint( 0, 0 ) ));

    QPropertyAnimation *animation;

    switch(m_orientation){
    case Qt::Horizontal:
        animation = new QPropertyAnimation(wdg_scrollArea_dz->horizontalScrollBar(), "value");
        animation->setDuration(100);
        animation->setStartValue(wdg_scrollArea_dz->horizontalScrollBar()->value());
        animation->setEndValue(panPos.x() - offset);
        animation->start();
        break;
    case Qt::Vertical:
        animation = new QPropertyAnimation(wdg_scrollArea_dz->verticalScrollBar(), "value");
        animation->setDuration(100);
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

    for( int i=0; i<lst_PanelList.size(); ++i )
    {
        if(lst_PanelList.at(i)->dockState() == IndigoPanel::Docked || lst_PanelList.at(i)->dockState() == IndigoPanel::HiddenDocked){

            if(lst_PanelList.at(i)->objectName() == PanelName){

                this->scrollToPanel(i);
                return;
            }
        }
    }
}



void IndigoDock::updateMinHeight(){

    int lastPanelDimension = 0;
    int allPanelDimension = 0;
    int countHiddenPanels = 0;


    // get height of last visible Panel
    for( int i=0; i<lst_PanelList.size(); ++i )
    {

        switch(lst_PanelList.at(i)->dockState()){


        case IndigoPanel::Docked:{
            IndigoPanel * panel = lst_PanelList.at(i);

            switch(m_orientation){
            case Qt::Vertical:
                lastPanelDimension = panel->height();
                allPanelDimension += panel->height() + wdg_panelSplitter->handleWidth();
                break;
            case Qt::Horizontal:
                lastPanelDimension = panel->width();
                allPanelDimension += panel->width() + wdg_panelSplitter->handleWidth();
                break;
            }

            break;
        }
        default:{
            countHiddenPanels += 1;
            break;
        }

        }

    }


    // hide dock if all panels are hidden
    if(countHiddenPanels == lst_PanelList.size()){

        hide();

    }else{


        // hide tabbar if only one visible panel is inside
        if(lst_PanelList.size() <= 1){
            wdg_scrollArea_tb->hide();
        }else wdg_scrollArea_tb->show();



        int minDimension = 0;
        int spacer = 0;

        switch(m_orientation){
        case Qt::Vertical:

            minDimension = wdg_panelSplitter->height();
            spacer = wdg_scrollArea_dz->height() - lastPanelDimension;

            if(minDimension < lastPanelDimension) minDimension = lastPanelDimension;

            // set fixed height based on content
            wdg_dropzone->setMaximumWidth(QWIDGETSIZE_MAX);
            wdg_dropzone->setFixedHeight(minDimension + spacer);

            // reset size limit
            setMaximumSize(QSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX));

            break;
        case Qt::Horizontal:

            minDimension = wdg_panelSplitter->width();
            spacer = wdg_scrollArea_dz->width() - lastPanelDimension;

            if(minDimension < lastPanelDimension) minDimension = lastPanelDimension;

            // set fixed width based on content
            wdg_dropzone->setFixedWidth(minDimension + spacer);
            wdg_dropzone->setMaximumHeight(QWIDGETSIZE_MAX);

            // reset size limit
            setMaximumSize(QSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX));
            break;
        }

        wdg_scrollArea_dz->show();

        update();
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



    if(index == -1){
        wdg_panelSplitter->addWidget(wdg_placeholder);
        wdg_panelSplitter->setCollapsible(wdg_panelSplitter->count()-1, false);

    }else{
        wdg_panelSplitter->insertWidget(index, wdg_placeholder);
        wdg_panelSplitter->setCollapsible(index, false);
    }

}



void IndigoDock::removePlaceholder (){

    wdg_placeholder->setParent(this);

}



void IndigoDock::updateTabPosition(Qt::DockWidgetArea area){

    switch(area){
    case Qt::LeftDockWidgetArea:{

        m_orientation = Qt::Vertical;

        calculateSize();

        wdg_mainSplitter->setOrientation(Qt::Horizontal);
        wdg_mainSplitter->addWidget(wdg_scrollArea_tb);
        wdg_mainSplitter->addWidget(wdg_scrollArea_dz);

        int_toolBarIndex = 0;


        break;
    }
    case Qt::RightDockWidgetArea:{

        m_orientation = Qt::Vertical;

        calculateSize();

        wdg_mainSplitter->setOrientation(Qt::Horizontal);
        wdg_mainSplitter->addWidget(wdg_scrollArea_dz);
        wdg_mainSplitter->addWidget(wdg_scrollArea_tb);

        int_toolBarIndex = 1;

        break;
    }
    case Qt::TopDockWidgetArea:{

        m_orientation = Qt::Horizontal;

        calculateSize();

        wdg_mainSplitter->setOrientation(Qt::Vertical);
        wdg_mainSplitter->addWidget(wdg_scrollArea_tb);
        wdg_mainSplitter->addWidget(wdg_scrollArea_dz);


        int_toolBarIndex = 0;

        break;
    }
    case Qt::BottomDockWidgetArea:{

        m_orientation = Qt::Horizontal;

        calculateSize();

        wdg_mainSplitter->setOrientation(Qt::Vertical);
        wdg_mainSplitter->addWidget(wdg_scrollArea_dz);
        wdg_mainSplitter->addWidget(wdg_scrollArea_tb);


        int_toolBarIndex = 1;

        break;
    }
    default:

        break;

    }

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

        // Panel Splitter
        wdg_panelSplitter->setOrientation(m_orientation);

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

        // Panel Splitter
        wdg_panelSplitter->setOrientation(m_orientation);


        lyt_dropzone->setDirection(QBoxLayout::LeftToRight);

        wdg_scrollArea_dz->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        wdg_scrollArea_dz->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);



        break;

    default:
        break;


    }

    // qDebug() << "Toolbar Size: Height" << wdg_toolbar->height() << "Width" << wdg_toolbar->width() << "MaxSize"<< wdg_toolbar->maximumSize()<< endl;

    wdg_dropzone->setMinimumWidth(int_minWidth);
    wdg_dropzone->setMinimumHeight(int_minHeight);

}



void IndigoDock::hoverDock(IndigoPanel * pan){

    if (!pan || isHidden()) return;

    QPoint cursor = this->mapFromGlobal(QCursor::pos());

    if (this->rect().contains(cursor) ) {


        if  (wdg_scrollArea_dz->geometry().contains(cursor) ){

            int index = -1;

            for( int i=0; i<lst_PanelList.size(); ++i )
            {

                if(lst_PanelList.at(i)->dockState() == IndigoPanel::Docked || lst_PanelList.at(i)->dockState() == IndigoPanel::HiddenDocked){

                    IndigoPanel *panel = lst_PanelList.at(i);


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


        }else if (wdg_scrollArea_tb->geometry().contains(cursor) ) {

            wdg_toolbar->hoverTabBar();

        }

    }else{
        this->removePlaceholder();
        wdg_toolbar->leaveTabBar();
    }


}



void IndigoDock::dropPanel(IndigoPanel *pan){

    if (!pan || isHidden()) return;

    QPoint cursor = this->mapFromGlobal(QCursor::pos());

    if (this->rect().contains(cursor) ) {

        this->removePlaceholder();

        addIndigoPanel(pan, pan->Index());

    }
}



void IndigoDock::clear(){

    lst_PanelList.clear();
    wdg_toolbar->clear();

    while ( IndigoPanel* pan = findChild<IndigoPanel*>() )
        pan->setParent(0);

}



void IndigoDock::updatePanelSize(){

    for( int i=0; i<lst_PanelList.size(); ++i )
    {
        IndigoPanel * pan = lst_PanelList.at(i);

        qDebug() << "Panel SizeHintHeight" << pan->sizeHint().height() << endl;

        pan->setMinimumSize(int_minPanelWidth, int_minPanelHeight);

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
    case QEvent::Resize:
    {
        // trigger sizeUpdate if splitters resize event was triggered
        if(object == wdg_panelSplitter){
            updateMinHeight();
        }

        break;

    }

    default:
        break;
    }


    return QWidget::eventFilter(object, event);
}


/**********************
 *
 * Settings
 *
 * *******************/


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


