#ifndef SECTION_H
#define SECTION_H
#include <iostream>
#include <doctor.h>
#include<list>
using namespace std;

class section
{   
public:
    section();
    section(QString sn);
//          commenting temporarily      //
//    doctor&  getd1() {return d1;}
//    doctor&  getd2() { return d2;}
//    void setd1(doctor &D1);
//    void setd2(doctor  &D2);
        //          ..........          //

    QString  getsection_name() {return section_name;}
    void  set_section_name(QString sn){section_name = sn;}

    //          under testing part      //
    void set_ith_doctor(doctor & D1,QString dn);
    doctor & get_ith_doctor(QString docnam);
//    void  Save_doctors_in_file();

    //          ..................      //

    void TransferToMainDoctor(doctor & d, string pnam, string dname);

    void Add_Doc(doctor &d1);

    list<doctor>  dlist;

private:
    QString section_name;
};

#endif // SECTION_H
