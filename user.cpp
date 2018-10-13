#include "user.h"

User::User(QString connectionname,QString databasename)
{
    this->ConnectionTool.setConnectionName(connectionname);
    this->ConnectionTool.setDataBaseName(databasename);
}

User::User(QString username)
{
    this->UserName = username;
}

User::User()
{}
