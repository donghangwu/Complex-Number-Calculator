#include "complexNumber.h"
#include<iomanip>
complexNumber::complexNumber()
{
    real =0;
    imagine=0;
}

complexNumber::complexNumber(mixednumber realp,mixednumber imagpa)
{
  real =realp;
  imagine=imagpa;

}

complexNumber::~complexNumber()
{
    real =0;
    imagine=0;
}
complexNumber::complexNumber(mixednumber mix)
{
    real =mix;
}
complexNumber::complexNumber(const complexNumber& complexNumbers)
{
    copy(complexNumbers);
}
complexNumber &complexNumber::operator =(const mixednumber& mixnumber)
{
    real=mixnumber;
    imagine=0;

}
complexNumber &complexNumber::operator =(const complexNumber& comp)
{
    real= comp.real;
    imagine=comp.imagine;
}
complexNumber &complexNumber::operator =(const fraction& fract)
{
    real = fract;
    imagine=0;
    return *this;
}
complexNumber &complexNumber::operator =(const double& decimal)
{
    real = decimal;
    imagine=0;
    return *this;
}
complexNumber &complexNumber::operator =(const int& number)
{
    real = number;
    imagine=0;
    return *this;
}
complexNumber &complexNumber::operator +=(const complexNumber& comp)
{
    *this = *this+comp;
    return *this;
}
complexNumber &complexNumber::operator -=(const complexNumber& comp)
{
    *this = *this-comp;
    return *this;
}
complexNumber &complexNumber::operator *=(const complexNumber &comp)
{
    *this = *this*comp;
    return *this;
}
complexNumber &complexNumber::operator /=(const complexNumber &comp)
{
    *this = *this/comp;
    return *this;
}
void complexNumber:: trig()
{
    using namespace std;
    mixednumber z,the;
    double r,theta;
    double a,b;
    a=mixTodouble(real);
    if(imagine==0)
    {
        throw NoTrig;
    }
    b=mixTodouble(imagine);
    r=sqrt((pow(a,2)+pow(b,2)));
    theta = atan(b/a);
    if(theta<0)
    {
        theta+=M_PI;
    }
    z=r;
    the=theta;
    cout<<setprecision(3)<<"("<<z<<", "<<the<<")"<<endl;

}
mixednumber complexNumber:: mag()
 {
     mixednumber result;
     double r,i,answer;
    r=real.toDouble();
    i=imagine.toDouble();
     answer = sqrt(pow(r,2)+pow(i,2));
     result=answer;
     return result;

 }


void complexNumber::setvalue(mixednumber realp,mixednumber imag)
{
    real = realp;
    imagine=imag;
}
void complexNumber::copy(const complexNumber& comp)
{
    real = comp.real;
    imagine=comp.imagine;

}

mixednumber complexNumber::getReal() const
{
    return real;
}
mixednumber complexNumber::getimagine() const
{
    return imagine;
}

