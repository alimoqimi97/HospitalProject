#include "hospital.h"
#include "doctor.h"
#include "user.h"
#include "pharmacy.h"
#include <iostream>
#include <QTextStream>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QCoreApplication>
using namespace std;

QTextStream qin(stdin);
extern QTextStream qout;

void CreateMySqlConnection(QString connectname,QString databasename)
{
    QSqlDatabase HosConnect = QSqlDatabase ::addDatabase("QMYSQL",connectname);

    HosConnect.setDatabaseName(databasename);
    HosConnect.setHostName("localhost");
    HosConnect.setUserName("root");
    HosConnect.setPassword("Ali@real@sharif@2223");
}

void RemoveMySQLConnection(QString connectname)
{
    QSqlDatabase ::removeDatabase(connectname);
}

bool CreateOwnersInfoTable(QSqlQuery & maketable)
{
    QSqlDatabase toMySql = QSqlDatabase ::database("HosConnect");

    if(!toMySql.open())
    {
        return false;
    }

    bool state = maketable.exec("CREATE TABLE OwnersInfo ( Name varchar(20) , UserName varchar(20) ,"
                                "HospitalName varchar(20) , Password varchar(20) , Phone varchar(20));");
    toMySql.close();

    return state;
}

bool CreateDoctorsInfoTable(QSqlQuery & maketable)
{
    QSqlDatabase todriver = QSqlDatabase ::database("HosConnect");

    if(!todriver.open())
    {
        return false;
    }

    bool state = maketable.exec("CREATE TABLE DoctorsInfo (Name varchar(20) , UserName varchar(20) ,"
                                "Password varchar(20) , WorkPlace varchar(20) , Phone varchar(11));");
    todriver.close();
    return state;
}

bool CreateHospitalsInfoTable(QSqlQuery & maketable)
{
    QSqlDatabase tomysql = QSqlDatabase ::database("HosConnect");

    if(!tomysql.open())
    {
        return false;
    }

    bool state = maketable.exec("CREATE TABLE HospitalsInfo ( Name varchar(20) , Address varchar(20) , Phone varchar(11),"
                                "OwnerName varchar(20));");
    tomysql.close();

    return state;
}

bool CreatePatientsInfoTable(QSqlQuery & maketable)
{
    QSqlDatabase tomysql = QSqlDatabase ::database("HosConnect");

    if(!tomysql.open())
    {
        return false;
    }

    bool state = maketable.exec("CREATE TABLE PatientsInfo ( Name varchar(20) ,"
                                "UserName varchar(20) , Password varchar(20) ,"
                                "Phone varchar(11));");
    tomysql.close();

    return state;
}

bool CreateAllUsersTable()
{
    QSqlDatabase  todriver = QSqlDatabase ::database("HosConnect");
    QSqlQuery  build(todriver);
    QStringList  tablesname = todriver.tables();

    if(tablesname.contains("ownersinfo"))
    {
        return false;
    }

    if(!todriver.open())
    {
        cout << "The MySQL connection failed..." << endl;
        cout << todriver.lastError().text().toStdString() << endl;
        return false;
    }

    if(!CreateOwnersInfoTable(build))
    {
        cout << "The OwnersInfo table creation failed..." << endl;
        return false;
    }

    if(!CreateDoctorsInfoTable(build))
    {
        cout << "The DoctorsInfo table creation failed..." << endl;
        return false;
    }

    if(!CreateHospitalsInfoTable(build))
    {
        cout << "The HospitalsInfo table creation failed..." << endl;
        return false;
    }

    if(!CreatePatientsInfoTable(build))
    {
        cout << "The PatientsInfo table creation failed..." << endl;
        return false;
    }

    todriver.close();

    return true;
}

bool CreateHospitalDoctorsTable(QString hospitalname)
{
    QSqlDatabase todriver = QSqlDatabase ::database("HosConnect");
    QSqlQuery create(todriver);
    bool state;

    if(!todriver.open())
    {
        return false;
    }

    hospitalname.append("Doctors");

    create.prepare("CREATE TABLE :tn ( Name varchar(20) , Phone varchar(10) "
                   "Section varchar(20) , UserName varchar(20));");

    create.bindValue(":tn",hospitalname);

    state = create.exec();

    todriver.close();

    return state;
}

bool CreateDoctorWorkHoursTable(QString doctorname)
{
    QSqlDatabase tomysql = QSqlDatabase ::database("HosConnect");
    QSqlQuery  create(tomysql);
    bool state;

    if(!tomysql.open())
    {
        return false;
    }

    doctorname.append("VisitWorkHours");

    create.prepare("CREATE TABLE :tn (Date varchar(10) , StartTime int ,"
                   "EndTime int , Status bool);");
    create.bindValue(":tn",doctorname);

    state = create.exec();

    tomysql.close();
    return state;
}

bool CreatePatientSelectedHoursTable(QString patientname)
{
    QSqlDatabase tomysql = QSqlDatabase ::database("HosConnect");
    QSqlQuery create(tomysql);
    bool state;

    if(!tomysql.open())
    {
        return false;
    }

    patientname.append("SelectedHours");

    create.prepare("CREATE TABLE :tn (DoctorName varchar(20) , StartTime int ,"
                   "EndTime int , Date varchar(10) , HospitalName varchar(20)"
                   ", HospitalAddress varchar(30) , HospitalPhone varchar(13),"
                   "Section varchar(10));");

    create.bindValue(":tn",patientname);

    state = create.exec();
    tomysql.close();

    return state;
}

bool CreateDoctorVisitListTable(QString doctorname)
{
    QSqlDatabase tomysql = QSqlDatabase ::database("HosConnect");
    QSqlQuery create(tomysql);
    bool state;

    if(!tomysql.open())
    {
        return false;
    }

    doctorname.append("VisitList");

    create.prepare("CREATE TABLE :tn ( PatientName varchar(20) , StartTime int ,"
                   "EndTime int , PatientPhone varchar(11) , Date varchar(8));");
    create.bindValue(":tn",doctorname);

    state = create.exec();

    tomysql.close();
    return state;
}



bool ExistsInTable(User * u)
{
    return u->Exists();
}

User * CheckUser(QString userName)
{       
    User * U = new doctor(userName);

    if(ExistsInTable(U))
    {
        U->setID(1);
        return U;
    }

    U = new patient(userName);

    if(ExistsInTable(U))
    {
        U->setID(2);
        return U;
    }

    U = new Manager(userName);

    if(ExistsInTable(U))
    {
        U->setID(3);
        return U;
    }

    return 0;
}


void PrintAllPharmacies()
{
    QFile  pharmacyfile("pharmacyfile.txt");
    QTextStream  fin(&pharmacyfile);
    QString tmp;

    pharmacyfile.open(QIODevice ::ReadOnly);

    tmp  = fin.readLine();

    cout << "----------------Pharmacy file------------" << endl;

    while(!tmp.isEmpty())
    {
        cout << tmp.toStdString() << endl;
        tmp = fin.readLine();
    }
    cout << "-------------------End-------------------" << endl;

    pharmacyfile.close();
}


void PrintNamesOfAllHospitals()
{
    QSqlDatabase todriver = QSqlDatabase ::database("HosConnect");
    QSqlQuery  qprint(todriver);

    if(!todriver.open())
    {
        cout << "Connection to MySQL failed..." << endl;
        return ;
    }

    qprint.exec("SELECT Name FROM HospitalsInfo ;");

    todriver.close();

    cout << "------------HospitalsName------------" << endl;

    while(qprint.next())
    {
        qout << qprint.value("Name").toString() << endl;
    }

    cout << "------------------End-----------------" << endl;
}

//ostream & tab(ostream& output)
//{
//    return output << '\t';
//}

int main(int argc,char * argv[])
{
//    QCoreApplication a(argc,argv);

    QString  psk;
    hospital  hos;
    QString  sign;
    User * logger;
    Pharmacy phar;

    CreateMySqlConnection("HosConnect","Hospitals");
    CreateAllUsersTable();

    cout << "Welcome to the electornic system of hospitals" << endl;

    while(true)
    {
        int id = 0;

        cout << "Please enter your Username." << endl;
        cout << "Enter register to register." << endl;
        cout << "Enter exit to exit." << endl;
        qin >> psk;

        logger = CheckUser(psk);


        if(psk == "exit")
        {
            cout << "Thanks." << endl;
            return 0;
        }

        if(psk == "register")
        {
            QString  username , name , pass;
            QString  phone;

            cout << "Your username : ";
            qin >> username;

            logger = CheckUser(username);

            if(logger != 0)
            {
                cout << "Your entered information already exists" << endl;
                delete logger;
                continue;
            }

            cout << "Your Password : ";
            qin >> pass;

            cout << "Name : ";
            qin >> name;

            cout << "Phone : " ;
            qin >> phone;

            cout << "doctor or patient or hospital or pharmacy?" << endl;
            qin >> psk;

            if(psk.toLower() == "doctor")
            {
                doctor D;
                QString wp;

                D.setUserName(username);
                D.setPassword(pass);
                D.setName(name);


                cout << "Your workplace : " << endl;
                qin >> wp;
                D.setWorkPlace(wp);
                D.RegisterUser();
                CreateDoctorWorkHoursTable(D.getName());
                CreateDoctorVisitListTable(D.getName());
            }
            else if(psk.toLower() == "patient")
            {
                patient pat;

                pat.setName(name);
                pat.setUserName(username);
                pat.setPassword(pass);
                pat.setPhone(phone);

                pat.RegisterUser();
                CreatePatientSelectedHoursTable(pat.getName());
            }
            else if(psk.toLower() == "hospital")
            {
                QString hinfo;
                Manager m;

                m.setName(name);
                m.setUserName(username);
                m.setPassword(pass);

                cout << "Hospital name : ";
                qin >> hinfo;
                m.setOrgName(hinfo);

                m.RegisterUser();
                CreateHospitalDoctorsTable(m.getOrgName());
            }
            if(psk.toLower() == "pharmacy")
            {
                phar.setOwnerUserName(username);
                phar.setOwnerPassword(pass);
                phar.setOwnerName(name);

                cout << "Your pharmacyname : ";
                qin >> psk;
                phar.setName(psk);

                cout << "Your pharmacy address : ";
                qin >> psk;
                phar.setAddress(psk);

                phar.SaveInPharmaciesFile();
                phar.SaveOwnerUserPassInFile();
            }

            cout << "Registration was successful. Please enter again." << endl;
            continue;
        }

        if(logger == 0)
        {
            cout << "Username not found...!" << endl;
            delete logger;
            continue;
        }

        QString  pass;

        id = logger->getID();

        logger->ReceiveUserFromDataBase();

        cout << "Enter your password " << endl;
        qin >> pass;

        if(logger->getPassword() != pass)
        {
            cout << "Wrong Password...!" << endl;
            continue;
        }

        if(id  == 1)
        {
            doctor * d = (doctor * )logger;
            QString  lower;

            cout << "Hello " << d->getName().toStdString() << endl;

            //              Menu            //

            cout << "see patient list = see" << endl;
            cout << "PrescribeMedicine = prescribe" << endl;
            cout << "SendPatientToPharmacy = sendtopharmacy" << endl;

            //              ----            //

            qin >> psk;
            lower = psk.toLower();

            if(lower == "see")
            {
                //          receiving doctor patientsList from DB...    //
                d->PrintVisitList();
            }
            else if(lower == "prescribe")
            {
                patient pat;
                Prescription pres;
                int medicinenumber = 0;

                cout << "Patient name : " ;
                qin >> psk;
                pat.setName(psk);

                cout << "Number of medicines = ";
                cin >> medicinenumber;

                for(int i = 0 ; i < medicinenumber ; i++)
                {
                    cout << "Medicine name : ";
                    qin >> psk;
                    pres.AddtoMedicineList(psk);
                    pat.AddPrescription(pres);
                }
                pat.SaveMedicinesInFile();
            }
            else if(lower == "sendtopharmacy")
            {
                PrintAllPharmacies();
                cout << "Select your pharmacy : " << endl;
                qin >> psk;
                phar.setName(psk);

                d->PrintVisitList();
                cout << "Select patient : ";
                qin >> psk;
                phar.AddToExpectationFile(psk);
            }

        }
        else if(id == 2)
        {
            patient * p = (patient *)logger ;
            QString lower;

            cout << "Welcome " << p->getName().toStdString() << endl;
            cout << "visit = take visit time." << endl;
            cout << "TakeMedicine" << endl;
            cout << "SeePrescriptedMedicines" << endl;
            cout << "rate = rate the doctor." << endl;
            qin >> psk;

            lower = psk.toLower();

            if(lower == "visit")
            {
                QString  info1,info2;
                PatientVisitTime  pvt;

                PrintNamesOfAllHospitals();

                cout << "Select your hospital :" << endl;
                qin >> info1;
                pvt.setTargetHospital(info1);
                hos.setHospitalName(info1);

                //         get general informations of hospital        //
                hos.ReceiveHospitalFromDatabase();

                pvt.setHospitalAddress(hos.getHospitalAddress());
                pvt.setHospitalPhone(hos.getPhone());

                //          get hospital doctors informations       //
                hos.ReceiveHospitalDoctorsFromDB();

                hos.PrintAllSections();
                cout << "Select your section :" << endl;
                qin >> info1;
                pvt.setSectionName(info1);

                hos.PrintASectionDoctors(info1);
                cout << "Choose your doctor :" << endl;
                qin >> info1;
                pvt.setVisitingDoctor(info1);

//                hos.PrintADoctorWorkHours(info1);

                cout << "StartTime : ";
                qin >> info1;
                pvt.setStartTime(info1);

                cout << "End time : " << endl;
                qin >> info1;
                pvt.setEndTime(info1);

                cout << "Date : " ;
                qin >> info1;
                pvt.setDate(info1);

                p->AddtoSelectedTimes(pvt);
                hos.TakeVisitTime(pvt,p->getName(),p->getPhone());
//                p->PrintLastSelectedTime();




//                PrintNamesOfAllHospitals();

//                cout << "choose your hospital" << endl;
//                qin >> info1;

//                pvt.setTargetHospital(info1);

//                hos.setHospitalName(info1);

//                if(!hos.RecognizeHospital())
//                {
//                    cout << "Your hospital not found!... try again!" << endl;
//                    exit(0);
//                }

////                hos.ReceiveHospitalFromDatabase();

//                hos.ReceiveHospitalDoctorsFromDB();
//                hos.PrintAllSections();

//                cout << "choose your section." << endl;
//                qin >> info2;

//                hos.PrintASectionDoctors(info2);

//                cout << "Choose your doctor " << endl;
//                qin >> info1;
//                pvt.setVisitingDoctor(info1);

//                //          doctor name checking...        //

//                //                    d.set_doctorname(info1);


//                //              for future...               //
//                //                    visit_time  tmpvt;

//                //                    qout << d.get_doctor_visittime() << endl;
//                //                    qin >> tmpvt;
//                //                    d.set_doctor_visit_time(tmpvt);
//                //          --------------------------      //

//                p->AddToPvt(pvt);
//                p->SaveSelectedTimesInDataBase();

//                hos.TakeVisitTime(p,info2,info1);
//                p->PrintPatient(hos.getHospitalName(),info1);

////                pat.print_pa(hos.getHospitalName(),d.get_doctorname());

            }
            else if(lower == "takemedicine")
            {
                cout << "Select your pharmacy." << endl;
                PrintAllPharmacies();
                qin >> psk;

                phar.setName(psk);

                if(!phar.Exists())
                {
                    cout << "Pharmacy not found!..." << endl;
                    break;
                }
                phar.AddToExpectationFile(p->getName());
            }
            else if(lower == "seeprescriptedmedicines")
            {
                phar.ShowPatientMedicines(p->getName());
            }
        }
        else if(id == 3)
        {
            cout << "Hospital Name : ";
            qin >> psk;
            hos.setHospitalName(psk);
            hos.ReceiveHospitalFromDatabase();

            while(true)
            {
                QString lower;

                cout << "Type  a  to add hopital." << endl;
                cout << "Type  sh  to see hospital information." << endl;
                cout << "Type  ssd  to see All doctor of a section." << endl;
                cout << "Type  sas  to see all sectionsName." << endl;
                cout << "AddDoctor" << endl;
                cout << "AddDoctor to a section" << endl;

                cout << "Type  ex  to exit." << endl;
                qin >> psk;


                if(lower == "sh")
                {
                    if(!hos.RecognizeHospital())
                    {
                        cout << "Hospital Not Found...!" << endl;
                        continue;
                    }

                    hos.PrintHospital();
                }
                if(lower == "a")
                {

                    cout << "newhospital = add new hospital." << endl;
                    qin >> psk;

                    if(psk == "newhospital")
                    {
                        int  sectionsNumber = 0;

                        cout << "Hospital name : " << endl;
                        qin >> psk;
                        hos.setHospitalName(psk);

                        cout << "Hospital address : " << endl;
                        qin >> psk;
                        hos.setHospitalAddress(psk);

                        cout << "Hospital phone : " << endl;
                        qin >> psk;
                        hos.setPhone(psk);

                        cout << "Number of sections = ";
                        cin >> sectionsNumber;

                        for(int i = 0 ; i < sectionsNumber ; i++)
                        {
                            QList<doctor>  tmplist;
                            QString  sectionName;

                            cout << "Section Name : " ;
                            qin >> sectionName;

                            while(true)
                            {
                                doctor tmpdct;

                                qin >> tmpdct;

                                tmplist.push_back(tmpdct);

                                cout << "Do you want to continue?" << endl;
                                qin >> psk;

                                if(psk.toLower() == "yes")
                                {
                                    continue;
                                }
                                else if(psk.toLower() == "no")
                                {
                                    hos.AddDoctor(sectionName,tmplist);
                                    break;
                                }
                                else
                                {
                                    cout << "Unknown command...!" << endl;
                                    break;
                                }
                            }
                        }

                    }

                    hos.RegisterHospital();
                    hos.SaveHospitalDoctorsInDataBase();
//                    hos.FillHopsitalNamesFile();

//                    hos.SaveDoctorsInFile();

//                    hos.fill_hospital_file();
                }
                if(lower == "ssd")
                {
                    cout << "Section Name : " ;
                    qin >> psk;

                    hos.PrintASectionDoctors(psk);
                }
                if(lower == "sas")
                {
                    hos.PrintAllSections();
                }
                else if(lower == "ex")
                {
                    cout << "Thanks for your choice...!" << endl;
                    break;
                }
            }
        }
        else if(sign == "phar")
        {
            QString lower;

            cout << "Pharmacy name : " ;
            qin >> psk;
            phar.setName(psk);

            phar.LoadPharmacyInfo();
            phar.LoadOwnerUserPass();
            phar.LoadStore();

            cout << "--------------------Pharmacy Menu------------------" << endl;
            cout << "Welcome " << phar.getOwnerName().toStdString() << endl;
            cout << "SeeStore = see store" << endl;
            cout << "AddToStore = add to store" << endl;
            cout << "RemoveFromStore = removing medicine from store" << endl;
            cout << "SeeExpectationList = see expectation list" << endl;
            cout << "ClearExpectationList = clear all patients from expectation list" << endl;
            cout << "SeeAPatientMedicines = see a special patient medicine" << endl;
            cout << "RemoveFromExpectationList = remove patient from expectation list." << endl;
            cout << "SeePharmacyInfo = see pharmacy name and address" << endl;
            cout << "Back = return" << endl;
            cout << "-------------------------End-----------------------" << endl;
            qin >> psk;

            if(lower == "back")
            {
                continue;
            }
            else if(lower == "seestore")
            {
                phar.ShowMedicineStore();
            }
            else if(lower == "seepharmacyinfo")
            {
                phar.PrintPharmacy();
            }
            else if(lower == "removefromexpectationlist")
            {
                cout << "Enter patient name : ";
                qin >> psk;

                phar.RemoveFromPatientBasket(psk);
            }
            else if(lower == "addtostore")
            {
                Medicine m;
                int num = 0;

                cout << "Medicine Name : " ;
                qin >> psk;
                m.setMedicineName(psk);

                cout << "Medicine ConsumeDate : ";
                qin >> psk;
                m.setConsumeDate(psk);

                cout << "Number = ";
                cin >> num;
                m.setNumber(num);

                phar.AddToStore(m);
            }
            else if(lower == "removefromstore")
            {
                cout << "Enter MedicineName : " ;
                qin >> psk;
                phar.RemoveFromStoreByName(psk);
            }
            else if(lower == "seeexpectationlist")
            {
                phar.UpdatePatientBasket();
                phar.ShowExpectationList();
            }
            else if(lower == "seeaspecialpatientmedicine")
            {
                cout << "Enter patient name : ";
                qin >> psk;

                phar.ShowPatientMedicines(psk);
            }
            else if(lower == "clearexpectationlist")
            {
                phar.ClearAllExpectationList();
            }
            else if(lower == "seeapatientmedicines")
            {
                cout << "Patient name : " ;
                qin >> psk;

                phar.UpdatePatientBasket();
                phar.ShowPatientMedicines(psk);
            }
            else
            {
                cout << "Unknown command." << endl;
            }
        }
        else
        {
            cout << "Your input expression is used before.Please change it." << endl;
            continue;
        }
    }
    RemoveMySQLConnection("HosConnect");
}
