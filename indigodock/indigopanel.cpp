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


#include "indigopanel.h"
#include <QPushButton>
#include "qapplication.h"
#include <QDrag>
#include <QStyle>
#include <QStyleOptionDockWidget>


//
// IndigoPanelHandle
//

IndigoPanelHandle::IndigoPanelHandle(QWidget *parent) :
    QWidget(parent)
{

    setAutoFillBackground( true );

    str_title = "";

    // Objects 
    wdg_btnClose = new QToolButton(this);
    wdg_btnClose->setFixedSize(16,16);
    wdg_btnClose->setAutoRaise(true);
    wdg_btnClose->setFocusPolicy(Qt::NoFocus);

    wdg_btnFloat = new QToolButton(this);
    wdg_btnFloat->setFixedSize(16,16);
    wdg_btnFloat->setAutoRaise(true);
    wdg_btnFloat->setFocusPolicy(Qt::NoFocus);

    QStyleOptionDockWidget opt;
    wdg_btnClose->setIcon(style()->standardIcon(QStyle::SP_TitleBarCloseButton, &opt, this));
    wdg_btnFloat->setIcon(style()->standardIcon(QStyle::SP_TitleBarShadeButton, &opt, this)); // SP_TitleBarUnshadeButton // http://doc.qt.io/qt-4.8/qstyle.html


    // Main LayoutContainer
    QHBoxLayout * mainLayout = new QHBoxLayout;
    mainLayout->setMargin(4);
    setLayout(mainLayout);

    mainLayout->addStretch(1);
    mainLayout->addWidget(wdg_btnFloat);
    mainLayout->addWidget(wdg_btnClose);

    // Actions
    connect(wdg_btnClose, SIGNAL (clicked()), parent, SLOT (hide()));
    connect(wdg_btnFloat, SIGNAL (clicked()), parent, SLOT (expander()));

}



void IndigoPanelHandle::setCaption(QString title, int fontSize){

    str_title = title;
    int_fontSize = fontSize;
}

QString IndigoPanelHandle::Caption(){
    return str_title;
}



void IndigoPanelHandle::setIcon(QIcon icon, int iconSize){

    ico_icon = icon;
    int_iconSize = iconSize;
}


void IndigoPanelHandle::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter p(this);


    int h = this->height();
    int iconY = (h - int_iconSize) / 2;

    QFont font = p.font() ;
    font.setPointSize ( int_fontSize );
    font.setWeight(QFont::DemiBold);
    QFontMetrics fm(this->font());
    int lbl_width = fm.width(str_title);


    if (h > 0)
    {
        int labelX = int_iconSize + 4;

        p.drawPixmap(QRect(0, iconY, int_iconSize,int_iconSize),ico_icon.pixmap(int_iconSize,int_iconSize));
        p.setFont(font);
        p.drawText( QRect(labelX, 0, lbl_width, h), Qt::AlignVCenter, str_title );
    }
}



//
// IndigoPanel
//


IndigoPanel::IndigoPanel(QString name, QWidget *dock) :
   QFrame(dock)
{
    int int_padding = 5;

    // Widgets
    wdg_handle = new IndigoPanelHandle(this);
    wdg_handle->installEventFilter(this);
    wdg_handle->setFixedHeight(30);

    wdg_normalContainer = new QWidget;
    wdg_normalContainer->setMinimumHeight(100); // simulate fake content - remove for productive usage
    lyt_normalArea = new QVBoxLayout(wdg_normalContainer);
    lyt_normalArea->setMargin(int_padding);

    wdg_extendedContainer = new QWidget;
    lyt_extendedArea = new QVBoxLayout(wdg_extendedContainer);
    lyt_extendedArea->setMargin(int_padding);

    //wdg_Parent = dock;

    // Layouts
    lyt_main = new QVBoxLayout;
    lyt_main->setMargin(0);
    setLayout(lyt_main);

    lyt_main->addWidget(wdg_handle);
    lyt_main->addWidget(wdg_normalContainer);
    lyt_main->addWidget(wdg_extendedContainer);
    lyt_main->setAlignment(Qt::AlignTop);

    wdg_spacer = new QSpacerItem(10, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding);
    lyt_main->addSpacerItem(wdg_spacer);

    // Extended Properties
    int_index = -1;
    m_state = IndigoPanel::None;
    m_expander = IndigoPanel::Normal;
    wdg_extendedContainer->hide();

    // General Properties
    setMouseTracking(true);
    setAutoFillBackground( true );
    setBackgroundRole(QPalette::Background);
    setMinimumWidth(220);
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding));
    setCaption(name);
    setAccessibleName(name);
    setObjectName(name);

}



IndigoPanel::IndigoPanel(QString name, QIcon icon, int iconSize, QWidget *dock) :
    IndigoPanel(name, dock)
{
    setIcon(icon, iconSize);

}



bool IndigoPanel::eventFilter(QObject *object, QEvent *event)
{

    switch( event->type() )
    {
    case QEvent::MouseButtonPress:
    {

        QMouseEvent *me = static_cast<QMouseEvent *>(event);


        if (me->buttons() == Qt::LeftButton) {


            qDebug() << "PanelIndex is:" << Index() << endl;

            QPoint point = me->globalPos();
            QPoint xy = this->mapToGlobal(QPoint(0,0));

            pnt_relativeOffset = point - xy;

        }


        break;

    }

    case QEvent::MouseMove:
    {
        QMouseEvent *me = static_cast<QMouseEvent *>(event);

        if (me->buttons() == Qt::LeftButton) {

            QPoint point = me->globalPos();


            // undock Panel if not already undocked
            if(dockState() == IndigoPanel::Docked){

                emit isFloating(int_index);

                setDockState(IndigoPanel::Floating);


            }

            move(point - pnt_relativeOffset);
            emit mouseMove(); // activate DropZone hover*


        }


        break;
    }

    case QEvent::MouseButtonRelease:
    {

        if(dockState() == IndigoPanel::Floating){
            emit mouseReleased(); // activate reparenting in DropZone*
        }

        break;

    }

    default:
        break;
    }



    return QFrame::eventFilter(object, event);
}



void IndigoPanel::setCaption(const QString title, int fontSize){
    wdg_handle->setCaption(title, fontSize);
}


QString IndigoPanel::Caption(){
    return wdg_handle->Caption();
}



void IndigoPanel::setIcon(QIcon icon, int iconSize){
    ico_icon = icon;
    wdg_handle->setIcon(icon, iconSize); // iconSize will used for icon in caption bar
}



QIcon IndigoPanel::Icon(){
    return ico_icon;
}



/**
 * @brief IndigoPanel::Index
 * @return index in dropzone
 */
int IndigoPanel::Index(){
    return int_index;
}



/**
 * @brief IndigoPanel::setIndex
 * @param index
 */
void IndigoPanel::setIndex(int index){
     int_index = index;
}



void IndigoPanel::addWidgetNormal(QWidget *content){
     lyt_normalArea->addWidget(content);

}

void IndigoPanel::addWidgetNormal(QLayout *content){

    QWidget *widget = new QWidget();
    widget->setLayout(content);

     lyt_normalArea->addWidget(widget);

}



void IndigoPanel::addWidgetExtend(QWidget *content){
     lyt_extendedArea->addWidget(content);

}

void IndigoPanel::addWidgetExtend(QLayout *content){

    QWidget *widget = new QWidget();
    widget->setLayout(content);

     lyt_extendedArea->addWidget(widget);

}



void IndigoPanel::hide(){

     switch(dockState()){
     case IndigoPanel::Docked:
         setDockState(IndigoPanel::HiddenDocked);
         break;
     case IndigoPanel::Floating:
         setDockState(IndigoPanel::HiddenFloating);
         break;
     default:
        break;

     }
}



void IndigoPanel::show(){


    switch(dockState()){
    case IndigoPanel::HiddenDocked:
        setDockState(IndigoPanel::Docked);
        break;
    case IndigoPanel::HiddenFloating:
        setDockState(IndigoPanel::Floating);
        break;
    default:
        break;
    }
}



void IndigoPanel::expander(){

    lyt_main->removeItem(wdg_spacer);

    switch(expanderState()){
    case IndigoPanel::Normal:

        if(!lyt_extendedArea->isEmpty()){
            wdg_extendedContainer->show();
            m_expander = IndigoPanel::Advanced;

            lyt_main->addItem(wdg_spacer);

        }else{
            wdg_normalContainer->hide();
            wdg_extendedContainer->hide();
            m_expander = IndigoPanel::Collapsed;

        }
        break;

    case IndigoPanel::Advanced:

        wdg_normalContainer->hide();
        wdg_extendedContainer->hide();
        m_expander = IndigoPanel::Collapsed;

        break;

    case IndigoPanel::Collapsed:

        if(!lyt_normalArea->isEmpty()){
            wdg_normalContainer->show();
            m_expander = IndigoPanel::Normal;

            lyt_main->addItem(wdg_spacer);

        }else{
            wdg_extendedContainer->show();
            m_expander = IndigoPanel::Advanced;

            lyt_main->addItem(wdg_spacer);

        }

        break;
    }

    this->adjustSize();
}



IndigoPanel::IndigoDockState IndigoPanel::dockState(){
    return m_state;
}



void IndigoPanel::setDockState(IndigoPanel::IndigoDockState state){
    m_state = state;

    switch(state){
        case IndigoPanel::HiddenDocked:
        case IndigoPanel::HiddenFloating:
            if(!this->isHidden()){
                QFrame::hide();
            }
            break;

        case IndigoPanel::Floating:
        case IndigoPanel::Docked:
        case IndigoPanel::None:
        default:
            if(!this->isVisible()){
                QFrame::show();
            }
            break;
    }

}



void IndigoPanel::setDockState(int state){

    switch(state){
        case 0:{
            setDockState(IndigoPanel::HiddenDocked);
            break;
        }
        case 1:{
            setDockState(IndigoPanel::HiddenFloating);
            break;
        }
        case 2:{
            setDockState(IndigoPanel::Floating);
            break;
        }
        case 3:{
            setDockState(IndigoPanel::Docked);
            break;
        }
        default:{
            setDockState(IndigoPanel::None);
            break;
        }

    }
}



IndigoPanel::IndigoExpanderState IndigoPanel::expanderState(){
    return m_expander;
}



void IndigoPanel::setExpanderState(IndigoPanel::IndigoExpanderState expanderState){
    m_expander = expanderState;


    lyt_main->removeItem(wdg_spacer);

    switch(expanderState){
    case IndigoPanel::Normal:

        wdg_normalContainer->show();
        wdg_extendedContainer->hide();
        lyt_main->addItem(wdg_spacer);

        break;

    case IndigoPanel::Advanced:

        wdg_normalContainer->show();
        wdg_extendedContainer->show();
        lyt_main->addItem(wdg_spacer);

        break;

    case IndigoPanel::Collapsed:

        wdg_normalContainer->hide();
        wdg_extendedContainer->hide();

        break;
    }

    this->adjustSize();


}



void IndigoPanel::setExpanderState(int expanderState){

    switch(expanderState){
        case 0:{
            setExpanderState(IndigoPanel::Normal);
            break;
        }
        case 1:{
            setExpanderState(IndigoPanel::Advanced);
            break;
        }
        case 2:{
            setExpanderState(IndigoPanel::Collapsed);
            break;
        }
        default:{
            setExpanderState(IndigoPanel::Normal);
            break;
        }

    }
}



void IndigoPanel::setParent(QWidget * parent){

    QWidget::setParent(parent);

    setWindowFlags(Qt::ToolTip | Qt::CustomizeWindowHint); // avoid flickering by moving
}
