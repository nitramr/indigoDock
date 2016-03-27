#include "indigodock.h"

//
// IndigoSplitter
//

IndigoSplitter::IndigoSplitter(QWidget *parent): QSplitter(parent){}



void IndigoSplitter::resizeEvent(QResizeEvent *e){

    QSplitter::resizeEvent(e);
    emit resize();

}



//
// IndigoDock
//


IndigoDock::IndigoDock(QWidget *parent) : QDockWidget(parent)
{


    QString styleSheetScroll( "QScrollArea {"
                                "border: 0px solid transparent;"
                            "}"

            );



    int_padding = 3;
    int_placeholderHeight = 3;

    wdg_toolbar = new  IndigoTabBar;

    wdg_placeholder = new QWidget();
    wdg_placeholder->setFixedHeight(int_placeholderHeight);
    wdg_placeholder->setAutoFillBackground( true );
    wdg_placeholder->setBackgroundRole(QPalette::Highlight);


    wdg_splitter = new IndigoSplitter();
    wdg_splitter->setHandleWidth(int_padding);
    wdg_splitter->setOrientation(Qt::Vertical);
    wdg_splitter->move(this->pos());


    lyt_dropzone = new QVBoxLayout();
    lyt_dropzone->setMargin(int_padding);
    lyt_dropzone->setSpacing(0);
    lyt_dropzone->addWidget(wdg_splitter);
    lyt_dropzone->addStretch(1);


    wdg_dropzone = new QWidget();
    wdg_dropzone->setLayout(lyt_dropzone);
    wdg_dropzone->setMinimumWidth(220 + 2*int_padding);
    wdg_dropzone->setBackgroundRole(QPalette::Base);


    wdg_scrollArea_dz = new QScrollArea;
    wdg_scrollArea_dz->setStyleSheet( styleSheetScroll);
    wdg_scrollArea_dz->setWidgetResizable(true);
    wdg_scrollArea_dz->setWidget(wdg_dropzone);
    wdg_scrollArea_dz->setMinimumWidth(wdg_dropzone->minimumWidth() + 20); //scrollbar fix
    wdg_scrollArea_dz->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    wdg_scrollArea_tb = new QScrollArea;
    wdg_scrollArea_tb->setStyleSheet( styleSheetScroll);
    wdg_scrollArea_tb->setWidgetResizable(true);
    wdg_scrollArea_tb->setWidget(wdg_toolbar);
    wdg_scrollArea_tb->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    wdg_scrollArea_tb->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    wdg_scrollArea_tb->setBackgroundRole(QPalette::Base);


    lyt_main = new QGridLayout();
    lyt_main->setSpacing(0);
    lyt_main->setMargin(0);
    lyt_main->addWidget(wdg_scrollArea_tb,1,1);
    lyt_main->addWidget(wdg_scrollArea_dz,1,0);


    QWidget *container = new QWidget();
    container->setLayout(lyt_main);

    /*QWidget* titleWidget = new QWidget(this);
    titleWidget->setFixedSize(20,20);
    titleWidget->setBackgroundRole(QPalette::Highlight);
    titleWidget->setAutoFillBackground(true);

    //setTitleBarWidget( titleWidget );*/
    setWidget(container);
    setMouseTracking(true);
    setAutoFillBackground( true );
    setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));


    connect(this, SIGNAL(panelAdded(QIcon,int, QString)), wdg_toolbar, SLOT(insertTab(QIcon, int, QString)));
    connect(this, SIGNAL(panelRemoved(int)), wdg_toolbar, SLOT(removeTab(int)));
    connect(this, SIGNAL(dockLocationChanged(Qt::DockWidgetArea)), this, SLOT(updateTabPosition(Qt::DockWidgetArea)));
    connect(wdg_toolbar, SIGNAL(tabMoved(int,int)), this, SLOT(movePanel(int,int)));
    connect(wdg_toolbar, SIGNAL(scrollToPanel(int)), this, SLOT(scrollToPanel(int)));
    connect(wdg_splitter, SIGNAL(resize()), this, SLOT(updateMinHeight()));


}



void IndigoDock::addIndigoPanel(IndigoPanel *panel, int tabIndex){


    this->connect(panel, SIGNAL(mouseReleased()), this, SLOT(dropPanel()));
    this->connect(panel, SIGNAL(mouseMove()), this, SLOT(hoverDock()));
    this->connect(panel, SIGNAL(isFloating(int)), this, SLOT(removePanel(int)));
    this->connect(panel, SIGNAL(panelClosed(int)), wdg_toolbar, SLOT(hideTab(int)));
    this->connect(panel, SIGNAL(panelShown(int)), wdg_toolbar, SLOT(showTab(int)));


    addPanel (panel, tabIndex);


}



/**
 * Add Panel in Splitter
 * @brief Indigo2DropZone::addPanel
 * @param panel
 */
void IndigoDock::addPanel (IndigoPanel *panel, int tabIndex){

    // add panel to PanelList
    if(tabIndex == -1){
        lst_PanelList.append(panel);
    }else lst_PanelList.insert(tabIndex, panel);


    // add panel to DropZone
    if(tabIndex == -1){
        wdg_splitter->addWidget(panel);

    }else  wdg_splitter->insertWidget(tabIndex, panel);


    panel->setDockState(IndigoPanel::Docked);
    panel->show();

    updatePanels();

    // send signal for successful adding
    emit panelAdded(panel->Icon(), panel->Index(), panel->Caption());

}



void IndigoDock::updatePanels(){

    // update panel index
    for( int i=0; i<lst_PanelList.count(); ++i )
    {

        if(lst_PanelList.at(i)->dockState() == IndigoPanel::Docked || lst_PanelList.at(i)->dockState() == IndigoPanel::HiddenDocked){
            lst_PanelList.at(i)->setIndex(i);
        }

    }

    updateMinHeight();

}



void IndigoDock::removePanel(int index){

    lst_PanelList.removeAt(index);
    updatePanels();
    emit panelRemoved(index);
}



void IndigoDock::movePanel(int oldIndex, int newIndex){

    // Take out
    IndigoPanel * pan = lst_PanelList.takeAt(oldIndex);
    pan->setParent(this);

    // Put in
    lst_PanelList.insert(newIndex, pan);
    wdg_splitter->insertWidget(newIndex, pan);

    // update panels
    updatePanels();

}



void IndigoDock::scrollToPanel(int PanelIndex){


    updateMinHeight();

    IndigoPanel *panel = lst_PanelList.at(PanelIndex);
    int offset = int_padding;

    QPoint panPos = wdg_dropzone->mapFromGlobal(panel->mapToGlobal( QPoint( 0, 0 ) ));

    QPropertyAnimation *animation = new QPropertyAnimation(wdg_scrollArea_dz->verticalScrollBar(), "value");
    animation->setDuration(100);
    animation->setStartValue(wdg_scrollArea_dz->verticalScrollBar()->value());
    animation->setEndValue(panPos.y() - offset);
    animation->start();

}



void IndigoDock::scrollToPanel(QString PanelName){

    for( int i=0; i<lst_PanelList.size(); ++i )
    {
        if(lst_PanelList.at(i)->dockState() == IndigoPanel::Docked || lst_PanelList.at(i)->dockState() == IndigoPanel::HiddenDocked){

            if(lst_PanelList.at(i)->objectName() == PanelName){

                this->scrollToPanel(i);
            }
        }
    }


}



void IndigoDock::updateMinHeight(){

    int lastPanelHeight = 0;
    int countHiddenPanels = 0;

    // get height of last visible Panel
    for( int i=0; i<lst_PanelList.size(); ++i )
    {

        if(lst_PanelList.at(i)->dockState() == IndigoPanel::Docked){

            IndigoPanel * panel = lst_PanelList.at(i);
            lastPanelHeight = panel->height();

        }else if(lst_PanelList.at(i)->dockState() == IndigoPanel::HiddenDocked){
            countHiddenPanels += 1;

        }

    }


    // hide drop zone if all panels are hidden
    if(countHiddenPanels == lst_PanelList.size()){

        // DO stuff if all panels are hidden

       /* wdg_scrollArea_dz->hide();
        this->resize(QSize(wdg_toolbar->width(), this->height()));
        this->adjustSize();*/

        return;
    }else{

        int minHeight = wdg_splitter->height();
        int spacer = wdg_scrollArea_dz->height() - lastPanelHeight;

        if(minHeight < lastPanelHeight) minHeight = lastPanelHeight;

        wdg_dropzone->setFixedHeight(minHeight + spacer);
       // wdg_scrollArea_dz->show();

        update();
    }


}



void IndigoDock::addPlaceholder (int index){

    wdg_placeholder->setFixedHeight(int_placeholderHeight);

    if(index == -1){
        wdg_splitter->addWidget(wdg_placeholder);
    }else wdg_splitter->insertWidget(index, wdg_placeholder);


}



void IndigoDock::removePlaceholder (){

    wdg_placeholder->setParent(this);
    wdg_placeholder->setFixedHeight(0);

}




void IndigoDock::updateTabPosition(Qt::DockWidgetArea area){

    switch(area){
    case Qt::LeftDockWidgetArea:{
            wdg_toolbar->setTabOrientation(IndigoTabBar::Vertical);
            lyt_main->setAlignment(Qt::AlignLeft);

            lyt_main->removeWidget(wdg_scrollArea_tb);
            lyt_main->removeWidget(wdg_scrollArea_dz);

            lyt_main->addWidget(wdg_scrollArea_tb,1,0);
            lyt_main->addWidget(wdg_scrollArea_dz,1,1);

            wdg_scrollArea_tb->setMinimumSize(QSize(wdg_toolbar->width(), wdg_toolbar->width()));
            wdg_scrollArea_tb->setMaximumSize(wdg_toolbar->maximumSize());
        break;
    }
    case Qt::RightDockWidgetArea:{
           wdg_toolbar->setTabOrientation(IndigoTabBar::Vertical);
            lyt_main->setAlignment(Qt::AlignRight);

            lyt_main->removeWidget(wdg_scrollArea_tb);
            lyt_main->removeWidget(wdg_scrollArea_dz);

            lyt_main->addWidget(wdg_scrollArea_tb,1,1);
            lyt_main->addWidget(wdg_scrollArea_dz,1,0);

            wdg_scrollArea_tb->setMinimumSize(QSize(wdg_toolbar->width(), wdg_toolbar->width()));
            wdg_scrollArea_tb->setMaximumSize(wdg_toolbar->maximumSize());


        break;
    }
    case Qt::TopDockWidgetArea:{

            wdg_toolbar->setTabOrientation(IndigoTabBar::Horizontal);
            lyt_main->setAlignment(Qt::AlignTop);

            lyt_main->removeWidget(wdg_scrollArea_tb);
            lyt_main->removeWidget(wdg_scrollArea_dz);

            lyt_main->addWidget(wdg_scrollArea_tb,1,0);
            lyt_main->addWidget(wdg_scrollArea_dz,2,0);

            wdg_scrollArea_tb->setMinimumSize(QSize(wdg_toolbar->height(), wdg_toolbar->height()));
            wdg_scrollArea_tb->setMaximumSize(wdg_toolbar->maximumSize());

        break;
    }
    case Qt::BottomDockWidgetArea:{

           wdg_toolbar->setTabOrientation(IndigoTabBar::Horizontal);
            lyt_main->setAlignment(Qt::AlignBottom);

            lyt_main->removeWidget(wdg_scrollArea_tb);
            lyt_main->removeWidget(wdg_scrollArea_dz);

            lyt_main->addWidget(wdg_scrollArea_tb,2,0);
            lyt_main->addWidget(wdg_scrollArea_dz,1,0);


            wdg_scrollArea_tb->setMinimumSize(QSize(wdg_toolbar->height(), wdg_toolbar->height()));
            wdg_scrollArea_tb->setMaximumSize(wdg_toolbar->maximumSize());


        break;
    }
    default:

        break;

    }

}




// TODO: decide if DropZone or TabBar hovered
void IndigoDock::hoverDock(){

    IndigoPanel *pan = qobject_cast<IndigoPanel *>(sender());
    if (!pan) return;

    QPoint cursor = this->mapFromGlobal(QCursor::pos());

   // qDebug() << "CursorPos:" << cursor << "RectZone:" << wdg_scrollArea_dz->geometry() << "RectTabBar:" << wdg_scrollArea_tb->geometry() << endl;

    if (this->rect().contains(cursor) ) {


        if  (wdg_scrollArea_dz->geometry().contains(cursor) ){
            //qDebug() << "hover DropZone" << endl;

            int index = -1;

            for( int i=0; i<lst_PanelList.size(); ++i )
            {

                if(lst_PanelList.at(i)->dockState() == IndigoPanel::Docked || lst_PanelList.at(i)->dockState() == IndigoPanel::HiddenDocked){

                    IndigoPanel *panel = lst_PanelList.at(i);


                    // calculate IndigoPanel position on DropZone
                    QPoint childPosBegin = this->mapFromGlobal(panel->mapToGlobal( QPoint( 0, 0 ) ));

                    QRect panRect = QRect(childPosBegin, QPoint(childPosBegin.x() + panel->width(), childPosBegin.y()+panel->height()+2*int_padding + int_placeholderHeight));
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

            this->addPlaceholder(index);


        }else if (wdg_scrollArea_tb->geometry().contains(cursor) ) {

            // qDebug() << "hover IconBar" << endl;
         }

    }else{
        this->removePlaceholder();
    }


}




void IndigoDock::dropPanel(){

    QPoint cursor = this->mapFromGlobal(QCursor::pos());

    if (this->rect().contains(cursor) ) {

        IndigoPanel *pan = qobject_cast<IndigoPanel *>(sender());
        if (!pan) return;

        addPanel(pan, pan->Index());

        this->removePlaceholder();

    }
}



void IndigoDock::resizeEvent(QResizeEvent *e){

     QWidget::resizeEvent(e);
     updateMinHeight();

}
