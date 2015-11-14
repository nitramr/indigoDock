#ifndef INDIGOGROUPBOX_H
#define INDIGOGROUPBOX_H

#include <QWidget>
#include <QGroupBox>
#include <QEvent>
#include <QtGui>
#include <QLayout>

class IndigoGroupBox : public QGroupBox
{
    Q_OBJECT
public:
    explicit IndigoGroupBox(QWidget *parent = 0);

private:
    bool eventFilter(QObject *o, QEvent *e);
    QVBoxLayout * mainLayout;
    int minHeight;

signals:

public slots:
};

#endif // INDIGOGROUPBOX_H
