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

    m_splitter = new QSplitter();
    m_splitter->setHandleWidth(padding);
    m_splitter->setOrientation(Qt::Vertical);
    m_splitter->setStretchFactor(1, 1);
    m_splitter->move(this->pos());

    m_layout = new QVBoxLayout;
    m_layout->setMargin(padding);
    setLayout(m_layout);

    m_placeholder = new QWidget(this);


}


void IndigoDropZone::createPanel(const QString &title, QWidget *widget)
{
    IndigoPanel * pan = new IndigoPanel(this);
    this->connect(pan, SIGNAL(mouseReleased()), this, SLOT(dropPanel()));
    this->connect(pan, SIGNAL(mouseMove()), this, SLOT(hoverZone()));
    pan->m_handle->setTitle(title);
    pan->addWidget(widget);
    //pan->setBackgroundColor(QColor( 204, 204, 204 ));
    //pan->handle->setBackgroundColor(QColor( 204, 204, 204 ));
    addPanel(pan);

}

void IndigoDropZone::hoverZone(){

    QPoint cursor = this->mapFromGlobal(QCursor::pos());

    if (this->rect().contains(cursor) ) {

        if(IndigoTabbar *tab = qobject_cast<IndigoTabbar*>(parent()->parent())) {

            IndigoDropZone *zone = qobject_cast<IndigoDropZone*>(tab->m_activeWidget);

            zone->isHighlight = true;
            zone->addPlaceholder();
            zone->update();

        }

    }else{
        if(IndigoTabbar *tab = qobject_cast<IndigoTabbar*>(parent()->parent())) {

            IndigoDropZone *zone = qobject_cast<IndigoDropZone*>(tab->m_activeWidget);

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

            IndigoDropZone *zone = qobject_cast<IndigoDropZone*>(tab->m_activeWidget);

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

    m_splitter->addWidget(panel);
    m_layout->addWidget(m_splitter);

    m_splitter->show();
    panel->show();

}

void IndigoDropZone::addPlaceholder (){

    m_splitter->addWidget(m_placeholder);
    m_layout->addWidget(m_splitter);

    m_splitter->show();

}

void IndigoDropZone::removePlaceholder (){

    m_placeholder->setParent(this);

}


void IndigoDropZone::setBackgroundColor(const QColor &bgColor){

    colorNormal = bgColor;
}


void IndigoDropZone::paintEvent(QPaintEvent*) {

    QPainter painter(this);

    // Draw highlight
    if(isHighlight){

        QPoint pRect = m_placeholder->mapToParent(QPoint(padding,padding));

        int width = m_placeholder->width();
        int height = m_placeholder->height();

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


