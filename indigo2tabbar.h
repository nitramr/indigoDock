#ifndef INDIGO2TABBAR_H
#define INDIGO2TABBAR_H

#include <QTabWidget>
#include <QIcon>
#include "indigodropzone.h"

class Indigo2Tabbar : public QTabWidget
{
    Q_OBJECT
public:
    Indigo2Tabbar(QWidget* parent = 0);
    void addTab ( QWidget * child, const QString & label );
    void addTab ( QWidget * child, const QIcon & icon, const QString & label );
    QWidget * activeWidget;

protected:
    bool eventFilter(QObject *o, QEvent *e);

signals:

public slots:

};

#endif // INDIGO2TABBAR_H
