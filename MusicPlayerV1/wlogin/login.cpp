#include "login.h"
#include "ui_login.h"

#include "execsql.h"

#include <QMessageBox>
#include <QHBoxLayout>
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

    //暗注释
    ui->cb_id->setEditable(true);
    QLineEdit *lineEdit = ui->cb_id->lineEdit();
    lineEdit->setPlaceholderText(tr("账号"));
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
        msgBox.setText("请输入账号!!!");
        msgBox.exec();
    }else if (info.getID() != ui->cb_id->currentText()) //输入的账号数据库中没有
    {
        QMessageBox msgBox;
        msgBox.setText("您输入的账号是空号，请您重新输入账号\n"
                       "或者去注册新的账号!!!");
        msgBox.exec();
    }else
    {
        if(info.getPswd() == ui->le_pswd->text()) //账号和密码均正确
        {
            this->hide();
        }else if(ui->le_pswd->text() == NULL)     //未输入密码
        {
            QMessageBox msgBox;
            msgBox.setText("请输入密码");
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
}

void Login::on_pb_register_clicked()
{
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
