#ifndef INDIGODROPZONE_H
#define INDIGODROPZONE_H

#include <QWidget>
#include <QFrame>
#include <QVBoxLayout>
#include <indigopanel.h>
#include <indigotabbar.h>
#include <QSplitter>

class IndigoDropZone : public QWidget
{
    Q_OBJECT
public:
    IndigoDropZone(QWidget* parent = 0);
    void addPanel (IndigoPanel * panel);
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

#endif // INDIGODROPZONE_H
