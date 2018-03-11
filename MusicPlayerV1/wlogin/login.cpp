#include "login.h"
#include "ui_login.h"

#include "execsql.h"

#include <QMessageBox>
#include <QHBoxLayout>
#include <QRegExp>
#include <QDebug>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    initWindow();

    m_register = new Register;

    connect(m_register, SIGNAL(signalShowLogin()),
            this,SLOT(slotShowLogin()));
}

Login::~Login()
{
    delete ui;
}

void Login::initWindow()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowFlag(Qt::WindowStaysOnTopHint);

    //暗注释
    ui->cb_id->setEditable(true);
    QLineEdit *lineEdit = ui->cb_id->lineEdit();
    lineEdit->setPlaceholderText(tr("手机号"));
    ui->le_pswd->setPlaceholderText(tr("密码"));

//    //密码框中的小键盘按钮
//    m_keyboardButton = new QPushButton();
//    m_keyboardButton->setObjectName("pButtonKeyboard");
//    m_keyboardButton->setFixedSize(QSize(16,16));
//    m_keyboardButton->setCursor(Qt::PointingHandCursor);//移动到这显示鼠标状态

//    QHBoxLayout *passwordEditLayout = new QHBoxLayout;
//    passwordEditLayout->addStretch();
//    passwordEditLayout->addWidget(m_keyboardButton);
//    passwordEditLayout->setSpacing(0);
//    passwordEditLayout->setContentsMargins(0, 0, 8, 0);

//    ui->le_pswd->setLayout(passwordEditLayout);
//    ui->le_pswd->setTextMargins(0, 0, m_keyboardButton->width() + 12, 0);
}

void Login::on_pb_enter_clicked()
{
    UserInfo info = ExecSQL::selectUserInfo(ui->cb_id->currentText());
    if(ui->cb_id->currentText() == NULL)          //未输入账号的情况
    {
        QMessageBox msgBox;
        msgBox.setText("请输入手机号或邮箱!!!");
        msgBox.exec();
    }else if (info.getID() != ui->cb_id->currentText()) //输入的账号数据库中没有
    {
        QRegExp number("^13[0-9]{1}[0-9]{8}|^15[0-3|5-9]{1}[0-9]{8}"
                     "|^18[0-9]{1}[0-9]{8}|^147{1}[0-9]{8}");

        QRegExp email("^[a-z|0-9]+([._\\-]*[a-z|0-9])*"
                      "@([a-z|0-9]+[-a-z0-9]*[a-z0-9]+.)(com|cn|net)+$");

        //读取字符串并与正则表达式比对
        if(number.exactMatch(ui->cb_id->currentText()) || email.exactMatch(ui->cb_id->currentText()))
        {
            //通过检测含有"@"的字符串来判断是否为邮箱
            if(ui->cb_id->currentText().contains("@",Qt::CaseSensitive))
            {
                QMessageBox msgBox;
                msgBox.setText("您输入的邮箱未注册，\n"
                               "请您转到注册界面去注册!!!");
                msgBox.exec();
            }else
            {
                QMessageBox msgBox;
                msgBox.setText("您输入的手机号未注册，\n"
                               "请您转到注册界面去注册!!!");
                msgBox.exec();
            }
        }else
        {
            if(ui->cb_id->currentText().contains("@",Qt::CaseSensitive))
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
    }else
    {
        if(info.getPswd() == ui->le_pswd->text()) //账号和密码均正确
        {
            this->hide();

            QMessageBox msgBox;
            msgBox.setText("登录成功！");
            msgBox.exec();
        }else if(ui->le_pswd->text() == NULL)     //未输入密码
        {
            QMessageBox msgBox;
            msgBox.setText("请输入密码！");
            msgBox.exec();
        }else                                     //密码错误
        {
            QMessageBox msgBox;
            msgBox.setText("您输入的密码错误!");
            msgBox.setInformativeText("请再次输入!");
            msgBox.setStandardButtons(QMessageBox::Retry | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Retry);
            int ret = msgBox.exec();

            switch(ret)
            {
                case QMessageBox::Retry:
                    ui->le_pswd->setFocus();
                    break;
                case QMessageBox::Cancel:
                    this->close();
                    break;
                default:
                    // should never be reached
                    break;
            }
        }
    }

    ui->cb_id->clear();
    ui->le_pswd->clear();
}

void Login::on_pb_register_clicked()
{
    ui->cb_id->clear();
    ui->le_pswd->clear();

    this->hide();
    m_register->show();
}

void Login::slotShowLogin()
{
    this->show();
}

void Login::on_pb_close_clicked()
{
    this->close();
}

void Login::on_pb_min_clicked()
{
    this->showMinimized();
}

void Login::mousePressEvent(QMouseEvent *ev)
{
    if(ev->buttons() == Qt::LeftButton)
    {
        m_widgetMove = ev->globalPos() - this->frameGeometry().topLeft();
        ev->accept();
    }
}

void Login::mouseMoveEvent(QMouseEvent *ev)
{
    if(ev->buttons() == Qt::LeftButton)
    {
        this->move(ev->globalPos() - m_widgetMove);
        ev->accept();
    }
}
