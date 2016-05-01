/*******************************************************
 *
 * Copyright (C) 2016  a.l.e
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



#include "indigomenubar.h"
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTextCodec>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QGraphicsColorizeEffect>
#include "configmanager.h"


IndigoMenuBar::IndigoMenuBar()
{
    /*
    QMenu *menuWindow = this->addMenu(tr("&Window"));
    QAction *addNew = new QAction(menuWindow);
    addNew->setText(tr("Add new"));
    menuWindow->addAction(addNew);
    QAction *quit = new QAction(menuWindow);
    quit->setText(tr("&Quit"));
    menuWindow->addAction(quit);
    connect(quit, SIGNAL(triggered()), this, SLOT(close()));
    */
    // connect(addNew, SIGNAL(triggered()), this, SLOT(onAddNew()));

    loadSettings();


}



bool IndigoMenuBar::loadSettings()
{

    iconPath = ConfigManager().getIconPath();


    QFile loadFile(QStringLiteral(":data/navigation.json"));

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open menubarfile.");
        return false;
    }

    QByteArray data = loadFile.readAll();

    //qDebug() << "data" << data << endl;

    QJsonParseError jerror;
    QJsonDocument loadDoc(QJsonDocument::fromJson(data, &jerror));
    if(jerror.error != QJsonParseError::NoError) {
        qWarning("Error while parsing json.");
        qDebug() << jerror.errorString() << endl;
        qDebug() << "error at" << QTextCodec::codecForMib(106)->toUnicode(data).mid(jerror.offset - 1, 20) << endl;
        return false;
    }
    read(loadDoc.object());
    return true;
}



void IndigoMenuBar::read(const QJsonObject &json)
{
    //qDebug() << "json" << json << endl;
   // qDebug() << "name" << json["name"].toString();
    // TODO: check that menubar exists
    this->fill(json["menubar"].toArray());
}



void IndigoMenuBar::fill(const QJsonArray menuMainEntries)
{
    for (int i = 0; i < menuMainEntries.size(); i++) {
        QJsonObject child = menuMainEntries[i].toObject();
        if (child.contains("children")) {
            this->addMenu(this->getMenuItemFromJson(child));
        } else {
            this->addAction(this->getActionFromJson(child, this));
        }
    }
    /*
    QMenu *menuWindow = this->addMenu(tr("&Window"));
    QAction *addNew = new QAction(menuWindow);
    addNew->setText(tr("Add new"));
    menuWindow->addAction(addNew);
    QAction *quit = new QAction(menuWindow);
    quit->setText(tr("&Quit"));
    menuWindow->addAction(quit);
    connect(quit, SIGNAL(triggered()), this, SLOT(close()));
    */
}



QMenu* IndigoMenuBar::getMenuItemFromJson(const QJsonObject json)
{
    // TODO: make sure that label exists
    QMenu *menuItem = new QMenu(json["label"].toString());
    QJsonArray children = json["children"].toArray();
    for (int i = 0; i < children.size(); i++) {
        QJsonObject child = children[i].toObject();
        if (child.contains("children")) {
            menuItem->addMenu(this->getMenuItemFromJson(child));
        } else {
            menuItem->addAction(this->getActionFromJson(child, menuItem));
        }
    }
    return menuItem;
}



QAction* IndigoMenuBar::getActionFromJson(const QJsonObject json, QObject* parent)
{
    // TODO: make sure that label exists
    if (json.contains("type")) {
        QString type = json["type"].toString();
        if (type == "divider") {
            return qobject_cast<QMenu*>(parent)->addSeparator();
        }
    }
    QAction *action = new QAction(parent);

    QIcon icon = QIcon(iconPath + json["icon"].toString());

    //qDebug() << "action" << json["label"].toString() <<  iconPath + json["icon"].toString() << endl;
    action->setText(json["label"].toString());
    action->setIcon(icon);
    return action;
}
