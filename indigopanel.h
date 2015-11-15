#ifndef INDIGOPANEL_H
#define INDIGOPANEL_H

#include <QWidget>
#include <QtGui>
#include <QFrame>
#include <QLayout>
#include <QLabel>
#include <QPushButton>

class IndigoPanelHandle : public QWidget
{
        Q_OBJECT
public:
    IndigoPanelHandle(QWidget* parent = 0);
    void setTitle(const QString &title);
    void setBackgroundColor(const QColor &bgColor);

protected:

private:
    QLabel * m_lblTitle;
    QPushButton * m_btnClose;
    QPalette palette;

signals:

public slots:
};

/**********************************************************/

class IndigoPanel : public QFrame
{
    Q_OBJECT

public:
    IndigoPanel(QWidget* parent = 0);
    IndigoPanelHandle * m_handle;
    void setBackgroundColor(const QColor &bgColor);
    void addWidget(QWidget *content);
    void setLastParent(QWidget * dropzone);
    QWidget * lastParent();

protected:   
    bool eventFilter(QObject *o, QEvent *e);

private:
    QPalette palette;
    QVBoxLayout *m_contentArea;
    QPoint oldPos;
    int relative_x;
    int relative_y;
    QWidget *m_lastParentWidget;
    QWidget *m_mainWindow;

signals:
    void mouseReleased();
    void mouseMove();

public slots:
    void hide();
};

#endif // INDIGOPANEL_H
