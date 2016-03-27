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
    QString Caption();
    void setCaption(QString title, int fontSize);
    void setIcon(QIcon icon, int iconSize);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QIcon ico_icon;
    int int_iconSize;
    QString str_title;
    int int_fontSize;
    QToolButton * wdg_btnClose;
    QToolButton * wdg_btnFloat;


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

    IndigoPanelHandle * wdg_handle;

    QString Caption();
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
    QWidget *wdg_normalContainer;
    QWidget *wdg_extendedContainer;
    QVBoxLayout *lyt_normalArea;
    QVBoxLayout *lyt_extendedArea;
    QVBoxLayout *lyt_main;

    QPoint pnt_relativeOffset;
    QIcon ico_icon;    
    int int_index; 
    IndigoState m_state;
    IndigoExpander m_expander;
    QWidget *wdg_Parent;
    QSpacerItem *wdg_spacer;

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
