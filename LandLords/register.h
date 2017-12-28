#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
//#include <QRadioButton>
#include <QLineEdit>
#include <QPaintEvent>
//#include <QCloseEvent>

namespace Ui {
class Register;
}

class Register:public QDialog
{
    Q_OBJECT
public:
    explicit Register(QWidget *parent = 0);
    ~Register();

protected:
    void paintEvent(QPaintEvent *event); //注册界面背景
    void registInterface();                    //注册界面按钮
//    bool validData()const;               //判断帐号密码输入合法性
    void connectFun();                     //连接信号与槽函数

private slots:
    void accountEditingFinishedslot();//验证手机号的正确与否
    void passwordeditingFinishedslot();//密码正确与否
    void repeateditingFinishedslot();//再次输入密码正确与否
    void backBtnslot(); //返回事件处理

private:
    Ui::Register *ui;
    QLabel *label;                         //“填写信息”标签
    QLabel *accountLabel;                  //账号标签
    QLineEdit *accountLineEdit;            //账号输入框
    QLabel *aLabel1;                       //账号的“对错”标签
    QLabel *passwordLabel;                 //密码标签
    QLineEdit *passwordLineEdit;           //密码输入框
    QLabel *aLabel2;                       //密码的“对错”标签
    QLabel *repeatLabel;                   //确认密码标签
    QLineEdit *repeatLinEdit;              //确认密码输入框
    QLabel *aLabel3;                       //确认密码的“对错”标签

    QPushButton *registerButton;           //注册按钮
    QPushButton *backButton;               //返回按钮

    bool _canRegist;                       //是否可以点击 注册按钮
    bool _canBack;                         //是否可以点击 返回按钮
};

#endif // REGISTER_H
