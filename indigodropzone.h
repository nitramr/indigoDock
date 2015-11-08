#ifndef INDIGOCONTAINER_H
#define INDIGOCONTAINER_H

#include <QMainWindow>
#include <QListWidget>
#include <QDockWidget>
#include "indigopanel.h"

class IndigoDropZone: public QMainWindow
{
    Q_OBJECT
public:
    void createIndigoPanel(QString title);

    IndigoDropZone(QWidget* parent = 0);
    ~IndigoDropZone();
protected:  
    bool eventFilter( QObject * watched, QEvent * event );

private:
signals:

public slots:
};

#endif // INDIGOCONTAINER_H
