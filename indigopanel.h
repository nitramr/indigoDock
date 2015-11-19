#ifndef INDIGOPANEL_H
#define INDIGOPANEL_H

#include <QWidget>
#include <QtGui>
#include <QFrame>
#include <QLayout>
#include <QLabel>
#include <QToolButton>

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
    QToolButton * m_btnClose;
    QToolButton * m_btnFloat;
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


    void setBackgroundColor(const QColor &bgColor);
    void setCaption(const QString &title);
    void setIcon(QIcon icon);
    QIcon Icon();
    void addWidget(QWidget *content);
    void setLastParent(QWidget * dropzone);
    QWidget * lastParent();

protected:   
    bool eventFilter(QObject *o, QEvent *e);

private:
    QPalette palette;
    QVBoxLayout *m_contentArea;
    IndigoPanelHandle * m_handle;
    QPoint oldPos;
    int relative_x;
    int relative_y;
    QWidget *m_lastParentWidget;
    QWidget *m_mainWindow;
    QIcon m_icon;
signals:
    void mouseReleased();
    void mouseMove();

public slots:
    void hide();
    void dock();
};

#endif // INDIGOPANEL_H
