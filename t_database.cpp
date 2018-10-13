#include "t_database.h"

T_DataBase::T_DataBase()
{

}

void T_DataBase::setQueryTool(QSqlQuery qt)
{
    this->QueryTool = qt;
}

QSqlQuery T_DataBase::getQueryTool()
{
    return this->QueryTool;
}

void T_DataBase::setDataBaseName(QString dbname)
{
    this->DataBaseName = dbname;
}

QString T_DataBase::getDataBaseName()
{
    return this->DataBaseName;
}

void T_DataBase::setConnectionName(QString cn)
{
    this->ConnectionName = cn;
}

QString T_DataBase::getConnectionName()
{
    return this->ConnectionName;
}

bool T_DataBase::DBRowCount()
{
    return this->QueryTool.size();
}

QVariant T_DataBase::Value(QString colname)
{
    return this->QueryTool.value(colname);
}

QVariant T_DataBase::Value(int colnum)
{
    return this->QueryTool.value(colnum);
}

bool T_DataBase::NextRow()
{
    return this->QueryTool.next();
}

bool T_DataBase::exists(QString targetcol, QString tablename, QString condition)
{
    QVariant  temp;
    QSqlDatabase todriver = QSqlDatabase ::database(this->ConnectionName);

    if(!todriver.open())
    {
        return false;
    }

    this->QueryTool.prepare("select exists(select :tc from :tn where :cnd"
                            ");");
    temp = targetcol;
    this->QueryTool.bindValue(":tc",targetcol);

    temp = tablename;
    this->QueryTool.bindValue(":tn",tablename);

    temp = tablename;
    this->QueryTool.bindValue(":cnd",condition);

    this->QueryTool.exec();

    this->QueryTool.next();

    if(this->QueryTool.value(0).toInt() == 1)
    {
        return true;
    }

    return false;
}

bool T_DataBase::ArbitraryQuery(QString query)
{
    QSqlDatabase tomysql = QSqlDatabase ::database(this->ConnectionName);
    bool state;

    if(!tomysql.open())
    {
        return false;
    }

    state = this->QueryTool.exec(query);

    tomysql.close();

    return state;
}

bool T_DataBase::SELECTAll(QString tablename)
{
    QSqlDatabase todriver = QSqlDatabase ::database(this->ConnectionName);
    bool state;

    if(!todriver.open())
    {
        return false;
    }

    this->QueryTool.prepare("SELECT * FROM :tn;");
    this->QueryTool.bindValue(":tn",tablename);
    state = this->QueryTool.exec();

    return state;
}

bool T_DataBase::SELECTColumn(QString colname, QString tablename)
{
    bool state;
    QSqlDatabase todriver = QSqlDatabase ::database(this->ConnectionName);
    const QString  ph = ":clmnname";
    const QString  plh = ":tn";
    QVariant value;

    if(!todriver.open())
    {
        return false;
    }

    this->QueryTool.prepare("SELECT :clmnname FROM :tn ;");

    value = colname;
    this->QueryTool.bindValue(ph ,colname);

    value = tablename;
    this->QueryTool.bindValue(plh ,tablename);

    state = this->QueryTool.exec();
    this->QueryTool.next();

    return state;
}

bool T_DataBase::SELECTColumnWHERE(QString tablename, QString colname, QString condition)
{
    bool state;
    QSqlDatabase tomysql = QSqlDatabase ::database(this->ConnectionName);

    if(!tomysql.open())
    {
        return false;
    }

    this->QueryTool.prepare("SELECT :cn FROM :tn WHERE :cnd ;");
    this->QueryTool.bindValue(":cn",colname);
    this->QueryTool.bindValue(":tn",tablename);
    this->QueryTool.bindValue(":cnd",condition);

    state = this->QueryTool.exec();
    tomysql.close();

    return state;
}

bool T_DataBase::SELECTRow(QString tblname, QString condition)
{
    QSqlDatabase todriver = QSqlDatabase ::database(this->ConnectionName);
    bool state;

    if(!todriver.open())
    {
        return false;
    }

    this->QueryTool.prepare("SELECT * FROM :tn WHERE :cnd ;");
    this->QueryTool.bindValue(":tn",tblname);
    this->QueryTool.bindValue(":cnd",condition);

    state = this->QueryTool.exec();
    todriver.close();

    return state;
}

bool T_DataBase::INSERTRow(QString tblname, QStringList &values)
{
    QSqlDatabase tomysql = QSqlDatabase ::database(this->ConnectionName);
    bool state ;
    QString invalues;

    if(!tomysql.open())
    {
        return false;
    }

    this->QueryTool.prepare("INSERT INTO :tn VALUES ( :vls ) ;");
    this->QueryTool.bindValue(":tn",tblname);
    this->QueryTool.bindValue(":vls",values);

    for(int i = 0 ; i < values.size() ; i++)
    {
        invalues += "' " + values.at(i) + "' ," ;
    }

    int lindex = invalues.lastIndexOf(",");
    invalues.remove(lindex);

    this->QueryTool.bindValue(":vls",invalues);

    state = this->QueryTool.exec();
    tomysql.close();
    return state;
}

void T_DataBase::CreateConnectionToMySQL()
{
    QSqlDatabase todriver = QSqlDatabase ::addDatabase("QMYSQL" ,
                                                       this->ConnectionName);
    todriver.setDatabaseName(this->DataBaseName);
    todriver.setHostName("localhost");
    todriver.setUserName("root");
    todriver.setPassword("Ali@real@Sharif@2223");
}

bool T_DataBase::DELETERow(QString tbn, QString cnd)
{
    QSqlDatabase tomysql = QSqlDatabase ::database(this->ConnectionName);
    QVariant condition = cnd , tablename = tbn;
    bool state;

    if(!tomysql.open())
    {
        return false;
    }

    this->QueryTool.exec("DELETE FROM :tbn WHERE :cnd ;");

    this->QueryTool.bindValue(":tbn",tablename);
    this->QueryTool.bindValue(":cnd",condition);
    state = this->QueryTool.exec();

    tomysql.close();

    return state;
}

bool T_DataBase::UPDATERow(QString tablename, QString settingvalue, QString condition)
{
    QSqlDatabase todriver = QSqlDatabase ::database(this->ConnectionName);
    bool state;

    if(!todriver.open())
    {
        return false;
    }

    this->QueryTool.prepare("UPDATE :tn SET :sv WHERE :cnd ;");
    this->QueryTool.bindValue(":tn",tablename);
    this->QueryTool.bindValue(":sv",settingvalue);
    this->QueryTool.bindValue(":cnd" , condition);

    state = this->QueryTool.exec();

    todriver.close();
    return state;
}
