#ifndef REGISTERINFO_H
#define REGISTERINFO_H

#include <QString>
#include <QList>

class RegisterInfo
{
public:
    RegisterInfo();

    RegisterInfo(
            const QString &id, const QString &pswd);
    ~RegisterInfo();

    void updataRegisterinfo(RegisterInfo *info);
    void updataRegisterinfo(const QString &id, const QString &pswd);

    void clearRegisterInfo(void);

    virtual void printInfos(void) const;
    virtual QString *packageinfos(void);

    const QString &getID(void) const;
    void setID(const QString &id);

    const QString &getPswd(void) const;
    void setPswd(const QString &pswd);

private:
    QString m_ID;
    QString m_Pswd;
};

typedef QList<RegisterInfo> List_RegisterInfo;

#endif // REGISTERINFO_H
