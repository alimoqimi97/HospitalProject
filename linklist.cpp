#include "linklist.h"

linklist::linklist() : patient_number(0) , first(nullptr) , last(nullptr)
{}

void linklist::pushFront(QString p_name)
{
    patient *n = new patient;

    ++patient_number;
    n->setName(p_name);

    if(first == nullptr)
    {
        this->last = n;
    }

    n->next = first;
    first = n;
}

//void linklist::write_to_file(QString &doc, patient & pat)
//{
//    ofstream  wtf("patientsList.txt",ios :: out | ios :: app);

//    if(!wtf)
//    {
//        cout << "The patientsList is not open." << endl;
//        exit(0);
//    }

//    wtf << doc.get_doctorname().toStdString() << ":" << endl;
//    wtf << pat.toStdString() << ',' << pat.get_visit_time().start_time.toStdString() << ',';
//    wtf << pat.get_visit_time().start_time.toStdString() << endl;

//    wtf << ";" << endl;

//    wtf.close();
//}

void linklist::pushBack(patient & pn)
{
    patient * p = new patient;

    *p = pn;
    ++patient_number;

        if(first == nullptr)
        {
            p->next = this->first;
            this->first = p;
            this->last = p;
        }
        else
        {
            last->next = p;
            last = p;
        }
}

void linklist::insert_to_list(QString dname)
{
    QFile   patientsfile("Visittime.txt");
    QTextStream  ReadFile(&patientsfile);
    QString  tmpstr;

    patientsfile.open(QIODevice ::ReadOnly);

    tmpstr = ReadFile.readLine();

    while(!tmpstr.isEmpty())
    {
        if(tmpstr == dname)
        {
            tmpstr = ReadFile.readLine();
            this->pushFront(tmpstr);
        }
    }

    patientsfile.close();
}

//void linklist::chap_ll()
//{
//    if(first == nullptr)
//    {
//        cout << "Your patientlist is empty!..." << endl;
//        return;
//    }

//    cout << "-------------------Doctor patientslist----------------" << endl;

//    while(first != nullptr)
//    {
//        cout << *first;
//        first = first->next;
//    }

//    cout << "======================End of List======================" << endl;
//}
