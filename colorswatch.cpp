#include "colorswatch.h"

/****************************
 *
 * TODO: Add edit buttons
 *
 * ***************************/


ColorSwatch::ColorSwatch(QWidget *parent)
    : QWidget(parent)
{


    setAutoFillBackground(true);


    conWidth = 9; // countour thickness
    spacer = 1; // spacer between countour and fill
    valveWidth = 4; // valve width
    valveHeight = 4; // valve height
    btnSize = 22; // button dimensions

    setMinimumHeight(btnSize*2);

    setFixedHeight(44);
    setMinimumWidth(height() + valveWidth + btnSize);

    conSize = this->height(); // square width and height without valves

    // Placeholder Buttons
    btn_Contour = new QPushButton(this);
    btn_Fill = new QPushButton(this);

    // place buttons
    placeContourButton();
    placeFillButton();

    // set default brush
    br_fill = QBrush(Qt::black);
    br_contour = QBrush(Qt::black);



    // Dummy brush (please remove)
    QLinearGradient gradient(0,0,this->height(),this->height());
        gradient.setColorAt(0, QColor(110,110,110));
        gradient.setColorAt(0.27, QColor(230,230,230));
        gradient.setColorAt(0.44, QColor(110,110,110));
        gradient.setColorAt(0.76, QColor(230,230,230));
        gradient.setColorAt(1, QColor(110,110,110));

    setFillBrush(QBrush(gradient));


}


void ColorSwatch::paintEvent(QPaintEvent*) {

    QPainter painter(this);



    // Contour Points
    int conX1 = 0;
    int conY1 = 0;

    int conX2   = conSize;
    int conY2   = 0;

    int conX3   = conSize;
    int conY3   = conWidth;

    int conX4   = conWidth;
    int conY4   = conWidth;

    int conX5   = conWidth;
    int conY5   = conSize - conWidth ;

    int conX6   = conY5; //conSize - conWidth;
    int conY6   = conY5; //conSize - conWidth;

    int conX7   = conY5; //conSize - conWidth;
    int conY7   = conWidth + (spacer*2) + valveHeight;

    int conX8   = conSize;
    int conY8   = conY7; //conWidth + (spacer*2) + valveHeight;

    int conX9   = conSize;
    int conY9   = conSize - spacer - conWidth - valveHeight;

    int conX10   = conSize + valveWidth;
    int conY10   = conY9; //conSize - spacer - conWidth - valveHeight;

    int conX11   = conSize + valveWidth;
    int conY11   = conSize - spacer - conWidth;

    int conX12   = conSize;
    int conY12   = conY11; //conSize - spacer - conWidth;

    int conX13   = conSize;
    int conY13   = conSize;

    int conX14   = 0;
    int conY14   = conSize;


    // Fill Points
    int fillX1 = conX4 + spacer;
    int fillY1 = conY4 + spacer;

    int fillX2 = conX10;
    int fillY2 = fillY1;

    int fillX3 = conX10;
    int fillY3 = conWidth + spacer + valveHeight;

    int fillX4 = conY11;
    int fillY4 = fillY3; //conWidth + spacer + valveHeight;

    int fillX5 = conX6 - spacer;
    int fillY5 = conY6 - spacer;

    int fillX6 = fillX1;
    int fillY6 = fillY5;

    QPainterPath countour;
    countour.moveTo (conX1, conY1);
    countour.lineTo (conX2, conY2);
    countour.lineTo (conX3, conY3);
    countour.lineTo (conX4, conY4);
    countour.lineTo (conX5, conY5);
    countour.lineTo (conX6, conY6);
    countour.lineTo (conX7, conY7);
    countour.lineTo (conX8, conY8);
    countour.lineTo (conX9, conY9);
    countour.lineTo (conX10, conY10);
    countour.lineTo (conX11, conY11);
    countour.lineTo (conX12, conY12);
    countour.lineTo (conX13, conY13);
    countour.lineTo (conX14, conY14);
    countour.lineTo (conX1, conY1);

    QPainterPath fill;
    fill.moveTo (fillX1, fillY1);
    fill.lineTo (fillX2, fillY2);
    fill.lineTo (fillX3, fillY3);
    fill.lineTo (fillX4, fillY4);
    fill.lineTo (fillX5, fillY5);
    fill.lineTo (fillX6, fillY6);
    fill.lineTo (fillX1, fillY1);

    painter.setPen (Qt :: NoPen);
    painter.fillPath (countour, br_contour);
    painter.fillPath (fill, br_fill);


}

void ColorSwatch::setContourBrush(QBrush brush){
    br_contour = brush;
    update();
}

void ColorSwatch::setFillBrush(QBrush brush){
    br_fill = brush;
    update();
}

void ColorSwatch::setContourButton(QPushButton *btnContour){
    btn_Contour = btnContour;
    placeContourButton();
}

void ColorSwatch::setFillButton(QPushButton *btnFill){
    btn_Fill = btnFill;
    placeFillButton();
}

void ColorSwatch::placeContourButton(){
    if (!btn_Contour) return;

    btn_Contour->setFixedSize(btnSize,btnSize);
    btn_Contour->move(conSize + valveWidth, 0);

}

void ColorSwatch::placeFillButton(){
    if(!btn_Fill) return;

    btn_Fill->setFixedSize(btnSize,btnSize);
    btn_Fill->move(conSize + valveWidth, conSize - btn_Fill->height());
}

