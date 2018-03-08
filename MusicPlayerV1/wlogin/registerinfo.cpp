#include "registerinfo.h"
#include <QDebug>

RegisterInfo::RegisterInfo()
{
    clearRegisterInfo();
}

RegisterInfo::RegisterInfo(const QString &id,
        const QString &pswd)
{
    updataRegisterinfo(id, pswd);
}

RegisterInfo::~RegisterInfo()
{
}

void RegisterInfo::updataRegisterinfo(RegisterInfo *info)
{
    m_ID = info->getID();
    m_Pswd = info->getPswd();
}

void RegisterInfo::updataRegisterinfo(const QString &id,
                    const QString &pswd)
{
    m_ID = id;
    m_Pswd = pswd;
}

void RegisterInfo::clearRegisterInfo(void)
{
    m_ID.clear();
    m_Pswd.clear();
}

void RegisterInfo::printInfos(void) const
{
    qDebug() << "RegisterInfo-----------------------------------";
    qDebug() << "ID: " << getID();
    qDebug() << "Password: " << getPswd();
    qDebug() << "RegisterInfo===================================";
}
QString *RegisterInfo::packageinfos(void)
{
    QString *data = new QString();
    data->clear();

    data->append(getID());
    data->append("|");
    data->append(getPswd());

    return data;
}

const QString &RegisterInfo::getID(void) const
{
    return m_ID;
}
void RegisterInfo::setID(const QString &id)
{
    m_ID = id;
}

const QString &RegisterInfo::getPswd(void) const
{
    return m_Pswd;
}
void RegisterInfo::setPswd(const QString &pswd)
{
    m_Pswd = pswd;
}


