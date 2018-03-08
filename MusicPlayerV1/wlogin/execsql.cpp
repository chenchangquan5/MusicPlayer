#include "execsql.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>


ExecSQL::ExecSQL()
{

}

UserInfo ExecSQL::selectUserInfo(QString id)
{
    UserInfo info;
    QSqlQuery query;
    QString queryString = QString("select * from user where ID = '%1'").arg(id);

    if(query.exec(queryString))
    {
          int id_id = query.record().indexOf("ID");
          int pswd_id = query.record().indexOf("pswd");

          while(query.next())
          {
              QString id = query.value(id_id).toString();
              QString pswd = query.value(pswd_id).toString();

              info.updateUserInfo(id, pswd);
          }
    }

    return info;
}

//void ExecSQL::getTotalRegisterUser()
//{
//    m_registerUserTotal = 0;

//    QSqlQuery query;
//    QString queryString = QString("select * from user");

//    if(query.exec(queryString))
//    {
//        int id_idx = query.record().indexOf("ID");

//        while (query.next())
//        {
//            QString id = query.value(id_idx).toString();
//            m_registerUserTotal++;
//        }
//    }
//}

bool ExecSQL::insertRegisterInfo(QString id, QString pswd)
{
//    getTotalRegisterUser();
    QSqlQuery query;

    QString basicString = QString("insert into user values('%1', '%2')");
    QString queryString = basicString.arg(id).arg(pswd);

    return query.exec(queryString);
}

RegisterInfo *ExecSQL::selectRegisterInfo(QString id)
{
    RegisterInfo *info = new RegisterInfo;
    QSqlQuery query;
    QString queryString = QString("select * from user "
                                  "where user.ID = '%1'").arg(id);

    if(query.exec(queryString))
    {
        int id_idx = query.record().indexOf("ID");
        int pswd_idx = query.record().indexOf("pswd");

        while (query.next())
        {
            QString id = query.value(id_idx).toString();
            QString pswd = query.value(pswd_idx).toString();

            info->updataRegisterinfo(id, pswd);
        }
    }

    return info;
}

