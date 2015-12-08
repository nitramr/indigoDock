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
    QDockWidget* m_dockleft;
    QDockWidget* m_dockright;
    QGridLayout* m_mainLayout_r;
    QGridLayout* m_mainLayout_l;

    MainWindow(QWidget* parent = 0);
    ~MainWindow();

   /* static MainWindow* getInstance()
      {
        if(!instance)
        {
          instance = new MainWindow();
        }
        return instance;
      }
*/

protected:
   // MainWindow(QWidget* = NULL);
signals:  

private:
    Ui::MainWindow *ui;
    bool invert;
    const QString iconPath = "icons/";
    QIcon iconInvert(const QIcon &icon, bool invert = false);
    //static MainWindow* instance;

    void textPanel(IndigoPanel *parent);
};


#endif // MAINWINDOW_H
