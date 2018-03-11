#include "register.h"
#include "ui_register.h"

#include "execsql.h"

#include <QMessageBox>
#include <QRegExp>
#include <QDebug>

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);

    initWindow();
}

Register::~Register()
{
    delete ui;
}

void Register::initWindow()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowFlag(Qt::WindowStaysOnTopHint);

    //暗注释
    ui->le_id->setPlaceholderText(tr("请输入手机号或邮箱"));
    ui->le_pswd->setPlaceholderText(tr("设置密码，不少于6位"));
}

void Register::on_pb_register_clicked()
{
    RegisterInfo info = *ExecSQL::selectRegisterInfo(ui->le_id->text());
    if(ui->le_id->text() == NULL)
    {
        QMessageBox msgBox;
        msgBox.setText("请输入手机号或邮箱！");
        msgBox.exec();
    }else if(info.getID() == ui->le_id->text())
    {
        //通过判断字符串中是否有"@"来判定是否为邮箱
        if(ui->le_id->text().contains("@",Qt::CaseSensitive))
        {
            QMessageBox msgBox;
            msgBox.setText("您输入的邮箱已注册！");
            msgBox.exec();
        }else
        {
            QMessageBox msgBox;
            msgBox.setText("您输入的手机号已注册！");
            msgBox.exec();
        }
    }else
    {
        QRegExp number("^13[0-9]{1}[0-9]{8}|^15[0-3|5-9]{1}[0-9]{8}"
                     "|^18[0-9]{1}[0-9]{8}|^147{1}[0-9]{8}");

        QRegExp email("^[a-z|0-9]+([._\\-]*[a-z|0-9])*"
                      "@([a-z|0-9]+[-a-z0-9]*[a-z0-9]+.)(com|cn|net)+$");

        //读取字符串并与正则表达式比对
        if(number.exactMatch(ui->le_id->text()) || email.exactMatch(ui->le_id->text()))
        {
            if(ui->le_pswd->text() == NULL)
            {
                QMessageBox msgBox;
                msgBox.setText("请输入密码！");
                msgBox.exec();
            }else
            {
                if(ui->le_pswd->text().length() < 6)
                {
                    QMessageBox msgBox;
                    msgBox.setText("请输入不少于6位数密码！");
                    msgBox.exec();
                }else
                {
                    ExecSQL::insertRegisterInfo(ui->le_id->text(),ui->le_pswd->text());

                    QMessageBox msgBox;
                    msgBox.setText("注册成功！");
                    msgBox.exec();
                }
            }
        }else
        {
            if(ui->le_id->text().contains("@",Qt::CaseSensitive))
            {
                QMessageBox msgBox;
                msgBox.setText("您输入的邮箱有误！");
                msgBox.exec();
            }else
            {
                QMessageBox msgBox;
                msgBox.setText("您输入的手机号有误！");
                msgBox.exec();
            }
        }
    }
}

void Register::on_pb_close_clicked()
{
    this->close();

    ui->le_id->clear();
    ui->le_pswd->clear();
}

void Register::on_pb_return_clicked()
{
    this->close();
    emit signalShowLogin();

    ui->le_id->clear();
    ui->le_pswd->clear();
}

//当按下鼠标左键时，获取主窗体左上角的位置
void Register::mousePressEvent(QMouseEvent *ev)
{
    if(ev->buttons() == Qt::LeftButton)
    {
        m_widgetMove = ev->globalPos() - this->frameGeometry().topLeft();
        ev->accept();
    }
}
//当按下鼠标左键时，移动窗体
void Register::mouseMoveEvent(QMouseEvent *ev)
{
    if(ev->buttons() == Qt::LeftButton)
    {
        this->move(ev->globalPos() - m_widgetMove);
        ev->accept();
    }
}
