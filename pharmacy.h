#ifndef PHARMACY_H
#define PHARMACY_H
#include "medicine.h"
#include<QString>
#include<QSet>
#include<QFile>
#include<QTextStream>
#include<QMap>
#include<fstream>

class Pharmacy
{
private:
    QString OwnerName;
    QString OwnerUserName;
    QString OwnerPassword;

    QString Name;
    QString Address;
    QSet<Medicine> MedicineStore;
    QMap<QString,QList<QString>> PatientBasket;

public:
    Pharmacy();

    //          get and set methods         //
    void setOwnerUserName(QString username)
    {
        this->OwnerUserName = username;
    }
    QString getOwnerUserName()
    {
        return this->OwnerUserName;
    }

    void setOwnerPassword(QString password)
    {
        this->OwnerPassword = password;
    }
    QString getOwnerPassword()
    {
        return this->OwnerPassword;
    }

    void setOwnerName(QString ownername)
    {
        this->OwnerName = ownername;
    }
    QString getOwnerName()
    {
        return this->OwnerName;
    }

    QString getName()
    {
        return this->Name;
    }
    void setName(QString pharmacyName)
    {
        this->Name = pharmacyName;
    }

    QString getAddress()
    {
        return this->Address;
    }
    void setAddress(QString address)
    {
        this->Address = address;
    }

    QSet<Medicine> & getMedicineStore()
    {
        return this->MedicineStore;
    }
    void setMedicineStore(QSet<Medicine> & medst)
    {
        this->MedicineStore = medst;
    }
    //          ---------------------           //

    void SaveInPharmaciesFile();
    void AddToExpectationFile(QString patientname);
    void SaveStoreInFile();
    void SaveOwnerUserPassInFile();
    void FillPatientBasket(QString patientname);
    void LoadPatientMedicine(QString patname,QList<QString> & medicinelist);
    void RemoveFromPatientBasket(QString patientname);
    void LoadStore();
    void UpdatePatientBasket();
    bool Exists();
    void LoadOwnerUserPass();
    void LoadPharmacyInfo();
    void AddToStore(Medicine & m);
    bool RemoveFromStore(Medicine & m);
    void ShowPatientMedicines(QString patientname);
    void ShowMedicineStore();
    void RemoveFromStoreByName(QString medicinename);
    void ShowExpectationList();
    void ClearAllExpectationList();
    void PrintPharmacy();

};

#endif // PHARMACY_H
