#ifndef COLORSWATCH_H
#define COLORSWATCH_H

#include <QWidget>
#include <QtGui>
#include <QPushButton>


class ColorSwatch : public QWidget
{
    Q_OBJECT

public:
    ColorSwatch(QWidget *parent = 0);

    void setContourBrush(QBrush brush);
    void setFillBrush(QBrush brush);
    void setContourButton(QPushButton *btnContour);
    void setFillButton(QPushButton *btnFill);

protected:
    QPushButton *btn_Contour;
    QPushButton *btn_Fill;

private:  
    void paintEvent(QPaintEvent*);
    QBrush br_contour;
    QBrush br_fill;

    int conSize;
    int conWidth;
    int spacer;
    int valveWidth;
    int valveHeight;
    int btnSize;

    void placeContourButton();
    void placeFillButton();

signals:

public slots:
};





#endif // COLORSWATCH_H
