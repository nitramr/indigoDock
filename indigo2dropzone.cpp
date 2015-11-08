#include "indigo2dropzone.h"

/* TODO:
 *
 * - add better splitter widget (low prio)
 *
 */

Indigo2DropZone::Indigo2DropZone(QWidget *parent) :
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
    createPanel();

}


void Indigo2DropZone::createPanel()
{
    Indigo2Panel * pan = new Indigo2Panel(this);
    this->connect(pan, SIGNAL(mouseReleased()), this, SLOT(dropPanel()));
    addPanel(pan);

}

void Indigo2DropZone::dropPanel()
{
    QPoint cursor = this->mapFromGlobal(QCursor::pos());

    if (this->rect().contains(cursor) ) {

        Indigo2Panel *pan = qobject_cast<Indigo2Panel *>(sender());

        if(Indigo2Tabbar *tab = qobject_cast<Indigo2Tabbar*>(parent()->parent())) {
           //qDebug() << "DropZone Parent " << tab << endl;

            Indigo2DropZone *zone = qobject_cast<Indigo2DropZone*>(tab->activeWidget);

            pan->setParent(zone);            

            zone->addPanel(pan);
            //qDebug() << "Pan2 In Dock2 " << pan << " in " << zone << endl;

        }else{
            qDebug() << "DropZone parent is not type of IndigoTabbar" << endl;
        }

    }
}

void Indigo2DropZone::addPanel (Indigo2Panel * panel){

    splitter->addWidget(panel);
    layout->addWidget(splitter);

    splitter->show();
    panel->show();

}
