#include "indigopanel.h"
#include <QPushButton>
#include "qapplication.h"
#include <QDrag>
#include <indigogroupbox.h>

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
    handle = new IndigoPanelHandle(this);
    handle->installEventFilter(this);
    handle->setFixedHeight(30);
    //handle->setTitle("Property"); // set panel title
    //handle->setBackgroundColor(QColor( 240, 240, 240 )); // set bg color for title bar

    // Content Widget
    contentArea = new QVBoxLayout;

    // Main LayoutContainer
    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    setLayout(mainLayout);

    mainLayout->addWidget(handle);
    mainLayout->addLayout(contentArea);
    mainLayout->addStretch(1);

    // lastParent
    lastParentWidget = parent;

    // TODO: Replace MainWindow with WidgetList in IndigoDock
    foreach(QWidget *mWindow, QApplication::topLevelWidgets()) {
      if(mWindow->inherits("QMainWindow")){
          mainWindow = mWindow;

      }
    }


    // Add dummy content
    IndigoGroupBox *group = new IndigoGroupBox();
    IndigoGroupBox *group2 = new IndigoGroupBox();
    contentArea->addWidget(group);
    contentArea->addWidget(group2);

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
                if(parent() != mainWindow){

                    QPoint point = me->globalPos();//QCursor::pos();

                    QPoint xy = this->mapToGlobal(QPoint(0,0));

                    // mouse press relative position
                    relative_x = point.x() - xy.x();
                    relative_y = point.y() - xy.y();

                    qDebug() << "Panel is undocked: Panel Parent == MainWindow" << endl;
                    setParent(mainWindow);

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
     contentArea->addWidget(content);
}

void IndigoPanel::hide(){
     qDebug() << "Pan hide" << endl;

    // TODO: set entry in WatchList to show this again

     QFrame::hide();
}

void IndigoPanel::setLastParent(QWidget *dropzone){
    //lastParentWidget = dropzone; // unused
}

QWidget *IndigoPanel::lastParent(){
    return lastParentWidget;
}
