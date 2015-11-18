#ifndef INDIGODOCK_H
#define INDIGODOCK_H

#include <QWidget>
#include "indigotabbar.h"
#include "indigodropzone.h"

class IndigoDock : public QWidget
{
    Q_OBJECT
public:
    explicit IndigoDock(QWidget *parent = 0);
    IndigoTabbar *m_indigoTab;
    void addIndigoPanel(IndigoPanel *panel, int tabIndex = -1);

private:
    void init();

signals:

public slots:
};

#endif // INDIGODOCK_H
