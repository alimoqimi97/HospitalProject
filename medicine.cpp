#include "medicine.h"

Medicine::Medicine() : Number(0)
{
}

bool Medicine::operator <(Medicine &other)
{
    if(this->MedicineName < other.getMedicineName())
    {
        return true;
    }

    return false;
}

bool Medicine::operator ==(const Medicine &other) const
{
    if(this->MedicineName == other.getMedicineName())
    {
        if(this->ConsumeDate == other.getConsumeDate())
        {
            if(this->Number == other.getNumber())
            {
                return true;
            }
        }
    }
    return false;
}

ostream &operator <<(ostream &output,  const Medicine &target)
{
    output << target.getMedicineName().toStdString() << ',';
    output << target.getNumber() << ',';
    output << target.getConsumeDate().toStdString() << endl;

    return output;
}


ofstream &operator <<(ofstream &fout, const Medicine &target)
{
    fout << target.getMedicineName().toStdString() << ',';
    fout << target.getConsumeDate().toStdString() << ',';
    fout << target.getNumber() << endl;

    return fout;
}


uint qHash(const Medicine &m)
{
    return qHash(m.getMedicineName().size());
}
