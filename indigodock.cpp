#include "indigodock.h"
#include "mainwindow.h"
#include <QtGui>



IndigoDock::IndigoDock(QWidget *parent) :
    QMainWindow(parent)
{
    setDockNestingEnabled(true);
    setCentralWidget(0);
    setAcceptDrops(true);
    setMouseTracking(true);

    setStyleSheet(
                "IndigoDock::separator"
                "{"
                    "background: lightgrey;"
                    "width: 4px;"
                    "border: none;"
                "}"
                );

    // Dummy Panel
    createIndigoPanel("Property");

}



// active Docking Widget
static IndigoPanel* ip = NULL;


void IndigoDock::createIndigoPanel(QString title)
{
    IndigoPanel *dock = new IndigoPanel(this);
    dock->setAllowedAreas(Qt::AllDockWidgetAreas);
    dock->setWindowTitle(title);
    dock->installEventFilter( this );

    addDockWidget(Qt::RightDockWidgetArea, dock);

    connect(dock, SIGNAL(dockLocationChanged (Qt::DockWidgetArea)) , this, SLOT(dragEnded()));

}

/*void IndigoDock::addIndigoPanel(IndigoPanel * panel){
    addDockWidget(Qt::RightDockWidgetArea, panel);
}*/


bool IndigoDock::eventFilter( QObject * watched, QEvent * event )
{
    IndigoPanel *ipan = qobject_cast<IndigoPanel *>(watched);

    if( watched == ipan )
    {
        switch( event->type() )
                {
                case QEvent::MouseButtonPress:
                 qDebug() << "PanelMousePress" << endl;
                    //event->ignore(); // not sure if this is necessary

                 ip = ipan;
                    break;
                default:
                    break;
                };
    }


    return QObject::eventFilter(watched, event);
}



bool IndigoDock::event ( QEvent * event )
{
    switch ( event->type() ) {
        case QEvent::HoverEnter:{

            if(ip && ip->parent() != this)
              {

                addDockWidget(Qt::RightDockWidgetArea, ip);
                ip = NULL;

            }

            //qDebug() << "hoverEnter" << endl;
            break;
        }
        case QEvent::HoverLeave:{
             //qDebug() << "hoverLeave" << endl;
             ip = NULL;
            break;
        }
        case QEvent::HoverMove:  {
            //qDebug() << "hoverMove" << endl;
              break;
        }
        default:
           break;
    }
    return QMainWindow::event(event);
}


 void IndigoDock::dragEnded()
  {
    ip = NULL;
  }

 IndigoDock::~IndigoDock()
 {
 }

