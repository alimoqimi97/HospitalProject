#ifndef PATIENTVISITTIME_H
#define PATIENTVISITTIME_H
#include "visit_time.h"

class PatientVisitTime : public visit_time
{
private:
    QString VisitingDoctor;
    QString TargetHospital;
    QString HospitalPhone;
    QString HospitalAddress;
    QString SectionName;
public:
    PatientVisitTime();

    //          set and get methods     //

    void setSectionName(QString  sectionname);
    QString getSectionName();

    void setHospitalAddress(QString hospitaladdress);
    QString getHospitalAddress();

    void setHospitalPhone(QString phone);
    QString getHospitalPhone();

    void setVisitingDoctor(QString  vd);
    QString getVisitingDoctor() const;

    void setTargetHospital(QString  th);
    QString getTargetHospital() const;
    //          ------------------      //

    //          public methods          //

    bool operator == (const PatientVisitTime & other);

    //          --------------          //
};

ostream & operator << (ostream & out , PatientVisitTime & vt);

#endif // PATIENTVISITTIME_H
