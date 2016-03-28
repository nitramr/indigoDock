#ifndef INDIGOICONWIDGET_H
#define INDOGOICONWIDGET_H

#include <QWidget>
#include <QtGui>

class IndigoIconWidget : public QWidget
{
    Q_OBJECT
public:
    IndigoIconWidget(QWidget *parent = 0);
    IndigoIconWidget(QIcon icon, int iconSize, QWidget *parent = 0);
    IndigoIconWidget(QString filePath, int iconSize, QWidget *parent = 0);
    void setIcon(QIcon icon, int iconSize = 22);
    void setIcon(QString fielPath, int iconSize = 22);

protected:
    void paintEvent(QPaintEvent *);

private:
    QPixmap pxm_icon;
    int int_iconSize;

signals:

public slots:
};

#endif // INDIGOICONWIDGET_H
