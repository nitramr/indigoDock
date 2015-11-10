#include "indigopanel.h"
#include <QPushButton>
#include "qapplication.h"

/*
 * TODO:
 * - Create a WidgetList and store all undocked Panels in it (in IndigoDock).
 * - fix panel flickering by mous move on multi-screens with different screen height
 */

IndigoPanel::IndigoPanel(QWidget *parent) :
   QFrame(parent)
{

    setAutoFillBackground( true );

    // Dummy Widget as handleBar
    handle = new IndigoPanelHandle(this);
    handle->installEventFilter(this);
    handle->setFixedHeight(30);
    //handle->setTitle("Property"); // set panel title
    //handle->setBackgroundColor(QColor( 240, 240, 240 )); // set bg color for title bar

    // Content Widget
    contentArea = new QHBoxLayout;

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



}


bool IndigoPanel::eventFilter(QObject *o, QEvent *event)
{

    switch( event->type() )
    {
        case QEvent::MouseButtonPress:
        {

            QMouseEvent *me = static_cast<QMouseEvent *>(event);

            if (me->buttons() == Qt::LeftButton) {

                QPoint point = QCursor::pos();

                QPoint xy = mapToGlobal(QPoint(0,0));

                // mouse press relative position
                relative_x = point.x() - xy.x();
                relative_y = point.y() - xy.y();

                // undock Panel if not already undocked
                if(parent() != mainWindow){

                    qDebug() << "Panel is undocked: Panel Parent == MainWindow" << endl;
                    setParent(mainWindow);

                    // flickering can be solved by change window type to tooltip, but no window resizing possible
                    setWindowFlags(windowFlags() |Qt::Tool /*|Qt::ToolTip*/ /*|Qt::WindowStaysOnTopHint*/| Qt::FramelessWindowHint);

                    move(xy);
                    show();

                }

            }

            break;
        }

        case QEvent::MouseButtonRelease:
        {
                emit mouseReleased(); // activate reparenting in DropZone
                break;
        }

        case QEvent::MouseMove:
        {

                QPoint point = QCursor::pos();
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
