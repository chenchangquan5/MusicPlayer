#include "userinfo.h"

#include <QDebug>

UserInfo::UserInfo()
{
    m_id.clear();
    m_pswd.clear();
}

UserInfo::UserInfo(const QString &id,
                   const QString &pswd)
{
    m_id = id;
    m_pswd = pswd;
}

UserInfo::~UserInfo()
{

}

void UserInfo::updateUserInfo(const UserInfo &info)
{
    m_id = info.getID();
    m_pswd = info.getPswd();
}

void UserInfo::updateUserInfo(const QString &id,
          const QString &pswd)
{
    m_id = id;
    m_pswd = pswd;
}

void UserInfo::display() const
{
    qDebug() << "--------------Disp UserInfo---------------";
    qDebug() << "ID: " << m_id;
    qDebug() << "Psed: " << m_pswd;
    qDebug() << "--------------UserInfo End----------------";
}

void UserInfo::setID(const QString &id)
{
    m_id = id;
}

const QString &UserInfo::getID() const
{
    return m_id;
}
void UserInfo::setPswd(const QString &pswd)
{
    m_pswd = pswd;
}

const QString &UserInfo::getPswd() const
{
    return m_pswd;
}

