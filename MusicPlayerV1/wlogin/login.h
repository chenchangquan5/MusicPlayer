#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>
#include <QPoint>

#include "register.h"
#include "userinfo.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public slots:
    void slotShowLogin(void);

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

protected:
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);

private slots:
    void on_pb_enter_clicked();
    void on_pb_register_clicked();
    void on_pb_close_clicked();
    void on_pb_min_clicked();

private:
    Ui::Login *ui;

    void initWindow(void);

//    //密码框小键盘按钮
//    QPushButton *m_keyboardButton;

    Register *m_register;

    QPoint m_widgetMove;
};

#endif // LOGIN_H
