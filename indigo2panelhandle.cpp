#include "indigo2panelhandle.h"


/* TODO:
 *
 * - add title
 * - add close button
 *
 */

Indigo2PanelHandle::Indigo2PanelHandle(QWidget *parent) :
    QWidget(parent)
{
    QPalette palette;
    palette.setColor( QPalette::Background, QColor( 240, 240, 255 ) );
    setPalette( palette );
    setAutoFillBackground( true );
}
