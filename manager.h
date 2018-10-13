#ifndef MANAGER_H
#define MANAGER_H

#include "user.h"
#include <QStringList>
#include <QString>
#include <QSqlQuery>

class Manager : public User
{
    QString OrganizationName;
public:
    Manager();
    Manager(QString userName);


    //          set and get methods         //
    void setOrgName(QString orgname);
    QString getOrgName();
    //          -------------------         //

    //      virtual methods         //

    virtual bool RegisterUser();

    virtual void ReceiveUserFromDataBase();

    virtual bool EditInformation(User * NewUser);

    virtual bool Exists();
};

#endif // MANAGER_H
