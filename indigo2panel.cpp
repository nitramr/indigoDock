#include "indigo2panel.h"
#include <QPushButton>

Indigo2Panel::Indigo2Panel(QWidget *parent) :
   QFrame(parent)
{


    palette.setColor( QPalette::Background, QColor( 200, 200, 200 ) );
    setPalette( palette );
    setAutoFillBackground( true );

     //connect(qApp, SIGNAL(close(bool)) , this, SLOT(close(bool)));

    // Dummy Widget as handleBar
    handle = new Indigo2PanelHandle();
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

}


bool Indigo2Panel::eventFilter(QObject *o, QEvent *event)
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
                   setWindowFlags(windowFlags() |Qt::ToolTip | Qt::FramelessWindowHint);
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
                break;
        }

        default:
                break;
    }



    return QFrame::eventFilter(o, event);
}


void Indigo2Panel::close(bool * exit){

    if(exit){
        qDebug() << "Close" << endl;
    }

}
