#ifndef COLORSWATCH_H
#define COLORSWATCH_H

#include <QWidget>
#include <QtGui>


class ColorSwatch : public QWidget
{
     Q_OBJECT
     Q_ENUMS(ColorMode)
public:
    ColorSwatch(QWidget *parent = 0);
    enum ColorMode{ Stroke, Fill };

    ColorMode getColorMode();
    void setColorMode(ColorMode colormode);

private:
    ColorMode colormode;

signals:

public slots:
};





#endif // COLORSWATCH_H
