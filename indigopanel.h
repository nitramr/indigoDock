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
#include "indigodock.h"

class IndigoPanel : public QDockWidget
{
    Q_OBJECT
public:
    IndigoPanel(QWidget* parent = 0);

protected:
   bool eventFilter( QObject * watched, QEvent * event );

signals:
    void panelMove(bool isMove);

private:
   QPoint dragStartPosition;

public slots:

};

#endif // INDIGOPANEL_H
