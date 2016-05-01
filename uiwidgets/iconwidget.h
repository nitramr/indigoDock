#ifndef ICONWIDGET_H
#define ICONWIDGET_H

#include <QWidget>
#include <QtGui>

class IconWidget : public QWidget
{
    Q_OBJECT
public:
    IconWidget(QWidget *parent = 0);
    IconWidget(QIcon icon, int iconSize, QWidget *parent = 0);
    IconWidget(QString filePath, int iconSize, QWidget *parent = 0);
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

#endif // ICONWIDGET_H
