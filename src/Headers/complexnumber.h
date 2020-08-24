#ifndef complexNumber_H
#define complexNumber_H
#include"mixednumber.h"
#include<fstream>


enum complexNumberError{compzeroDenom,NoTrig,noARG};
class complexNumber
{
public:
    complexNumber();
    ~complexNumber();
    complexNumber(mixednumber realp, mixednumber imagpa);
    complexNumber(mixednumber mix);
    complexNumber(const complexNumber& complexNumbers);

    complexNumber &operator =(const complexNumber& comp);
    complexNumber &operator =(const mixednumber& mixnumber);
    complexNumber &operator =(const fraction& fract);
    complexNumber &operator =(const double& decimal);
    complexNumber &operator =(const int& number);
    complexNumber &operator +=(const complexNumber &comp);
    complexNumber &operator -=(const complexNumber& comp);
    complexNumber &operator *=(const complexNumber& comp);
    complexNumber &operator /=(const complexNumber& comp);

    void setvalue(mixednumber realp, mixednumber imag);
    void trig();
    mixednumber mag();

    mixednumber getReal() const;
    mixednumber getimagine() const;
    double arg(double x,double y) const;


    friend
    complexNumber operator+(const complexNumber &x,const complexNumber &y);
    friend
    complexNumber operator-(const complexNumber &x,const complexNumber &y);
    friend
    complexNumber operator*(const complexNumber &x,const complexNumber &y);
    friend
    complexNumber operator/(const complexNumber &x,const complexNumber &y);
    friend
    complexNumber operator^(const complexNumber &x,const complexNumber &y);
    friend
    complexNumber operator~(const complexNumber &x);

    friend
    bool operator ==(const complexNumber &x,const complexNumber &y);
    friend
    bool operator !=(const complexNumber &x,const complexNumber &y);


    friend
    std::ostream&operator<<(std::ostream &out,const complexNumber &n);
    friend
    std::istream&operator>>(std::istream &in, complexNumber &n);

private:

    mixednumber real;
    mixednumber imagine;
    void copy(const complexNumber& comp);
    void Nospace(std::istream &in);




};

#endif // complexNumber_H
