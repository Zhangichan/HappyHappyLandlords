#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QPaintEvent>
#include <QEvent>

namespace Ui {
class Interface;
}

//首页
class Interface : public QWidget
{
    Q_OBJECT
public:
    explicit Interface(QWidget *parent = 0);
    ~Interface();
private:
    void originWindow();                            //初始化窗体
    void paintEvent(QPaintEvent * event);           //绘图事件
    void originDanjiButton();                       //初始化 进入单击模式按钮
    void originLianjiButton();                      //初始化 进入联机模式按钮
    bool eventFilter(QObject * obj, QEvent * event);//事件过滤器
private:

    Ui::Interface *ui;
    //ui成员:
    QPushButton * danji;  //单机按钮
    QPushButton * lianji; //联机按钮
    //非ui成员:
    bool canDanji;        //是否可以点击单机按钮(为了防止多次点击)
    bool canLianji;       //是否可以点击联机按钮(为了防止多次点击)
};

#endif // INTERFACE_H















//namespace Ui {
//class MainWindow;
//}

//class MainWindow : public QMainWindow
//{
//    Q_OBJECT

//public:
//    explicit MainWindow(QWidget *parent = 0);
//    ~MainWindow();

//private:
//    Ui::MainWindow *ui;
//};




