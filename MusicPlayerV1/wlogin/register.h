#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>

namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

signals:
    void signalShowLogin(void);

public:
    explicit Register(QWidget *parent = 0);
    ~Register();

protected:
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);

private slots:
    void on_pb_register_clicked();
    void on_pb_close_clicked();
    void on_pb_return_clicked();

private:
    Ui::Register *ui;

    QPoint m_widgetMove;

    void initWindow(void);
};

#endif // REGISTER_H
