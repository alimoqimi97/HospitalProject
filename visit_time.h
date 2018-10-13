#ifndef VISIT_TIME_H
#define VISIT_TIME_H
#include <iostream>
#include <QString>
#include <QTextStream>
using namespace std;

enum Timestatus {EMPTY,FULL};

class visit_time
{
private:
    QString Date;
    QString start_time;
    QString end_time;
    Timestatus  ts;
public:
    visit_time();

    //          get and set methods     //
    void setDate(QString date);
    QString getDate() const;

    void setStartTime(QString st);
    QString getStartTime() const;

    void setEndTime(QString et);
    QString getEndTime() const;

    void setStatus(Timestatus t);
    Timestatus getStatus() const;
    //          -------------------    //

    bool operator== (visit_time const & other);


};

ostream & operator << (ostream & vout , visit_time & vt);

QTextStream & operator << (QTextStream & qout, visit_time & vt);

QTextStream & operator >> (QTextStream & qin , visit_time & vt);

#endif // VISIT_TIME_H
