#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include "indigopanel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:

    enum Theme{
        Dark,
        Light
    };

    QDockWidget* m_dockleft;
    QDockWidget* m_dockright;
    QGridLayout* m_mainLayout_r;
    void loadTheme();
    void saveTheme(Theme theme);

    MainWindow(QWidget* parent = 0);
    ~MainWindow();


signals:  

public slots:
   void loadLightTheme();
   void loadDarkTheme();

private:
    Ui::MainWindow *ui;
    QString str_iconPath;
    void textPanel(IndigoPanel *parent);
};


#endif // MAINWINDOW_H
