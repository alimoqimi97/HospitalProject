#ifndef DOCTORVISITTIME_H
#define DOCTORVISITTIME_H
#include "visit_time.h"

class DoctorVisitTime : public visit_time
{
    QString  PatientName;
    QString  PatientPhone;
public:
    DoctorVisitTime();

    //      get and set methods     //
    void setPatientName(QString pn);
    QString  getPatientName() const;

    void setPatientPhone(QString ph);
    QString getPatientPhone();

    //      ------------------      //

    bool operator == (DoctorVisitTime const & other)
    {
        if(this->PatientName == other.getPatientName())
        {
            if(this->PatientPhone == other.PatientPhone)
            {
                if(this->getDate() == other.getDate())
                {
                    if(this->getStartTime() == other.getStartTime())
                    {
                        if(this->getEndTime() == other.getEndTime())
                        {
                            if(this->getStatus() == other.getStatus())
                            {
                                return true;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }
};

ostream &operator << (ostream & vout , DoctorVisitTime & dvt);

#endif // DOCTORVISITTIME_H
