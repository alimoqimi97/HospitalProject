#ifndef PRESCRIPTION_H
#define PRESCRIPTION_H
#include<QList>
#include<QString>
#include<iostream>
#include<fstream>
using namespace std;


class Prescription
{
private:
    QList<QString>  MedicineList;
    QString  DoctorName;
    QString  VisitDate;

public:
    Prescription();

    //          set and get methods         //
    void setMedicineList(QList<QString> ml)
    {
        this->MedicineList = ml;
    }
    QList<QString> getMedicineList()
    {
        return this->MedicineList;
    }

    void setDoctorName(QString doctorname)
    {
        this->DoctorName = doctorname;
    }
    QString getDoctorName()
    {
        return this->DoctorName;
    }

    void setVisitDate(QString vd)
    {
        this->VisitDate = vd;
    }
    QString getVisitDate()
    {
        return this->VisitDate;
    }
    //          -----------------------         //

    void SaveMedicineInFile(QString patientname);
    void AddtoMedicineList(QString  medicinename);
    bool RemoveFromMedicineList(QString medicinename);
    void clearPrescription();
    void PrintPrescription();
};

#endif // PRESCRIPTION_H
