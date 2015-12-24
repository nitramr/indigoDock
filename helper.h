#ifndef HELPER_H
#define HELPER_H

#include <QColor>

class Helper
{
public:
    Helper();
    QColor blendColor(QColor color1, QColor color2, double ratio);


};

#endif // HELPER_H
