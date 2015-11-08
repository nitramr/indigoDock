#include <indigodropzone.h>
#include "mainwindow.h"
#include "indigotabwidget.h"
#include <QtGui>



IndigoDropZone::IndigoDropZone(QWidget *parent) :
    QMainWindow(parent)
{
    setDockNestingEnabled(true);
    setCentralWidget(0);
    setMouseTracking(true);

    setStyleSheet(
                "IndigoDropZone::separator"
                "{"
                    "background: lightgrey;"
                    "width: 4px;"
                    "border: none;"
                "}"
                );

    // Dummy Panel
    createIndigoPanel("Property");

}

void IndigoDropZone::createIndigoPanel(QString title)
{
    IndigoPanel *dock = new IndigoPanel(this);
    dock->setAllowedAreas(Qt::AllDockWidgetAreas);
    dock->setWindowTitle(title);
    dock->installEventFilter( this );

    addDockWidget(Qt::RightDockWidgetArea, dock);

}

bool IndigoDropZone::eventFilter( QObject * watched, QEvent * event )
{
    IndigoPanel *pan = qobject_cast<IndigoPanel *>(watched);

    if( watched == pan )
    {
        switch( event->type() )
                {
                case QEvent::MouseButtonRelease:
                {

                    QPoint cursor = this->mapFromGlobal(QCursor::pos());

                    if (this->rect().contains(cursor) ) {

                        if(IndigoTabWidget *tab = qobject_cast<IndigoTabWidget*>(parent()->parent())) {
                            //qDebug() << "DropZone Parent " << tab << endl;

                            IndigoDropZone *zone = qobject_cast<IndigoDropZone*>(tab->activeWidget);

                           // qDebug() << "Panel Parent: " << pan->parent() << endl;

                            if (pan->parent() == zone) break;
                            //IndigoDropZone *panParent = qobject_cast<IndigoDropZone*>(pan->parent());
                            //panParent->removeDockWidget(pan);


                            // BUG: if a dockwidget is redocking in an previous one App is crashing
                            zone->addDockWidget(Qt::RightDockWidgetArea, pan);

                            qDebug() << "Panel: " << pan << " in DropZone: " << zone << endl;
                        }else{
                            qDebug() << "DropZone parent is not type of IndigoTabWidget, parent is: " << parent()->parent() << endl;
                        }

                    }

                    break;
                }
                default:
                    break;
                };
    }


    return QObject::eventFilter(watched, event);
}

 IndigoDropZone::~IndigoDropZone()
 {
 }
