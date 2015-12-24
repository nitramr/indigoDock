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

protected:

private:
    QLabel * m_lblTitle;
    QToolButton * m_btnClose;
    QToolButton * m_btnFloat;

signals:

public slots:
};

/**********************************************************/

class IndigoPanel : public QFrame
{
    Q_OBJECT

public:
    enum IndigoState{
        HiddenDocked,
        HiddenFloating,
        Floating,
        Docked,
        None
    };

    enum IndigoExpander{
        Normal,
        Advanced,
        Collapsed
    };

    IndigoPanel(QString name, QWidget* parent = 0);   
    void addWidgetNormal(QWidget *content);
    void addWidgetExtend(QWidget *content);

    void setCaption(const QString title);

    QIcon Icon();
    void setIcon(QIcon icon);

    int Index();
    void setIndex(int index);

    IndigoState dockState();
    void setDockState(IndigoState state);

    IndigoExpander expanderState();
    void setExpanderState(IndigoExpander expander);


protected:   
    bool eventFilter(QObject *o, QEvent *e);

private:   
    QWidget *m_normalContainer;
    QWidget *m_extendedContainer;
    QVBoxLayout *m_normalArea;
    QVBoxLayout *m_extendedArea;
    QVBoxLayout *m_mainLayout;
    IndigoPanelHandle * m_handle;
    QPoint oldPos;  
    int relative_x;
    int relative_y;
    QIcon m_icon;    
    int m_index; 
    IndigoState m_state;
    IndigoExpander m_expander;
    QWidget *m_Parent;

signals:
    void mouseReleased();
    void mouseMove(int height);
    void isFloating(int index);
    void panelClosed(int index);
    void panelShown(int index);

public slots:
    void show();
    void hide();
    void expander();
};

#endif // INDIGOPANEL_H
