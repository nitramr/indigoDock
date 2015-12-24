#include "helper.h"

Helper::Helper()
{

}


QColor Helper::blendColor(QColor color1, QColor color2, double ratio){

    if(ratio < 0 && ratio > 1){
        ratio = 0;
    }

    return QColor(
                color1.red()* (1-ratio) + color2.red()*ratio,
                color1.green()* (1-ratio) + color2.green()*ratio,
                color1.blue()* (1-ratio) + color2.blue()*ratio,
                255);

}
