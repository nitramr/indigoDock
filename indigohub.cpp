#include "indigohub.h"

IndigoHub::IndigoHub(QWidget *parent) : QWidget(parent){}



void IndigoHub::connectIndigoPanel(IndigoPanel *panel, IndigoDock *indigoDock, IndigoDock *indigoDock2){

    this->connect(panel, SIGNAL(mouseMove()), indigoDock, SLOT(hoverDock()));
    this->connect(panel, SIGNAL(mouseReleased()), indigoDock, SLOT(dropPanel()));

    this->connect(panel, SIGNAL(mouseMove()), indigoDock2, SLOT(hoverDock()));
    this->connect(panel, SIGNAL(mouseReleased()), indigoDock2, SLOT(dropPanel()));

}
