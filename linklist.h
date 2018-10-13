#ifndef LINKLIST_H
#define LINKLIST_H
#include "patient.h"
#include <QFile>
#include <QTextStream>

class linklist
{
public:
    linklist();

    int  patient_number;
    patient  * first;
    patient  * last;

    void  pushFront(QString p_name);
//    void  write_to_file(QString &doc, patient &pat);
    void  pushBack(patient &pn);
    void  insert_to_list(QString dname);

//    void  chap_ll();

private:

};

#endif // LINKLIST_H
