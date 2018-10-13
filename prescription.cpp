#include "prescription.h"

Prescription::Prescription()
{
}

void Prescription::SaveMedicineInFile(QString patientname)
{
    ofstream  send(patientname.toStdString() , ios :: out | ios :: app);
    QList<QString> ::iterator litr;

    if(!send)
    {
        cout << "The patient file doesn't opened!" << endl;
        return;
    }

    for(litr = this->MedicineList.begin() ; litr != MedicineList.end() ; litr++)
    {
        send << litr->toStdString() << endl;
    }

    send.close();
}

void Prescription::AddtoMedicineList(QString medicinename)
{
    this->MedicineList.push_back(medicinename);
}

bool Prescription::RemoveFromMedicineList(QString medicinename)
{
    return this->MedicineList.removeOne(medicinename);
}

void Prescription::clearPrescription()
{
    this->DoctorName.clear();
    this->VisitDate.clear();
    this->MedicineList.clear();
}

void Prescription::PrintPrescription()
{
    QList<QString> ::iterator litr;

    cout << this->DoctorName.toStdString() << endl;
    cout << this->VisitDate.toStdString() << endl;
    cout << "Medicines : " << endl;

    for(litr = this->MedicineList.begin() ; litr != MedicineList.end() ; litr++)
    {
        cout << litr->toStdString() << endl;
    }
}
