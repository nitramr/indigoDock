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

    QPoint cursor = this->mapFromGlobal(QCursor::pos());

    if (this->rect().contains(cursor) ) {

        int index = -1;
        int height = 0;

        IndigoPanel *pan = qobject_cast<IndigoPanel *>(sender());
        if (!pan) return;
        pan->setIndex(index);
        height = pan->height();

        QList<IndigoPanel *> panels = findChildren<IndigoPanel *>();
        foreach(IndigoPanel * panel, panels)
        {

            //qDebug() << "WidgetRect" << panel->rect() << endl;
            //qDebug() << "CursorPos" << cursor << endl;

            if(panel->rect().contains(cursor)){
                index = panel->Index();
                pan->setIndex(index);
            }
        }



       // qDebug() << "Index under mouse" << index << endl;

        this->isHighlight = true;  // switch highlighter on
        this->placeholderHeight = height;
        this->addPlaceholder(index);
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
void IndigoDropZone::addPanel (IndigoPanel * panel, int index){

   // add panel to list
   if(index == -1){
       PanelList.append(panel);
   }else PanelList.insert(index, panel);


   // add panel to widget
   if(index == -1){
        m_splitter->addWidget(panel);
    }else m_splitter->insertWidget(index, panel);

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

    IndigoPanel * pan = PanelList.takeAt(oldIndex);
    pan->setParent(this);

    PanelList.insert(newIndex, pan);
    m_splitter->insertWidget(newIndex, pan);

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


void IndigoDropZone::paintEvent(QPaintEvent*) {


    QPainter p(this);

    p.fillRect(0, 0, width(), height(), QColor(this->palette().color(QPalette::Background)));

    // Draw highlight
    if(isHighlight){

        QPoint pRect = m_placeholder->mapToParent(QPoint(padding,padding));

        int width = m_placeholder->width();
        int height = m_placeholder->height();

        int x = pRect.x();
        int y = pRect.y();

        int offset = borderHighlight;

        Helper h;

        colorHighlightAlpha = h.blendColor(QColor(this->palette().color(QPalette::Background)),QColor(this->palette().color(QPalette::Highlight)), transparency);

        p.fillRect(x, y, width, height, QColor(this->palette().color(QPalette::Highlight)));
        p.fillRect(x + offset, y + offset, width -(offset*2), height -(offset*2),colorHighlightAlpha);


    }

}



void IndigoDropZone::resizeEvent(QResizeEvent*){
    emit resize();
}





