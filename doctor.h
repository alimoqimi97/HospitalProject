#ifndef DOCTOR_H
#define DOCTOR_H
#include "user.h"
#include "patient.h"
#include "linklist.h"
#include "doctorvisittime.h"
#include <iostream>
#include "stdlib.h"
#include <QStringList>
#include <fstream>
#include "time.h"
#include <QString>

using namespace std;

class doctor : public User
{
private:
    int  doctor_rank;
    QString  WorkPlace;
    QString  Specialization;
    QList<DoctorVisitTime> VisitList;
    QList<visit_time> WorkHours;
public:
//    doctor(doctor & other);
    doctor(QString userName);
    doctor();

    //          get and set methods         //

    void setSpecialization(QString s);
    QString getSpecialization();

    void setWorkHours(QList<visit_time> wh);
    QList<visit_time> getWorkHours();

    void setVisitList(QList<DoctorVisitTime> & vl);
    QList<DoctorVisitTime> getVisitList();

    void setWorkPlace(QString workplace);
    QString getWorkPlace();

    void setDoctorRank(int ra){ doctor_rank = ra;}
    int  getDoctorRank() { return doctor_rank;}

    //          -------------------         //

    //      public methods          //

    void SaveVisitListInDataBase();
    void LoadVisitListFromDataBase();

    void SavePatientListInDatabase();
    void ReceivePatientListFromDatabase();

    void AddToVisitList(DoctorVisitTime dvt);
    bool RemoveFromVisitList(DoctorVisitTime & dvt);

    void AddToWorkHours(visit_time & vt);
    bool RemoveFromWorkHours(visit_time & vt);

    void SaveDoctorWorkHoursInDataBase();
    void LoadDoctorWorkHoursFromDataBase();

    void PrintVisitList();

    void PrintWorkHours();

//    void EnterVisitTime(patient &pa);
    void givePcode(patient &pati);
    void WritePrescription(patient target_p,Prescription pres);

    //      virtual methods         //

    virtual bool RegisterUser();

    virtual bool Exists();

    virtual void ReceiveUserFromDataBase();

    virtual bool EditInformation(User * NewUser);

    //          ---------------------           //

//    linklist  patient_ll;

};


ostream & operator << (ostream & dout , doctor & target);

QTextStream & operator << (QTextStream & qout , doctor & target);

ofstream & operator << (ofstream & fout , doctor & d);

QTextStream & operator >> (QTextStream & sin , doctor & target);

#endif // DOCTOR_H
