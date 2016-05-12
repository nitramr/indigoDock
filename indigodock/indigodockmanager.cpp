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

IndigoDockManager::IndigoDockManager(QWidget *parent) : QWidget(parent){

    version = "1.0"; // workspace manager version

}



void IndigoDockManager::addIndigoDock(IndigoDock * dock){

    if(!lst_Docks.contains(dock)){
         lst_Docks.append(dock);

          this->connect(dock, SIGNAL(panelDropped(int)), this, SLOT(panelDropped(int)));
    }

}



void IndigoDockManager::addIndigoPanel(IndigoDock * dock, IndigoPanel * panel, int tabIndex){

    if(lst_Docks.contains(dock)){
        dock->addIndigoPanel(panel, tabIndex);
    }else{
        lst_Docks.append(dock);
        dock->addIndigoPanel(panel, tabIndex);
    }

    this->connect(panel, SIGNAL(mouseMove()), this, SLOT(hoverDock()));
    this->connect(panel, SIGNAL(mouseReleased()), this, SLOT(dropPanel()));
    this->connect(panel, SIGNAL(isFloating(int)), this, SLOT(removePanel(int)));


}



void IndigoDockManager::removePanel(int index){

    IndigoPanel *pan = qobject_cast<IndigoPanel *>(sender());
    if (!pan) return;


    if(lst_Docks.size() > 0){

        for( int i=0; i<lst_Docks.count(); ++i )
        {

            if(lst_Docks.at(i)->getPanels().contains(pan)){

                lst_Docks.at(i)->removePanel(index);

                qDebug() << "pan is:" << pan << endl;

                lst_floatingPanels.append(pan);

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

        for( int i=0; i<lst_Docks.count(); ++i )
        {

             lst_Docks.at(i)->hoverDock(pan);

        }

    }

}



void IndigoDockManager::dropPanel(){
    IndigoPanel *pan = qobject_cast<IndigoPanel *>(sender());
    if (!pan) return;


    if(lst_Docks.size() > 0){

        for( int i=0; i<lst_Docks.count(); ++i )
        {
            lst_Docks.at(i)->dropPanel(pan);

        }

    }
}



void IndigoDockManager::panelDropped(int index){

    IndigoDock *dock = qobject_cast<IndigoDock *>(sender());
    if (!dock) return;

    IndigoPanel *pan = dock->getPanels().at(index);

     qDebug() << "Panel dropped" << endl;

    if(lst_floatingPanels.contains(pan)){
        int index = lst_floatingPanels.indexOf(pan);
        lst_floatingPanels.removeAt(index);
        qDebug() << "Pan was removed from Floating List" << endl;
    }

}


void IndigoDockManager::loadWorkspace(QString file){


    qDebug() << "Load Workspace" << endl;

    QFile xmlFile(file);

    if (!xmlFile.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(0, "Workspace wont load!", "Workspace file not found! Save Workspace at first to create a file.");
    }
    else
    {

        QList<IndigoDock*> lst_tmpDocks;
        QList<IndigoPanel*> lst_tmpPanels;

        QDomDocument doc;
        doc.setContent(xmlFile.readAll());

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

        // collect all floating panels
        if(lst_floatingPanels.size() > 0){
            for( int i=0; i<lst_floatingPanels.count(); ++i )
            {
                IndigoPanel * tPanel = lst_floatingPanels.at(i);

                lst_tmpPanels.append(tPanel);

            }

             lst_floatingPanels.clear();

        }





        // restore dock layout and docked panels
        while(!indigoDock.isNull())
        {

            if(lst_tmpDocks.size() > 0){


                for( int i=0; i<lst_tmpDocks.count(); ++i )
                {

                    IndigoDock * sortDock = lst_tmpDocks.at(i);

                    if (sortDock->accessibleName() == indigoDock.attribute("name","")){



                      /*qDebug() << "Dock"
                               << "id" << indigoDock.attribute("id")
                               << "name" << indigoDock.attribute("name")
                               << "position" << indigoDock.attribute("position");
                       */

                      // Add atrributes of dock


                      // add sorted panels
                      QDomElement indigoPanel = indigoDock.firstChildElement("IndigoPanel");

                      while(!indigoPanel.isNull())
                      {


                          if(lst_tmpPanels.size() > 0){

                              for( int i=0; i<lst_tmpPanels.count(); ++i )
                              {
                                  IndigoPanel * sortPanel = lst_tmpPanels.at(i);

                                  if (sortPanel->accessibleName() == indigoPanel.attribute("name", "")){

                                      sortDock->addIndigoPanel(sortPanel);

                                      //add attribute
                                     // sortPanel->setIndex(indigoPanel.attribute("id").toInt());
                                      sortPanel->setExpanderState(indigoPanel.attribute("expanderState", "-1").toInt());
                                      sortPanel->setDockState(indigoPanel.attribute("dockState", "-1").toInt());


                                  }

                              }

                          }

                          indigoPanel = indigoPanel.nextSiblingElement("IndigoPanel");


                      }


                      addIndigoDock(sortDock);


                    }

                }
            }


            // next dock
            indigoDock = indigoDock.nextSiblingElement("IndigoDock");

        }



        // restore floating panels
        if(!floatingPanels.isNull())
        {

            QDomElement indigoPanel = floatingPanels.firstChildElement("IndigoPanel");

            while(!indigoPanel.isNull())
            {

                if(lst_tmpPanels.size() > 0){

                    for( int i=0; i<lst_tmpPanels.count(); ++i )
                    {
                        IndigoPanel * floatingPanel = lst_tmpPanels.at(i);

                        if (floatingPanel->accessibleName() == indigoPanel.attribute("name", "")){

                            if(!lst_floatingPanels.contains(floatingPanel))
                                lst_floatingPanels.append(floatingPanel);

                            floatingPanel->setParent(this);

                            //add attribute
                            floatingPanel->setIndex(indigoPanel.attribute("id", "-1").toInt());
                            floatingPanel->setExpanderState(indigoPanel.attribute("expanderState", "-1").toInt());
                            floatingPanel->setGeometry(indigoPanel.attribute("x", "0").toInt(), indigoPanel.attribute("y", "0").toInt(), floatingPanel->geometry().width(), floatingPanel->geometry().height());
                            floatingPanel->setDockState(indigoPanel.attribute("dockState", "-1").toInt());


                        }

                    }

                }

                indigoPanel = indigoPanel.nextSiblingElement("IndigoPanel");


            }

        }


        xmlFile.close();
    }


}



void IndigoDockManager::saveWorkspace(QString file){


    qDebug() << "Save Workspace start" << endl;

    QXmlStreamWriter xmlWriter;
    QFile xmlFile(file);

    if (!xmlFile.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(0, "Error!", "Error opening workspace file");
    }
    else
    {

        xmlWriter.setDevice(&xmlFile);
        xmlWriter.setAutoFormatting(true);


        xmlWriter.writeStartDocument();

        xmlWriter.writeStartElement("IndigoDockManager");
        xmlWriter.writeAttribute("version",version);        

        // Docks
        if(lst_Docks.size() > 0){

            for( int i=0; i<lst_Docks.count(); ++i )
            {

                IndigoDock *dock = lst_Docks.at(i);

                xmlWriter.writeStartElement("IndigoDock");
                xmlWriter.writeAttribute("id",QString::number(i));
                xmlWriter.writeAttribute("name",dock->accessibleName());
                xmlWriter.writeAttribute("position","");


                if(dock->getPanels().size() > 0){

                    for( int p=0; p<dock->getPanels().count(); ++p )
                    {
                        IndigoPanel *pan = dock->getPanels().at(p);

                        xmlWriter.writeStartElement("IndigoPanel");
                        xmlWriter.writeAttribute("id",QString::number(pan->Index()));
                        xmlWriter.writeAttribute("name",pan->accessibleName());
                        xmlWriter.writeAttribute("expanderState",QString::number(pan->expanderState()));
                        xmlWriter.writeAttribute("dockState",QString::number(pan->dockState())); // only Docked & HiddenDocked will be available
                        //xmlWriter.writeAttribute("x",QString::number(pan->geometry().x()));
                        //xmlWriter.writeAttribute("y",QString::number(pan->geometry().y()));
                        xmlWriter.writeEndElement();
                    }
                }


                xmlWriter.writeEndElement();

            }

        }

        qDebug() << lst_floatingPanels.size() << endl;

        // Floating Panels
        if(lst_floatingPanels.size() > 0){

            xmlWriter.writeStartElement("FloatingPanels");

            for( int i=0; i<lst_floatingPanels.count(); ++i )
            {

                IndigoPanel *fPanel = lst_floatingPanels.at(i);

                xmlWriter.writeStartElement("IndigoPanel");
                xmlWriter.writeAttribute("id",QString::number(fPanel->Index()));
                xmlWriter.writeAttribute("name",fPanel->accessibleName());
                xmlWriter.writeAttribute("expanderState",QString::number(fPanel->expanderState()));
                xmlWriter.writeAttribute("dockState",QString::number(fPanel->dockState())); // only Floating & HiddenFloating will be available
                xmlWriter.writeAttribute("x",QString::number(fPanel->geometry().x()));
                xmlWriter.writeAttribute("y",QString::number(fPanel->geometry().y()));
                xmlWriter.writeEndElement();


            }

            xmlWriter.writeEndElement();

        }


        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();

        xmlFile.close();

    }

     qDebug() << "Save Workspace end" << endl;

}
