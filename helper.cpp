/*******************************************************
 *
 * Copyright (C) 2016  Martin Reininger
 *
 * This file is part of IndigoDock.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 *******************************************************/

#include "helper.h"

Helper::Helper(){}


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
