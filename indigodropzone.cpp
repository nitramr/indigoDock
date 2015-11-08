#include "indigodropzone.h"

/* TODO:
 *
 * - add better splitter widget (redocking within a dropzone
 *
 */

IndigoDropZone::IndigoDropZone(QWidget *parent) :
   QWidget(parent)
{

    QPalette palette;
    palette.setColor( QPalette::Background, QColor( 153, 153, 153 ) );
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

    // Demo Panels
    //createPanel();

}


void IndigoDropZone::createPanel(const QString &title, QWidget *widget)
{
    IndigoPanel * pan = new IndigoPanel(this);
    this->connect(pan, SIGNAL(mouseReleased()), this, SLOT(dropPanel()));
    pan->handle->setTitle(title);
    pan->addWidget(widget);
    //pan->setBackgroundColor(QColor( 204, 204, 204 ));
    //pan->handle->setBackgroundColor(QColor( 204, 204, 204 ));
    addPanel(pan);

}

void IndigoDropZone::dropPanel()
{
    QPoint cursor = this->mapFromGlobal(QCursor::pos());

    if (this->rect().contains(cursor) ) {

        IndigoPanel *pan = qobject_cast<IndigoPanel *>(sender());

        if(IndigoTabbar *tab = qobject_cast<IndigoTabbar*>(parent()->parent())) {
           //qDebug() << "DropZone Parent " << tab << endl;

            IndigoDropZone *zone = qobject_cast<IndigoDropZone*>(tab->activeWidget);

            pan->setParent(zone);            

            zone->addPanel(pan);
            //qDebug() << "Pan2 In Dock2 " << pan << " in " << zone << endl;

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
