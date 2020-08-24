#include"fraction.h"

using namespace std;
std::ostream& operator<<(std::ostream& out, const fraction &frac)
{
    out<<frac.num;
    if(frac.denom != 1)
        out<<"/"<<frac.denom;
    return out;
}

std::istream& operator>>(std::istream& in, fraction &frac)
{
    char junk;
    std::stringstream ss;
    std::string possibleFraction;
    fraction decimalFRac,reverse;
    double decimal;
        if(!in.eof())
        {
            if(in>>decimal)
            {
                if(in.peek() =='/')
                {
                    frac = decimal;
                    in>>junk;
                    while(in.peek()==' ')
                    {
                        in.get(junk);
                    }
                    decimal=1;
                    in>>decimal;

                    if((decimal) == 0)
                    {
                        throw ZeroDenom;
                    }
                    decimalFRac = decimal;
                    reverse.setValue(decimalFRac.denom,decimalFRac.num);
                    frac *=reverse;

                }
                else
                {
                    frac = decimal;
                }

            }
        }
    return in;
}

fraction operator+(const fraction &x,const fraction &y)
{
    fraction result;
    int num = x.num * y.denom + y.num  * x.denom,
            denom = x.denom * y.denom;
    result.setValue(num,denom);
    return result;
}

fraction operator-(const fraction &x,const fraction &y)
{
    fraction result;
    int num = x.num * y.denom - y.num  * x.denom,
            denom = x.denom * y.denom;
    result.setValue(num,denom);
    return result;
}

fraction operator*(const fraction &x,const fraction &y)
{
    fraction result;
    int num = x.num * y.num,
            denom = x.denom * y.denom;
    result.setValue(num,denom);
    return result;
}

fraction operator/(const fraction &x,const fraction &y)
{
    fraction result;
    int num = x.num * y.denom,
            denom = x.denom * y.num;
    result.setValue(num,denom);
    return result;
}
fraction operator^(const fraction &x,const fraction &y)
{
    double temp1,temp2;
    temp1= pow(pow(x.num,y.num),1.0/y.denom);
    temp2= pow(pow(x.denom,y.num),1.0/y.denom);
    fraction answer,answer2;
    answer = temp1;
    answer2 = temp2;
    return answer/answer2;

}

bool operator==(const fraction &x,const fraction &y)
{
    return x.num * y.denom == y.num * x.denom;
}

bool operator>=(const fraction &x,const fraction &y)
{
    return x.num * y.denom >= y.num * x.denom;
}

bool operator<=(const fraction &x,const fraction &y)
{
    return x.num * y.denom <= y.num * x.denom;
}

bool operator!=(const fraction &x,const fraction &y)
{
    return x.num * y.denom != y.num * x.denom;
}

bool operator<(const fraction &x,const fraction &y)
{
    return x.num * y.denom < y.num * x.denom;
}


bool operator>(const fraction &x,const fraction &y)
{
    return x.num * y.denom > y.num * x.denom;
}
