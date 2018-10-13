#ifndef USER_H
#define USER_H
#include "t_database.h"
#include <QString>

class User
{
private:
    QString Name;
    QString UserName;
    QString Password;
    QString Phone;
    int ID;

protected:
    T_DataBase  ConnectionTool;

public:
    User(QString connectionname,QString databasename);
    User(QString username);
    User();

//     set and get methods     //

    void setID(int id)
    {
        this->ID = id;
    }
    int getID()
    {
        return this->ID;
    }

    void setName(QString name)
    {
        this->Name = name;
    }
    QString getName()
    {
        return this->Name;
    }

    void setUserName(QString username)
    {
        this->UserName = username;
    }
    QString getUserName()
    {
        return this->UserName;
    }

    void setPassword(QString password)
    {
        this->Password = password;
    }
    QString getPassword()
    {
        return this->Password;
    }

    void setPhone(QString phone)
    {
        this->Phone = phone;
    }
    QString getPhone()
    {
        return this->Phone;
    }

    //          ------------------          //

    virtual bool RegisterUser() = 0;

    virtual bool Exists() = 0;

    virtual void ReceiveUserFromDataBase() = 0;

    virtual bool EditInformation(User * NewUser) = 0;

    virtual ~User()
    {}
};

#endif // USER_H
