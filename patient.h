#ifndef PATIENT_H
#define PATIENT_H
#include "user.h"
#include "assurance.h"
#include "patientvisittime.h"
#include <iostream>
#include <QString>
//#include <visit_time.h>
#include <fstream>
#include <QSqlError>
using namespace std;

class patient : public User
{
private:
    Assurance  AssuranceNoteBook;
    QList<PatientVisitTime> SelectedTimes;
    int pCode;

public:
    patient();
    patient(QString userName);

    //          get and set methods         //

    void setPvt(QList<PatientVisitTime> & vt);
    QList<PatientVisitTime> getPvt();

    void setPcode(int pc);
    int getPcode();

    void  setAssuranceNoteBook(Assurance & anb);
    Assurance  getAssuranceNoteBook();

    //          ------------------          //

    //          public methods              //

    void SaveSelectedTimesInDataBase();
    void LoadSelectedTimesInDataBase();

    void  PrintSelectedHours();

    void  PrintPatient(QString hn, QString dn);

    void  AddPrescription(Prescription p);

    void SaveMedicinesInFile();

    void AddtoSelectedTimes(PatientVisitTime & vt);
    bool RemoveFromSelectedTimes(PatientVisitTime & vt);

    void SaveSelectedHoursInDataBase();
    void LoadSelectedHoursFromDataBase();

    //          ---------------             //

//          virtual methods         //

    virtual bool RegisterUser();

    virtual bool Exists();

    virtual void ReceiveUserFromDataBase();

    virtual bool EditInformation(User *NewUser);

//          ----------------        //

    patient * next;
};

//ostream & operator<< (ostream & output , patient & target);

#endif // PATIENT_H
