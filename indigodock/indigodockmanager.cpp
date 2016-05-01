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

IndigoDockManager::IndigoDockManager(QWidget *parent) : QWidget(parent){


}



void IndigoDockManager::addIndigoDock(IndigoDock * dock){

    if(!lst_Docks.contains(dock)){
         lst_Docks.append(dock);
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
