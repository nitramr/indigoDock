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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QListWidget>

#include "indigodock/indigodock.h"
#include "indigodock/indigopanel.h"
#include "indigodock/indigodockmanager.h"

#include "uiwidgets/iconwidget.h"

#include "textboxsimulator.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    QString str_iconPath;
    void textPanel(IndigoPanel *parent);

public:

    enum Theme{
        Dark,
        Light
    };

    IndigoDockManager * wdg_indigoDockManager;
    IndigoDock *wdg_indigoDock_r;
    IndigoDock *wdg_indigoDock_l;
    QWidget *wdg_document;
    TextBoxSimulator *wdg_textbox;

    void loadTheme();
    void saveTheme(Theme theme);

    MainWindow(QWidget* parent = 0);
    ~MainWindow();


signals:  

public slots:
    void loadLightTheme();
    void loadDarkTheme();
    void scrollToGeometry();
    void scrollToContent();
    void scrollToPage();
    void saveWorkspace();
    void loadWorkspace();


};


#endif // MAINWINDOW_H
