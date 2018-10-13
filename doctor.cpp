#include "doctor.h"

extern QTextStream qin;

//doctor::doctor(doctor & other) : User()
//{
//    *this = other;
//}

doctor::doctor(QString userName) : User(userName)
{}

doctor::doctor() :User() , doctor_rank(0)
{}

void doctor::setSpecialization(QString s)
{
    this->Specialization = s;
}

QString doctor::getSpecialization()
{
    return this->Specialization;
}

void doctor::setWorkHours(QList<visit_time> wh)
{
    this->WorkHours = wh;
}

QList<visit_time> doctor::getWorkHours()
{
    return this->WorkHours;
}

void doctor::setVisitList(QList<DoctorVisitTime> &vl)
{
    this->VisitList = vl;
}

QList<DoctorVisitTime> doctor::getVisitList()
{
    return this->VisitList;
}

void doctor::setWorkPlace(QString workplace)
{
    this->WorkPlace = workplace;
}

QString doctor::getWorkPlace()
{
    return this->WorkPlace;
}

void doctor::SaveVisitListInDataBase()
{
    QList<DoctorVisitTime> ::iterator ditr;
    QString tn = this->getUserName() + "VisitList";

    for(ditr = VisitList.begin() ; ditr != VisitList.end() ; ditr++)
    {
        QStringList sv;

        sv.push_back(ditr->getPatientName());
        sv.push_back(ditr->getStartTime());
        sv.push_back(ditr->getEndTime());
        sv.push_back(ditr->getPatientPhone());
        sv.push_back(ditr->getDate());
        this->ConnectionTool.INSERTRow(tn,sv);
    }
}

void doctor::LoadVisitListFromDataBase()
{
    QString tn = this->getUserName() + "VisitList";

    this->ConnectionTool.SELECTAll(tn);
    while(ConnectionTool.NextRow())
    {
        DoctorVisitTime dvt;

        dvt.setPatientName(ConnectionTool.Value("PatientName").toString());
        dvt.setPatientPhone(ConnectionTool.Value("PatientPhone").toString());
        dvt.setStartTime(ConnectionTool.Value("StartTime").toString());
        dvt.setEndTime(ConnectionTool.Value("EndTime").toString());
        dvt.setStatus(FULL);
        this->VisitList.push_back(dvt);
    }
}

void doctor::AddToVisitList(DoctorVisitTime dvt)
{
    this->VisitList.push_back(dvt);
}

bool doctor::RemoveFromVisitList(DoctorVisitTime &dvt)
{
    return this->VisitList.removeOne(dvt);
}

void doctor::AddToWorkHours(visit_time &vt)
{
    this->WorkHours.push_back(vt);
}

bool doctor::RemoveFromWorkHours(visit_time &vt)
{
    return this->WorkHours.removeOne(vt);
}

//void doctor::setDoctorVisitTime(visit_time &t)
//{
//    dvt.start_time = t.start_time;
//    dvt.end_time = t.end_time;
//    dvt.ts = EMPTY;
//}



//void doctor::EnterVisitTime(patient & pa)
//{
//    dvt.ts = FULL;

//    pa.set_visit_time(dvt);
//    this->patient_ll.pushBack(pa);
//    this->givePcode(pa);
//}

//void doctor::save_patient_name_in_pll(string pname)
//{
//    patient_ll.add_patient(pname);
//}

void doctor::givePcode(patient &pati)
{
    int temp;

    srand(10000);
    temp = rand() %  1000 + 1;

    pati.setPcode(temp);
}

//void doctor::SavePatientListInDatabase()
//{
//    patient * p = this->patient_ll.first;
//    QString tn = this->getUserName() + "PatientList";

//    while(p != nullptr)
//    {
//        QStringList patientinfo;

//        patientinfo.push_back(p->getName());
//        patientinfo.push_back(p->get_visit_time().start_time);
//        patientinfo.push_back(p->get_visit_time().end_time);
//        patientinfo.push_back(p->getPhone());
//        this->ConnectionTool.INSERTRow(tn,patientinfo);
//        p = p->next;
//    }

//}

//void doctor::ReceivePatientListFromDatabase()
//{
//    QString tn = this->getUserName() + "PatientsList";
//    DoctorVisitTime dv;
//    this->ConnectionTool.SELECTAll(tn);

//    while(this->ConnectionTool.NextRow())
//    {
//        dv.setPatientName(ConnectionTool.Value("PatientName").toString());
//        dv.setPatientPhone(ConnectionTool.Value("PatientPhone").toString());
//        dv.setDate(ConnectionTool.Value("Date").toString());
//        dv.setStartTime(ConnectionTool.Value("StartTime").toString());
//        dv.setEndTime(ConnectionTool.Value("EndTime").toString());
//        dv.setStatus(FULL);

//        this->VisitList.push_back(dv);
//    }
//}

void doctor::SaveDoctorWorkHoursInDataBase()
{
    QString  tn = this->getUserName() + "WorkHours";
    QList<DoctorVisitTime> ::iterator  litr;

    for(litr = this->VisitList.begin() ; litr != VisitList.end() ; litr++)
    {
        QStringList vlist;

        vlist.push_back(litr->getDate());
        vlist.push_back(litr->getStartTime());
        vlist.push_back(litr->getEndTime());
        if(litr->getStatus() == true)
        {
            vlist.push_back("true");
        }
        else
        {
            vlist.push_back("false");
        }
        this->ConnectionTool.INSERTRow(tn,vlist);
    }
}

void doctor::LoadDoctorWorkHoursFromDataBase()
{
    QString tn = this->getUserName() + "WorkHours";
    visit_time v;

    this->ConnectionTool.SELECTAll(tn);

    while(ConnectionTool.NextRow())
    {
        v.setDate(ConnectionTool.Value("Date").toString());
        v.setStartTime(ConnectionTool.Value("StartTime").toString());
        v.setEndTime(ConnectionTool.Value("EndTime").toString());
        this->WorkHours.push_back(v);
    }
}

void doctor::PrintVisitList()
{
    QList<DoctorVisitTime> ::iterator ditr;

    for(ditr = this->VisitList.begin() ; ditr != this->VisitList.end() ; ditr++)
    {
        cout << *ditr ;
    }
}

void doctor::PrintWorkHours()
{
    QList<visit_time> ::iterator litr;

    for(litr = this->WorkHours.begin() ; litr != WorkHours.end() ; litr++)
    {
        *litr;
    }
}

void doctor::WritePrescription(patient target_p, Prescription pres)
{
    target_p.AddPrescription(pres);
}

bool doctor::RegisterUser()
{
    QStringList doctorinfo;

    doctorinfo.push_back(this->getName());
    doctorinfo.push_back(this->getUserName());
    doctorinfo.push_back(this->getPassword());
    doctorinfo.push_back(this->getPhone());
    doctorinfo.push_back(this->getWorkPlace());

    return this->ConnectionTool.INSERTRow("DoctorsInfo",doctorinfo);
}

bool doctor::Exists()
{
    return this->ConnectionTool.exists("*","DoctorsInfo","UserName = '" +
                                       this->getUserName() + "'");
}

//bool doctor::Exists()
//{
//    QSqlQuery select ;
//    QString  command = "SELECT UserName FROM DoctorsInfo WHERE UserName LIKE ' ";
//    QString  letter = this->getUserName().at(0);

//    letter.append("%';");

//    command.append(letter);


//    this->ConnectionTool.ArbitraryQuery(command);

//    select = this->ConnectionTool.getQueryTool();

//    if(select.size() == 0)
//    {
//        return false;
//    }

//    while(select.next())
//    {
//        if(this->getUserName() == select.value("UserName").toString())
//        {
//            return true;
//        }
//    }

//    return false;
//}

void doctor::ReceiveUserFromDataBase()
{
    QSqlQuery select ;

    this->ConnectionTool.SELECTRow("DoctorsInfo","UserName = "
                                   + this->getUserName());

    select = this->ConnectionTool.getQueryTool();

    this->setName(select.value("Name").toString());
    this->setUserName(select.value("UserName").toString());
    this->setPassword(select.value("Password").toString());
    this->setPhone(select.value("Phone").toString());
    this->setWorkPlace(select.value("WorkPlace").toString());
    this->setID(1);
}

bool doctor::EditInformation(User *NewUser)
{
    QString settingvalue = NewUser->getName() + ","
            + NewUser->getUserName() + ","
            + NewUser->getPassword() + ","
            + this->getWorkPlace() + ","
            + NewUser->getPhone();

    return ConnectionTool.UPDATERow("DoctorsInfo",settingvalue,
                                    "UserName = " + this->getUserName());
}

//QTextStream &operator <<(QTextStream &output, doctor &target)
//{
//    output << target.get_doctorname() ;
//    output << target.get_doctor_visittime().start_time << " " ;
//    output << target.get_doctor_visittime().end_time << " ";
//    output << target.get_doctor_visittime().ts << endl;

//    return  output;
//}


ostream & operator <<(ostream &dout, doctor &target)
{
    dout << target.getName().toStdString();

    target.PrintWorkHours();

    return  dout;
}


ofstream &operator <<(ofstream &fout, doctor &d)
{
    fout << d.getName().toStdString() << ",";
//    fout << d.getDoctorVisitTime().start_time.toStdString() << ",";
//    fout << d.getDoctorVisitTime().end_time.toStdString() << endl;

    return fout;
}


QTextStream &operator <<(QTextStream &qout, doctor &target)
{
    qout  << target.getName() ;

    target.PrintVisitList();
//    qout << '(' << target.getDoctorVisitTime().start_time << ',';
//    qout << target.getDoctorVisitTime().end_time << ')' << endl;

    return qout;
}


QTextStream &operator >>(QTextStream &sin, doctor &target)
{
    QString  dctInfo;
    visit_time  vt;

    cout << "Doctor Name : " ;
    sin >> dctInfo;
    target.setName(dctInfo);

    cout << "Doctor UserName : ";
    sin >> dctInfo;
    target.setName(dctInfo);

    cout << "Doctor Password : ";
    sin >> dctInfo;
    target.setPassword(dctInfo);

//    sin >> vt;
//    target.setDoctorVisitTime(vt);

    return sin;
}
