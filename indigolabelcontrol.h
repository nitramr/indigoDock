#ifndef INDIGOLABELCONTROL_H
#define INDIGOLABELCONTROL_H

#include <QWidget>
#include <QtGui>
#include <QLayout>
#include <QLabel>

class IndigoLabelControl : public QWidget
{
       Q_OBJECT
public:
    IndigoLabelControl(QWidget *parent = 0);

    void setWidget(QWidget *widget, int width = -1);
    QWidget *Widget();

    void setLabel(QIcon icon, int iconSize = 22, Qt::Alignment alignment = Qt::AlignRight);
    void setLabel(QString string, int width = 22, Qt::Alignment alignment = Qt::AlignRight);
    void setLabel(QWidget *widget, int width = 22, Qt::Alignment alignment = Qt::AlignRight);
    QIcon Icon();
    QWidget *Label();


private:
    QIcon ico_icon;
    QWidget *wdg_label;
    QWidget *wdg_widget;
    QHBoxLayout *lyt_widgetLayout;
    QHBoxLayout *lyt_labelLayout;

    int int_iconSize;

signals:

public slots:
};

#endif // INDIGOLABELCONTROL_H
