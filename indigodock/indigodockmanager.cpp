/*******************************************************
 *
 * Copyright (C) 2016  Martin Reininger
 *
 * This file is part of IndigoDock.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 *******************************************************/


#include "indigodockmanager.h"
#include <QDomDocument>

IndigoDockManager::IndigoDockManager(QMainWindow *parent) : QWidget(parent){

    version = "1.0"; // workspace manager version
    int_minimumPanelHeight = 50;
    int_minimumPanelWidth = 100;

}



void IndigoDockManager::addIndigoDock(IndigoDock *dock){


    if(!lst_Docks.contains(dock)){
        lst_Docks.append(dock);

        QString count = QString::number(lst_Docks.size());

        dock->setAccessibleName("IndigoDock"+count);
        dock->setObjectName("IndigoDock"+count);
        dock->setMinimumPanelSize(minimumPanelSize()); // set min size


        this->connect(dock, SIGNAL(dockDestroyed()), this, SLOT(removeDock()));
    }

}



void IndigoDockManager::addIndigoDock(IndigoDock *dock, Qt::DockWidgetArea area){

    QMainWindow * main = qobject_cast<QMainWindow *>(parent());

    if(main){

        main->addDockWidget(area,dock);

        addIndigoDock(dock);

    }

}



void IndigoDockManager::addIndigoPanel(IndigoDock * dock, IndigoPanel * panel, int tabIndex){

    //panel->setMinimumSize(minimumPanelSize()); // set min size

    if(lst_Docks.contains(dock)){
        dock->addIndigoPanel(panel, tabIndex);
    }else{
        lst_Docks.append(dock);
        dock->addIndigoPanel(panel, tabIndex);
    }

    // disconnect (remove old connections to other docks)
    this->disconnect(panel, SIGNAL(mouseMove()), this, SLOT(hoverDock()));
    this->disconnect(panel, SIGNAL(mouseReleased()), this, SLOT(dropPanel()));
    this->disconnect(panel, SIGNAL(isFloating(int)), this, SLOT(removePanel(int)));
    this->disconnect(panel, SIGNAL(panelClosed(int)), this, SLOT(hideTab(int)));
    this->disconnect(panel, SIGNAL(panelShown(int)), this, SLOT(showTab(int)));


    // reconnect
    this->connect(panel, SIGNAL(mouseMove()), this, SLOT(hoverDock()));
    this->connect(panel, SIGNAL(mouseReleased()), this, SLOT(dropPanel()));
    this->connect(panel, SIGNAL(isFloating(int)), this, SLOT(removePanel(int)));
    this->connect(panel, SIGNAL(panelClosed(int)), this, SLOT(hideTab(int)));
    this->connect(panel, SIGNAL(panelShown(int)), this, SLOT(showTab(int)));

}



void IndigoDockManager::addIndigoPanel(IndigoDock * dock, IndigoPanel * panel, IndigoPanel::IndigoDockState dockState, int tabIndex){

    switch(dockState){
    case IndigoPanel::Docked:
    case IndigoPanel::HiddenDocked:

        addIndigoPanel(dock, panel, tabIndex);
        panel->setDockState(dockState);

        break;

    case IndigoPanel::Floating:
    default:
        addFloatingDock(panel);
        break;

    }

}



void IndigoDockManager::addFloatingDock(IndigoPanel * panel){

    IndigoDock * dock = new IndigoDock();

    // add Dock in list
    addIndigoDock(dock,Qt::LeftDockWidgetArea);
    dock->setFloating(true);
    dock->move(panel->pos());

    // add Panel in dock
    addIndigoPanel(dock, panel);


}



void IndigoDockManager::removePanel(int index){

    IndigoPanel *pan = qobject_cast<IndigoPanel *>(sender());
    if (!pan) return;


    if(lst_Docks.size() > 0){

        for( int i=0; i<lst_Docks.count(); ++i )
        {

            if(lst_Docks.at(i)->getPanels().contains(pan)){

                qDebug() << "Remove Panel: Dock index" << i << "Dock" << lst_Docks.at(i) << "Panel index" << index << endl;


                lst_Docks.at(i)->removePanel(index);


                pan->setParent(this);

                return;
            }


        }

    }
}



void IndigoDockManager::hideTab(int index){

    IndigoPanel *pan = qobject_cast<IndigoPanel *>(sender());
    if (!pan) return;


    if(lst_Docks.size() > 0){

        for( int i=0; i<lst_Docks.count(); ++i )
        {

            if(lst_Docks.at(i)->getPanels().contains(pan)){


                lst_Docks.at(i)->hideTab(index);

                return;
            }


        }

    }
}



void IndigoDockManager::showTab(int index){

    IndigoPanel *pan = qobject_cast<IndigoPanel *>(sender());
    if (!pan) return;


    if(lst_Docks.size() > 0){

        for( int i=0; i<lst_Docks.count(); ++i )
        {

            if(lst_Docks.at(i)->getPanels().contains(pan)){


                lst_Docks.at(i)->showTab(index);

                return;
            }


        }

    }
}



void IndigoDockManager::scrollToPanel(QString name){


    if(lst_Docks.size() > 0){

        for( int i=0; i<lst_Docks.count(); ++i )
        {
            lst_Docks.at(i)->scrollToPanel(name);
        }

    }

}



void IndigoDockManager::hoverDock(){

    IndigoPanel *pan = qobject_cast<IndigoPanel *>(sender());
    if (!pan) return;


    if(lst_Docks.size() > 0){

        for( int i=0; i<lst_Docks.size(); ++i )
        {
            lst_Docks.at(i)->hoverDock(pan);
        }

    }

}



void IndigoDockManager::dropPanel(){
    IndigoPanel *pan = qobject_cast<IndigoPanel *>(sender());
    if (!pan) return;


    if(lst_Docks.size() > 0){

        for( int i=0; i<lst_Docks.size(); ++i )
        {
            lst_Docks.at(i)->dropPanel(pan);

        }
    }

    // create floating dock if panel is not already docked
    if (pan->dockState() == IndigoPanel::Floating){

        addFloatingDock(pan);
    }


}



void IndigoDockManager::removeDock(){
    IndigoDock *dock = qobject_cast<IndigoDock *>(sender());

    if (!dock) return;

    if(lst_Docks.contains(dock)){
        int index = lst_Docks.indexOf(dock);
        lst_Docks.removeAt(index);
    }

}



void IndigoDockManager::loadWorkspace(QByteArray workspaceArray){

    QList<IndigoDock*> lst_tmpDocks;
    QList<IndigoPanel*> lst_tmpPanels;


    QDomDocument doc;
    doc.setContent(workspaceArray);

    QDomElement root = doc.documentElement();
    QDomElement indigoDock;
    QDomElement floatingPanels;

    QString fileVersion = root.attribute("version", "1.0");

    if(fileVersion > version){
        QMessageBox::warning(0, "Workspace could not load!", "Workspace file version ("+fileVersion+") is newer than " + version + ".");

        return;
    }


    indigoDock = root.firstChildElement("IndigoDock");
    floatingPanels = root.firstChildElement("FloatingPanels");



    // collect all docks and docked panels
    if(lst_Docks.size() > 0){
        for( int i=0; i<lst_Docks.count(); ++i )
        {
            IndigoDock * tDock = lst_Docks.at(i);

            lst_tmpDocks.append(tDock);


            // collect all docked panels
            if(tDock->getPanels().size() > 0){
                for( int i=0; i < tDock->getPanels().count(); ++i )
                {
                    IndigoPanel * tPanel = tDock->getPanels().at(i);

                    lst_tmpPanels.append(tPanel);

                }
            }

            // clear dock at index
            tDock->clear();

        }


        lst_Docks.clear();

    }


    int i = 0;

    // restore dock layout and docked panels
    while(!indigoDock.isNull())
    {

        if(lst_tmpDocks.size() > 0){

            IndigoDock * newDock = new IndigoDock();

            if(i < lst_tmpDocks.size()) newDock = lst_tmpDocks.at(i);


            // add sorted panels
            QDomElement indigoPanel = indigoDock.firstChildElement("IndigoPanel");

            while(!indigoPanel.isNull())
            {


                if(lst_tmpPanels.size() > 0){

                    for( int i=0; i<lst_tmpPanels.size(); ++i )
                    {
                        IndigoPanel * sortPanel = lst_tmpPanels.at(i);

                        if (sortPanel->objectName() == indigoPanel.attribute("name", "")){

                            newDock->addIndigoPanel(sortPanel);

                            //add attribute
                            sortPanel->setExpanderState(indigoPanel.attribute("expanderState", "-1").toInt());
                            sortPanel->setDockState(indigoPanel.attribute("dockState", "-1").toInt());


                        }

                    }

                }

                indigoPanel = indigoPanel.nextSiblingElement("IndigoPanel");


            }


            addIndigoDock(newDock, Qt::LeftDockWidgetArea);



            i++;



        }


        // next dock
        indigoDock = indigoDock.nextSiblingElement("IndigoDock");

    }


    lst_tmpDocks.clear();
    lst_tmpPanels.clear();


}




QByteArray IndigoDockManager::saveWorkspace(){


    QByteArray qba_panels;


    QXmlStreamWriter xmlWriter(&qba_panels);

    xmlWriter.setAutoFormatting(true);


    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("IndigoDockManager");
    xmlWriter.writeAttribute("version",version);

    // Docks
    if(lst_Docks.size() > 0){

        for( int i=0; i<lst_Docks.size(); ++i )
        {

            IndigoDock *dock = lst_Docks.at(i);


            xmlWriter.writeStartElement("IndigoDock");
            //xmlWriter.writeAttribute("id",QString::number(i));
            xmlWriter.writeAttribute("name",dock->objectName());


            if(dock->getPanels().size() > 0){

                for( int p=0; p<dock->getPanels().count(); ++p )
                {
                    IndigoPanel *sortPanel = dock->getPanels().at(p);

                    xmlWriter.writeStartElement("IndigoPanel");
                    xmlWriter.writeAttribute("id",QString::number(sortPanel->Index()));
                    xmlWriter.writeAttribute("name",sortPanel->objectName());
                    xmlWriter.writeAttribute("expanderState",QString::number(sortPanel->expanderState()));
                    xmlWriter.writeAttribute("dockState",QString::number(sortPanel->dockState())); // only Docked & HiddenDocked will be available
                    xmlWriter.writeEndElement();
                }
            }


            xmlWriter.writeEndElement();

        }

    }


    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();




    return qba_panels;
}



/**********************
 *
 * Settings
 *
 * *******************/


void IndigoDockManager::setMinimumPanelHeight(int height){

    int_minimumPanelHeight = height;

}



void IndigoDockManager::setMinimumPanelWidth(int width){

    int_minimumPanelWidth = width;

}



void IndigoDockManager::setMinimumPanelSize(QSize size){

    setMinimumPanelHeight(size.height());
    setMinimumPanelWidth(size.width());

}



QSize IndigoDockManager::minimumPanelSize(){

   return QSize(int_minimumPanelWidth, int_minimumPanelHeight);

}
