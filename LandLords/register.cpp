#include "register.h"
#include "ui_register.h"
#include <QPainter>
#include <QPixmap>
#include <QString>
#include <QRegExp>
#include "login.h"

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    this->setFixedSize(800,600);
    registInterface();
    connectFun();
}
Register::~Register()
{
    delete ui;
}
//注册界面背景
void Register::paintEvent(QPaintEvent *event)
{
    static QPixmap backpic(":/res/register.jpg");
    QPainter painter(this);
    painter.drawPixmap(this->rect(),backpic);
}
//注册界面的标签
void Register::registInterface()
{
    QFont font;
    font.setFamily("方正喵呜体");
    font.setPointSize(26);
    font.setBold(true);
    QBrush brush(QColor(255, 255, 255, 255));
    brush.setStyle(Qt::SolidPattern);
    QBrush brush1(QColor(231, 231, 231, 255));
    brush1.setStyle(Qt::SolidPattern);
    //填写信息标签
    label = new QLabel(this);
    label->setGeometry(QRect(200,40,400,60));
    label->setText(">填写信息<");
    label->setAlignment(Qt::AlignCenter);
    QPalette palette1;
    palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
    palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
    palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
    label->setPalette(palette1);
    label->setFont(font);
    label->setFrameShape(QFrame::NoFrame);
    label->setFrameShadow(QFrame::Plain);

    //账号标签
    accountLabel = new QLabel(this);
    accountLabel->setGeometry(QRect(50, 130, 160, 40));
    accountLabel->setText("手机号：");
    QPalette palette2;
    palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
    palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
    palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
    accountLabel->setPalette(palette2);
    accountLabel->setFont(font);
    //账号输入框
    accountLineEdit = new QLineEdit(this);
    accountLineEdit->setGeometry(QRect(220, 130, 250, 40));
    accountLineEdit->setMaxLength(11);
    accountLineEdit->setFont(font);
    QPalette palette3;
    accountLineEdit->setPalette(palette3);
    //账号的“对错”标签
    aLabel1 = new QLabel(this);
    aLabel1->setGeometry(QRect(500, 130, 250, 40));

    //密码标签
    passwordLabel = new QLabel(this);
    passwordLabel->setGeometry(QRect(50, 200, 160, 40));
    passwordLabel->setText("密  码：");
    QPalette palette4;
    palette4.setBrush(QPalette::Active, QPalette::WindowText, brush);
    palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
    palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
    passwordLabel->setPalette(palette4);
    passwordLabel->setFont(font);
    //密码输入框
    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setGeometry(QRect(220, 200, 250, 40));
    passwordLineEdit->setMaxLength(6);
    passwordLineEdit->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText|Qt::ImhSensitiveData);
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    passwordLineEdit->setFont(font);
    //密码的“对错”标签
    aLabel2 = new QLabel(this);
    aLabel2->setGeometry(QRect(500, 200, 250, 40));

    //确认密码标签
    repeatLabel = new QLabel(this);
    repeatLabel->setGeometry(QRect(50, 270, 160, 40));
    repeatLabel->setText("重复密码：");
    QPalette palette5;
    palette5.setBrush(QPalette::Active, QPalette::WindowText, brush);
    palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
    palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
    repeatLabel->setPalette(palette5);
    repeatLabel->setFont(font);
    //确认密码输入框
    repeatLinEdit = new QLineEdit(this);
    repeatLinEdit->setGeometry(QRect(220, 270, 250, 40));
    repeatLinEdit->setEchoMode(QLineEdit::Password);
    repeatLinEdit->setMaxLength(6);
    repeatLinEdit->setFont(font);
    //确认密码的“对错”标签
    aLabel3 = new QLabel(this);
    aLabel3->setGeometry(QRect(500, 270, 250, 40));

    _canRegist=true;//一开始可以点击注册按钮
    _canBack=true;  //一开始可以点击返回按钮
    QPalette palette6;
    palette6.setBrush(QPalette::Active, QPalette::WindowText, brush);
    palette6.setBrush(QPalette::Active, QPalette::Text, brush);
    palette6.setBrush(QPalette::Active, QPalette::ButtonText, brush);
    palette6.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
    palette6.setBrush(QPalette::Inactive, QPalette::Text, brush);
    palette6.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
    palette6.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
    palette6.setBrush(QPalette::Disabled, QPalette::Text, brush1);
    palette6.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
    QFont font1;
    font1.setFamily("方正喵呜体");
    font1.setBold(true);
    font1.setPointSize(16);
    //注册按钮
    registerButton = new QPushButton(this);
    registerButton->setGeometry(QRect(50, 470, 100, 40));
    registerButton->setPalette(palette6);
    registerButton->setFont(font1);
    registerButton->setContextMenuPolicy(Qt::DefaultContextMenu);
    registerButton->setCheckable(false);
    registerButton->setAutoDefault(false);
    registerButton->setFlat(false);
    registerButton->setText("注册");
    registerButton->setStyleSheet("color:#2b2b2b");
    registerButton->setCursor(Qt::PointingHandCursor);
    //返回按钮
    backButton=new QPushButton(this);
    backButton->setGeometry(QRect(250,470,100,40));
    backButton->setPalette(palette6);
    backButton->setFont(font1);
    backButton->setContextMenuPolicy(Qt::DefaultContextMenu);
    backButton->setCheckable(false);
    backButton->setAutoDefault(false);
    backButton->setFlat(false);
    backButton->setText("返回");
    backButton->setStyleSheet("color:#2b2b2b");
    backButton->setCursor(Qt::PointingHandCursor);
}
//判断帐号密码输入合法性
//bool Register::validData()const
//{
//    QString user = accountLineEdit->text();
//    QString pwd = passwordLineEdit->text();
//    QString rpwd = repeatLinEdit->text();
//    QRegExp re1("[0-9]{11}");
//    QRegExp re2("[0-9]{6}");
//    if(re1.indexIn(user)!=0)
//        return false;
//    if(re2.indexIn(pwd)!=0)
//        return false;
//    if(re2.indexIn(rpwd)!=0)
//        return false;
//    return pwd==rpwd;
//}
//连接信号与槽函数
void Register::connectFun()
{
    //连接账号对错的信号与槽
    connect(accountLineEdit,SIGNAL(editingFinished()),this,SLOT(accountEditingFinishedslot()));
    //连接密码对错的信号与槽
    connect(passwordLineEdit,SIGNAL(editingFinished()),this,SLOT(passwordeditingFinishedslot()));
    //连接确认密码对错的信号与槽
    connect(repeatLinEdit,SIGNAL(editingFinished()),this,SLOT(repeateditingFinishedslot()));
    //连接返回登录界面的信号与槽
    connect(backButton,SIGNAL(clicked()),this,SLOT(backBtnslot()));
}

//验证手机号的正确与否
void Register::accountEditingFinishedslot()
{
    QPixmap pics1(":/res/available.png");
    QPixmap pics2(":/res/wrong.png");
    if(QRegExp("[0-9]{11}").indexIn(accountLineEdit->text())==0)
       aLabel1->setPixmap(pics1);
    else
       aLabel1->setPixmap(pics2);
}

//密码正确与否
void Register::passwordeditingFinishedslot()
{
    QPixmap pics1(":/res/available.png");
    QPixmap pics2(":/res/wrong.png");
    if(QRegExp("[0-9]{6}").indexIn(passwordLineEdit->text())==0)
        aLabel2->setPixmap(pics1);
    else
        aLabel2->setPixmap(pics2);
}

//再次输入密码正确与否
void Register::repeateditingFinishedslot()
{
    QPixmap pics1(":/res/available.png");
    QPixmap pics2(":/res/wrong.png");
    if(QRegExp("[0-9]{6}").indexIn(repeatLinEdit->text())==0 && passwordLineEdit->text()==repeatLinEdit->text())
        aLabel3->setPixmap(pics1);
    else
        aLabel3->setPixmap(pics2);
}
//返回到登录界面
void Register::backBtnslot()
{
    if(_canBack)
    {
        _canBack=false;
        close();
        Login *l=new Login;
        l->show();
    }
}
