#ifndef INDIGOPANEL_H
#define INDIGOPANEL_H

#include <QApplication>
#include <QWidget>
#include <QDockWidget>
#include <QMouseEvent>
#include <QEvent>
#include <QLabel>
#include <QDrag>
#include <QMimeData>
#include "indigodropzone.h"

class IndigoPanel : public QDockWidget
{
    Q_OBJECT
public:
    IndigoPanel(QWidget* parent = 0);

protected:

signals:   

private:  

public slots:

};

#endif // INDIGOPANEL_H
