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
#include <QXmlStreamWriter>
#include <QMainWindow>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QStyle>

IndigoDockManager::IndigoDockManager(QMainWindow *parent) : QWidget(parent){

    version = "1.0"; // workspace manager version
    int_minimumPanelHeight = 50;
    int_minimumPanelWidth = 100;
    int_fadeSpeed = 100;

    setFixedSize(0,0);

}



void IndigoDockManager::connectPanel(IndigoPanel * panel){

    // reconnect
    this->connect(panel, SIGNAL(panelClosed(int)), this, SLOT(hideTab(int)));
    this->connect(panel, SIGNAL(panelShown(int)), this, SLOT(showTab(int)));
    this->connect(panel, SIGNAL(mouseMove()), this, SLOT(hoverDock()));
    this->connect(panel, SIGNAL(mouseReleased()), this, SLOT(dropPanel()));
    this->connect(panel, SIGNAL(isFloating()), this, SLOT(dragoutPanel()));


}



void IndigoDockManager::addIndigoDock(IndigoDock *dock, Qt::DockWidgetArea area){

    QMainWindow * main = qobject_cast<QMainWindow *>(parent());

    if(main){


        if(!lst_Docks.contains(dock)){
            lst_Docks.append(dock);



            QString count = QString::number(lst_Docks.size());

            dock->setAccessibleName("IndigoDock"+count);
            dock->setObjectName("IndigoDock"+count);
            dock->setMinimumPanelSize(minimumPanelSize()); // set min size

            main->addDockWidget(area,dock);

        }else{
            qDebug() << "Dock exists in DockManager list" << dock << endl;
        }

    }

}



void IndigoDockManager::removeDock(IndigoDock * dock){

    QMainWindow * main = qobject_cast<QMainWindow *>(parent());

    if(main){

        main->removeDockWidget(dock);
        lst_Docks.removeAll(dock);
        dock->deleteLater();

        return;

    }
}



void IndigoDockManager::removeAllDocks(QList<IndigoPanel *> &lst_outPanel, QList<IndigoDock *> &lst_outDock){

    QMainWindow * main = qobject_cast<QMainWindow *>(parent());

    if(main){

        IndigoDock * dock;
        foreach (dock, lst_Docks) {


            // Make copy of dock
            lst_outDock.append(dock);

            // make copy of panels
            IndigoPanel * panel;
            foreach(panel, dock->getPanels()){
                lst_outPanel.append(panel);
            }

            // clear dock
            dock->clear();

            // remove dock
            main->removeDockWidget(dock);


        }

        lst_Docks.clear();
    }

}



void IndigoDockManager::addIndigoPanel(IndigoPanel * panel, IndigoPanel::IndigoDockState dockState, bool isNewPanel, int tabIndex){

    addIndigoPanel(NULL, panel, dockState, isNewPanel, tabIndex);
}



void IndigoDockManager::addIndigoPanel(IndigoDock * dock, IndigoPanel * panel, IndigoPanel::IndigoDockState dockState, bool isNewPanel, int tabIndex){

    if(!dock) dock = new IndigoDock(this);

    // connect panel signals
    if(isNewPanel)
        connectPanel(panel);

    // add dock if needed
    addIndigoDock(dock);


    // set floating options
    if(dockState == IndigoPanel::Floating){

        dock->setWindowOpacity(0);
        dock->show();
        dock->adjustSize();

        int titleHeight = dock->style()->pixelMetric(QStyle::PM_TitleBarHeight);
        int titleMargin = dock->style()->pixelMetric(QStyle::PM_DockWidgetTitleMargin);

        QPoint pntOffset(0, titleHeight + titleMargin);

        dock->setFloating(true);
        dock->move(panel->pos() - pntOffset);

        QPropertyAnimation *animation;
        animation = new QPropertyAnimation(dock, "windowOpacity");
        animation->setDuration(int_fadeSpeed);
        animation->setStartValue(0);
        animation->setEndValue(1);
        animation->start();

        //dock->setWindowOpacity(1);

    }

    // add panel
    dock->addIndigoPanel(panel, dockState, tabIndex);


}



void IndigoDockManager::dragoutPanel(){

    IndigoPanel *panel = qobject_cast<IndigoPanel *>(sender());

    if (!panel) return;
    panel->setParent(this);
    panel->setDockState(IndigoPanel::Floating);

    qDebug() << "Panel DragOut" << endl;


    removePanel(panel);

}



void IndigoDockManager::removePanel(IndigoPanel * panel){


    int index = panel->Index();

    IndigoDock * dock;
    foreach(dock, lst_Docks){

        if(dock->getPanels().contains(panel)){

            dock->removePanel(index);
            panel->setParent(this);
            panel->show();

            if(dock->getPanels().size() <= 0){

               /* QPropertyAnimation *animation;
                animation = new QPropertyAnimation(dock, "windowOpacity");
                animation->setDuration(int_fadeSpeed);
                animation->setStartValue(1);
                animation->setEndValue(0);
                animation->start();*/

                dock->hide();
                lst_removeDocks.append(dock); // add remove candidate

            }

            return;
        }

    }

}



void IndigoDockManager::hideTab(int index){

    IndigoPanel *pan = qobject_cast<IndigoPanel *>(sender());
    if (!pan) return;

    IndigoDock * dock;
    foreach(dock, lst_Docks){

        if(dock->getPanels().contains(pan)){

            dock->hideTab(index);

            return;
        }

    }

}



void IndigoDockManager::showTab(int index){

    IndigoPanel *pan = qobject_cast<IndigoPanel *>(sender());
    if (!pan) return;


    IndigoDock * dock;
    foreach(dock, lst_Docks){

        if(dock->getPanels().contains(pan)){

            dock->showTab(index);

            return;
        }

    }
}



void IndigoDockManager::scrollToPanel(QString name){


    IndigoDock * dock;
    foreach(dock, lst_Docks){

        dock->scrollToPanel(name);
    }

}



void IndigoDockManager::hoverDock(){

    IndigoPanel *pan = qobject_cast<IndigoPanel *>(sender());
    if (!pan) return;


    IndigoDock * dock;
    foreach(dock, lst_Docks){

        dock->hoverDock(pan);
    }


}



void IndigoDockManager::dropPanel(){
    IndigoPanel *pan = qobject_cast<IndigoPanel *>(sender());
    if (!pan) return;

    // try to add panel if it hover a dock
    IndigoDock * dock;
    foreach(dock, lst_Docks){

        dock->dropPanel(pan);

    }


    // create floating dock if panel is not already docked
    if (pan->dockState() == IndigoPanel::Floating){

        addIndigoPanel(pan, pan->dockState(), false);

    }


    // remove remove-candidate docks

    if (lst_removeDocks.size() <= 0) return;

    IndigoDock * remDock;
    foreach(remDock, lst_removeDocks){

        removeDock(remDock);

    }

    lst_removeDocks.clear();

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

    // remove all dock and save copies to restore
    removeAllDocks(lst_tmpPanels, lst_tmpDocks);


    int i = 0;

    // restore dock layout and docked panels
    while(!indigoDock.isNull())
    {


        if(lst_tmpDocks.size() > 0){

            IndigoDock * newDock;

            if(i < lst_tmpDocks.size()){
                newDock = lst_tmpDocks.at(i);
            }else newDock = new IndigoDock(this);


            // add sorted panels
            QDomElement indigoPanel = indigoDock.firstChildElement("IndigoPanel");

            while(!indigoPanel.isNull())
            {

                IndigoPanel * sortPanel;
                foreach(sortPanel, lst_tmpPanels){

                    if (sortPanel->objectName() == indigoPanel.attribute("name", "")){

                        newDock->addIndigoPanel(sortPanel);

                        //add attribute
                        sortPanel->setExpanderState(indigoPanel.attribute("expanderState", "-1").toInt());
                        sortPanel->setDockState(indigoPanel.attribute("dockState", "-1").toInt());

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
    IndigoDock * dock;
    foreach(dock, lst_Docks){

        xmlWriter.writeStartElement("IndigoDock");
        //xmlWriter.writeAttribute("id",QString::number(i));
        xmlWriter.writeAttribute("name",dock->objectName());

        IndigoPanel * panel;
        foreach(panel, dock->getPanels()){

            xmlWriter.writeStartElement("IndigoPanel");
            xmlWriter.writeAttribute("id",QString::number(panel->Index()));
            xmlWriter.writeAttribute("name",panel->objectName());
            xmlWriter.writeAttribute("expanderState",QString::number(panel->expanderState()));
            xmlWriter.writeAttribute("dockState",QString::number(panel->dockState())); // only Docked & HiddenDocked will be available
            xmlWriter.writeEndElement();

        }


        xmlWriter.writeEndElement();

    }


    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();




    return qba_panels;
}



/**********************
 *
 * Properties
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
