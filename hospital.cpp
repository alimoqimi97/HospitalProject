#include "hospital.h"

hospital::hospital()
{}

void hospital::setBoss(Manager &boss)
{
    this->Boss = boss;
}

Manager hospital::getBoss()
{
    return this->Boss;
}

void hospital::setDBPort(T_DataBase db)
{
    this->DBPort = db;
}

T_DataBase hospital::getDBPort()
{
    return this->DBPort;
}

void hospital::setPhone(QString phone)
{
    this->Phone = phone;
}

QString hospital::getPhone()
{
    return this->Phone;
}

QTextStream  qout(stdout);

void hospital::AddDoctor(QString secname, QList<doctor> &dl)
{
    this->SectionsList[secname] = dl;
}

void hospital::AddDoctor(QString secname, doctor d)
{
    this->SectionsList[secname].push_back(d);
}

void hospital::AddSection(QString secname)
{
    this->SectionsList[secname];
}

bool hospital::CheckDoctor(QString docname, QString sn)
{
    QList<doctor> ::iterator ditr;
    QList<doctor> dl = this->SectionsList[sn];

    for(ditr = dl.begin() ; ditr != dl.end() ; ditr++)
    {
        if(ditr->getName() == docname)
        {
            return true;
        }
    }
    return false;
}

QList<doctor>::iterator hospital::FindDoctor(QString sn, QString doctorname)
{
    QList<doctor> ::iterator  dBegin,dEnd;
    QList<doctor> ::iterator dit;

    dBegin = SectionsList[sn].begin();
    dEnd = SectionsList[sn].end();

    for(dit = dBegin ; dit != dEnd ; dit++)
    {
        if(dit->getName() == doctorname)
        {
            return dit;
        }
    }

    return  dEnd;
}

doctor hospital::MakeDoctor(QString docline)
{
    QStringList docInfo;
    doctor  d;
    visit_time v;

    docInfo = docline.split(',');
    d.setName(docInfo.at(0));
    v.setStartTime(docInfo.at(1));
    v.setEndTime(docInfo.at(1));

    d.AddToWorkHours(v);

    return d;
}

void hospital::TakeVisitTime(PatientVisitTime &vt, QString patientname, QString patientphone)
{
    DoctorVisitTime dvt;

    dvt.setPatientName(patientname);
    dvt.setPatientPhone(patientphone);
    dvt.setDate(vt.getDate());
    dvt.setStartTime(vt.getStartTime());
    dvt.setEndTime(vt.getEndTime());
    dvt.setStatus(FULL);

    DBPort.SELECTColumnWHERE("DoctorsInfo","UserName","Name = "
                             + vt.getVisitingDoctor());

    doctor d(DBPort.Value("UserName").toString());

    d.AddToVisitList(dvt);
    d.SaveVisitListInDataBase();
}







//void hospital::TakeVisitTime(patient *p, QString sn, QString dn)
//{
//    QList<doctor> ::iterator  target;

//    if(!this->CheckDoctor(dn,sn))
//    {
//        cout << "The doctor not found!..." << endl;
//        return;
//    }

//    target = this->FindDoctor(sn,dn);
//    target->patient_ll.pushBack(*p);
//    pset_visit_time(target->getDoctorVisitTime());
//    p.get_pcode();
//    this->FillVisitTimeFile(dn,*p);
//}


//QString hospital::GetHospitalNameFromFile(QString hpsw)
//{
//    QFile  ufile("pd_user_pass.txt");
//    QTextStream  readFile(&ufile);
//    QString  hpss;

//    ufile.open(QIODevice ::ReadOnly);

//    while(hpss != hpsw)
//    {
//        readFile >> hpss;
//    }

//    for(int i = 0 ; i < 3 ; i++)
//    {
//        hpss = readFile.readLine();
//    }

//    return hpss;
//}

//void hospital::save_boss_user_pass()
//{
//    ofstream  write("pd_user_pass.txt" , ios :: out | ios :: app);
//    string  mark = " H";

//    write << this->boss_username.toStdString() << endl;
//    write << this->boss_password.toStdString() << endl;
//    write << this->boss_name.toStdString() << mark << endl;
//    write << this->Name.toStdString() << endl;
//    write << "------------------------------" << endl;

//    write.close();
//}

//void hospital::save_pd_user_pass()
//{
//    ofstream  write_pd("pd_user_pass.txt" , ios :: out);
//    string  mark = " D";

//    //  emergency :: D1.info    //
//    write_pd << this->emergency.getd1().get_doctorusername();
//    write_pd << this->emergency.getd1().get_doctorname() << mark;
//    //        write_pd << this->emergency.getd1().get_doctor_pass ;

//    //  emergency :: D2.info    //
//    //        write_pd << this->emergency.getd2().get_doctorname() ;
//    //        write_pd << "D" << this->emergency.getd1().get_doctorusername();
//    //        write_pd << this->emergency.getd1().get_doctor_pass;

//    //  heart :: D1.info        //
//    write_pd << this->heart.getd1().get_doctorusername();
//    write_pd << this->heart.getd1().get_doctorname() << mark;
//    //      write_pd << this->heart.getd1().get_doctor_pass;

//    //  aurtopedy :: D1.info    //
//    write_pd << this->aurtopedy.getd1().get_doctorusername();
//    write_pd << this->aurtopedy.getd1().get_doctorname() << mark;
//    //      write_pd << this->aurtopedy.getd1().get_doctor_pass; //

//    //      generic :: D1.info      //
//    write_pd << this->generic.getd1().get_doctorusername();
//    write_pd << this->generic.getd1().get_doctorname() << mark;
//    //      write_pd << this->generic.getd1().get_doctor_pass;  //
//}

bool hospital::RecognizeHospital()
{
    QFile  hfile("h_names.txt");
    QTextStream  h_re(&hfile);
    QString  tmpstr;
    QString  hospitalName = this->Name;

    hfile.open(QIODevice ::ReadOnly);

    tmpstr = h_re.readLine();

    while(!tmpstr.isEmpty())
    {
        if(tmpstr == hospitalName)
        {
            hfile.close();

            return true;
        }

        tmpstr = h_re.readLine();
    }

    hfile.close();

    return false;
}

void hospital::PrintAllSections()
{
    QList<QString>  sectionsname = this->SectionsList.keys();
    QList<QString> ::iterator  litr;

    cout << endl;

    cout << "-----------------Hopital sections---------------" << endl;

    for(litr = sectionsname.begin() ; litr != sectionsname.end() ; litr++)
    {
        cout << litr->toStdString() << endl;
    }

    cout << endl;

    cout << "---------------------End-----------------------" << endl;
}

//void hospital::SaveDoctorsInFile()
//{
//    mitr  mapitr;
//    litr  listitr;

//    if(!this->boss_name.isEmpty())
//    {
//        this->save_boss_user_pass();
//    }

//    for(mapitr = SectionsList.begin() ; mapitr != SectionsList.end() ; mapitr++)
//    {
//        for(listitr = mapitr->begin() ; listitr != mapitr->end() ; listitr++)
//        {
//            listitr->save_doctor_infile();
//        }
//    }

//    ofstream  write("pd_user_pass.txt", ios :: out | ios :: app);

//    write << "-------------------------" << endl;

//    write.close();
//}

bool hospital::RegisterHospital()
{
    QStringList sv;

    sv.push_back(this->Name);
    sv.push_back(this->Address);
    sv.push_back(this->Phone);
    sv.push_back(this->Boss.getName());

    return this->DBPort.INSERTRow("HospitalsInfo",sv);
}

bool hospital::ReceiveHospitalFromDatabase()
{
    bool state;

    state = this->DBPort.SELECTRow("HospitalInfo","Name = " + this->Name);
    DBPort.NextRow();

    this->Address = this->DBPort.Value("Address").toString();
    this->Name = this->DBPort.Value("Name").toString();
    this->Phone = this->DBPort.Value("Phone").toString();
    this->Boss.setName(this->DBPort.Value("OwnerName").toString());

    return state;
}

//void hospital::PrintHospital()
//{
//    mitr  mapitr;
//    litr  listitr;

//    cout << "-------------------Hospital Info------------------------" << endl;
//    cout << this->Name.toStdString() << endl;
//    cout << "Address: " << this->Address.toStdString() << endl;

//    for(mapitr = SectionsList.begin() ; mapitr != SectionsList.end() ; mapitr++)
//    {
//        cout << mapitr.key().toStdString() << ": ";

//        for(listitr = mapitr->begin() ; listitr != mapitr->end() ; listitr++)
//        {
//            cout << *listitr << " ";
//        }
//        cout << endl;
//    }
//    cout << "-------------------------End---------------------------" << endl;
//}

//void hospital::FillHopsitalNamesFile()
//{
//    ofstream  write_h_name;

//    write_h_name.open("h_names.txt",ios :: out | ios :: app);

//    if(!write_h_name)
//    {
//        cout << "The hospitalnames file doesn't opened...!!" << endl;
//        exit(0);
//    }

//    write_h_name << this->Name.toStdString() << endl;

//    write_h_name.close();
//}

//void hospital::fill_hospital_file()
//{
//    ofstream  InFile("hospital_file.txt",ios :: out);
//    QMap<QString,QList<doctor>> ::iterator  mitr;
//    QList<doctor> ::iterator litr;
//    QString  hospitalname = this->Name;

////    hospitalname.append(":");

//    InFile << hospitalname.toStdString() << endl;

//    InFile << this->Address.toStdString() << endl;

//    for(mitr = SectionsList.begin() ; mitr != SectionsList.end() ; mitr++)
//    {
//        QList<doctor>  dl = mitr.value();
//        QString  sectionName = mitr.key();

//        InFile << sectionName.append('{').toStdString() << endl;

//        for(litr = dl.begin() ; litr != dl.end() ; litr++)
//        {
//            InFile << *litr ;
//        }
//        InFile << "}" << endl;
//    }

//    InFile << "#end" << endl;

//    InFile.close();


//    visit_time  vt;
//    doctor  D;
//    ofstream  write;
//    ofstream  write_h_name;
//    list<doctor> ::iterator ITR;


//    this->FillHopsitalNamesFile();

//    write.open("hospital_file.txt" , ios :: out | ios :: app);

//    if(!write)
//    {
//        cout << "The files aren't open." << endl;
//        exit(0);
//    }


//    write << h_name << endl;

//    for(list<section> ::iterator itr = slist.begin() ; itr != slist.end() ; ++itr)
//    {
//        section  s1 = *itr;

//        ITR = s1.dlist.begin();

//        while(ITR != s1.dlist.end())
//        {
//            D = *ITR;
//            vt = D.get_doctor_visittime();

//            write << D.get_doctorname() << " (" << vt.start_time << " " << vt.end_time << ") ";

//            write << " , ";
//            ++ITR;
//        }
//        write << ";" << endl;
//    }

//    write  << emergency.getd1().get_doctorname() ;
//    vt = emergency.getd1().get_doctor_visittime();
//    write <<" " << vt.start_time << " " << vt.end_time ;

//    write << heart.getd1().get_doctorname();
//    vt = heart.getd1().get_doctor_visittime();
//    write <<" " << vt.start_time << " " << vt.end_time;

//    write << aurtopedy.getd1().get_doctorname();
//    vt = aurtopedy.getd1().get_doctor_visittime();
//    write << " " << vt.start_time << " " << vt.end_time;

//    write << generic.getd1().get_doctorname();
//    vt = generic.getd1().get_doctor_visittime();
//    write <<" " << vt.start_time << " " << vt.end_time;

//    write << h_address << " :address" << endl;

    //          Under testing part      //
//    write << "address: " << this->h_address << endl;
    //          ..................      //
//    write << "#end" << endl;

//    write.close();
//    write_h_name.close();
//}

//void hospital::read_hospital_file()
//{
//    ifstream  rf("hospital_file.txt" , ios :: in);
//    string ans;
//    visit_time  v;

//    if(!rf)
//    {
//        cout << "The file in reading action isn't open." << endl;
//    }

//    rf >> h_name;

////    rf >> ans;
//    //      receiving the name and visit time informations  //
//    rf >> ans >> v.start_time >> v.end_time;
//    emergency.getd1().set_doctor_visit_time(v);
//    emergency.getd1().set_doctorname(ans);

////    rf >> ans;
//    rf >> ans >> v.start_time >> v.end_time ;
//    heart.getd1().set_doctor_visit_time(v);
//    heart.getd1().set_doctorname(ans);

////    rf >> ans;
//    rf >> ans >> v.start_time >> v.end_time;
//    aurtopedy.getd1().set_doctor_visit_time(v);
//    aurtopedy.getd1().set_doctorname(ans);

//    rf >> ans >> v.start_time >> v.end_time;
//    generic.getd1().set_doctor_visit_time(v);
//    generic.getd1().set_doctorname(ans);

//    rf >> ans;
//    h_address = ans;

//    rf.close();
//}

//void hospital ::read_hospital_file()
//{
//    QFile  hos_file("hospital_file.txt");
//    QTextStream  fin(&hos_file);
//    QString currenthospitalname = this->Name;
//    QString  htmp,sectionname;
//    doctor d;
//    QList<doctor>  DL;

//    hos_file.open(QIODevice ::ReadOnly);


//    while(htmp != currenthospitalname)
//    {
//        htmp = fin.readLine();
//        if(htmp.isEmpty())
//        {
//            cout << "The hospital file is Empty!..." << endl;
//            return ;
//        }
//    }

//    htmp = fin.readLine();

//    this->Address = htmp;

//    while(!htmp.isEmpty())
//    {

//        htmp = fin.readLine();

//        if(htmp == "#end")
//        {
//            break;
//        }

//        if(htmp.contains("{"))
//        {
//            sectionname = htmp.remove("{");
//            continue;
//        }

//        if(htmp.contains("}"))
//        {
//            this->AddDoctor(sectionname,DL);
//            DL.clear();
//            continue;
//        }

//        d = this->MakeDoctor(htmp);

//        DL.push_back(d);
//    }

//    hos_file.close();

//}


//QString hospital::search_mark(QString psw)
//{
//    QFile   ufile("pd_user_pass.txt");
//    QTextStream  rf(&ufile);
//    QString ps,mark;

//    ufile.open(QIODevice ::ReadOnly);

//    while(ps != psw)
//    {
//        rf >> ps;
//    }

//    rf >> ps >> mark;
//    ufile.close();

//    return mark;
//}

//QString hospital::getpdname(QString usn)
//{
//    QFile  ufile("pd_user_pass.txt");
//    QTextStream  rf(&ufile);
//    QString un , mark;

//    ufile.open(QIODevice ::ReadOnly);

//    while(un != usn)
//    {
//        rf >> un;
//    }

//    rf >> un ;

//    rf >> un >> mark;
//    ufile.close();

//    return un;
//}

void hospital::PrintHospital()
{
    cout << "----------------Hospital Info---------------" << endl;

    qout << "HospitalName : " << this->getHospitalName() << endl;
    qout << "Hospital Address : " << this->getHospitalAddress() << endl;
    qout << "Hospital phone : " << this->getPhone() << endl;
    qout << "Hospital Boss name : " << this->getBossName() << endl;

    cout << "--------------------End---------------------" << endl;

//    ifstream  rf("hospital_file.txt",ios :: in);
//    string  ans;

//    if(!rf)
//    {
//        cout << "The file in chap fuction isn't open" << endl;
//    }


//    cout << "----------------Hopital info-------------"  << endl;

//    while(rf >> ans)
//    {
//        if(ans == "," || ans == ";")
//        {
//            continue;
//        }
//        cout << ans << endl;
//    }

//    cout << "-------------------End------------------" << endl;
}

void hospital::PrintASectionDoctors(QString sectionName)
{
    QList<doctor>  targetlist = this->SectionsList.value(sectionName);
    QList<doctor> ::iterator  li;

    for(li = targetlist.begin() ; li != targetlist.end() ; li++)
    {
        cout << li->getName().toStdString() << endl;
    }
}

//void hospital::FillVisitTimeFile(QString dn, patient &p)
//{
//    ofstream  fillfile("VisitTime.txt", ios :: out | ios :: app);

//    if(!fillfile)
//    {
//        cout << "VisitTime file isn't open" << endl;
//        return ;
//    }

//    fillfile << dn.toStdString() << endl;
//    fillfile << p.getpname().toStdString() << ' ';
//    fillfile << p.get_visit_time().start_time.toStdString() << ' ';
//    fillfile << p.get_visit_time().end_time.toStdString() << endl;
//    fillfile << "--------------------" << endl;

//    fillfile.close();
//}

//void hospital::setBossPassword(QString p)
//{
//    this->Boss.setPassword(p);
//}

//QString hospital::getBossPassword()
//{
//    return this->Boss.getPassword();
//}

void hospital::SaveHospitalDoctorsInDataBase()
{
    QString tn = this->Name + "Doctors";

    for(mitr mtr = SectionsList.begin() ; mtr != SectionsList.end() ; mtr++)
    {
        for(litr dtr = mtr->begin() ; dtr != mtr->end() ; dtr++)
        {
            QStringList info;

            info.push_back(dtr->getName());
            info.push_back(dtr->getPhone());
            info.push_back(mtr.key());
            info.push_back(dtr->getUserName());

            this->DBPort.INSERTRow(tn,info);
        }        
    }

}

void hospital::ReceiveHospitalDoctorsFromDB()
{
    QString hospitaldoctors = this->Name + "Doctors";
//    QString doctorworkhours , sn;
    QList<QString> sn;
    QString command = "SELECT DISTINCT(Section) From " + this->Name + "Doctors;";

    this->DBPort.ArbitraryQuery(command);
    while(DBPort.NextRow())
    {
        sn.push_back(DBPort.Value("Section").toString());
    }

    for(int i = 0 ; i < sn.size() ; i++)
    {
        QList<doctor> dl;

        DBPort.SELECTRow(hospitaldoctors , "Section = " + sn[i]);

        while(DBPort.NextRow())
        {
            doctor d;

            d.setName(DBPort.Value("Name").toString());
            d.setUserName(DBPort.Value("UserName").toString());
            d.setPhone(DBPort.Value("Phone").toString());
            d.LoadDoctorWorkHoursFromDataBase();
            dl.push_back(d);
        }
        this->SectionsList.insert(sn[i],dl);
    }


}

//void hospital::Add_sec(section & s)
//{
//    doctor  d1;
//    string  info;
//    int n = 0;

//    cout << "Number of doctors of section" << endl;
//    cin >> n;

//    for(int j = 0 ; j < n ; j++)
//    {
//        visit_time  vt;

//        cout << "doctorname : ";
//        cin >> info;
//        d1.set_doctorname(info);

//        cout << "doctor default username : ";
//        cin >> info;
//        d1.set_doctorusername(info);

//        cout << "doctor default password : ";
//        cin >> info;
//        d1.set_doctorpassword(info);

//        cout << "Doctor hourwork : " << endl;
//        cin >> vt;
//        d1.set_doctor_visit_time(vt);

//        s.dlist.push_back(d1);
//    }

//    this->slist.push_back(s);
//}
