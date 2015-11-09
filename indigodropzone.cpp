#include "indigodropzone.h"

/* TODO:
 *
 * - add better splitter widget (redocking within a dropzone
 *
 */

IndigoDropZone::IndigoDropZone(QWidget *parent) :
   QWidget(parent)
{

    setMouseTracking(true);

    colorNormal = QColor( 153, 153, 153 );
    colorHighlight = QColor( 101, 201, 243 );


    palette.setColor( QPalette::Background, colorNormal );
    setPalette( palette );
    setAutoFillBackground( true );

    padding = 6;

    splitter = new QSplitter();
    splitter->setHandleWidth(padding);
    splitter->setOrientation(Qt::Vertical);
    splitter->setStretchFactor(1, 1);
    splitter->move(this->pos());

    layout = new QVBoxLayout;
    layout->setMargin(padding);
    setLayout(layout);


}


void IndigoDropZone::createPanel(const QString &title, QWidget *widget)
{
    IndigoPanel * pan = new IndigoPanel(this);
    this->connect(pan, SIGNAL(mouseReleased()), this, SLOT(dropPanel()));
    this->connect(pan, SIGNAL(mouseMove()), this, SLOT(hoverZone()));
    pan->handle->setTitle(title);
    pan->addWidget(widget);
    //pan->setBackgroundColor(QColor( 204, 204, 204 ));
    //pan->handle->setBackgroundColor(QColor( 204, 204, 204 ));
    addPanel(pan);

}

void IndigoDropZone::hoverZone(){

    QPoint cursor = this->mapFromGlobal(QCursor::pos());

    if (this->rect().contains(cursor) ) {

        if(IndigoTabbar *tab = qobject_cast<IndigoTabbar*>(parent()->parent())) {

            IndigoDropZone *zone = qobject_cast<IndigoDropZone*>(tab->activeWidget);

            zone->setBackgroundColor(colorHighlight);

            //Paint Highlighter
           /* QPainter painter(zone);

            int width = size().width();
            int height = size().height();

            painter.fillRect(0, 0, width, height, colorHighlight);
            painter.fillRect(4, 4, width - 8, height-8, colorNormal);*/

        }

    }else{
        if(IndigoTabbar *tab = qobject_cast<IndigoTabbar*>(parent()->parent())) {

            IndigoDropZone *zone = qobject_cast<IndigoDropZone*>(tab->activeWidget);

            zone->setBackgroundColor(colorNormal);
            /*//Paint Highlighter
            QPainter painter(zone);

            int width = size().width();
            int height = size().height();

            painter.fillRect(0, 0, width, height, colorNormal);*/


        }
    }

}


void IndigoDropZone::dropPanel()
{
    QPoint cursor = this->mapFromGlobal(QCursor::pos());

    if (this->rect().contains(cursor) ) {

        if(IndigoTabbar *tab = qobject_cast<IndigoTabbar*>(parent()->parent())) {

            IndigoDropZone *zone = qobject_cast<IndigoDropZone*>(tab->activeWidget);

            IndigoPanel *pan = qobject_cast<IndigoPanel *>(sender());
            pan->setParent(zone);
            pan->setLastParent(zone);

            zone->addPanel(pan);
            zone->setBackgroundColor(colorNormal); // de-highlight


        }else{
            qDebug() << "DropZone parent is not type of IndigoTabbar" << endl;
        }

    }
}

/**
 * Add Panel in Splitter
 * @brief Indigo2DropZone::addPanel
 * @param panel
 */
void IndigoDropZone::addPanel (IndigoPanel * panel){

    splitter->addWidget(panel);
    layout->addWidget(splitter);

    splitter->show();
    panel->show();

}

void IndigoDropZone::setBackgroundColor(const QColor &bgColor){
     palette.setColor( QPalette::Background, bgColor );
     setPalette( palette );
}

