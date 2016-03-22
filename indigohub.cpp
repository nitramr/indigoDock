#include "indigohub.h"

IndigoHub::IndigoHub(QWidget *parent) : QWidget(parent)
{

}

void IndigoHub::connectIndigoPanel(IndigoPanel *panel, IndigoDock *indigoDock, IndigoDock *indigoDock2){

    this->connect(panel, SIGNAL(mouseMove()), indigoDock->m_dropzone, SLOT(hoverZone()));
    this->connect(panel, SIGNAL(mouseReleased()), indigoDock->m_dropzone, SLOT(dropPanel()));

    this->connect(panel, SIGNAL(mouseMove()), indigoDock2->m_dropzone, SLOT(hoverZone()));
    this->connect(panel, SIGNAL(mouseReleased()), indigoDock2->m_dropzone, SLOT(dropPanel()));

}
