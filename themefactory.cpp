/***************************************************************************
 *   Copyright (C) 2005-2015 by the Quassel Project                        *
 *   devel@quassel-irc.org                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) version 3.                                           *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 *                                                                         *
 * *************************************************************************

     This is a modified version of original code on:
     https://github.com/quassel/quassel/blob/master/src/uisupport/qssparser.h

 */


#include "themefactory.h"
#include <QDebug>
#include <QMetaEnum>
#include <QtMath>


ThemeFactory::ThemeFactory()
{
    str_theme = "";


    // Init palette color groups

    _paletteColorGroups["active"]   = QPalette::Active;
    _paletteColorGroups["inactive"] = QPalette::Inactive;
    _paletteColorGroups["disabled"] = QPalette::Disabled;
    _paletteColorGroups["normal"]   = QPalette::Normal;


    // Init palette color roles

    _paletteColorRoles["alternate-base"]    = QPalette::AlternateBase;
    _paletteColorRoles["background"]        = QPalette::Background;
    _paletteColorRoles["base"]              = QPalette::Base;
    _paletteColorRoles["bright-text"]       = QPalette::BrightText;
    _paletteColorRoles["button"]            = QPalette::Button;
    _paletteColorRoles["button-text"]       = QPalette::ButtonText;
    _paletteColorRoles["dark"]              = QPalette::Dark;
    _paletteColorRoles["foreground"]        = QPalette::Foreground;
    _paletteColorRoles["highlight"]         = QPalette::Highlight;
    _paletteColorRoles["highlighted-text"]  = QPalette::HighlightedText;
    _paletteColorRoles["light"]             = QPalette::Light;
    _paletteColorRoles["link"]              = QPalette::Link;
    _paletteColorRoles["link-visited"]      = QPalette::LinkVisited;
    _paletteColorRoles["mid"]               = QPalette::Mid;
    _paletteColorRoles["midlight"]          = QPalette::Midlight;
    _paletteColorRoles["shadow"]            = QPalette::Shadow;
    _paletteColorRoles["text"]              = QPalette::Text;
    _paletteColorRoles["tooltip-base"]      = QPalette::ToolTipBase;
    _paletteColorRoles["tooltip-text"]      = QPalette::ToolTipText;
    _paletteColorRoles["window"]            = QPalette::Window;
    _paletteColorRoles["window-text"]       = QPalette::WindowText;


}



QString ThemeFactory::getTheme(){
    return str_theme;
}



void ThemeFactory::parseString(QString &StyleString){


    if (StyleString.isEmpty())
           return;

       // Remove C-style comments /* */ or //
       QRegExp rx_comments("(//.*(\\n|$)|/\\*.*\\*/)");
       rx_comments.setMinimal(true);
       StyleString.remove(rx_comments);


       QString str_Palette = "(Palette\\s*::)\\s*(light|dark)([^{]*\\{)([^\\}]+)(\\})";
       QRegExp rx_Palette(str_Palette);

       if (rx_Palette.indexIn(StyleString) < 0) {
           qDebug("Can't find Palette Section in UI file.");
           return;
       }

       // remove palette style in QSS File
       StyleString.remove(rx_Palette.cap(0));

       QString str_palette = rx_Palette.cap(0).trimmed();

       str_theme = rx_Palette.cap(2).trimmed();
       qDebug() << "UI theme is:" << str_theme << endl;

       // remove palette style in QSS File
       str_palette.remove(rx_Palette.cap(1)); // Palette
       str_palette.remove(rx_Palette.cap(2)); // theme
       str_palette.remove(rx_Palette.cap(3)); // {
       str_palette.remove(rx_Palette.cap(5)); // }


        QString str_Settings = "\\[(\\w+)\\]\\s*([a-zA-Z-]+)\\s*:\\s*([a-zA-Z#0-9-(),. ]*);\\s*";
        QRegExp rx_Settings(str_Settings);

       int pos = 0;
       while ((pos = rx_Settings.indexIn(str_palette, pos)) >= 0) {
           //qDebug() << rx_Settings.cap(1).trimmed() << rx_Settings.cap(2).trimmed() << rx_Settings.cap(3).trimmed() << endl;

            builtPalette(rx_Settings.cap(1).trimmed(),rx_Settings.cap(2).trimmed(), rx_Settings.cap(3).trimmed() );

           str_palette.remove(pos, rx_Settings.matchedLength());
       }


}



void ThemeFactory::builtPalette(QString group, QString role, QString color){

    QPalette::ColorGroup cg;
    QPalette::ColorRole cr;
    QColor co;

    // set Color Group
    if(!_paletteColorGroups.contains(group)){
        cg = QPalette::Normal;
    }else cg = _paletteColorGroups.value(group);


    // set Color Role
    if(!_paletteColorRoles.contains(role)) return;
    cr = _paletteColorRoles.value(role);


    // set Color
    co = parseColor(color);


    if(group == "all"){
         pal_palette.setColor(cr, co);
    }else{
         pal_palette.setColor(cg, cr, co);
    }



}



QColor ThemeFactory::parseColor(const QString str)
{
    if (str.startsWith("rgba")) {
        QRegExp rx_rgba("\\(\\s*(\\d{1,3})\\s*,\\s*(\\d{1,3})\\s*,\\s*(\\d{1,3})\\s*,\\s*(\\d{1,3})\\s*\\)");
        rx_rgba.setMinimal(true);
        if(rx_rgba.indexIn(str) >=0){

            qreal r = colorRange(rx_rgba.cap(1).toInt(),0,255);
            qreal g = colorRange(rx_rgba.cap(2).toInt(),0,255);
            qreal b = colorRange(rx_rgba.cap(3).toInt(),0,255);
            qreal a = colorRange(rx_rgba.cap(4).toDouble() / 100 *255,0,255);

            return QColor(r, g, b, a);
        }
    }
    else if (str.startsWith("rgb")) {
        QRegExp rx_rgb("\\(\\s*(\\d{1,3})\\s*,\\s*(\\d{1,3})\\s*,\\s*(\\d{1,3})\\s*\\)");
        rx_rgb.setMinimal(true);
        if(rx_rgb.indexIn(str) >=0){

            qreal r = colorRange(rx_rgb.cap(1).toInt(),0,255);
            qreal g = colorRange(rx_rgb.cap(2).toInt(),0,255);
            qreal b = colorRange(rx_rgb.cap(3).toInt(),0,255);

            return QColor(r, g, b);
        }
    }
    else if (str.startsWith("hsva")) {


        QRegExp rx_hsva("\\(\\s*(\\d{1,3})\\s*,\\s*(\\d{1,3})\\s*,\\s*(\\d{1,3})\\s*,\\s*(\\d{1,3})\\s*\\)");
        rx_hsva.setMinimal(true);
        if(rx_hsva.indexIn(str) >=0){

            qreal h = colorRange(rx_hsva.cap(1).toDouble() / 360,0,1);
            qreal s = colorRange(rx_hsva.cap(2).toDouble() / 100,0,1);
            qreal v = colorRange(rx_hsva.cap(3).toDouble() / 100,0,1);
            qreal a = colorRange(rx_hsva.cap(4).toDouble() / 100,0,1);

            QColor c;
            c.setHsvF(h, s, v, a);
            return c;
        }

    }
    else if (str.startsWith("hsv")) {

        QRegExp rx_hsv("\\(\\s*(\\d{1,3})\\s*,\\s*(\\d{1,3})\\s*,\\s*(\\d{1,3})\\s*\\)");
        rx_hsv.setMinimal(true);
        if(rx_hsv.indexIn(str) >=0){

            qreal h = colorRange(rx_hsv.cap(1).toDouble() / 360,0,1);
            qreal s = colorRange(rx_hsv.cap(2).toDouble() / 100,0,1);
            qreal v = colorRange(rx_hsv.cap(3).toDouble() / 100,0,1);

            QColor c;
            c.setHsvF(h, s, v);
            return c;
        }

    }
    else {
        QRegExp rx("#?[0-9A-Fa-f]+");
        if (rx.exactMatch(str))
            return QColor(str);
    }
    return QColor();
}



qreal ThemeFactory::colorRange(qreal value, qreal min, qreal max){

    if(value < min) value = min;
    if(value > max) value = max;

    return value;

}
