#include "patient.h"

patient::patient() : pCode(0) , next(nullptr)
{}

patient::patient(QString userName) : User(userName)
{}

void patient::setPvt(QList<PatientVisitTime> &vt)
{
    this->SelectedTimes = vt;
}

QList<PatientVisitTime> patient::getPvt()
{
    return this->SelectedTimes;
}

int patient::getPcode()
{return pCode;}


void patient::setPcode(int pc)
{
    if(pc > 0)
    {
        pCode = pc;
    }
}

void patient::setAssuranceNoteBook(Assurance &anb)
{
    this->AssuranceNoteBook = anb;
}

Assurance patient::getAssuranceNoteBook()
{
    return this->AssuranceNoteBook;
}

void patient::SaveSelectedTimesInDataBase()
{
    QString tn = this->getUserName() + "SelectedHours";
    QList<PatientVisitTime> ::iterator vitr;

    for(vitr = this->SelectedTimes.begin() ; vitr != SelectedTimes.end() ; vitr++)
    {
        QStringList sv;

        sv.push_back(vitr->getVisitingDoctor());
        sv.push_back(vitr->getStartTime());
        sv.push_back(vitr->getEndTime());
        sv.push_back(vitr->getTargetHospital());
        sv.push_back(vitr->getHospitalAddress());
        sv.push_back(vitr->getHospitalPhone());
        sv.push_back(vitr->getSectionName());

        this->ConnectionTool.INSERTRow(tn,sv);
    }

}

void patient::LoadSelectedTimesInDataBase()
{
    QString tn = this->getUserName() + "SelectedHours";
    PatientVisitTime pvt;

    this->ConnectionTool.SELECTAll(tn);

    while(ConnectionTool.NextRow())
    {
        pvt.setVisitingDoctor(ConnectionTool.Value("DoctorName").toString());
        pvt.setTargetHospital(ConnectionTool.Value("HospitalName").toString());
        pvt.setDate(ConnectionTool.Value("Date").toString());
        pvt.setStartTime(ConnectionTool.Value("StartTime").toString());
        pvt.setEndTime(ConnectionTool.Value("EndTime").toString());
        pvt.setHospitalAddress(ConnectionTool.Value("HospitalAddress").toString());
        pvt.setHospitalPhone(ConnectionTool.Value("HospitalPhone").toString());
        pvt.setSectionName(ConnectionTool.Value("Section").toString());

        this->SelectedTimes.push_back(pvt);
    }
}

void patient::PrintSelectedHours()
{
    QList<PatientVisitTime> ::iterator pitr;

    for(pitr = SelectedTimes.begin() ; pitr != SelectedTimes.end(); pitr++)
    {
        cout << *pitr ;
    }
}


void patient::PrintPatient(QString hn, QString dn)
{
    cout << "------------------Patient Reciept---------------" << endl;
    cout << "Patient Name :" << this->getName().toStdString() << endl;
    cout << "Doctorname : " << dn.toStdString() << endl;
    cout << "Hospitalname : " << hn.toStdString() << endl;



    cout << "Pcode is :" << pCode << endl;
    cout << "====================End=========================" << endl;
}

void patient::AddPrescription(Prescription p)
{
    this->AssuranceNoteBook.setVisitSheet(p);
}

void patient::SaveMedicinesInFile()
{
    //          implementing method with DB in future...    //

//    QString  fileName = this->getName();

//    fileName.append(".txt");

//    this->SavePatientInfoInFile(fileName);
//    this->AssuranceNoteBook.getVisitSheet().SaveMedicineInFile(fileName);
}

void patient::AddtoSelectedTimes(PatientVisitTime &vt)
{
    this->SelectedTimes.push_back(vt);
}

bool patient::RemoveFromSelectedTimes(PatientVisitTime &vt)
{
    return this->SelectedTimes.removeOne(vt);
}

void patient::SaveSelectedHoursInDataBase()
{
    QList<PatientVisitTime> ::iterator pitr;
    QString tn = this->getUserName() + "SelectedHours";

    for(pitr = this->SelectedTimes.begin() ; pitr != SelectedTimes.end() ; pitr++)
    {
        QStringList sv;

        sv.push_back(pitr->getVisitingDoctor());
        sv.push_back(pitr->getStartTime());
        sv.push_back(pitr->getEndTime());
        sv.push_back(pitr->getDate());
        sv.push_back(pitr->getTargetHospital());
        this->ConnectionTool.INSERTRow(tn,sv);
    }
}

void patient::LoadSelectedHoursFromDataBase()
{
    QString tn = this->getUserName() + "SelectedHours";

    this->ConnectionTool.SELECTAll(tn);
    while(ConnectionTool.NextRow())
    {
        PatientVisitTime pvt;

        pvt.setVisitingDoctor(ConnectionTool.Value("DoctorName").toString());
        pvt.setStartTime(ConnectionTool.Value("StartTime").toString());
        pvt.setEndTime(ConnectionTool.Value("EndTime").toString());
        pvt.setDate(ConnectionTool.Value("Date").toString());
        pvt.setTargetHospital(ConnectionTool.Value("HospitalName").toString());
        this->SelectedTimes.push_back(pvt);
    }

}

bool patient::RegisterUser()
{
    QStringList patientinfo;

    patientinfo.push_back(this->getName());
    patientinfo.push_back(this->getUserName());
    patientinfo.push_back(this->getPassword());
    patientinfo.push_back(this->getPhone());
    return this->ConnectionTool.INSERTRow("PatientsInfo",patientinfo);
}

bool patient::Exists()
{
    //    this->setID(2);
    return this->ConnectionTool.exists("*","PatientsInfo","UserName = '"
                                       + this->getUserName() + "'");
}


void patient::ReceiveUserFromDataBase()
{
    QSqlQuery select;

    this->ConnectionTool.SELECTRow("PatientsInfo","UserName = "
                                   + this->getUserName());

    select = this->ConnectionTool.getQueryTool();
    select.next();

    this->setName(select.value("Name").toString());
    this->setUserName(select.value("UserName").toString());
    this->setPassword(select.value("Password").toString());
    this->setPhone(select.value("Phone").toString());
    this->setID(2);
}

bool patient::EditInformation(User *NewUser)
{
    QString sv = NewUser->getName() + ","
            + NewUser->getUserName() + ","
            + NewUser->getPassword() + ","
            + NewUser->getPhone();
    return this->ConnectionTool.UPDATERow("PatientsInfo" , sv,"UserName = "
                                          + this->getUserName());
}

//ostream &operator <<(ostream &output, patient &target)
//{
//    output << target.getName().toStdString() << ' ';
//    output << target.get_visit_time().start_time.toStdString() << ' ';
//    output << target.get_visit_time().end_time.toStdString() << endl;

//    return output;
//}
