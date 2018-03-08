#include "connectsqlite.h"

#include <QDebug>

ConnectSQLite::ConnectSQLite()
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("user.db");

    if(db.open()){
        qDebug() << "Success:Connect SQLite";
    }else
    {
        qDebug() << "Fail:Connect SQLite";
    }
}

ConnectSQLite::~ConnectSQLite()
{

}
