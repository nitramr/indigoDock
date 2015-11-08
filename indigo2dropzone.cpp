#include "indigo2dropzone.h"

Indigo2DropZone::Indigo2DropZone(QWidget *parent) :
   QWidget(parent)
{

    QPalette palette;
    palette.setColor( QPalette::Background, QColor( 250, 250, 255 ) );
    setPalette( palette );
    setAutoFillBackground( true );


    layout = new QVBoxLayout;
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->setContentsMargins(0,0,0,0);
    setLayout(layout);

    // Demo Panels
    createPanel();

}


void Indigo2DropZone::createPanel()
{
    Indigo2Panel * pan = new Indigo2Panel(this);
    this->connect(pan, SIGNAL(mouseReleased()), this, SLOT(dropPanel()));
    layout->addWidget(pan);

}

void Indigo2DropZone::dropPanel()
{
    QPoint cursor = this->mapFromGlobal(QCursor::pos());

    if (this->rect().contains(cursor) ) {

        Indigo2Panel *pan = qobject_cast<Indigo2Panel *>(sender());

        if(Indigo2Tabbar *tab = qobject_cast<Indigo2Tabbar*>(parent()->parent())) {
            qDebug() << "DropZone Parent " << tab << endl;

            Indigo2DropZone *zone = qobject_cast<Indigo2DropZone*>(tab->activeWidget);

            //pan->setParent(this);
            pan->setParent(zone);
            pan->move(this->pos());

            // add panel in Layout Container
            zone->layout->addWidget(pan);

            pan->show();
            qDebug() << "Pan2 In Dock2 " << pan << " in " << zone << endl;
        }else{
            qDebug() << "DropZone parent is not type of IndigoTabbar" << endl;
        }

    }
}


bool Indigo2DropZone::event ( QEvent * event )
{
    switch ( event->type() ) {
        case QEvent::HoverEnter:{

           /* if(ip && ip->parent() != this)
              {

                addDockWidget(Qt::RightDockWidgetArea, ip);
                ip = NULL;

            }*/

            qDebug() << "hoverEnter" << endl;
            break;
        }
        case QEvent::HoverLeave:{
             qDebug() << "hoverLeave" << endl;
             //ip = NULL;
            break;
        }
        case QEvent::HoverMove:  {
            //qDebug() << "hoverMove" << endl;
              break;
        }
        default:
           break;
    }
    return QWidget::event(event);
}
