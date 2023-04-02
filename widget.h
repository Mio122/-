
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QChartView>
#include <QValueAxis>
#include <QLineSeries>
#include <QString>

QT_CHARTS_USE_NAMESPACE


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget

{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


private:

    QTimer * timer;     //定时器
    QChart* cr;         //图表
    QValueAxis *axisX, * axisY;     //X， Y 轴
    QLineSeries * Lse;      //曲线对象

    const int AXIS_MAX_X = 10, AXIS_MAX_Y = 10; //最大范围

    int pointcnt = 0;   //记录点数

    void Init_Graph();

private slots:
    void slotTimeout();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
