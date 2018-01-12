#include "interface.h"
#include "ui_interface.h"
#include "login.h"
#include "maininterface.h"
#include <QPixmap>
#include <QPainter>
#include <QFont>

Interface::Interface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Interface)
{
    originWindow();         //初始化窗体
    originDanjiButton();    //初始化单击按钮
    originLianjiButton();   //初始化联机按钮
    ui->setupUi(this);
}

Interface::~Interface()
{
    delete ui;
}

//初始化窗体
void Interface::originWindow()
{
    setFixedSize(800,600);//设置窗口大小
}

//绘图事件(设置背景)
void Interface::paintEvent(QPaintEvent *)
{
    static QPixmap backpic("://res/img1.png");
    QPainter painter(this);
    painter.drawPixmap(this->rect(),backpic);
}

//初始化单机按钮
void Interface::originDanjiButton()
{
    danji=new QPushButton(this);//新建一个按钮
//    danji->setGeometry(200,180,400,70);
    danji->setGeometry(500,180,200,70);
    QFont font;
    font.setPointSize(40);
    font.setFamily("Arial Rounded MT Bold");
    font.setBold(true);
    danji->setFont(font);
    danji->setStyleSheet("color:#2b2b2b");
    danji->setCursor(Qt::PointingHandCursor);
    danji->setText("单机模式");
    danji->installEventFilter(this);//设置监听
    canDanji=true;                  //刚开始可以点击 单击模式按钮
}

//初始化联机按钮
void Interface::originLianjiButton()
{
    lianji=new QPushButton(this);
    lianji->setGeometry(500,350,200,70);
    QFont font;
    font.setPointSize(25);
    font.setFamily("Arial Rounded MT Bold");
    font.setBold(true);
    lianji->setFont(font);
    lianji->setStyleSheet("color:#2b2b2b");
    lianji->setCursor(Qt::PointingHandCursor);
    lianji->setText("在线模式");
    lianji->installEventFilter(this);//设置监听
    canLianji=true;                  //刚开始可以点击 联机模式按钮
}

//事件过滤器
/*
 * 注: 设置按钮可用不可用 是为了 防止连续快速多次点击 造成的多余的事件
 * if 按下 进入单机模式 且 该按钮可用
 * {
 *    设置该按钮不可用
 *    关闭该界面
 *    创建并打开单机界面
 * }
 * if 按下 进入联机模式 且 该按钮可用
 * {
 *    设置该按钮不可用
 *    关闭该界面
 *    创建并打开联机界面
 * }
*/
bool Interface::eventFilter(QObject *obj, QEvent *event)
{
    if(obj==danji && event->type()==QEvent::MouseButtonPress && canDanji)
    {
        canDanji=false;
        close();
        MainInterface * newPage=new MainInterface;
        newPage->setWindowTitle("单机");
        newPage->show();
        return true;
    }
    if(obj==lianji && event->type()==QEvent::MouseButtonPress && canLianji)
    {
        canLianji=false;
        close();
        Login * newPage=new Login;
        newPage->setWindowTitle("登陆");
        newPage->show();
        return true;
    }
    return QWidget::eventFilter(obj,event);
}
