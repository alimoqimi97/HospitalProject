#include "patientvisittime.h"

PatientVisitTime::PatientVisitTime()
{
}

void PatientVisitTime::setSectionName(QString sectionname)
{
    this->SectionName = sectionname;
}

QString PatientVisitTime::getSectionName()
{
    return this->SectionName;
}

void PatientVisitTime::setHospitalAddress(QString hospitaladdress)
{
    this->HospitalAddress = hospitaladdress;
}

QString PatientVisitTime::getHospitalAddress()
{
    return this->HospitalAddress;
}

void PatientVisitTime::setHospitalPhone(QString phone)
{
    this->HospitalPhone = phone;
}

QString PatientVisitTime::getHospitalPhone()
{
    return this->getHospitalPhone();
}

void PatientVisitTime::setVisitingDoctor(QString vd)
{
    this->VisitingDoctor = vd;
}

QString PatientVisitTime::getVisitingDoctor() const
{
    return this->VisitingDoctor;
}

void PatientVisitTime::setTargetHospital(QString th)
{
    this->TargetHospital = th;
}

QString PatientVisitTime::getTargetHospital() const
{
    return this->TargetHospital;
}

bool PatientVisitTime::operator ==(const PatientVisitTime &other)
{
    if(this->getDate() == other.getDate() && getStartTime() ==other.getStartTime())
    {
        if((this->getEndTime() == other.getEndTime()) && (getStatus() == other.getStatus()))
        {
            if((this->getTargetHospital() == other.getTargetHospital()) && (getVisitingDoctor() == other.getVisitingDoctor()))
            {
                return true;
            }
        }
    }
    return false;
}


ostream & operator <<(ostream &out, PatientVisitTime &vt)
{
    out <<"Date : " << vt.getDate().toStdString() << endl;
    out << "StartTime : " << vt.getStartTime().toStdString() << endl;
    out << "EndTime : " << vt.getEndTime().toStdString() << endl;
    out << "Hospital : " << vt.getTargetHospital().toStdString() << endl;
    out << "Doctor : " << vt.getVisitingDoctor().toStdString() << endl;

    return out;
}
