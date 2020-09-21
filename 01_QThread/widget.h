#ifndef WIDGET_H
#define WIDGET_H
#include<QTimer>
#include"mythread.h"
#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

     void dealTimeout();
     void dealDone();//线程槽结束函数
     void stopThread();//停止线程槽函数

private slots:
     void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    QTimer *myTimer;//声明变量
    MyThread *thread;//线程对象
};

#endif // WIDGET_H


