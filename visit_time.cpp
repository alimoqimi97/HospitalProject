#include "visit_time.h"

visit_time::visit_time() : start_time("0") , end_time("0") , ts(EMPTY)
{

}

void visit_time::setDate(QString date)
{
    this->Date = date;
}

QString visit_time::getDate() const
{
    return this->Date;
}

void visit_time::setStartTime(QString st)
{
    this->start_time = st;
}

QString visit_time::getStartTime() const
{
    return this->start_time;
}

void visit_time::setEndTime(QString et)
{
    this->end_time = et;
}

QString visit_time::getEndTime() const
{
    return this->end_time;
}

void visit_time::setStatus(Timestatus t)
{
    this->ts = t;
}

Timestatus visit_time::getStatus() const
{
    return this->ts;
}

bool visit_time::operator==(const visit_time &other)
{
    if(this->Date == other.getDate())
    {
        if(this->start_time == other.getStartTime())
        {
            if(this->end_time == other.getEndTime())
            {
                if(this->ts == other.getStatus())
                {
                    return true;
                }
            }
        }
    }
    return false;
}

//ostream & operator <<(ostream &output, visit_time &pot)
//{
//    output << "Start time is : " << pot.start_time.toStdString() << endl;
//    output << "End time is : " << pot.end_time.toStdString() << endl;
//    return output;
//}

//istream & operator>>(istream &input, visit_time &vt)
//{
//    cout << "Start time : ";
//    input >> vt.start_time ;
//    cout << "end time : ";
//    input >> vt.end_time;
//    return input;
//}


QTextStream &operator <<(QTextStream &qout, visit_time &vt)
{
    qout << "StartTime is : " << vt.getStartTime() << endl;
    qout << "EndTime is : " << vt.getEndTime() << endl;
    return qout;
}


QTextStream &operator >>(QTextStream &qin, visit_time &vt)
{
    QString setime;

    cout << "Date : ";
    qin >> setime;
    vt.setDate(setime);

    cout << "StartTime : " ;
    qin >> setime;
    vt.setStartTime(setime);

    cout << "End time : ";
    qin >> setime;
    vt.setEndTime(setime);

    return qin ;
}


ostream &operator <<(ostream &vout, visit_time &vt)
{
    vout << "( ";
    vout << vt.getDate().toStdString() << ',';
    vout << vt.getStartTime().toStdString() << ',';
    vout << vt.getEndTime().toStdString() << ',';

    if(vt.getStatus() == FULL)
    {
        vout << "Full" << endl;
    }
    else
    {
        vout << "Empty" << endl;
    }
    vout << ") " ;

    return vout;
}
