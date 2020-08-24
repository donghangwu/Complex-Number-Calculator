#include "mixednumber.h"

using namespace std;
mixednumber::mixednumber()
{
}

mixednumber::~mixednumber()
{
    nukeEveryone();
}

mixednumber::mixednumber(double decimal)
{
    *this = decimal;
}

mixednumber::mixednumber( fraction frac)
{
    num = frac.getNum();
    denom=frac.getDenom();
}
mixednumber::mixednumber(int w,int n,int d)
{
    setValue(w,n,d);
}

double mixednumber::toDouble() const
{
    double result;
    result = (num)/(denom*1.0);
    return result;
}

mixednumber::mixednumber(const mixednumber &other)
{
    copy(other);
}
 mixednumber &mixednumber::operator = (const mixednumber &other)
{
    if(this != &other)
    {
        copy(other);
    }
    return *this;
}

 mixednumber& mixednumber::operator=(const fraction &other)
 {
     num = other.getNum();

     denom = other.getDenom();
     return *this;
 }


 mixednumber& mixednumber::operator=(const int &other)
 {

     fraction temp(other);
     *this = temp;
     return *this;
 }

 mixednumber& mixednumber::operator=(const double &other)
 {
     fraction temp(other);
     *this = temp;
     return *this;
 }


void mixednumber::getValue(int &w, int &n, int &d)
{
    w = num/denom;
    n = num%denom;
    d=denom;
}
void mixednumber::setValue(int w, int n, int d)
{
   fraction::setValue(w*d + n,d);
}

double mixTodouble(const mixednumber &x)
{
    mixednumber y=x;
    return (y.getNum()*1.0 / y.getDenom()*1.0);
}

std::ostream&operator<<(std::ostream &out,const mixednumber &n)
{
    int whole = n.num/n.denom;
    int numerator = n.num%n.denom;
    //out<<"num "<<n.num;
    if(numerator==0)
    {
        out<<whole;
    }
    else
    {
        if(whole == 0)
        {

            out<<numerator<<"/"<<n.denom;
        }
        else
        {
            out<<whole<<" "<<abs(numerator)<<"/"<<n.denom;
        }
    }
    return out;
}
std::istream&operator>>(std::istream &in, mixednumber &n)
{
    //using namespace std;
    double decimal;
    //fraction convertWhole;
    fraction fracPart;
    fraction wholeP;

    char junk;

    if(in>>wholeP)
    {

        if(in.peek() == ' ')
        {
            in.get(junk);
            while(in.peek()==' ')
            {
                in.get(junk);
            }

            if(isdigit(in.peek()))
            {
                in>>fracPart;
                if(wholeP<0)
                {
                    n=wholeP+fracPart* -1;
                }
                else
                {
                    n=wholeP+fracPart;
                }
            }
            else
            {
                n=wholeP;
            }

        }

        else
        {
            n = wholeP;
        }
    }
    return in;
}

void mixednumber::copy(const mixednumber &other)
{
    num =other.num;
    denom = other.denom;
}
void mixednumber::nukeEveryone()
{
    num=0;
    denom=1;
}
