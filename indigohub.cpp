#include "indigohub.h"

IndigoHub::IndigoHub(QWidget *parent) : QWidget(parent){}


void IndigoHub::addIndigoDock(IndigoDock * dock){

    if(!lst_Docks.contains(dock)){
         lst_Docks.append(dock);
    }

}



void IndigoHub::addIndigoPanel(IndigoDock * dock, IndigoPanel * panel, int tabIndex){

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



void IndigoHub::scrollToPanel(QString name){


    if(lst_Docks.size() > 0){

        for( int i=0; i<lst_Docks.count(); ++i )
        {
            lst_Docks.at(i)->scrollToPanel(name);
        }

    }

}



void IndigoHub::hoverDock(){

    IndigoPanel *pan = qobject_cast<IndigoPanel *>(sender());
    if (!pan) return;


    if(lst_Docks.size() > 0){

        for( int i=0; i<lst_Docks.count(); ++i )
        {

             lst_Docks.at(i)->hoverDock(pan);

        }

    }

}


void IndigoHub::dropPanel(){
    IndigoPanel *pan = qobject_cast<IndigoPanel *>(sender());
    if (!pan) return;


    if(lst_Docks.size() > 0){

        for( int i=0; i<lst_Docks.count(); ++i )
        {
            lst_Docks.at(i)->dropPanel(pan);
        }

    }
}



void IndigoHub::removePanel(int index){

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
