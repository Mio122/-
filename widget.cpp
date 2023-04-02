
#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    Init_Graph();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::Init_Graph()
{
    ui->start->setText("启动定时器");
    ui->cancal->setText("清空定时器");


    timer = new QTimer(this);
    timer->setSingleShot(false);    //设置不是触发一次触发器
    connect(timer, &QTimer::timeout, this, &Widget::slotTimeout);       //signals timeout 超时的时候发送

    connect(ui->cancal, &QPushButton::clicked, [=]()
            {
                Lse->clear();
                cr->axisX()->setMin(0);
                cr->axisX()->setMax(AXIS_MAX_X);
                pointcnt = 0;
            });

    connect(ui->start, &QPushButton::clicked, [=]()
            {
                if(timer->isActive())
                {
                    timer->stop();
                    ui->start->setText("启动定时器");

                }
                else
                {
                    pointcnt = 0;
                    timer->start(200);          //200Ms执行一次
                    ui->start->setText("停止定时器");
                }
            });


    //
    // 创建横纵坐标轴并设置显示范围
    //

    axisX = new QValueAxis();
    axisY = new QValueAxis();
    axisX->setTitleText("X-Label");
    axisY->setTitleText("Y-Label");
    axisX->setMin(0);      //设置X轴的最大值为0
    //    axisY->setMax(0);
    axisY->setMax(0);
    axisX->setMax(AXIS_MAX_X);
    axisY->setMax(AXIS_MAX_Y);

    Lse = new QLineSeries();
    Lse->setPointsVisible(true);        //设置可见且可绘制
    Lse->setName("随机曲线");

    cr = new QChart();
    cr->addAxis(axisY, Qt::AlignLeft);      //将Y轴添加到图表上
    cr->addAxis(axisX, Qt::AlignBottom);    //将X轴添加到图表
    cr->addSeries(Lse);                     //添加曲线到图表
    cr->setAnimationOptions(QChart::SeriesAnimations);  //动画：能使曲线绘制显示的更平滑，过渡效果更好看

    Lse->attachAxis(axisX);               // 曲线对象关联上X轴，此步骤必须在m_chart->addSeries之后
    Lse->attachAxis(axisY);

    ui->widget->setChart(cr);             //将图表和QchartView绑定
    ui->widget->setRenderHint(QPainter::Antialiasing);
}

void Widget::slotTimeout()
{

    if(pointcnt > AXIS_MAX_X)
    {
        Lse->remove(0);     //去掉这个 index = 0 的这个点
        cr->axisX()->setMin(pointcnt - AXIS_MAX_X);
        cr->axisX()->setMax(pointcnt);  //更新X轴范围
    }

    Lse->append(QPointF(pointcnt, rand() % AXIS_MAX_Y));     // 更新显示（随机生成10以内的一个数）
    ++pointcnt;
}


