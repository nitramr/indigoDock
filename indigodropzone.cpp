#include "indigodropzone.h"
#include <QStyle>
#include "qapplication.h"

/* TODO:
 *
 * - add better splitter widget (redocking within a dropzone
 *
 */

IndigoDropZone::IndigoDropZone(QWidget *parent) :
   QWidget(parent)
{
    setObjectName("IndigoDropZone");

    setMouseTracking(true);
    setAutoFillBackground( true );


    transparency = 0.1; // 10% 

    padding = 6;
    borderHighlight = 3;
    isHighlight = false;

    m_placeholder = new QWidget(this);

    m_splitter = new QSplitter();
    m_splitter->setHandleWidth(padding);
    m_splitter->setOrientation(Qt::Vertical);
   // m_splitter->setStretchFactor(1, 1);
    m_splitter->move(this->pos());

    m_layout = new QVBoxLayout;
    m_layout->setMargin(padding);
    //setLayout(m_layout);

    QVBoxLayout * layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addLayout(m_layout);
    layout->addStretch(1);
    setLayout(layout);

}




void IndigoDropZone::mousePressEvent(QMouseEvent *event){

    IndigoPanel *child = static_cast<IndigoPanel*>(childAt(event->pos()));

    if (!child) return;

   /* QPixmap pixmap = *child->pixmap();

        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);
        dataStream << pixmap << QPoint(event->pos() - child->pos());

        QMimeData *mimeData = new QMimeData;
        mimeData->setData("application/x-dnditemdata", itemData);

        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->setPixmap(pixmap);
        drag->setHotSpot(event->pos() - child->pos());

        QPixmap tempPixmap = pixmap;
        QPainter painter;
        painter.begin(&tempPixmap);
        painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
        painter.end();

        child->setPixmap(tempPixmap);

        if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
            child->close();
        } else {
            child->show();
            child->setPixmap(pixmap);
        }*/

}



void IndigoDropZone::hoverZone(int height){

    QPoint cursor = this->mapFromGlobal(QCursor::pos());

    if (this->rect().contains(cursor) ) {

                this->isHighlight = true;
                this->addPlaceholder(height);
                this->update();

    }else{

                this->isHighlight = false;
                this->removePlaceholder();
                this->update();

    }

}



void IndigoDropZone::dropPanel()
{
    QPoint cursor = this->mapFromGlobal(QCursor::pos());

    if (this->rect().contains(cursor) ) {

            IndigoPanel *pan = qobject_cast<IndigoPanel *>(sender());
            if (!pan) return;

            this->isHighlight = false;
            this->removePlaceholder();
            this->addPanel(pan);
            this->update(); // defocus

            emit pan->isDock();

    }
}



/**
 * Add Panel in Splitter
 * @brief Indigo2DropZone::addPanel
 * @param panel
 */
void IndigoDropZone::addPanel (IndigoPanel * panel, int index){

    //index is used for order in Splitter

    m_splitter->addWidget(panel);
    m_layout->addWidget(m_splitter);

    m_splitter->show();
    panel->show();

    this->setFixedWidth(panel->width() + padding*2);

}



void IndigoDropZone::movePanel(int newIndex, QString name){

    qDebug() << "panel remove:" << name << endl;

    IndigoPanel * pan = this->findChild<IndigoPanel*>(name);
    pan->setParent(0);
    m_splitter->insertWidget(newIndex, pan);

}


void IndigoDropZone::addPlaceholder (int height){

    m_placeholder->setFixedHeight(height);
    m_splitter->addWidget(m_placeholder);
    m_layout->addWidget(m_splitter);

    m_splitter->show();

}



void IndigoDropZone::removePlaceholder (){

    m_placeholder->setParent(this);

}



void IndigoDropZone::paintEvent(QPaintEvent*) {


    QPainter painter(this);

    painter.fillRect(0, 0, width(), height(), QColor(this->palette().color(QPalette::Background)));

    // Draw highlight
    if(isHighlight){

        QPoint pRect = m_placeholder->mapToParent(QPoint(padding,padding));

        int width = m_placeholder->width();
        int height = m_placeholder->height();

        int x = pRect.x();
        int y = pRect.y();

        int offset = borderHighlight;

        colorHighlightAlpha = blendColor(QColor(this->palette().color(QPalette::Background)),QColor(this->palette().color(QPalette::Highlight)), transparency);

        //painter.fillRect(0, 0, size().width(), size().height(), colorNormal);
        painter.fillRect(x, y, width, height, QColor(this->palette().color(QPalette::Highlight)));
        painter.fillRect(x + offset, y + offset, width -(offset*2), height -(offset*2),colorHighlightAlpha);

    // Reset highlight (normal view)
    }

}



void IndigoDropZone::resizeEvent(QResizeEvent*){
    emit resize();
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

