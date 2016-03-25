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
    void setTitle(QString title, int fontSize);
    void setIcon(QIcon icon, int iconSize);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QIcon m_icon;
    int m_iconSize;
    QString m_title;
    int m_fontSize;
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
    void addWidgetNormal(QLayout *content);
    void addWidgetExtend(QWidget *content);
    void addWidgetExtend(QLayout *content);

    IndigoPanelHandle * m_handle;

    void setCaption(QString title = "", int fontSize = 10);

    QIcon Icon();
    void setIcon(QIcon icon, int iconSize = 22);

    int Index();
    void setIndex(int index);

    IndigoState dockState();
    void setDockState(IndigoState state);

    IndigoExpander expanderState();
    void setExpanderState(IndigoExpander expander);


protected:   
    bool eventFilter(QObject *object, QEvent *e);

private:   
    QWidget *m_normalContainer;
    QWidget *m_extendedContainer;
    QVBoxLayout *m_normalArea;
    QVBoxLayout *m_extendedArea;
    QVBoxLayout *m_mainLayout;

    QPoint relativeOffset;
    QIcon m_icon;    
    int m_index; 
    IndigoState m_state;
    IndigoExpander m_expander;
    QWidget *m_Parent;
    QSpacerItem *m_spacer;

signals:
    void mouseReleased();
    void mouseMove();
    void isFloating(int index);
    void panelClosed(int index);
    void panelShown(int index);

public slots:
    void show();
    void hide();
    void expander();
};

#endif // INDIGOPANEL_H
