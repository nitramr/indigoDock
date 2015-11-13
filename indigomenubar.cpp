#include "indigomenubar.h"

IndigoMenuBar::IndigoMenuBar()
{
    QMenu *menuWindow = this->addMenu(tr("&Window"));
    QAction *addNew = new QAction(menuWindow);
    addNew->setText(tr("Add new"));
    menuWindow->addAction(addNew);
    QAction *quit = new QAction(menuWindow);
    quit->setText(tr("&Quit"));
    menuWindow->addAction(quit);
    connect(quit, SIGNAL(triggered()), this, SLOT(close()));
    // connect(addNew, SIGNAL(triggered()), this, SLOT(onAddNew()));

}

