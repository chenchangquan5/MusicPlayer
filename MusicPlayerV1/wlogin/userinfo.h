#ifndef USERINFO_H
#define USERINFO_H

#include <QString>
#include <QList>

class UserInfo
{
public:
    UserInfo();
    UserInfo(const QString &id,
              const QString &pswd);
    virtual ~UserInfo();

    virtual void display() const;

    void updateUserInfo(const UserInfo &info);
    void updateUserInfo(const QString &id,
              const QString &pswd);

    void setID(const QString &id);
    const QString &getID() const;
    void setPswd(const QString &pswd);
    const QString &getPswd() const;

private:
    QString m_id;
    QString m_pswd;
};

typedef QList<UserInfo> ListUserInfo;

#endif // USERINFO_H
