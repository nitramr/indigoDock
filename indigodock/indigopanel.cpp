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


/*#####################
 #
 #
 # IndigoPanelHandle
 #
 #
 #####################*/

IndigoPanelHandle::IndigoPanelHandle(QWidget *parent) :
    QWidget(parent)
{

    setAutoFillBackground( true );
    setFixedHeight(24);

    str_title = "";

    // Objects
    wdg_btnClose = new QToolButton(this);
    wdg_btnClose->setFixedSize(16,16);
    wdg_btnClose->setAutoRaise(true);
    wdg_btnClose->setFocusPolicy(Qt::NoFocus);

    wdg_btnExpander = new QToolButton(this);
    wdg_btnExpander->setFixedSize(16,16);
    wdg_btnExpander->setAutoRaise(true);
    wdg_btnExpander->setFocusPolicy(Qt::NoFocus);

    QStyleOptionDockWidget opt;
    wdg_btnClose->setIcon(style()->standardIcon(QStyle::SP_TitleBarCloseButton, &opt, this));
    wdg_btnExpander->setIcon(style()->standardIcon(QStyle::SP_TitleBarUnshadeButton, &opt, this)); // SP_TitleBarUnshadeButton // http://doc.qt.io/qt-4.8/qstyle.html


    // Main LayoutContainer
    QHBoxLayout * mainLayout = new QHBoxLayout;
    mainLayout->setMargin(2);
    mainLayout->setSpacing(0);
    mainLayout->addStretch(0);
    mainLayout->addWidget(wdg_btnExpander);
    mainLayout->addWidget(wdg_btnClose);

    setLayout(mainLayout);

    // Actions
    connect(wdg_btnClose, SIGNAL (clicked()), parent, SLOT (hide()));
    connect(wdg_btnExpander, SIGNAL (clicked()), parent, SLOT (expander()));

}


/**********************
 *
 * Events
 *
 * *******************/


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


/**********************
 *
 * Settings
 *
 * *******************/


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



void IndigoPanelHandle::setExpanderState(IndigoExpanderState expanderState){


    QStyleOptionDockWidget opt;
    // SP_TitleBarUnshadeButton // http://doc.qt.io/qt-4.8/qstyle.html

    switch(expanderState){

    case IndigoPanelHandle::Advanced:
        wdg_btnExpander->setIcon(style()->standardIcon(QStyle::SP_TitleBarShadeButton, &opt, this));
        break;

    case IndigoPanelHandle::Normal:
    default:
        wdg_btnExpander->setIcon(style()->standardIcon(QStyle::SP_TitleBarUnshadeButton, &opt, this));
        break;

    }

}


/*#####################
 #
 #
 # IndigoPanel
 #
 #
 #####################*/


IndigoPanel::IndigoPanel(QString name, QWidget *dock) :
    QFrame(dock)
{
    int int_padding = 5;

    QString styleSheetScroll( "QScrollArea {"
                              "border: 0px solid transparent;"
                              "}"
                              );

    // Widgets
    wdg_handle = new IndigoPanelHandle(this);
    wdg_handle->installEventFilter(this);

    wdg_normalContainer = new QWidget;
    lyt_normalArea = new QVBoxLayout(wdg_normalContainer);
    lyt_normalArea->setMargin(int_padding);

    /*  wdg_scrollArea = new QScrollArea;
    wdg_scrollArea->setWidget(wdg_normalContainer);
    wdg_scrollArea->setStyleSheet( styleSheetScroll);
    wdg_scrollArea->setWidgetResizable(true);
    wdg_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    wdg_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    wdg_scrollArea->setBackgroundRole(QPalette::Highlight);*/

    // Layouts
    lyt_main = new QVBoxLayout;
    lyt_main->setMargin(0);
    lyt_main->addWidget(wdg_handle);
    lyt_main->addWidget(wdg_normalContainer);
    // lyt_main->addWidget(wdg_scrollArea);
    lyt_main->setAlignment(Qt::AlignTop);
    setLayout(lyt_main);

    // Extended Properties
    int_index = -1;
    m_state = IndigoPanel::None;
    m_expander = IndigoPanelHandle::Normal;

    // General Properties
    setMouseTracking(true);
    setAutoFillBackground( true );
    setBackgroundRole(QPalette::Background);
    setMinimumWidth(150);
    setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));
    setCaption(name);
    setAccessibleName(name);
    setObjectName(name);

}



IndigoPanel::IndigoPanel(QString name, QIcon icon, int iconSize, QWidget *dock) :
    IndigoPanel(name, dock)
{
    setIcon(icon, iconSize);

}



void IndigoPanel::hide(){

    switch(dockState()){
    case IndigoPanel::Docked:
        setDockState(IndigoPanel::HiddenDocked);
        emit panelClosed(Index());
        qDebug() << "emit: panelClosed(...);" << endl;
        break;
    default:
        QFrame::hide();
        break;

    }
}



void IndigoPanel::show(){

    switch(dockState()){
    case IndigoPanel::HiddenDocked:
        setDockState(IndigoPanel::Docked);
        emit panelShown(Index());
        qDebug() << "emit: panelShow(...);" << endl;
        break;
    default:
        QFrame::show();
        break;
    }

    update();
}



void IndigoPanel::expander(){


    switch(expanderState()){
    case IndigoPanelHandle::Normal:


        m_expander = IndigoPanelHandle::Advanced;
        wdg_handle->setExpanderState(m_expander);
        emit isAdvanced();
        qDebug() << "emit: isAdvanced();" << endl;
        break;

    case IndigoPanelHandle::Advanced:


        m_expander = IndigoPanelHandle::Normal;
        wdg_handle->setExpanderState(m_expander);
        emit isNormal();
        qDebug() << "emit: isNormal();" << endl;
        break;
    }
}


/**********************
 *
 * Events
 *
 * *******************/


bool IndigoPanel::eventFilter(QObject *object, QEvent *event)
{

    switch( event->type() )
    {
    case QEvent::MouseButtonPress:
    {

        QMouseEvent *me = static_cast<QMouseEvent *>(event);


        if (me->buttons() == Qt::LeftButton) {

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
            qDebug() << "emit: mouseReleased();" << endl;
            update();
        }

        break;
    }


    case QEvent::MouseButtonDblClick:

        expander();
        break;

    default:
        break;
    }


    return QFrame::eventFilter(object, event);
}


/**********************
 *
 * Settings
 *
 * *******************/



void IndigoPanel::setCaption(const QString title, int fontSize){
    wdg_handle->setCaption(title, fontSize);
}



QString IndigoPanel::Caption(){
    return wdg_handle->Caption();
}



QIcon IndigoPanel::Icon(){
    return ico_icon;
}



void IndigoPanel::setIcon(QIcon icon, int iconSize){
    ico_icon = icon;
    wdg_handle->setIcon(icon, iconSize); // iconSize will used for icon in caption bar
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



void IndigoPanel::addWidget(QWidget *content){
    lyt_normalArea->addWidget(content);
}



void IndigoPanel::addWidget(QLayout *content){

    QWidget *widget = new QWidget();
    widget->setLayout(content);

    addWidget(widget);
}



IndigoPanelHandle::IndigoExpanderState IndigoPanel::expanderState(){
    return m_expander;
}



void IndigoPanel::setExpanderState(IndigoPanelHandle::IndigoExpanderState expanderState){
    m_expander = expanderState;

    switch(expanderState){
    case IndigoPanelHandle::Normal:
        wdg_handle->setExpanderState(expanderState);
        emit isNormal();
        qDebug() << "emit: isNormal();" << endl;
        break;

    case IndigoPanelHandle::Advanced:

        wdg_handle->setExpanderState(expanderState);
        emit isAdvanced();
        qDebug() << "emit: isAdvanced();" << endl;
        break;
    }
}



void IndigoPanel::setExpanderState(int expanderState){

    switch(expanderState){
    case 0:{
        setExpanderState(IndigoPanelHandle::Normal);
        break;
    }
    case 1:{
        setExpanderState(IndigoPanelHandle::Advanced);
        break;
    }
    default:{
        setExpanderState(IndigoPanelHandle::Normal);
        break;
    }

    }
}



IndigoPanel::IndigoDockState IndigoPanel::dockState(){
    return m_state;
}



void IndigoPanel::setDockState(IndigoPanel::IndigoDockState state){
    m_state = state;

    switch(state){
    case IndigoPanel::HiddenDocked:
        QFrame::hide();
        break;

    case IndigoPanel::Floating:
        setWindowFlags(Qt::Tool | Qt::CustomizeWindowHint);
        this->adjustSize();
        QFrame::show();
        break;

    case IndigoPanel::Docked:
    case IndigoPanel::None:
    default:
        QFrame::show();
        break;
    }

    update();

}



void IndigoPanel::setDockState(int state){

    switch(state){
    case 0:{
        setDockState(IndigoPanel::HiddenDocked);
        break;
    }
    case 1:{
        setDockState(IndigoPanel::Floating);
        break;
    }
    case 2:{
        setDockState(IndigoPanel::Docked);
        break;
    }
    default:{
        setDockState(IndigoPanel::None);
        break;
    }

    }
}
