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

    m_title = "";

    // Objects 
    m_btnClose = new QToolButton(this);
    m_btnClose->setFixedSize(16,16);
    m_btnClose->setAutoRaise(true);
    m_btnClose->setFocusPolicy(Qt::NoFocus);

    m_btnFloat = new QToolButton(this);
    m_btnFloat->setFixedSize(16,16);
    m_btnFloat->setAutoRaise(true);
    m_btnFloat->setFocusPolicy(Qt::NoFocus);

    QStyleOptionDockWidget opt;
    m_btnClose->setIcon(style()->standardIcon(QStyle::SP_TitleBarCloseButton, &opt, this));
    m_btnFloat->setIcon(style()->standardIcon(QStyle::SP_TitleBarShadeButton, &opt, this)); // SP_TitleBarUnshadeButton // http://doc.qt.io/qt-4.8/qstyle.html


    // Main LayoutContainer
    QHBoxLayout * mainLayout = new QHBoxLayout;
    mainLayout->setMargin(4);
    setLayout(mainLayout);

    mainLayout->addStretch(1);
    mainLayout->addWidget(m_btnFloat);
    mainLayout->addWidget(m_btnClose);

    // Actions
    connect(m_btnClose, SIGNAL (clicked()), parent, SLOT (hide()));
    connect(m_btnFloat, SIGNAL (clicked()), parent, SLOT (expander()));

}



void IndigoPanelHandle::setTitle(QString title, int fontSize){

    m_title = title;
    m_fontSize = fontSize;
}



void IndigoPanelHandle::setIcon(QIcon icon, int iconSize){

    m_icon = icon;
    m_iconSize = iconSize;
}


void IndigoPanelHandle::paintEvent(QPaintEvent *)
{

    QPainter p(this);


    int h = this->height();
    int iconY = (h - m_iconSize) / 2;

    QFont font = p.font() ;
    font.setPointSize ( m_fontSize );
    font.setWeight(QFont::DemiBold);
    QFontMetrics fm(this->font());
    int lbl_width = fm.width(m_title);


    if (h > 0)
    {
        int labelX = m_iconSize + 4;

        p.drawPixmap(QRect(0, iconY, m_iconSize,m_iconSize),m_icon.pixmap(m_iconSize,m_iconSize));
        p.setFont(font);
        p.drawText( QRect(labelX, 0, lbl_width, h), Qt::AlignVCenter, m_title );
    }
}



//
// IndigoPanel
//


IndigoPanel::IndigoPanel(QString name, QWidget *parent) :
   QFrame(parent, Qt::ToolTip|Qt::WindowStaysOnTopHint|Qt::CustomizeWindowHint)
{
    // General Properties
    setMouseTracking(true);
    setAutoFillBackground( true );
    setBackgroundRole(QPalette::Background);
    //setWindowFlags(Qt::ToolTip|Qt::WindowStaysOnTopHint|Qt::CustomizeWindowHint);

    this->setObjectName(name);
    this->setMinimumWidth(220);
    this->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding));


    // Widgets
    m_handle = new IndigoPanelHandle(this);
    m_handle->installEventFilter(this);
    m_handle->setFixedHeight(30);

    m_normalContainer = new QWidget;
    m_normalContainer->setMinimumHeight(100); // simulate fake content - remove for productive usage
    m_extendedContainer = new QWidget;

    m_normalArea = new QVBoxLayout(m_normalContainer);
    m_normalArea->setMargin(0);
    m_extendedArea = new QVBoxLayout(m_extendedContainer);
    m_extendedArea->setMargin(0);

    m_Parent = parent;

    // Layouts
    m_mainLayout = new QVBoxLayout;
    m_mainLayout->setMargin(0);
    setLayout(m_mainLayout);

    m_mainLayout->addWidget(m_handle);
    m_mainLayout->addWidget(m_normalContainer);
    m_mainLayout->addWidget(m_extendedContainer);
    m_mainLayout->setAlignment(Qt::AlignTop);

    m_spacer = new QSpacerItem(10, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding);
    m_mainLayout->addSpacerItem(m_spacer);

    // Extended Properties
    m_index = -1;
    m_state = IndigoPanel::None;
    m_expander = IndigoPanel::Normal;
    m_extendedContainer->hide();

}


// http://doc.qt.io/qt-5/qtwidgets-widgets-shapedclock-example.html


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

            relativeOffset = point - xy;


            /*if(dockState() == IndigoPanel::Floating){
                //QPixmap pixmap = QWidget::grab();
                // TODO: replace real QWidget with pixmap proxy

            }*/
            me->accept();
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

                //QPixmap pixmap = QWidget::grab();
                // TODO: replace real QWidget with pixmap proxy


                setParent(m_Parent);

                setWindowFlags(Qt::ToolTip|Qt::WindowStaysOnTopHint|Qt::CustomizeWindowHint); // avoid flickering by moving, will replaced by pixmap

                show();

                //setParent(m_Parent);

                setDockState(IndigoPanel::Floating);
                emit isFloating(m_index);


            }

            move(point - relativeOffset);
            me->accept();

            emit mouseMove(); // activate DropZone hover*


        }


        break;
    }

    case QEvent::MouseButtonRelease:
    {


        if(dockState() == IndigoPanel::Floating){

            setWindowFlags(Qt::Tool
                           | Qt::WindowStaysOnTopHint
                           | Qt::CustomizeWindowHint);
            show();

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
    m_handle->setTitle(title, fontSize);
}



void IndigoPanel::setIcon(QIcon icon, int iconSize){
    m_icon = icon;
    m_handle->setIcon(icon, iconSize); // iconSize will used for icon in caption bar
}



QIcon IndigoPanel::Icon(){
    return m_icon;
}



/**
 * @brief IndigoPanel::Index
 * @return index in dropzone
 */
int IndigoPanel::Index(){
    return m_index;
}



/**
 * @brief IndigoPanel::setIndex
 * @param index
 */
void IndigoPanel::setIndex(int index){
     m_index = index;
}



void IndigoPanel::addWidgetNormal(QWidget *content){
     m_normalArea->addWidget(content);

}



void IndigoPanel::addWidgetExtend(QWidget *content){
     m_extendedArea->addWidget(content);

}



void IndigoPanel::hide(){

     if(dockState() == IndigoPanel::Docked){
         setDockState(IndigoPanel::HiddenDocked);
         emit panelClosed(Index());
     }else if(dockState() == IndigoPanel::Floating){
         setDockState(IndigoPanel::HiddenFloating);
     }

     QFrame::hide();
}



void IndigoPanel::show(){

    if(dockState() == IndigoPanel::HiddenDocked){
        setDockState(IndigoPanel::Docked);
        emit panelShown(Index());
    }else if(dockState() == IndigoPanel::HiddenFloating){
        setDockState(IndigoPanel::Floating);
    }

    QFrame::show();
}



void IndigoPanel::expander(){

   // QSize s = sizeHint();
   // s.setHeight(this->m_handle->height());

    m_mainLayout->removeItem(m_spacer);

    switch(expanderState()){
    case IndigoPanel::Normal:

        if(!m_extendedArea->isEmpty()){
            m_extendedContainer->show();
            setExpanderState(IndigoPanel::Advanced);

            m_mainLayout->addItem(m_spacer);

        }else{
            m_normalContainer->hide();
            m_extendedContainer->hide();
            setExpanderState(IndigoPanel::Collapsed);

            //resize(s);
        }
        break;

    case IndigoPanel::Advanced:

        m_normalContainer->hide();
        m_extendedContainer->hide();
        setExpanderState(IndigoPanel::Collapsed);

        //resize(s);

        break;

    case IndigoPanel::Collapsed:

        if(!m_normalArea->isEmpty()){
            m_normalContainer->show();
            setExpanderState(IndigoPanel::Normal);

            m_mainLayout->addItem(m_spacer);

        }else{
            m_extendedContainer->show();
            setExpanderState(IndigoPanel::Advanced);

            m_mainLayout->addItem(m_spacer);

        }

        break;
    }

    this->adjustSize();
}



IndigoPanel::IndigoState IndigoPanel::dockState(){
    return m_state;
}



void IndigoPanel::setDockState(IndigoPanel::IndigoState state){
    m_state = state;
}



IndigoPanel::IndigoExpander IndigoPanel::expanderState(){
    return m_expander;
}



void IndigoPanel::setExpanderState(IndigoPanel::IndigoExpander expander){
    m_expander = expander;
}
