#ifndef INDIGOHUB_H
#define INDIGOHUB_H

#include <QWidget>
#include "indigodock.h"

class IndigoHub: public QWidget
{
    Q_OBJECT
public:
    IndigoHub(QWidget *parent = 0);
    void connectIndigoPanel(IndigoPanel *panel, IndigoDock *indigoDock, IndigoDock *indigoDock2);

signals:

public slots:
};

#endif // INDIGOHUB_H
