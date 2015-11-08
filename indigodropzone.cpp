#include <indigodropzone.h>
#include "mainwindow.h"
#include "indigotabwidget.h"
#include <QtGui>

/**
 *
 * If an IndigoPanel drops in the DropZone the DropZone search in parent TabBar for active DropZone and set these as parent for the dropped IndigoPanel.
 *
 *
 * @brief IndigoDropZone::IndigoDropZone
 * @param parent
 */

static IndigoPanel * iPan = NULL;

IndigoDropZone::IndigoDropZone(QWidget *parent) :
    QMainWindow(parent)
{
    setDockNestingEnabled(true);
    setCentralWidget(0);
    //setMouseTracking(true);

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
                            qDebug() << "DropZone Parent: " << tab << endl;

                            if(IndigoDropZone *zone = qobject_cast<IndigoDropZone*>(tab->activeWidget)){
                                qDebug() << "DropZone: " << zone << endl;

                                qDebug() << "Panel Parent old: " << pan->parent() << endl;

                                iPan = pan;

                                if (iPan && iPan->parent() != zone){
                                    // BUG: if a dockwidget is redocking in an previous DropZone App is crashing
                                    zone->addDockWidget(Qt::RightDockWidgetArea, iPan);
                                    iPan = NULL;
                                    qDebug() << "Panel: " << iPan << " in DropZone: " << zone << endl;
                                }
                            }else qDebug() << "DropZone has no active Widget" << endl;
                        }else qDebug() << "DropZone parent is not type of IndigoTabWidget, parent is: " << parent()->parent() << endl;

                    }

                    break;
                }
                default:
                    break;
                }
    }


    return QObject::eventFilter(watched, event);
}

 IndigoDropZone::~IndigoDropZone()
 {
 }
