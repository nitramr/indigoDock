#include "indigotabbar.h"
#include <QDebug>
#include <QStyle>
#include "helper.h"

IndigoTab::IndigoTab(QIcon icon, QWidget *parent) :
    QWidget(parent)
{
    ico_icon = icon;
    m_display = IndigoTab::visible;
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
    int_borderHighlight = 2;
    dbl_transparency = 0.1; // 10%
    bool_dragProceed = false;
    int_realIndex = -1; // real index of visible dragged tab
    int_dragIndex = -1; // index of visible dragged tab
    int_minDimension = 0;

    setAccessibleName("IndigoTabBar");
    setMouseTracking(true);
    setAutoFillBackground(true);
    setBackgroundRole(QPalette::Background);

    setTabOrientation(IndigoTabBar::Vertical);

}



void IndigoTabBar::mousePressEvent(QMouseEvent*event){

    if(lst_TabList.size() < 0) return;

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
    if (event->buttons() == Qt::LeftButton) {
        int_dragIndex = int_hoverIndex;
    }


    update();

}



void IndigoTabBar::mouseReleaseEvent(QMouseEvent*event){

    if(lst_TabList.size() < 0) return;

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
        emit scrollToPanel(int_newIndex);

    }


    update();

}



void IndigoTabBar::mouseMoveEvent(QMouseEvent*event){


    if(lst_TabList.size() < 0) return;

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
    setToolTip(lst_TabList.at(int_hoverIndex)->toolTip());


    // drag proceed
    if (event->buttons() == Qt::LeftButton) {
        bool_dragProceed = true;
        int_realIndex = int_oldIndex;
    }


    update();

}



void IndigoTabBar::leaveEvent(QEvent *event){

    Q_UNUSED(event)

    int_hoverIndex = -1;
    update();
}



void IndigoTabBar::paintEvent(QPaintEvent *event)
{
   Q_UNUSED(event)

    QPainter p(this);

    int visIndex = 0;

    for (int i = 0; i < lst_TabList.count(); ++i){


        // draw visibile tabs
        IndigoTab *tab = lst_TabList.at(i);

        if(tab->displayState() == IndigoTab::visible){

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
            if(int_hoverIndex == visIndex && bool_dragProceed){


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
            }else if(int_hoverIndex == visIndex){

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

        if(int_realIndex > lst_TabList.count() || int_realIndex < 0) return;

        IndigoTab *tab = lst_TabList.at(int_realIndex);

        QIcon icon = tab->Icon();
        QPixmap pix = icon.pixmap(QSize(int_tabWidth, int_tabHeight));

        QRect dragFrame(pnt_dragPosition.x(), pnt_dragPosition.y(), int_tabWidth, int_tabHeight);
        //p.fillRect(dragFrame, QColor(this->palette().color(QPalette::Background)));
        p.drawPixmap(dragFrame, pix );


    }


}



int IndigoTabBar::realTabIndex(int mouseAxis){

    int fakeIndex = fakeTabIndex(mouseAxis);

     for (int i = 0; i < lst_TabList.count(); ++i){

        // check if there a hidden tab before visible one
        if(lst_TabList.at(i)->displayState() == IndigoTab::hidden){
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
    for (int i = 0; i < lst_TabList.count(); ++i){

        // all visible tabs are counted & fakeIndex was found
        if(visibleTabs == fakeIndex || i == lst_TabList.count()-1){
            return visibleTabs;
        }

        // check if there a visibile tab on index
        if(lst_TabList.at(i)->displayState() == IndigoTab::visible){
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
    tab->setDisplayState(IndigoTab::visible);
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
        lst_TabList.at(index)->setDisplayState(IndigoTab::hidden);
        calculateSize();
        update();
    }
}



void IndigoTabBar::showTab(int index){

    if(index >= 0 && index <= lst_TabList.count()){
        lst_TabList.at(index)->setDisplayState(IndigoTab::visible);
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



int IndigoTabBar::currentIndex(){
    return int_newIndex;
}



void IndigoTabBar::calculateSize(){

   int items=0;

   for( int i=0; i<lst_TabList.size(); ++i ){
       if(lst_TabList.at(i)->displayState() == IndigoTab::visible){

           items +=1;
       }

   }

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

