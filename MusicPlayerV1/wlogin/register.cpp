#include "register.h"
#include "ui_register.h"

#include "execsql.h"

#include <QMessageBox>
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

    //暗注释
    ui->le_id->setPlaceholderText(tr("请输入手机号"));
    ui->le_pswd->setPlaceholderText(tr("设置密码，不少于6位"));
}

void Register::on_pb_register_clicked()
{
    RegisterInfo info = *ExecSQL::selectRegisterInfo(ui->le_id->text());
    if(ui->le_id->text() == NULL)
    {
        QMessageBox msgBox;
        msgBox.setText("请输入手机号！");
        msgBox.exec();
    }else if(info.getID() == ui->le_id->text())
    {
        QMessageBox msgBox;
        msgBox.setText("您输入的手机号已注册！");
        msgBox.exec();
    }else
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

void Register::mousePressEvent(QMouseEvent *ev)
{
    if(ev->buttons() == Qt::LeftButton)
    {
        m_widgetMove = ev->globalPos() - this->frameGeometry().topLeft();
        ev->accept();
    }
}

void Register::mouseMoveEvent(QMouseEvent *ev)
{
    if(ev->buttons() == Qt::LeftButton)
    {
        this->move(ev->globalPos() - m_widgetMove);
        ev->accept();
    }
}
