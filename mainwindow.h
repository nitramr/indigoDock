#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include "indigodock.h"
#include "indigopanel.h"
#include "indigohub.h"
#include "textboxsimulator.h"
#include "indigoiconwidget.h"

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

   // IndigoHub * wdg_indigoHub;
    IndigoDock *wdg_indigoDock_r;
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


};


#endif // MAINWINDOW_H
