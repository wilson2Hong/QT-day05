#include "widget.h"
#include "ui_widget.h"
#include<QThread>
#include<Qdebug>
#include<QTimer>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    myTimer = new QTimer(this);
    //只要启动定时器，自动触发timeout()
    connect(myTimer,&QTimer::timeout,this,&Widget::dealTimeout);

    //分配空间
    thread = new MyThread(this);

    connect(thread,&MyThread::isDone,this,&Widget::dealDone);

    //当按右上角X时,窗口触发destroyed
    connect(this,&Widget::destroyed,this,&Widget::stopThread);
}

void Widget::stopThread()
{
    //停止线程
    thread->quit();

    //等待线程处理完手头工作
    thread->wait();

}

void Widget::dealDone()
{
      qDebug()<<"it is over";
      myTimer->stop();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::dealTimeout()
{
     static int i=0;
     i++;
     ui->lcdNumber->display(i);
}
void Widget::on_pushButton_clicked()
{
    if(myTimer->isActive() == false)
    {
        myTimer->start(100);
    }
//    //非常复杂的数据处理，耗时较长
//    QThread::sleep(5);

//    //处理完数据后，关闭定时器
//    //myTimer->stop();
//    qDebug()<<"over";



    //启动线程，处理数据
    thread->start();
}
