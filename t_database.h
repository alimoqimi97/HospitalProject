#ifndef T_DATABASE_H
#define T_DATABASE_H
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QString>
#include <QStringList>
#include <QVariant>

class T_DataBase
{
private:
    QSqlQuery QueryTool;
//    QSqlDataBase ToDriver;
    QString DataBaseName;
    QString ConnectionName;

public:
    T_DataBase();

    //      get and set methods        //

    void setQueryTool(QSqlQuery qt);
    QSqlQuery getQueryTool();

    void setDataBaseName(QString dbname);
    QString getDataBaseName();

    void setConnectionName(QString cn);
    QString getConnectionName();

    //      -----------------------         //

    bool DBRowCount();

    QVariant Value(QString colname);
    QVariant Value(int colnum);
    bool NextRow();

    bool exists(QString targetcol , QString tablename,QString condition);

    bool ArbitraryQuery(QString query);

    bool SELECTAll(QString tablename);

    bool SELECTColumn(QString colname , QString tablename);

    bool SELECTColumnWHERE(QString tablename , QString colname , QString condition);

    bool SELECTRow(QString tblname , QString condition);

    bool INSERTRow(QString tblname , QStringList & values);

    void CreateConnectionToMySQL();

    bool DELETERow(QString tbn,QString cnd);
    bool UPDATERow(QString tablename , QString settingvalue,QString condition);

};

#endif // T_DATABASE_H
