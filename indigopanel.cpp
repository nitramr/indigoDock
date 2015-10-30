#include "indigopanel.h"
#include <iostream>
#include <QDebug>


IndigoPanel::IndigoPanel(QWidget *parent) :
    QDockWidget(parent)
{
    parent->installEventFilter( this );

}


bool IndigoPanel::eventFilter( QObject * watched, QEvent * event )
{
    IndigoDock *idock = qobject_cast<IndigoDock *>(watched);

    if( watched == idock )
    {
        switch( event->type() )
                {
                case QEvent::HoverEnter:
                 qDebug() << "DockHover" << endl;
                //idock->addDockWidget(Qt::RightDockWidgetArea,this);
                    break;
                default:
                    break;
                };
    }


    return QObject::eventFilter(watched, event);
}

