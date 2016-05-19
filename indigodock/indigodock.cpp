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

IndigoDock::IndigoDock(QString name, QWidget *parent) : QDockWidget(parent)
{


    QString styleSheetScroll( "QScrollArea {"
                              "border: 0px solid transparent;"
                              "}"

                              );


    int_padding = 3;
    int_placeholderHeight = 3;

    wdg_toolbar = new IndigoTabBar;

    wdg_placeholder = new QWidget();
    wdg_placeholder->setFixedHeight(int_placeholderHeight);
    wdg_placeholder->setAutoFillBackground( true );
    wdg_placeholder->setBackgroundRole(QPalette::Highlight);


    wdg_panelSplitter = new QSplitter();
    wdg_panelSplitter->setHandleWidth(int_padding);
    wdg_panelSplitter->setOrientation(Qt::Vertical);
    wdg_panelSplitter->move(this->pos());
    wdg_panelSplitter->installEventFilter(this);


    lyt_dropzone = new QVBoxLayout();
    lyt_dropzone->setMargin(int_padding);
    lyt_dropzone->setSpacing(0);
    lyt_dropzone->addWidget(wdg_panelSplitter);
    lyt_dropzone->addStretch(1);


    wdg_dropzone = new QWidget();
    wdg_dropzone->setLayout(lyt_dropzone);
    wdg_dropzone->setMinimumWidth(220 + 2*int_padding);
    wdg_dropzone->setBackgroundRole(QPalette::Base);


    wdg_scrollArea_dz = new QScrollArea;
    wdg_scrollArea_dz->setStyleSheet( styleSheetScroll);
    wdg_scrollArea_dz->setWidgetResizable(true);
    wdg_scrollArea_dz->setWidget(wdg_dropzone);
    wdg_scrollArea_dz->setMinimumWidth(wdg_dropzone->minimumWidth() + 20); //scrollbar fix
    wdg_scrollArea_dz->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


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
    setAccessibleName(name);
    setObjectName(name);


    connect(this, SIGNAL(panelAdded(QIcon, int, QString)), wdg_toolbar, SLOT(insertTab(QIcon, int, QString)));
    connect(this, SIGNAL(panelRemoved(int)), wdg_toolbar, SLOT(removeTab(int)));
    connect(this, SIGNAL(dockLocationChanged(Qt::DockWidgetArea)), this, SLOT(updateTabPosition(Qt::DockWidgetArea)));
    connect(wdg_toolbar, SIGNAL(tabMoved(int,int)), this, SLOT(movePanel(int,int)));
    connect(wdg_toolbar, SIGNAL(tabClicked(int)), this, SLOT(scrollToPanel(int)));

}



QList<IndigoPanel*> IndigoDock::getPanels(){
    return lst_PanelList;

}


void IndigoDock::addIndigoPanel(IndigoPanel *panel, int tabIndex){

    this->connect(panel, SIGNAL(panelClosed(int)), wdg_toolbar, SLOT(hideTab(int)));
    this->connect(panel, SIGNAL(panelShown(int)), wdg_toolbar, SLOT(showTab(int)));


    addPanel (panel, tabIndex);


}



/**
 * Add Panel in Splitter
 * @brief Indigo2DropZone::addPanel
 * @param panel
 */
void IndigoDock::addPanel (IndigoPanel *panel, int tabIndex){

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
    //panel->show();

    updatePanels();

    // send signal for successful adding
    emit panelAdded(panel->Icon(), panel->Index(), panel->Caption());

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
    updatePanels();
    emit panelRemoved(index);
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


    updateMinHeight();

    IndigoPanel *panel = lst_PanelList.at(PanelIndex);
    int offset = int_padding;

    QPoint panPos = wdg_dropzone->mapFromGlobal(panel->mapToGlobal( QPoint( 0, 0 ) ));

    QPropertyAnimation *animation = new QPropertyAnimation(wdg_scrollArea_dz->verticalScrollBar(), "value");
    animation->setDuration(100);
    animation->setStartValue(wdg_scrollArea_dz->verticalScrollBar()->value());
    animation->setEndValue(panPos.y() - offset);
    animation->start();

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

    int lastPanelHeight = 0;
    int countHiddenPanels = 0;

    // get height of last visible Panel
    for( int i=0; i<lst_PanelList.size(); ++i )
    {

        switch(lst_PanelList.at(i)->dockState()){

        case IndigoPanel::Docked:{
            IndigoPanel * panel = lst_PanelList.at(i);
            lastPanelHeight = panel->height();
            break;
        }
        default:{
            countHiddenPanels += 1;
            break;
        }

        }

    }


    // hide drop zone if all panels are hidden
    if(countHiddenPanels == lst_PanelList.size()){

        wdg_scrollArea_dz->hide();
        setMaximumSize(wdg_toolbar->maximumSize());

    }else{

        int minHeight = wdg_panelSplitter->height();
        int spacer = wdg_scrollArea_dz->height() - lastPanelHeight;

        if(minHeight < lastPanelHeight) minHeight = lastPanelHeight;


        wdg_dropzone->setFixedHeight(minHeight + spacer);

        wdg_scrollArea_dz->show();

        QRect screen = QApplication::desktop()->screenGeometry();
        setMaximumSize(screen.width(), screen.height());

        update();
    }


}



void IndigoDock::addPlaceholder (int index){

    wdg_placeholder->setFixedHeight(int_placeholderHeight);

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
    wdg_placeholder->setFixedHeight(0);

}



void IndigoDock::updateTabPosition(Qt::DockWidgetArea area){

    switch(area){
    case Qt::LeftDockWidgetArea:{
        wdg_toolbar->setTabOrientation(IndigoTabBar::Vertical);

        wdg_mainSplitter->setOrientation(Qt::Horizontal);
        wdg_mainSplitter->addWidget(wdg_scrollArea_tb);
        wdg_mainSplitter->addWidget(wdg_scrollArea_dz);


        wdg_scrollArea_tb->setMinimumSize(QSize(wdg_toolbar->width(), wdg_toolbar->width()));
        wdg_scrollArea_tb->setMaximumSize(wdg_toolbar->maximumSize());

        break;
    }
    case Qt::RightDockWidgetArea:{
        wdg_toolbar->setTabOrientation(IndigoTabBar::Vertical);

        wdg_mainSplitter->setOrientation(Qt::Horizontal);
        wdg_mainSplitter->addWidget(wdg_scrollArea_dz);
        wdg_mainSplitter->addWidget(wdg_scrollArea_tb);

        wdg_scrollArea_tb->setMinimumSize(QSize(wdg_toolbar->width(), wdg_toolbar->width()));
        wdg_scrollArea_tb->setMaximumSize(wdg_toolbar->maximumSize());


        break;
    }
    case Qt::TopDockWidgetArea:{

        wdg_toolbar->setTabOrientation(IndigoTabBar::Horizontal);

        wdg_mainSplitter->setOrientation(Qt::Vertical);
        wdg_mainSplitter->addWidget(wdg_scrollArea_tb);
        wdg_mainSplitter->addWidget(wdg_scrollArea_dz);

        wdg_scrollArea_tb->setMinimumSize(QSize(wdg_toolbar->height(), wdg_toolbar->height()));
        wdg_scrollArea_tb->setMaximumSize(wdg_toolbar->maximumSize());

        break;
    }
    case Qt::BottomDockWidgetArea:{

        wdg_toolbar->setTabOrientation(IndigoTabBar::Horizontal);

        wdg_mainSplitter->setOrientation(Qt::Vertical);
        wdg_mainSplitter->addWidget(wdg_scrollArea_dz);
        wdg_mainSplitter->addWidget(wdg_scrollArea_tb);

        wdg_scrollArea_tb->setMinimumSize(QSize(wdg_toolbar->height(), wdg_toolbar->height()));
        wdg_scrollArea_tb->setMaximumSize(wdg_toolbar->maximumSize());


        break;
    }
    default:

        break;

    }

}



void IndigoDock::hoverDock(IndigoPanel * pan){

    if (!pan) return;

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

    if (!pan) return;

    QPoint cursor = this->mapFromGlobal(QCursor::pos());

    if (this->rect().contains(cursor) ) {

        this->removePlaceholder();

        addPanel(pan, pan->Index());

        emit panelDropped(pan->Index());

    }
}



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



void IndigoDock::clear(){

    lst_PanelList.clear();
    wdg_toolbar->clear();

    while ( IndigoPanel* pan = findChild<IndigoPanel*>() )
        pan->setParent(0);

}
