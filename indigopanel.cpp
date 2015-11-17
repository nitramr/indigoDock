#include "indigopanel.h"
#include <QPushButton>
#include "qapplication.h"
#include <QDrag>
#include <QStyle>
#include <indigoexpandergroup.h> // tmp include for demo elements
#include "colorswatch.h"
#include "QStyleOptionDockWidget"

IndigoPanelHandle::IndigoPanelHandle(QWidget *parent) :
    QWidget(parent)
{

    setAutoFillBackground( true );

    // Objects
    m_lblTitle = new QLabel("");

    m_btnClose = new QToolButton(this);
    m_btnClose->setFixedSize(16,18);
    m_btnClose->setAutoRaise(true);
    m_btnClose->setFocusPolicy(Qt::NoFocus);

   /* m_btnFloat = new QToolButton(this);
    m_btnFloat->setFixedSize(16,18);
    m_btnFloat->setAutoRaise(true);
    m_btnFloat->setFocusPolicy(Qt::NoFocus);*/

    QStyleOptionDockWidget opt;
    m_btnClose->setIcon(style()->standardIcon(QStyle::SP_TitleBarCloseButton, &opt, this));
   // m_btnFloat->setIcon(style()->standardIcon(QStyle::SP_TitleBarNormalButton, &opt, this));

    // Styles
    m_lblTitle->setStyleSheet("QLabel {"
                            "font-weight: bold;"
                            "font-size:10pt;"
                        "}"
                       );





    // Main LayoutContainer
    QHBoxLayout * mainLayout = new QHBoxLayout;
    mainLayout->setMargin(4);
    setLayout(mainLayout);

    mainLayout->addWidget(m_lblTitle);
    mainLayout->addStretch(1);
   // mainLayout->addWidget(m_btnFloat);
    mainLayout->addWidget(m_btnClose);

    // Actions
    connect(m_btnClose, SIGNAL (clicked()), parent, SLOT (hide()));
   // connect(m_btnFloat, SIGNAL (clicked()), parent, SLOT (dock()));


}

void IndigoPanelHandle::setTitle(const QString &title){
    m_lblTitle->setText(title);
}

void IndigoPanelHandle::setBackgroundColor(const QColor &bgColor){
     palette.setColor( QPalette::Background, bgColor );
     setPalette( palette );
}

/*********************************************************************************/

/*
 * TODO:
 * - Create a WidgetList and store all undocked Panels in it (in IndigoDock).
 */

IndigoPanel::IndigoPanel(QWidget *parent) :
   QFrame(parent)
{

    setAutoFillBackground( true );
    setMouseTracking(true);

    // Dummy Widget as handleBar
    m_handle = new IndigoPanelHandle(this);
    m_handle->installEventFilter(this);
    m_handle->setFixedHeight(30);

    // Content Widget
    m_contentArea = new QVBoxLayout;

    // Main LayoutContainer
    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    setLayout(mainLayout);

    mainLayout->addWidget(m_handle);
    mainLayout->addLayout(m_contentArea);
    mainLayout->addStretch(1);

    // lastParent
    m_lastParentWidget = parent;

    // TODO: Replace MainWindow with WidgetList in IndigoDock
    foreach(QWidget *mWindow, QApplication::topLevelWidgets()) {
      if(mWindow->inherits("QMainWindow")){
          m_mainWindow = mWindow;

      }
    }


    // Add dummy content
    IndigoExpanderGroup *group = new IndigoExpanderGroup();
    IndigoExpanderGroup *group2 = new IndigoExpanderGroup();
    ColorSwatch * colSwatch = new ColorSwatch();
    group->addWidget(colSwatch);
    m_contentArea->addWidget(group);
    m_contentArea->addWidget(group2);

}


bool IndigoPanel::eventFilter(QObject *o, QEvent *event)
{

    switch( event->type() )
    {
        case QEvent::MouseButtonPress:
        {

            QMouseEvent *me = static_cast<QMouseEvent *>(event);

            if (me->buttons() == Qt::LeftButton) {


                // undock Panel if not already undocked
                if(parent() != m_mainWindow){

                    QPoint point = me->globalPos();//QCursor::pos();

                    QPoint xy = this->mapToGlobal(QPoint(0,0));

                    // mouse press relative position
                    relative_x = point.x() - xy.x();
                    relative_y = point.y() - xy.y();

                    qDebug() << "Panel is undocked: Panel Parent == MainWindow" << endl;
                    setParent(m_mainWindow);

                    //setWindowFlags(windowFlags() |Qt::ToolTip/*|Qt::WindowStaysOnTopHint*/|Qt::FramelessWindowHint);
                    setWindowFlags(Qt::ToolTip|Qt::FramelessWindowHint); // avoid flickering by moving

                    move(xy);
                    show();

                }

            }

            break;
        }

        case QEvent::MouseButtonRelease:
        {

                setWindowFlags(Qt::Tool|Qt::FramelessWindowHint); // set back to a resizeable window type

                show();

                emit mouseReleased(); // activate reparenting in DropZone
                break;
        }

        case QEvent::MouseMove:
        {


            QMouseEvent *me = static_cast<QMouseEvent *>(event);

            QPoint point = me->globalPos();//QCursor::pos();

            move(QPoint(point.x() - relative_x, point.y() - relative_y));


            emit mouseMove(); // activate DropZone hover
            break;
        }

        default:
                break;
    }



    return QFrame::eventFilter(o, event);
}


void IndigoPanel::setBackgroundColor(const QColor &bgColor){
     palette.setColor( QPalette::Background, bgColor );
     setPalette( palette );
}

void IndigoPanel::addWidget(QWidget *content){
     m_contentArea->addWidget(content);
}

void IndigoPanel::hide(){
     qDebug() << "Pan hide" << endl;

    // TODO: set entry in WatchList to show this again

     QFrame::hide();
}

void IndigoPanel::dock(){
     qDebug() << "Pan dock" << endl;

    // TODO: set entry in WatchList to show this again


}

void IndigoPanel::setLastParent(QWidget *dropzone){
    //lastParentWidget = dropzone; // unused
}

QWidget *IndigoPanel::lastParent(){
    return m_lastParentWidget;
}
