#ifndef COLORSWATCH_H
#define COLORSWATCH_H

#include <QWidget>
#include <QtGui>


class ColorSwatch : public QWidget
{
    Q_OBJECT
public:
    ColorSwatch(QWidget *parent = 0);

    void setContourBrush(QBrush brush);
    void setFillBrush(QBrush brush);

private:  
    void paintEvent(QPaintEvent*);
    QBrush br_contour;
    QBrush br_fill;

signals:

public slots:
};





#endif // COLORSWATCH_H
