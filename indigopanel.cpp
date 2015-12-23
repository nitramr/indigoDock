#include "indigopanel.h"
#include <QPushButton>
#include "qapplication.h"
#include <QDrag>
#include <QStyle>
#include <QStyleOptionDockWidget>

IndigoPanelHandle::IndigoPanelHandle(QWidget *parent) :
    QWidget(parent)
{

    setAutoFillBackground( true );


    // Objects
    m_lblTitle = new QLabel("");
    QFont font = m_lblTitle->font();
    font.setPointSize(10);
    font.setBold(true);
    m_lblTitle->setFont(font);

    m_btnClose = new QToolButton(this);
    m_btnClose->setFixedSize(16,18);
    m_btnClose->setAutoRaise(true);
    m_btnClose->setFocusPolicy(Qt::NoFocus);

    m_btnFloat = new QToolButton(this);
    m_btnFloat->setFixedSize(16,18);
    m_btnFloat->setAutoRaise(true);
    m_btnFloat->setFocusPolicy(Qt::NoFocus);

    QStyleOptionDockWidget opt;
    m_btnClose->setIcon(style()->standardIcon(QStyle::SP_TitleBarCloseButton, &opt, this));
    m_btnFloat->setIcon(style()->standardIcon(QStyle::SP_TitleBarShadeButton, &opt, this)); // SP_TitleBarUnshadeButton // http://doc.qt.io/qt-4.8/qstyle.html


    // Main LayoutContainer
    QHBoxLayout * mainLayout = new QHBoxLayout;
    mainLayout->setMargin(4);
    setLayout(mainLayout);

    mainLayout->addWidget(m_lblTitle);
    mainLayout->addStretch(1);
    mainLayout->addWidget(m_btnFloat);
    mainLayout->addWidget(m_btnClose);

    // Actions
    connect(m_btnClose, SIGNAL (clicked()), parent, SLOT (hide()));
    connect(m_btnFloat, SIGNAL (clicked()), parent, SLOT (expander()));

}



void IndigoPanelHandle::setTitle(const QString &title){
    m_lblTitle->setText(title);
}


/*********************************************************************************/


IndigoPanel::IndigoPanel(QString name, QWidget *parent) :
   QFrame(parent)
{
    // General Properties
    setMouseTracking(true);
    setAutoFillBackground( true );

    this->setObjectName(name);
    this->setFixedWidth(220);
    //this->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum));


    // Widgets
    m_handle = new IndigoPanelHandle(this);
    m_handle->installEventFilter(this);
    m_handle->setFixedHeight(30);

    m_normalContainer = new QWidget;
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
    m_mainLayout->addStretch(1);


    // Extended Properties
    m_index = -1;
    m_state = IndigoPanel::None;
    m_expander = IndigoPanel::Normal;
    m_extendedContainer->hide();

}


bool IndigoPanel::eventFilter(QObject *o, QEvent *event)
{

    switch( event->type() )
    {
    case QEvent::MouseButtonPress:
    {

        QMouseEvent *me = static_cast<QMouseEvent *>(event);


        if (me->buttons() == Qt::LeftButton) {

           // QPoint point = me->globalPos();

            qDebug() << "PanelIndex is:" << Index() << endl;

            if(dockState() == IndigoPanel::Floating){
                //QPixmap pixmap = QWidget::grab();
                // TODO: replace real QWidget with pixmap proxy

                //setWindowFlags(Qt::ToolTip|Qt::FramelessWindowHint); // avoid flickering by moving, will replaced by pixmap
                //show();
            }

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

                QPoint xy = this->mapToGlobal(QPoint(0,0));

                // mouse press relative position
                relative_x = point.x() - xy.x();
                relative_y = point.y() - xy.y();

                emit isFloating(m_index);
                setDockState(IndigoPanel::Floating);

                setParent(m_Parent);
                setWindowFlags(Qt::ToolTip|Qt::FramelessWindowHint); // avoid flickering by moving, will replaced by pixmap

                move(xy);
                show();

            }


            move(QPoint(point.x() - relative_x, point.y() - relative_y));

            emit mouseMove(this->height()); // activate DropZone hover*/

        }



        break;
    }
    case QEvent::MouseButtonRelease:
    {


        if(dockState() == IndigoPanel::Floating){

            setWindowFlags(Qt::Tool|Qt::FramelessWindowHint);
            show();

            emit mouseReleased(); // activate reparenting in DropZone*/
        }

        //qDebug() << "MouseReleased" << dockState()<< endl;

        break;

    }

    default:
        break;
    }



    return QFrame::eventFilter(o, event);
}



void IndigoPanel::setCaption(const QString title){
    m_handle->setTitle(title);
}



void IndigoPanel::setIcon(QIcon icon){
    m_icon = icon;
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

    switch(expanderState()){
    case IndigoPanel::Normal:

        if(!m_extendedArea->isEmpty()){
            m_extendedContainer->show();
            setExpanderState(IndigoPanel::Advanced);
        }else{
            m_normalContainer->hide();
            m_extendedContainer->hide();
            setExpanderState(IndigoPanel::Collapsed);
        }
        break;

    case IndigoPanel::Advanced:

        m_normalContainer->hide();
        m_extendedContainer->hide();
        setExpanderState(IndigoPanel::Collapsed);
        break;

    case IndigoPanel::Collapsed:

        if(!m_normalArea->isEmpty()){
            m_normalContainer->show();
            setExpanderState(IndigoPanel::Normal);
        }else{
            m_extendedContainer->show();
            setExpanderState(IndigoPanel::Advanced);
        }

        break;
    }

   /* QSize s = sizeHint();
    s.setHeight(height());
    resize(s);*/

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
