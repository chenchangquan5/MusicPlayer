#ifndef EXECSQL_H
#define EXECSQL_H

#include "userinfo.h"
#include "registerinfo.h"

class ExecSQL
{
public:
    ExecSQL();

    static UserInfo selectUserInfo(QString id);

//    static void getTotalRegisterUser();
    static RegisterInfo *selectRegisterInfo(QString id);
    static bool insertRegisterInfo(QString id,QString pswd);


//    static quint32 m_registerUserTotal;
};

#endif // EXECSQL_H
