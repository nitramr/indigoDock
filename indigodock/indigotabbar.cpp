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

IndigoTab::IndigoTab(QIcon icon, QWidget *parent) :
    QWidget(parent)
{
    ico_icon = icon;
    m_display = IndigoTab::Visible;
}

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
 *
 * ************************************************************************/

IndigoTabBar::IndigoTabBar(QWidget *parent) :
    QWidget(parent)
{

    int_tabHeight = 32;
    int_tabWidth = 32;
    int_hoverIndex = -1; // index of visible hovered tab
    int_gap = 1;
    int_borderHighlight = 3;
    bool_dragProceed = false;
    bool_hover = false;
    bool_allowDrag = true; // allow moving tabs
    int_realIndex = -1; // real index of visible dragged tab
    int_dragIndex = -1; // index of visible dragged tab
    int_minDimension = 0;

    setAccessibleName("IndigoTabBar");
    setObjectName("IndigoTabBar");
    setMouseTracking(true);
    setAutoFillBackground(true);
    setBackgroundRole(QPalette::Background);

    setTabOrientation(IndigoTabBar::Vertical);

}



void IndigoTabBar::mousePressEvent(QMouseEvent*event){

    if(countVisibleTabs() <= 0) return;

    QPoint mouse = event->pos();


    switch (m_tabOrientation){

        case IndigoTabBar::Vertical:
            int_hoverIndex = mouse.y() / (int_tabHeight + int_gap);
            int_oldIndex = realTabIndex(mouse.y()/ (int_tabHeight + int_gap));

            break;

        case IndigoTabBar::Horizontal:
            int_hoverIndex = mouse.x() / (int_tabWidth + int_gap);
            int_oldIndex = realTabIndex(mouse.x()/ (int_tabWidth + int_gap));

            break;

    }


    // drag started
    if (event->buttons() == Qt::LeftButton && bool_allowDrag) {
        int_dragIndex = int_hoverIndex;
    }


    update();

}



void IndigoTabBar::mouseReleaseEvent(QMouseEvent*event){

    if(countVisibleTabs() <= 0) return;


    QPoint mouse = event->pos();

    switch (m_tabOrientation){

        case IndigoTabBar::Vertical:
            int_newIndex = realTabIndex(mouse.y()/ (int_tabHeight + int_gap));

            break;

        case IndigoTabBar::Horizontal:
        int_newIndex = realTabIndex(mouse.x()/ (int_tabWidth + int_gap));

        break;

    }


    int_dragIndex = -1;


    if(bool_dragProceed){
        bool_dragProceed = false;
        int_realIndex = -1;

        moveTab();
    }else{

        // Scroll to position in DropZone after mouse click
        emit tabClicked(int_newIndex);


    }


    update();

}



void IndigoTabBar::mouseMoveEvent(QMouseEvent*event){


    if(countVisibleTabs() <= 0) return;

    QPoint mouse = event->pos();


    switch (m_tabOrientation){

        case IndigoTabBar::Vertical:
            int_hoverIndex = mouse.y() / (int_tabHeight + int_gap);
            pnt_dragPosition = QPoint(0,event->pos().y() - (int_tabHeight/2));

            break;

        case IndigoTabBar::Horizontal:
            int_hoverIndex = mouse.x() / (int_tabWidth + int_gap);
            pnt_dragPosition = QPoint(event->pos().x() - (int_tabWidth/2), 0);

            break;

    }


    if (int_hoverIndex >= lst_TabList.size()-1) int_hoverIndex = lst_TabList.size()-1;
    else if (int_hoverIndex < 0) int_hoverIndex = 0;


    // ToolTip
   // setToolTip(lst_TabList.at(int_hoverIndex)->toolTip());


    // drag proceed
    if (event->buttons() == Qt::LeftButton && bool_allowDrag) {
        bool_dragProceed = true;
        int_realIndex = int_oldIndex;
    }

    update();

}



void IndigoTabBar::hoverTabBar(){
    bool_hover = true;
    update();

}



void IndigoTabBar::leaveTabBar(){
    int_hoverIndex = -1;
    int_dragIndex = -1;
    bool_hover = false;
    update();

}



void IndigoTabBar::leaveEvent(QEvent *event){

    Q_UNUSED(event)

   leaveTabBar();
}



void IndigoTabBar::paintEvent(QPaintEvent *event)
{
   Q_UNUSED(event)

    QPainter p(this);

    int visIndex = 0;

    for (int i = 0; i < lst_TabList.size(); ++i){


        // draw visibile tabs
        IndigoTab *tab = lst_TabList.at(i);

        if(tab->displayState() == IndigoTab::Visible){

            QRect  tabRect;
            QRect  gapRect;
            int xP, yP, xN, yN;

            // calculate tab rectangles based on tabBar orientation
            switch (m_tabOrientation){

                case IndigoTabBar::Vertical:
                    tabRect = QRect(0,visIndex*(int_tabHeight + int_gap), int_tabWidth, int_tabHeight);
                    gapRect = QRect(4,tabRect.y() - int_gap, int_tabWidth - 8, int_gap);
                    xN = 0;
                    yN = tabRect.y()-(int_tabHeight + int_gap);
                    xP = 0;
                    yP = tabRect.y()+(int_tabHeight + int_gap);
                    break;

                case IndigoTabBar::Horizontal:
                    tabRect = QRect(visIndex*(int_tabWidth + int_gap), 0, int_tabWidth, int_tabHeight);
                    gapRect = QRect(tabRect.x() - int_gap, 4, int_gap, int_tabHeight - 8);
                    xN = tabRect.x()-(int_tabWidth + int_gap);
                    yN = 0;
                    xP = tabRect.x()+(int_tabWidth + int_gap);
                    yP = 0;
                    break;

            }


            QIcon icon = tab->Icon();
            QPixmap pix = icon.pixmap(QSize(int_tabWidth, int_tabHeight));


            // draw highlighter
           /* if(int_hoverIndex == visIndex && bool_dragProceed){


                col_colorHighlightAlpha = Helper().blendColor(QColor(this->palette().color(QPalette::Background)),
                                                   QColor(this->palette().color(QPalette::Highlight)),
                                                   dbl_transparency);

                p.fillRect(tabRect,
                           QColor(this->palette().color(QPalette::Highlight)));

                p.fillRect(tabRect.x()+int_borderHighlight,
                           tabRect.y()+int_borderHighlight,
                           tabRect.width() -(int_borderHighlight*2),
                           tabRect.height() -(int_borderHighlight*2),
                           col_colorHighlightAlpha);


             // clear hovered background
            }else */if(int_hoverIndex == visIndex && bool_dragProceed == false){

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
            if(int_dragIndex == visIndex && bool_dragProceed == false){
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
        QPixmap pix = icon.pixmap(QSize(int_tabWidth, int_tabHeight));

        QRect dragFrame(pnt_dragPosition.x(), pnt_dragPosition.y(), int_tabWidth, int_tabHeight);
        QColor col_background = this->palette().color(QPalette::Base);
        col_background.setAlpha(128);

        p.fillRect(dragFrame, col_background);
        p.drawPixmap(dragFrame, pix );


    }


    // TabBar is empty - show dropZone
    if(countHiddenTabs() == lst_TabList.size() && bool_hover){

        switch (m_tabOrientation){

            case IndigoTabBar::Vertical:

                p.fillRect(this->geometry().x(),
                           this->geometry().y(),
                           int_tabWidth,
                           int_borderHighlight,
                           QColor(this->palette().color(QPalette::Highlight)));


                break;

            case IndigoTabBar::Horizontal:

                p.fillRect(this->geometry().x(),
                       this->geometry().y(),
                       int_borderHighlight,
                       int_tabHeight,
                       QColor(this->palette().color(QPalette::Highlight)));

                break;

        }



    }


}



int IndigoTabBar::realTabIndex(int mouseAxis){

    int fakeIndex = fakeTabIndex(mouseAxis);

     for (int i = 0; i < lst_TabList.size(); ++i){

        // check if there a hidden tab before visible one
        if(lst_TabList.at(i)->displayState() == IndigoTab::Hidden){
            ++fakeIndex;
        }

        // all hidden tabs are counted & realIndex was found
        if(fakeIndex == i){
            return i;
        }

    }

    return -1;
}



int IndigoTabBar::fakeTabIndex(int mouseAxis){

    // calculate fakeIndex by tab grid & mouse position
    int fakeIndex = mouseAxis;

    int visibleTabs = 0;

    // recalculate and limit index by real visible tabs
    for (int i = 0; i < lst_TabList.size(); ++i){

        // all visible tabs are counted & fakeIndex was found
        if(visibleTabs == fakeIndex || i == lst_TabList.size()-1){
            return visibleTabs;
        }

        // check if there a visibile tab on index
        if(lst_TabList.at(i)->displayState() == IndigoTab::Visible){
            ++visibleTabs;
        }
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

    if(index >= 0 && index <= lst_TabList.count()){
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
        qDebug() << "TabMoved old" << int_oldIndex << "new" << int_newIndex << endl;
    }

}



void IndigoTabBar::hideTab(int index){

    if(index >= 0 && index <= lst_TabList.count()){
        lst_TabList.at(index)->setDisplayState(IndigoTab::Hidden);
        calculateSize();
        update();
    }
}



void IndigoTabBar::showTab(int index){

    if(index >= 0 && index <= lst_TabList.count()){
        lst_TabList.at(index)->setDisplayState(IndigoTab::Visible);
        calculateSize();
        update();

    }

}



void IndigoTabBar::setTabSize(int side){
    setTabSize(side, side);
}



void IndigoTabBar::setTabSize(int width, int height){
    int_tabWidth = width;
    int_tabHeight = height;
}



IndigoTabBar::Orientation IndigoTabBar::TabOrientation(){
    return m_tabOrientation;
}



void IndigoTabBar::setTabOrientation(Orientation tabDirection){

    m_tabOrientation = tabDirection;

    calculateSize();

}



void IndigoTabBar::setMovingTabs(bool allowMoving){
    bool_allowDrag = allowMoving;
}



bool IndigoTabBar::movingTabs(){
   return bool_allowDrag;
}



int IndigoTabBar::currentIndex(){
    return int_newIndex;
}



int IndigoTabBar::countHiddenTabs(){

    int counter = 0;

    for( int i=0; i<lst_TabList.size(); ++i ){
        if(lst_TabList.at(i)->displayState() == IndigoTab::Hidden){
            ++counter;
        }
    }

    return counter;
}



int IndigoTabBar::countVisibleTabs(){

    int counter = 0;

    for( int i=0; i<lst_TabList.size(); ++i ){
        if(lst_TabList.at(i)->displayState() == IndigoTab::Visible){
            ++counter;
        }
    }

    return counter;
}



void IndigoTabBar::calculateSize(){

   int items = countVisibleTabs();

   switch (m_tabOrientation){

   case IndigoTabBar::Vertical:

       int_minDimension = items*(int_tabHeight + int_gap);

       setMinimumSize(QSize(int_tabWidth, int_minDimension));
       setMaximumSize(QSize(int_tabWidth, 16777215));
       setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::MinimumExpanding));

       break;

   case IndigoTabBar::Horizontal:

       int_minDimension = items*(int_tabWidth + int_gap);

       setMinimumSize(QSize(int_minDimension, int_tabHeight));
       setMaximumSize(QSize(16777215, int_tabHeight));
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
