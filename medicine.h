#ifndef MEDICINE_H
#define MEDICINE_H
#include<QString>
#include<iostream>
#include <QHash>
#include <QSet>
#include <fstream>
using namespace std;

class Medicine
{
private:
    QString  MedicineName;
    int  Number;
    QString  ConsumeDate;
public:
    Medicine();

    //          set and get methods     //
    void setMedicineName(QString medicinename)
    {
        this->MedicineName = medicinename;
    }
    QString getMedicineName()const
    {
        return this->MedicineName;
    }

    void setNumber(int number)
    {
        this->Number = number;
    }
    int getNumber() const
    {
        return this->Number;
    }

    void setConsumeDate(QString cd)
    {
        this->ConsumeDate = cd;
    }
    QString getConsumeDate() const
    {
        return this->ConsumeDate;
    }
    //          -------------------     //

    bool operator<(Medicine & other);
    bool operator == (const Medicine &other)const;
};

uint qHash(Medicine const & m);

ostream & operator << (ostream & output , const Medicine & target);

ofstream & operator << (ofstream & fout ,const Medicine & target);

#endif // MEDICINE_H
