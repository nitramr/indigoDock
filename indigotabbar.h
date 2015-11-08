#ifndef INDIGOTABBAR_H
#define INDIGOTABBAR_H

#include <QtWidgets>
#include <QTabWidget>
#include <QIcon>
#include "indigodropzone.h"

class IndigoTabbar : public QTabWidget
{
    Q_OBJECT
public:
    IndigoTabbar(QWidget* parent = 0);
    void addTab ( QWidget * child, const QString & label );
    void addTab ( QWidget * child, const QIcon & icon, const QString & label );
    QWidget * activeWidget;

protected:
    bool eventFilter(QObject *o, QEvent *e);

signals:

public slots:

};

#endif // INDIGOTABBAR_H
