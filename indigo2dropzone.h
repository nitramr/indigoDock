#ifndef INDIGODOCK2_H
#define INDIGODOCK2_H

#include <QWidget>
#include <QFrame>
#include <QVBoxLayout>
#include <indigo2panel.h>
#include "indigo2tabbar.h"
#include <QSplitter>

class Indigo2DropZone : public QWidget
{
    Q_OBJECT
public:
    Indigo2DropZone(QWidget* parent = 0);
    void addPanel (Indigo2Panel * panel);
    void createPanel(const QString &title, QWidget *widget);

protected:

private:
    QVBoxLayout *layout;
    QSplitter *splitter;
    int padding;

signals:

public slots:
    void dropPanel();
};

#endif // INDIGODOCK2_H
