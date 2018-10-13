#include "section.h"

section::section()
{}

section::section(QString sn)
{
    this->section_name = sn;
}

void section::set_ith_doctor(doctor &D1, QString dn)
{
    list<doctor> ::iterator it = this->dlist.begin();
    doctor d1;

    while(d1.getName() != dn)
    {
        ++it;
        d1 = *it;
    }
    this->dlist.erase(it);
    this->dlist.insert(it,D1);
}

doctor & section::get_ith_doctor(QString docnam)
{
    list<doctor> ::iterator itr = dlist.begin();
    doctor d;

    for(itr = dlist.begin() ; itr != dlist.end() ; ++itr)
    {
        d = *itr;
        if(d.getName() == docnam)
        {
            return *itr;
        }
    }

    cout << "Wrong choice of doctor" << endl;
    exit(0);


//    while(d.get_doctorname() != docnam)
//    {

//        if(itr == dlist.end())
//        {
//            cout << "Wrong choice of doctor" << endl;
//            exit(0);
//        }

//        d = *itr;
//        ++itr;
//    }
//    return  *itr;
}

//void section::Save_doctors_in_file()
//{
//    list<doctor> ::iterator  Itr;

//    for(Itr = dlist.begin() ; Itr != dlist.end() ; ++Itr)
//    {
//        doctor  d1;

//        d1 = *Itr;

//        d1.save_doctor_infile();
//    }
//}

//void section::setd1(doctor& D1)
//{
//    d1.set_doctorname(D1.get_doctorname());
//    d1.set_doctorusername(D1.get_doctorusername());
//    d1.set_doctor_visit_time(D1.get_doctor_visittime());
//    d1.set_doctorrank(D1.get_doctorrank());

//    //          use of deleted fuctions = use of implicity deleted functions.     //
////    d1 = D1;
//}

//doctor& ...
//void section::TransferToMainDoctor(doctor &d, string pnam,string dname)
//{
//    d = this->get_ith_doctor(dname);
//    d.patient_ll.pushFront(pnam);
//}

void section::Add_Doc(doctor & d1)
{
    this->dlist.push_back(d1);
}
