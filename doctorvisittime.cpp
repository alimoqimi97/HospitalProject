#include "doctorvisittime.h"

DoctorVisitTime::DoctorVisitTime()
{
}

void DoctorVisitTime::setPatientName(QString pn)
{
    this->PatientName = pn;
}

QString DoctorVisitTime::getPatientName() const
{
    return this->PatientName;
}

void DoctorVisitTime::setPatientPhone(QString ph)
{
    this->PatientPhone = ph;
}

QString DoctorVisitTime::getPatientPhone()
{
    return this->PatientPhone;
}



ostream &operator <<(ostream &vout, DoctorVisitTime &dvt)
{
    vout <<"PatientName : " << dvt.getPatientName().toStdString() << endl;
    vout << "PatientPhone : " << dvt.getPatientPhone().toStdString() << endl;
    vout << "Date : " << dvt.getDate().toStdString() << endl;
    vout << "Starttime : " << dvt.getStartTime().toStdString() << endl;
    vout << "Endtime : " << dvt.getEndTime().toStdString() << endl;
    vout << "Status : " ;
    if(dvt.getStatus() == FULL)
    {
        vout << "Full" << endl;
    }
    else
    {
        vout << "Empty" << endl;
    }

    return vout;
}
