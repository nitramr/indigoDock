#include "indigopanel.h"
#include <QPushButton>

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


               // undock Panel
               if(parent() != NULL){

                   qDebug() << "Pan2 Parent != 0" << endl;

                   setParent(0);
                   setWindowFlags(windowFlags() |Qt::ToolTip /*|Qt::WindowStaysOnTopHint*/| Qt::FramelessWindowHint);
                   move(xy);
                   show();


               }
            }

            break;
        }

        case QEvent::MouseButtonRelease:
        {
                emit mouseReleased();
                break;
        }

        case QEvent::MouseMove:
        {
                QPoint point = QCursor::pos();
                move(QPoint(point.x() - relative_x, point.y() - relative_y));
                emit mouseMove();
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
