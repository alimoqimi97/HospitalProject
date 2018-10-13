#ifndef ASSURANCE_H
#define ASSURANCE_H
#include "prescription.h"
#include<QString>

class Assurance
{
private:
    Prescription VisitSheet;
    QString  PatientName;

public:
    Assurance();

    //          get and set methods     //
    void setVisitSheet(Prescription & p)
    {
        this->VisitSheet = p;
    }
    Prescription & getVisitSheet()
    {
        return this->VisitSheet;
    }

    void setPatientName(QString patientname)
    {
        this->PatientName = patientname;
    }
    QString getPatientName()
    {
        return this->PatientName;
    }
    //          --------------------        //

    void AddMedicine(QString medicineName)
    {
        this->VisitSheet.AddtoMedicineList(medicineName);
    }
    void RemoveMedicine(QString medicineName)
    {
        this->VisitSheet.RemoveFromMedicineList(medicineName);
    }

    void PrintCurrentPrescription()
    {
        this->VisitSheet.PrintPrescription();
    }
    void ClearNoteBook()
    {
        this->VisitSheet.clearPrescription();
    }

};

#endif // ASSURANCE_H
