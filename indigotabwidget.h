#ifndef INDIGOTABWIDGET_H
#define INDIGOTABWIDGET_H

#include <QTabWidget>
#include <QIcon>
#include "indigodock.h"

class IndigoTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    IndigoTabWidget(QWidget* parent = 0);
    void addTab ( QWidget * child, const QString & label );
    void addTab ( QWidget * child, const QIcon & icon, const QString & label );
    //void addTab ( QWidget * child, QTab * tab );

protected:
signals:

public slots:
};

#endif // INDIGOTABWIDGET_H
