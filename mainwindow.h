#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include "indigodock.h"
#include "indigopanel.h"
#include "indigohub.h"

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

    IndigoHub * indigoHub;
    IndigoDock *indigoDock_r;
    IndigoDock *indigoDock_l;
    QDockWidget* m_dockholder_l;
    QDockWidget* m_dockholder_r;
    QGridLayout* m_mainLayout_r;
    QGridLayout* m_mainLayout_l;
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
