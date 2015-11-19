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
    setAutoFillBackground( true );

    colorNormal = QColor( 153, 153, 153 );
    colorHighlight = QColor( 0, 179, 255 );
    transparency = 0.1; // 10%
    colorHighlightAlpha = blendColor(colorNormal,colorHighlight, transparency);


    palette.setColor( QPalette::Background, colorNormal );
    setPalette( palette );


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

void IndigoDropZone::hoverZone(){

    QPoint cursor = this->mapFromGlobal(QCursor::pos());

    if (this->rect().contains(cursor) ) {

        // TODO: Add Global Tabwidget list; use for each loop to search in every tabbwidget for active docks;

        if(IndigoTabbar *tab = qobject_cast<IndigoTabbar*>(parent()->parent())) {

            if(IndigoDropZone *zone = qobject_cast<IndigoDropZone*>(tab->m_activeWidget)){
                zone->isHighlight = true;
                zone->addPlaceholder();
                zone->update();
            }

        }

    }else{
        if(IndigoTabbar *tab = qobject_cast<IndigoTabbar*>(parent()->parent())) {

            if(IndigoDropZone *zone = qobject_cast<IndigoDropZone*>(tab->m_activeWidget)){
                zone->isHighlight = false;
                zone->removePlaceholder();
                zone->update();
            }
        }
    }

}


void IndigoDropZone::dropPanel()
{
    QPoint cursor = this->mapFromGlobal(QCursor::pos());

    if (this->rect().contains(cursor) ) {

        if(IndigoTabbar *tab = qobject_cast<IndigoTabbar*>(parent()->parent())) {

            IndigoDropZone *zone = qobject_cast<IndigoDropZone*>(tab->m_activeWidget);
            if (!zone) return;

            IndigoPanel *pan = qobject_cast<IndigoPanel *>(sender());
            if (!pan) return;

            pan->setParent(zone);
            pan->setLastParent(zone);

            zone->isHighlight = false;
            zone->removePlaceholder();
            zone->addPanel(pan);
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


void IndigoDropZone::setBackgroundColor(const QColor bgColor){

    colorNormal = bgColor;
    colorHighlightAlpha = blendColor(colorNormal,colorHighlight, transparency);
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


/***********************+
 *
 * Helper
 *
 * *********************/

QColor IndigoDropZone::blendColor(QColor color1, QColor color2, double ratio){

    if(ratio < 0 && ratio > 1){
        ratio = 0;
    }

   return QColor(
    color1.red()* (1-ratio) + color2.red()*ratio,
    color1.green()* (1-ratio) + color2.green()*ratio,
    color1.blue()* (1-ratio) + color2.blue()*ratio,
    255);

}

