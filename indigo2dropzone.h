#ifndef INDIGODOCK2_H
#define INDIGODOCK2_H

#include <QWidget>
#include <QFrame>
#include <QVBoxLayout>
#include "indigo2panel.h"
#include "indigo2tabbar.h"

class Indigo2DropZone : public QWidget
{
    Q_OBJECT
public:
    Indigo2DropZone(QWidget* parent = 0);
    QVBoxLayout *layout;
protected:
    void createPanel();
    bool event ( QEvent * event );
private:

signals:

public slots:
    void dropPanel();
};

#endif // INDIGODOCK2_H
