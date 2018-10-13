#include "manager.h"

Manager::Manager() : User()
{}

Manager::Manager(QString userName) : User(userName)
{}

void Manager::setOrgName(QString orgname)
{
    this->OrganizationName = orgname;
}

QString Manager::getOrgName()
{
    return this->OrganizationName;
}

bool Manager::RegisterUser()
{
    QStringList managerinfo;

    managerinfo.push_back(this->getName());
    managerinfo.push_back(this->getUserName());
    managerinfo.push_back(this->getOrgName());
    managerinfo.push_back(this->getPassword());
    managerinfo.push_back(this->getPhone());

    return this->ConnectionTool.INSERTRow("OwnersInfo", managerinfo);
}

void Manager::ReceiveUserFromDataBase()
{
    QString condition = "UserName = '" + this->getUserName() + "'";
    QSqlQuery select;

    this->ConnectionTool.SELECTRow("OwnersInfo",condition);

    select = this->ConnectionTool.getQueryTool();

    select.next();

    this->setName(select.value("Name").toString());
    this->setUserName(select.value("UserName").toString());
    this->setOrgName(select.value("HospitalName").toString());
    this->setPassword(select.value("Password").toString());
    this->setPhone(select.value("Phone").toString());
    this->setID(3);
}

bool Manager::EditInformation(User *NewUser)
{
    QStringList managerinfo;

    managerinfo.push_back(NewUser->getName());
    managerinfo.push_back(NewUser->getUserName());
    managerinfo.push_back(this->OrganizationName);
    managerinfo.push_back(NewUser->getPassword());
    managerinfo.push_back(NewUser->getPhone());

    return this->ConnectionTool.INSERTRow("OwnersInfo",managerinfo);
}

bool Manager::Exists()
{
//    this->setID(3);
    return this->ConnectionTool.exists("*","OwnersInfo","UserName = '"
                                       + this->getUserName() + "'");
}
