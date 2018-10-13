#include "pharmacy.h"

Pharmacy::Pharmacy()
{}

void Pharmacy::SaveInPharmaciesFile()
{
    ofstream send("Pharmacyfile.txt",ios :: out | ios :: app);

    send << this->Name.toStdString() << endl;
    send << this->Address.toStdString() << endl;
    send.close();
}

void Pharmacy::AddToExpectationFile(QString patientname)
{
    QString  FileName = this->Name;
    FileName.append("ExpectationFile.txt");
    ofstream send(FileName.toStdString() , ios :: out | ios :: app);

    if(!send)
    {
        cout << "the pharmacy Expectation file isn't open" << endl;
        return;
    }

    send << patientname.toStdString() << endl;
    send.close();
}

void Pharmacy::SaveStoreInFile()
{
    ofstream send(this->Name.toStdString() + "Store.txt",ios :: out);
    QSet<Medicine> ::iterator sitr;

    for(sitr = this->MedicineStore.begin() ; sitr != MedicineStore.end() ; sitr++)
    {
//        Medicine m = *sitr;

        send << *sitr << endl;
    }

    send.close();
}

void Pharmacy::SaveOwnerUserPassInFile()
{
    ofstream send("pd_user_pass.txt",ios :: out | ios :: app);
    QString  mark = " phar";

    if(!send)
    {
        cout << "We can not Enter pharmacy owner info in pd_user_pass!..." << endl;
        return;
    }

    send << this->Name.toStdString() << endl;
    send << this->OwnerUserName.toStdString() << endl;
    send << this->OwnerPassword.toStdString() << endl;
    send << this->OwnerName.toStdString() << mark.toStdString() << endl;
    send << "------------------------------" << endl;
    send.close();
}

void Pharmacy::FillPatientBasket(QString patientname)
{
    QList<QString> tmplist;

    this->LoadPatientMedicine(patientname,tmplist);
    this->PatientBasket[patientname] = tmplist;

}

void Pharmacy::LoadPatientMedicine(QString patname, QList<QString> &medicinelist)
{
    QFile  patientfile(patname + ".txt");
    QTextStream fin(&patientfile);
    QString tmp;

    patientfile.open(QIODevice ::ReadOnly);

    for(int i = 0 ; i < 3 ; i++)
    {
        tmp = fin.readLine();
    }

    while(!tmp.isEmpty())
    {
        tmp = fin.readLine();
        medicinelist.push_back(tmp);
    }

    patientfile.close();
}

void Pharmacy::RemoveFromPatientBasket(QString patientname)
{
    PatientBasket.remove(patientname);
}

void Pharmacy::LoadStore()
{
    QFile storefile(this->Name + "Store.txt");
    QTextStream  recv(&storefile);
    QString tmp;
    QStringList s;
    Medicine m;

    if(!storefile.exists())
    {
        return;
    }

    storefile.open(QIODevice ::ReadOnly);

    tmp = recv.readLine();

    while(!tmp.isEmpty())
    {
        s = tmp.split(',');

        m.setMedicineName(s[0]);
        m.setConsumeDate(s[1]);
        m.setNumber(s[2].toInt());

        this->MedicineStore.insert(m);

        tmp = recv.readLine();
    }
    storefile.close();
}

void Pharmacy::UpdatePatientBasket()
{
    QString FileName = this->Name;
    FileName.append("ExpectationFile.txt");
    QFile pharmacyfile(FileName);
    QTextStream  recv(&pharmacyfile);
    QString tmp;

    pharmacyfile.open(QIODevice ::ReadOnly);

    tmp = recv.readLine();

    while(!tmp.isEmpty())
    {
        this->FillPatientBasket(tmp);
        tmp = recv.readLine();
    }

    pharmacyfile.close();
}

bool Pharmacy::Exists()
{
    QFile  pharmacyfile("Pharmacyfile.txt");
    QTextStream fin(&pharmacyfile);
    QString tmp;

    pharmacyfile.open(QIODevice ::ReadOnly);

    tmp = fin.readLine();

    while(!tmp.isEmpty())
    {
        if(tmp == this->Name)
        {
            return true;
        }
        tmp = fin.readLine();
    }

    return false;

}

void Pharmacy::LoadOwnerUserPass()
{
    QFile Userfile("pd_user_pass.txt");
    QTextStream  fin(&Userfile);
    QString tmp;
    QStringList s;

    Userfile.open(QIODevice ::ReadOnly);

    tmp = fin.readLine();

    while(!tmp.isEmpty())
    {
        if(tmp == this->Name)
        {
            break;
        }

        tmp = fin.readLine();
    }

    for(int i = 0 ; i < 2 ; i++)
    {
        s.push_back(fin.readLine());
    }

    this->OwnerUserName = s[0];
    this->OwnerPassword = s[1];
    fin >> tmp;
    this->OwnerName = tmp;

    Userfile.close();
}

void Pharmacy::LoadPharmacyInfo()
{
    QFile  pharmacyfile("Pharmacyfile.txt");
    QTextStream  fin(&pharmacyfile);
    QString tmp;

    pharmacyfile.open(QIODevice ::ReadOnly);

    tmp = fin.readLine();

    while(tmp != this->Name)
    {
        tmp = fin.readLine();
    }
    tmp = fin.readLine();
    this->Address = tmp;

    pharmacyfile.close();
}

void Pharmacy::AddToStore(Medicine &m)
{
    this->MedicineStore.insert(m);
}

bool Pharmacy::RemoveFromStore(Medicine &m)
{
    if(!MedicineStore.contains(m))
    {
        return false;
    }

    return this->MedicineStore.remove(m);
}

void Pharmacy::ShowPatientMedicines(QString patientname)
{
    QList<QString> medicinelist = PatientBasket[patientname];
    QList<QString> ::iterator litr;

    cout << "-----------------Your Medicines----------------" << endl;
    for(litr = medicinelist.begin() ; litr != medicinelist.end() ; litr++)
    {
        cout << litr->toStdString() << endl;
    }
    cout << "----------------------End----------------------" << endl;
}

void Pharmacy::ShowMedicineStore()
{
    QSet<Medicine> ::iterator sitr;

    if(MedicineStore.isEmpty())
    {
        cout << "Your Medicine store is empty..." << endl;
        return;
    }
    for(sitr = this->MedicineStore.begin() ; sitr != MedicineStore.end() ; sitr++)
    {
        cout << *sitr << endl;
    }
}

void Pharmacy::RemoveFromStoreByName(QString medicinename)
{
    QSet<Medicine> ::iterator sitr;

    for(sitr = this->MedicineStore.begin() ; sitr != MedicineStore.end() ; sitr++)
    {

        if(sitr->getMedicineName() == medicinename)
        {
            MedicineStore.erase(sitr);
        }
    }
    this->SaveStoreInFile();
}

void Pharmacy::ShowExpectationList()
{
    QMap<QString,QList<QString>> ::iterator mitr;
    QList<QString> :: iterator litr;
    QList<QString> tmplist;

    cout << "----------------------Expectation List----------------------" << endl;

    for(mitr = PatientBasket.begin() ; mitr != PatientBasket.end() ; mitr++)
    {
        tmplist = mitr.value();

        cout << mitr.key().toStdString() << " : ";

        for(litr = tmplist.begin() ; litr != tmplist.end() ; litr++)
        {
            cout << litr->toStdString() << ' ';
        }
        cout << endl;
    }
    cout << "---------------------------End------------------------------" << endl;
}

void Pharmacy::ClearAllExpectationList()
{
    this->PatientBasket.clear();
}

void Pharmacy::PrintPharmacy()
{
    cout << "-----------------------Pharmacy information----------------" << endl;
    cout << "Pharmacy Name : " << this->Name.toStdString() << endl;
    cout << "Pharmacy address : " << this->Address.toStdString() << endl;
    cout << "Owner name : " << this->OwnerName.toStdString() << endl;
    cout << "Owner Username : " << this->OwnerUserName.toStdString() << endl;
    cout << "Owner Password : " << this->OwnerPassword.toStdString() << endl;
    cout << "---------------------------End----------------------------" << endl;
}
