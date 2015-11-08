#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QListWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:  
    QDockWidget* dockleft;
    QDockWidget* dockright;
    QGridLayout* mainLayout;

    MainWindow(QWidget* parent = 0);
    ~MainWindow();

protected:

signals:  

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
