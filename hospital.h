#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "manager.h"
#include "section.h"
#include "t_database.h"
#include <fstream>
#include <QMap>
#include <QList>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>

class hospital
{
private:
    QString  Name;
    QString  Address;
    QString  Phone;
    Manager  Boss;
    T_DataBase DBPort;

public:
    hospital();

    QMap<QString,QList<doctor>>  SectionsList;

    //         set and get methods       //

    void setBoss(Manager & boss);
    Manager getBoss();

    void setDBPort(T_DataBase db);
    T_DataBase getDBPort();

    void setPhone(QString phone);
    QString getPhone();

    QString  getHospitalAddress() {return Address;}
    QString  getHospitalName() { return Name;}

    void  setHospitalName(QString na) { Name = na;}
    void  setHospitalAddress(QString  had){ Address = had;}


    void  setBossName(QString  bn) {this->Boss.setName(bn);}
    QString  getBossName() { return this->Boss.getName();}

    void  setBossPassword(QString p);
    QString  getBossPassword();

    void  setBossUserName(QString  bun) { this->Boss.setUserName(bun);}
    QString  getBossUserName() { return this->Boss.getUserName();}

    //      ----------------------     //

    typedef  QMap<QString,QList<doctor>> ::iterator  mitr;
    typedef  QList<doctor> ::iterator litr;

    //          public methods          //

    void SaveHospitalDoctorsInDataBase();
    void ReceiveHospitalDoctorsFromDB();


    void AddDoctor(QString secname , QList<doctor> & dl);
    void AddDoctor(QString secname , doctor d);
    void AddSection(QString secname);

    bool CheckDoctor(QString docname,QString sn);

    QList<doctor> ::iterator FindDoctor(QString sn , QString doctorname);

    doctor  MakeDoctor(QString docline);

//    void TakeVisitTime(patient *p, QString sn, QString dn);

    void TakeVisitTime(PatientVisitTime & vt , QString patientname ,
                       QString patientphone);

    bool RecognizeHospital();

    void PrintAllSections();

//    void SaveDoctorsInFile();

    bool RegisterHospital();

    bool ReceiveHospitalFromDatabase();

    void PrintHospital();

    void PrintASectionDoctors(QString sectionName);

//    void  FillVisitTimeFile(QString dn, patient & p);
};

#endif // HOSPITAL_H
