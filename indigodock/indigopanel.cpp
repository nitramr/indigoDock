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
    setObjectName("IndigoPanelHandle");

    // Actions
    connect(wdg_btnClose, SIGNAL (clicked()), parent, SLOT (hide()));
    connect(wdg_btnExpander, SIGNAL (clicked()), parent, SLOT (toggleExpander()));

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

        p.drawPixmap(QRect(0, iconY, int_iconSize,int_iconSize),ico_icon.pixmap(int_iconSize*devicePixelRatio(),int_iconSize*devicePixelRatio()));
        p.setFont(font);
        p.drawText( QRect(labelX, 0, lbl_width, h), Qt::AlignVCenter, str_title );
    }
}


/**********************
 *
 * Properties
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

    resizing = false;
    int_handleWidth = 2;
    col_grip = QColor(this->palette().color(QPalette::Background));
    m_orientation = Qt::Vertical;
    QIcon icon = QIcon();

    // Widgets
    wdg_handle = new IndigoPanelHandle(this);
    wdg_handle->installEventFilter(this);

    wdg_grip = new QWidget();

    //    lyt_normalArea = new FlowLayout(int_padding);
    //    lyt_normalArea->setSizeConstraint( QLayout::SetNoConstraint );

    lyt_normalArea = new QVBoxLayout();//(wdg_normalContainer);
    lyt_normalArea->setMargin(int_padding);
    lyt_normalArea->addWidget(wdg_handle);

    QWidget * wdg_contentHolder = new QWidget();
    wdg_contentHolder->setLayout(lyt_normalArea);


    // Layouts
    lyt_main = new QBoxLayout(QBoxLayout::TopToBottom);
    lyt_main->setMargin(0);
    lyt_main->addWidget(wdg_contentHolder);
    lyt_main->addWidget(wdg_grip);
    lyt_main->setSizeConstraint(QLayout::SetMinimumSize);
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
    setIcon(icon, 0);
   // setHandleWidth(int_handleWidth);


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
        emit panelClosed(Index()); // used for tab
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
        emit panelShown(Index()); // used for tab
        qDebug() << "emit: panelShow(...);" << endl;
        break;
    default:
        QFrame::show();
        break;
    }

    update();
}



void IndigoPanel::toggleExpander(){


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


bool IndigoPanel::mouseInGrip(QPoint mousePos)
{
    switch(m_orientation){

    case Qt::Vertical:

        qDebug() << "Pos Grip Y" << height() - int_handleWidth -2 << "Pos Mouse Y" << mousePos.y() << endl;

        if(mousePos.y() > (height() - int_handleWidth -2)){           
            this->setCursor(Qt::SizeVerCursor);
            return true;
        }
        break;
    case Qt::Horizontal:

        if(mousePos.x() > (width() - int_handleWidth -2)){
            this->setCursor(Qt::SizeHorCursor);
            return true;
        }
        break;
    }

    this->setCursor(Qt::ArrowCursor);
    return false;

}



void IndigoPanel::mousePressEvent(QMouseEvent*event){

    if (event->buttons() == Qt::LeftButton) {

        // Check if we hit the grip handle
        if (mouseInGrip(event->pos())) {
            oldPos = event->pos();
            resizing = true;
        } else {
            resizing = false;
        }

    }
}



void IndigoPanel::mouseReleaseEvent(QMouseEvent*event){

    this->setCursor(Qt::ArrowCursor);

}



void IndigoPanel::mouseMoveEvent(QMouseEvent*event){


    qDebug() << "mouseMove" << endl;

    mouseInGrip(event->pos());

    if (event->buttons() == Qt::LeftButton) {


        switch(m_orientation){

        case Qt::Vertical:

            if (resizing) {
                QPoint delta = event->pos() - oldPos;
                oldPos = event->pos();

                setMinimumSize(width(), height()+delta.y());

            }

            break;
        case Qt::Horizontal:



            if (resizing) {
                QPoint delta = event->pos() - oldPos;
                oldPos = event->pos();

                setMinimumSize(width()+delta.x(), height());

            }

            break;
        }
    }


}


void IndigoPanel::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QColor colBase = col_grip;


    switch(m_orientation){

    case Qt::Vertical:
        p.fillRect(0,
                   height()-int_handleWidth,
                   width(),
                   int_handleWidth,
                   colBase);

        break;
    case Qt::Horizontal:
        p.fillRect(width()-int_handleWidth,
                   0,
                   int_handleWidth,
                   height(),
                   colBase);
        break;
    }


}


void IndigoPanel::leaveEvent(QEvent *){

    this->setCursor(Qt::ArrowCursor);

}



bool IndigoPanel::eventFilter(QObject *object, QEvent *event)
{

    switch( event->type() )
    {
    case QEvent::MouseButtonPress:
    {

        QMouseEvent *me = static_cast<QMouseEvent *>(event);

        if(object == wdg_handle && me->buttons() == Qt::LeftButton){
            QPoint point = me->globalPos();
            QPoint xy = this->mapToGlobal(QPoint(0,0));

            pnt_relativeOffset = point - xy;
        }


        break;
    }

    case QEvent::MouseMove:
    {
        QMouseEvent *me = static_cast<QMouseEvent *>(event);

        if(object == wdg_handle && me->buttons() == Qt::LeftButton){
            // undock Panel if not already undocked
            if(dockState() == IndigoPanel::Docked){
                emit isFloating();

                setDockState(IndigoPanel::Floating);
            }

            //  setWindowState(Qt::WindowActive);

            QPoint point = me->globalPos();
            move(point - pnt_relativeOffset);


            emit mouseMove(); // activate DropZone hover*

        }



        break;
    }

    case QEvent::MouseButtonRelease:
    {
        if(object == wdg_handle){
            if(dockState() == IndigoPanel::Floating){

                emit mouseReleased(); // activate reparenting in DropZone*
                qDebug() << "emit: mouseReleased();" << endl;
                update();
            }
        }

        break;
    }

    case QEvent::MouseButtonDblClick:
        if(object == wdg_handle){
            toggleExpander();
        }
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


    QPixmap pix(iconSize, iconSize);
    pix.fill(QColor(0,0,0,0));

    if(icon.isNull()){
        icon = QIcon(pix);
    }

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

    wdg_widget = content;

//    wdg_widget->setMinimumSize(this->minimumSize());
//    wdg_widget->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);

    lyt_normalArea->addWidget(wdg_widget);


    //  setMinimumSize(this->sizeFromContent(content->size()));


}



void IndigoPanel::addWidget(QLayout *content){

    QWidget *widget = new QWidget();
    widget->setLayout(content);

    addWidget(widget);
}


void IndigoPanel::setWidget(QWidget * widget)
{
    addWidget(widget);

}

QWidget *IndigoPanel::widget() const
{
    // QLayout *layout = qobject_cast<QLayout*>(lyt_normalArea);

    //  QLayoutItem *item = lyt_normalArea->itemAt(0);
    // return item == 0 ? 0 : item->widget();

    //return lyt_normalArea->layout()->widget();


    return wdg_widget == 0 ? 0 : new QWidget();

}



void IndigoPanel::setOrientation(Qt::Orientation orientation){
    m_orientation = orientation;

    switch(m_orientation){

    case Qt::Vertical:
        lyt_main->setDirection(QBoxLayout::TopToBottom);
        break;
    case Qt::Horizontal:
        lyt_main->setDirection(QBoxLayout::LeftToRight);
        break;
    }


    setHandleWidth(int_handleWidth);

}



void IndigoPanel::setHandleWidth(int width){

    int_handleWidth = width;

    switch(m_orientation){

    case Qt::Vertical:
        wdg_grip->setFixedHeight(int_handleWidth);
        wdg_grip->setMaximumWidth(QWIDGETSIZE_MAX);
        break;
    case Qt::Horizontal:
        wdg_grip->setFixedWidth(int_handleWidth);
        wdg_grip->setMaximumHeight(QWIDGETSIZE_MAX);
        break;
    }

  //  wdg_grip = new QSpacerItem(int_handleWidth, int_handleWidth);

}


void IndigoPanel::setGripColor(QColor color){

    col_grip = color;
    update();

}



void IndigoPanel::setWindowTitle(const QString &title){

    QWidget::setWindowTitle(title);
    setCaption(title);

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
