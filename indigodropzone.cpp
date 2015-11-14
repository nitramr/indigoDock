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

    placeholder = new QWidget(this);


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
            zone->addPlaceholder();
            zone->update();

        }

    }else{
        if(IndigoTabbar *tab = qobject_cast<IndigoTabbar*>(parent()->parent())) {

            IndigoDropZone *zone = qobject_cast<IndigoDropZone*>(tab->activeWidget);

            zone->isHighlight = false;
            zone->removePlaceholder();
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
            zone->removePlaceholder();
            zone->update(); // defocus


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

void IndigoDropZone::addPlaceholder (){

    splitter->addWidget(placeholder);
    layout->addWidget(splitter);

    splitter->show();

}

void IndigoDropZone::removePlaceholder (){

    placeholder->setParent(this);

}


void IndigoDropZone::setBackgroundColor(const QColor &bgColor){

    colorNormal = bgColor;
}


void IndigoDropZone::paintEvent(QPaintEvent*) {

    QPainter painter(this);

    // Draw highlight
    if(isHighlight){

        QPoint pRect = placeholder->mapToParent(QPoint(padding,padding));

        int width = placeholder->width();
        int height = placeholder->height();

        int x = pRect.x();
        int y = pRect.y();

        int offset = borderHighlight;

        painter.fillRect(x, y, width, height, colorHighlight);
        painter.fillRect(x + offset, y + offset, width -(offset*2), height -(offset*2),colorHighlightAlpha);

    // Reset highlight (normal view)
    }else{

        int width = size().width();
        int height = size().height();

        painter.fillRect(0, 0, width, height, colorNormal);
    }

}


