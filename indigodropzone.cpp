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
    colorHighlight = QColor( 0, 179, 255 );
    colorHighlightAlpha = QColor( 140, 155, 161); // Linux don't support alpha channel


    palette.setColor( QPalette::Background, colorNormal );
    setPalette( palette );
    setAutoFillBackground( true );

    padding = 6;
    borderHighlight = 3;
    isHighlight = false;

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

            zone->isHighlight = true;
            zone->update();
        }

    }else{
        if(IndigoTabbar *tab = qobject_cast<IndigoTabbar*>(parent()->parent())) {

            IndigoDropZone *zone = qobject_cast<IndigoDropZone*>(tab->activeWidget);

            zone->isHighlight = false;
            zone->update();
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

            zone->isHighlight = false;
            zone->update();//zone->setBackgroundColor(colorNormal); // defocus


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

void IndigoDropZone::paintEvent(QPaintEvent*) {
    QPainter painter(this);

    if(isHighlight){

        int width = size().width() - (padding*2);
        int height = size().height() - (padding*2);

        painter.fillRect(padding, padding, width, height, colorHighlight);
        painter.fillRect(padding + borderHighlight, padding + borderHighlight, width -(borderHighlight*2), height -(borderHighlight*2),colorHighlightAlpha);

    }else{

        int width = size().width();
        int height = size().height();

        painter.fillRect(0, 0, width, height, colorNormal);
    }

}


