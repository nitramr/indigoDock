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


#include "indigotabbar.h"
#include <QDebug>
#include <QStyle>
#include "helper.h"


/*#####################
 #
 #
 # IndigoTab
 #
 #
 ####################*/

IndigoTab::IndigoTab(QIcon icon, QWidget *parent) :
    QWidget(parent)
{
    ico_icon = icon;
    m_display = IndigoTab::Visible;
}


/**********************
 *
 * Properties
 *
 * *******************/


void IndigoTab::setIcon(QIcon icon){
    ico_icon = icon;
}



QIcon IndigoTab::Icon(){
    return ico_icon;
}



void IndigoTab::setDisplayState(IndigoTab::Display display){
    m_display = display;
}



IndigoTab::Display IndigoTab::displayState(){
    return m_display;
}




/***************************************************************************
 * TODO:
 * - add overflow buttons
 * - add Tooltip
 *
 * ************************************************************************/



/*#####################
 #
 #
 # IndigoTabBar
 #
 #
 ####################*/



IndigoTabBar::IndigoTabBar(QWidget *parent) :
    QWidget(parent)
{

    int_tabHeight = 32;
    int_tabWidth = 32;
    int_hoverIndex = -1; // index of visible hovered tab
    int_gap = 1;
    int_borderHighlight = 2;
    bool_dragStart = false;
    bool_dragProceed = false;
    bool_hover = false;
    bool_allowDrag = true; // allow moving tabs
    bool_enableTooltip = false; // enable Tooltips on tabs
    int_realIndex = -1; // real index of visible dragged tab
    int_dragIndex = -1; // index of visible dragged tab
    int_minDimension = 0;
    int_dragTolerance = 5; // mouse offset after mouse click to start drag event


    setAccessibleName("IndigoTabBar");
    setObjectName("IndigoTabBar");
    setMouseTracking(true);
    setAutoFillBackground(true);
    setBackgroundRole(QPalette::Background);
    setTabOrientation(Qt::Vertical);

}



int IndigoTabBar::limitTabRange(int TabIndex){

    int limitTab = TabIndex;
    int limit = countVisibleTabs();

    if(limitTab >= limit){
        limitTab = limit;
    }
    if(limitTab < 0){
        limitTab = -1;
    }

    // qDebug() << "limitTab Index" << limitTab << endl;

    return limitTab;

}



int IndigoTabBar::realTabIndex(int mouseAxis){

    int fakeIndex = fakeTabIndex(mouseAxis);
    int i = 0;

    IndigoTab * tab;
    foreach (tab, lst_TabList) {
        // check if there a hidden tab before visible one
        if(tab->displayState() == IndigoTab::Hidden){
            ++fakeIndex;
        }

        // all hidden tabs has been counted & realIndex was found
        if(fakeIndex == i){
            return i;
        }
        i++;
    }


    return -1;
}



int IndigoTabBar::fakeTabIndex(int mouseAxis){

    // calculate fakeIndex by tab grid & mouse position
    int fakeIndex = mouseAxis;
    int visibleTabs = 0;
    int i = 0;

    // recalculate and limit index by real visible tabs
    IndigoTab * tab;
    foreach(tab, lst_TabList){


        // all visible tabs are counted & fakeIndex was found
        if(visibleTabs == fakeIndex || i == lst_TabList.size()-1){
            return visibleTabs;
        }

        // check if there a visibile tab on index
        if(tab->displayState() == IndigoTab::Visible){
            ++visibleTabs;
        }

        i++;
    }

    return -1;
}



void IndigoTabBar::addTab(QIcon icon, QString toolTip){

    insertTab(icon, -1, toolTip);
}



void IndigoTabBar::insertTab(QIcon icon, int index, QString toolTip){

    IndigoTab *tab = new IndigoTab(icon);
    tab->setDisplayState(IndigoTab::Visible);
    if(toolTip != "") tab->setToolTip(toolTip);

    if(index == -1){
        lst_TabList.append(tab);
    }else{
        lst_TabList.insert(index, tab);
    }

    calculateSize();
    update();
}



void IndigoTabBar::removeTab(int index){

    if(index >= 0 && index <= lst_TabList.size()){
        lst_TabList.removeAt(index);

        calculateSize();
        update();

    }

}



void IndigoTabBar::moveTab(){

    if(int_newIndex != int_oldIndex){

        IndigoTab *tab = lst_TabList.takeAt(int_oldIndex);
        lst_TabList.insert(int_newIndex, tab);

        emit tabMoved(int_oldIndex, int_newIndex);
        qDebug() << "emit: tabClicked(...); TabMoved old" << int_oldIndex << "new" << int_newIndex << endl;
    }

}



void IndigoTabBar::hideTab(int index){

    if(index >= 0 && index <= lst_TabList.size()){
        lst_TabList.at(index)->setDisplayState(IndigoTab::Hidden);
        calculateSize();
        update();
    }
}



void IndigoTabBar::showTab(int index){

    if(index >= 0 && index <= lst_TabList.size()){
        lst_TabList.at(index)->setDisplayState(IndigoTab::Visible);
        calculateSize();
        update();
    }
}



int IndigoTabBar::countHiddenTabs(){

    int counter = 0;

    IndigoTab * tab;
    foreach(tab, lst_TabList){
        if(tab->displayState() == IndigoTab::Hidden){
            ++counter;
        }
    }

    return counter;
}



int IndigoTabBar::countVisibleTabs(){

    int counter = 0;

    IndigoTab * tab;
    foreach(tab, lst_TabList){
        if(tab->displayState() == IndigoTab::Visible){
            ++counter;
        }
    }

    return counter;
}



void IndigoTabBar::calculateSize(){

    int items = countVisibleTabs();

    switch (m_tabOrientation){

    case Qt::Vertical:

        int_minDimension = items*(int_tabHeight + int_gap);

        setMinimumSize(QSize(int_tabWidth, int_minDimension));
        setMaximumSize(QSize(int_tabWidth, QWIDGETSIZE_MAX));
        setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::MinimumExpanding));

        break;

    case Qt::Horizontal:

        int_minDimension = items*(int_tabWidth + int_gap);

        setMinimumSize(QSize(int_minDimension, int_tabHeight));
        setMaximumSize(QSize(QWIDGETSIZE_MAX, int_tabHeight));
        setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));

        break;
    default:
        break;
    }
}



void IndigoTabBar::clear(){

    lst_TabList.clear();
    update();

}



void IndigoTabBar::leaveTabBar(){
    int_hoverIndex = -1;
    int_dragIndex = -1;
    bool_hover = false;
    update();

}


/**********************
 *
 * Events
 *
 * *******************/


void IndigoTabBar::mousePressEvent(QMouseEvent*event){

    int visTabs = countVisibleTabs();

    if(visTabs <= 0) return;

    QPoint mouse = event->pos();
    pnt_mouseDown = mouse;

    switch (m_tabOrientation){

    case Qt::Vertical:{
        int_hoverIndex = mouse.y() / (int_tabHeight + int_gap);

        int_oldIndex = realTabIndex(mouse.y() / (int_tabHeight + int_gap));

        break;
    }
    case Qt::Horizontal:
        int_hoverIndex = mouse.x() / (int_tabWidth + int_gap);
        int_oldIndex = realTabIndex(mouse.x() / (int_tabWidth + int_gap));

        break;
    }


    if(int_hoverIndex >= 0 && int_hoverIndex < visTabs){
        // drag started
        if (event->buttons() == Qt::LeftButton && bool_allowDrag) {
           // bool_dragStart = true;
            int_hoverIndex = limitTabRange(int_hoverIndex);
            int_dragIndex = int_hoverIndex;

        }
    }
}



void IndigoTabBar::mouseMoveEvent(QMouseEvent*event){

    int visTabs = countVisibleTabs();

    if(visTabs <= 0) return;

    QPoint mouse = event->pos();


    switch (m_tabOrientation){

    case Qt::Vertical:
        int_hoverIndex = mouse.y() / (int_tabHeight + int_gap);
        pnt_dragPosition = QPoint(0, mouse.y() - (int_tabHeight/2));

        if((pnt_mouseDown.y() - int_dragTolerance > mouse.y() && event->buttons() == Qt::LeftButton) || (pnt_mouseDown.y() + int_dragTolerance < mouse.y() && event->buttons() == Qt::LeftButton))
            bool_dragStart = true;

        break;

    case Qt::Horizontal:
        int_hoverIndex = mouse.x() / (int_tabWidth + int_gap);
        pnt_dragPosition = QPoint(mouse.x() - (int_tabWidth/2), 0);

        if((pnt_mouseDown.x() - int_dragTolerance > mouse.x() && event->buttons() == Qt::LeftButton) || (pnt_mouseDown.x() + int_dragTolerance < mouse.x() && event->buttons() == Qt::LeftButton))
            bool_dragStart = true;

        break;
    }


    if(int_hoverIndex >= 0 && int_hoverIndex < visTabs){

        if(bool_enableTooltip){
            int tabIndex = realTabIndex(int_hoverIndex);
            // ToolTip
            setToolTip(lst_TabList.at(tabIndex)->toolTip());

        }


        // drag proceed
        if (event->buttons() == Qt::LeftButton && bool_allowDrag && bool_dragStart) {

                bool_dragProceed = true;
                int_realIndex = int_oldIndex;

        }
    }

    update();

}



void IndigoTabBar::mouseReleaseEvent(QMouseEvent*event){

    int visTabs = countVisibleTabs();

    if(visTabs <= 0) return;


    QPoint mouse = event->pos();

    switch (m_tabOrientation){

    case Qt::Vertical:
        int_newIndex = realTabIndex(mouse.y() / (int_tabHeight + int_gap));

        break;

    case Qt::Horizontal:
        int_newIndex = realTabIndex(mouse.x() / (int_tabWidth + int_gap));

        break;
    }


    int_dragIndex = -1;
    bool_dragStart = false;

    if(bool_dragProceed){

        bool_dragProceed = false;
        int_realIndex = -1;

        moveTab();
    }else{

        // Scroll to position in DropZone after mouse click
        if(int_hoverIndex >= 0 && int_hoverIndex < visTabs){
            emit tabClicked(int_newIndex);
            qDebug() << "emit: tabClicked(...)" << endl;
        }
    }

    update();

}



void IndigoTabBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter p(this);

    int visIndex = 0;


    IndigoTab * tab;
    foreach(tab, lst_TabList){


           if(tab->displayState() == IndigoTab::Visible){

            QRect  tabRect;
            QRect  gapRect;
            int xP, yP, xN, yN;

            // calculate tab rectangles based on tabBar orientation
            switch (m_tabOrientation){

            case Qt::Vertical:
                tabRect = QRect(0,visIndex*(int_tabHeight + int_gap), int_tabWidth, int_tabHeight);
                gapRect = QRect(4,tabRect.y() - int_gap, int_tabWidth - 8, int_gap);
                xN = 0;
                yN = tabRect.y()-(int_tabHeight + int_gap);
                xP = 0;
                yP = tabRect.y()+(int_tabHeight + int_gap);
                break;

            case Qt::Horizontal:
                tabRect = QRect(visIndex*(int_tabWidth + int_gap), 0, int_tabWidth, int_tabHeight);
                gapRect = QRect(tabRect.x() - int_gap, 4, int_gap, int_tabHeight - 8);
                xN = tabRect.x()-(int_tabWidth + int_gap);
                yN = 0;
                xP = tabRect.x()+(int_tabWidth + int_gap);
                yP = 0;
                break;

            }


            QIcon icon = tab->Icon();
            QPixmap pix = icon.pixmap(QSize(int_tabWidth*devicePixelRatio(), int_tabHeight*devicePixelRatio()));


            // draw hovered background
            if(int_hoverIndex == visIndex && bool_dragProceed == false){

                p.fillRect(tabRect,
                           QColor(this->palette().color(QPalette::Base)));
            }


            // draw tab content but exclude dragged tab
            if(int_dragIndex != visIndex){

                if(visIndex <= int_hoverIndex && visIndex > int_dragIndex && bool_dragProceed){

                    QRect offsetRect(xN, yN, int_tabWidth, int_tabHeight);
                    p.drawPixmap(offsetRect, pix );



                }else if(visIndex >= int_hoverIndex && visIndex < int_dragIndex && bool_dragProceed){

                    QRect offsetRect(xP, yP, int_tabWidth, int_tabHeight);
                    p.drawPixmap(offsetRect, pix );


                }else{
                    p.drawPixmap(tabRect, pix );

                }

            }

            // draw clicked tab if no drag proceed
            if(int_dragIndex == visIndex && !bool_dragProceed){
                p.drawPixmap(tabRect, pix );
            }


            // draw divider
            p.fillRect(gapRect, Helper().blendColor(QColor(this->palette().color(QPalette::Background)),
                                                    QColor(this->palette().color(QPalette::Base)),
                                                    0.5));

            // count only visible tabs
            ++visIndex;
        }
    }


    // draw moveable Tab

    if(bool_dragProceed){

        if(int_realIndex > lst_TabList.size() || int_realIndex < 0) return;

        IndigoTab *tab = lst_TabList.at(int_realIndex);

        QIcon icon = tab->Icon();
        QPixmap pix = icon.pixmap(QSize(int_tabWidth *devicePixelRatio(), int_tabHeight *devicePixelRatio()));

        QRect dragFrame(pnt_dragPosition.x(), pnt_dragPosition.y(), int_tabWidth, int_tabHeight);
        QColor col_background = this->palette().color(QPalette::Base);
        col_background.setAlpha(128);

        p.fillRect(dragFrame, col_background);
        p.drawPixmap(dragFrame, pix );
    }
}



void IndigoTabBar::leaveEvent(QEvent *event){

    Q_UNUSED(event)

    leaveTabBar();
}


/**********************
 *
 * Properties
 *
 * *******************/


void IndigoTabBar::setTabSize(int side){
    setTabSize(side, side);
}



void IndigoTabBar::setTabSize(int width, int height){
    int_tabWidth = width;
    int_tabHeight = height;
}



Qt::Orientation IndigoTabBar::TabOrientation(){
    return m_tabOrientation;
}



void IndigoTabBar::setTabOrientation(Qt::Orientation tabDirection){

    m_tabOrientation = tabDirection;
    calculateSize();
}



void IndigoTabBar::setMovableTabs(bool allowMoving){
    bool_allowDrag = allowMoving;
}



bool IndigoTabBar::movableTabs(){
    return bool_allowDrag;
}



int IndigoTabBar::currentIndex(){
    return int_newIndex;
}
