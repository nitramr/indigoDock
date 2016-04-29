#ifndef INDIGOHUB_H
#define INDIGOHUB_H

#include <QWidget>
#include "indigodock.h"

class IndigoHub: public QWidget
{
    Q_OBJECT
public:
    IndigoHub(QWidget *parent = 0);
    void addIndigoDock(IndigoDock * dock);
    void addIndigoPanel(IndigoDock * dock, IndigoPanel * panel, int tabIndex = -1);
    void scrollToPanel(QString name);

private:
    QList<IndigoDock*> lst_Docks;

signals:

public slots:
    void hoverDock();
    void dropPanel();
    void removePanel(int index);
};

#endif // INDIGOHUB_H
