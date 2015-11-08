#ifndef INDIGO2DOCK_H
#define INDIGO2DOCK_H

#include <QWidget>
#include "indigo2tabbar.h"
#include "indigo2dropzone.h"

class Indigo2Dock : public QWidget
{
    Q_OBJECT
public:
    explicit Indigo2Dock(QWidget *parent = 0);
    Indigo2Tabbar *indigoTab;
    void addTab(QIcon icon);
private:
    void init();
signals:

public slots:
};

#endif // INDIGO2DOCK_H
