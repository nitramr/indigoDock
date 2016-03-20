#include "indigodropzone.h"
#include <QStyle>
#include "qapplication.h"
#include "helper.h"


IndigoDropZone::IndigoDropZone(QWidget *parent) :
    QWidget(parent)
{
    setObjectName("IndigoDropZone");

    setMouseTracking(true);
    setAutoFillBackground( true );

    transparency = 0.1; // 10%

    padding = 6;
    borderHighlight = 2;
    isHighlight = false;

    //rect_placeholder = new QRect();
    m_placeholder = new QWidget(this);


    m_splitter = new QSplitter();
    m_splitter->setHandleWidth(padding);
    m_splitter->setOrientation(Qt::Vertical);
    m_splitter->move(this->pos());

    m_layout = new QVBoxLayout;
    m_layout->setMargin(padding);

    QVBoxLayout * layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addLayout(m_layout);
    layout->addStretch(1);
    setLayout(layout);

}



void IndigoDropZone::hoverZone(){

    IndigoPanel *pan = qobject_cast<IndigoPanel *>(sender());
    if (!pan) return;

    QPoint cursor = this->mapFromGlobal(QCursor::pos());

    if (this->rect().contains(cursor) ) {


        int index = -1;
        int height = 4;

        for( int i=0; i<PanelList.size(); ++i )
        {

            if(PanelList.at(i)->dockState() == IndigoPanel::Docked || PanelList.at(i)->dockState() == IndigoPanel::HiddenDocked){
                PanelList.at(i)->setIndex(i);

                IndigoPanel *panel = PanelList.at(i);


                // calculate IndigoPanel position on DropZone
                // TODO: it occur a flickering if placerholder will add/remove -> panel pos will update
                QPoint childPosBegin = this->mapFromGlobal(panel->mapToGlobal( QPoint( 0, 0 ) ));

                QRect panRect = QRect(childPosBegin, QPoint(childPosBegin.x() + panel->width(), childPosBegin.y()+panel->height()+2*padding+height));
                /*qDebug() << "IndigoPanel from List:" << panel
                         << "Position:" << panRect
                         << "CursorPos:" << cursor
                         << endl;*/

                // Check if mouse is over an IndigoPanel and get Index
                if (panRect.contains(cursor) ) {

                    index = panel->Index();

                }

            }

        }

        //set Panel Index of floating panel
        pan->setIndex(index);
        //qDebug() << "Index under mouse" << index << endl;

        this->placeholderHeight = height;
        this->addPlaceholder(index);
        this->isHighlight = true;  // switch highlighter on
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

        addPanel(pan, pan->Index());

        this->isHighlight = false; // switch highlighter off
        this->removePlaceholder();
        this->update();

    }
}



/**
 * Add Panel in Splitter
 * @brief Indigo2DropZone::addPanel
 * @param panel
 */
void IndigoDropZone::addPanel (IndigoPanel *panel, int index){

    // add panel to PanelList
    if(index == -1){
        PanelList.append(panel);
    }else PanelList.insert(index, panel);


    // add panel to DropZone
    if(index == -1){
        m_splitter->addWidget(panel);

    }else  m_splitter->insertWidget(index, panel);


    m_layout->addWidget(m_splitter);


    panel->setDockState(IndigoPanel::Docked);
    panel->show();

    updatePanels();

    // send signal for successful adding
    emit panelAdded(panel->Icon(), panel->Index());

}



void IndigoDropZone::removePanel(int index){
    PanelList.removeAt(index);
    updatePanels();
    emit panelRemoved(index);
}



void IndigoDropZone::movePanel(int oldIndex, int newIndex){

    // Take out
    IndigoPanel * pan = PanelList.takeAt(oldIndex);
    pan->setParent(this);

    // Put in
    PanelList.insert(newIndex, pan);
    m_splitter->insertWidget(newIndex, pan);

    // update panels
    updatePanels();

}



void IndigoDropZone::updatePanels(){

    // update panel index
    for( int i=0; i<PanelList.count(); ++i )
    {

        if(PanelList.at(i)->dockState() == IndigoPanel::Docked || PanelList.at(i)->dockState() == IndigoPanel::HiddenDocked){
            PanelList.at(i)->setIndex(i);
        }

    }

}



void IndigoDropZone::addPlaceholder (int index){

    m_placeholder->setFixedHeight(placeholderHeight);

    if(index == -1){
        m_splitter->addWidget(m_placeholder);
    }else m_splitter->insertWidget(index, m_placeholder);


}



void IndigoDropZone::removePlaceholder (){

    m_placeholder->setParent(this);
    m_placeholder->setFixedHeight(0);
}


void IndigoDropZone::mouseMoveEvent(QMouseEvent *){

    // hoverZone(50);


}


void IndigoDropZone::paintEvent(QPaintEvent*e) {

    Q_UNUSED(e)

    QPainter p(this);

   // p.begin(p.device());

    p.fillRect(0, 0, width(), height(), QColor(this->palette().color(QPalette::Background)));

    // Draw highlight
    if(isHighlight){


        // Create Placeholder Frame
        QPoint pRect = m_placeholder->mapToParent(QPoint(padding,padding));

                int width = m_placeholder->width();
                int height = m_placeholder->height();

                int x = pRect.x();
                int y = pRect.y();


        int offset = borderHighlight;

        colorHighlightAlpha = Helper().blendColor(QColor(this->palette().color(QPalette::Background)),QColor(this->palette().color(QPalette::Highlight)), transparency);

        // Draw Placeholder
        p.fillRect(x, y, width, height, QColor(this->palette().color(QPalette::Highlight)));
        p.fillRect(x + offset, y + offset, width -(offset*2), height -(offset*2),colorHighlightAlpha);

    }

   // p.end();

}



void IndigoDropZone::resizeEvent(QResizeEvent*e){
    Q_UNUSED(e)
    emit resize();
}





