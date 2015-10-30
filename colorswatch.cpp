#include "colorswatch.h"

ColorSwatch::ColorSwatch(QWidget *parent)
    : QWidget(parent)
{
    //colormode = ColorMode::Fill;

}

ColorSwatch::ColorMode ColorSwatch::getColorMode(){
    return colormode;
}

void ColorSwatch::setColorMode(ColorMode colorMode){
    colormode = colorMode;
}

