#include"complexNumber.h"
#include<algorithm>
#include<cmath>
using namespace std;

complexNumber operator+(const complexNumber &x,const complexNumber &y)
{

    complexNumber result;
    result.real = x.real+y.real;
    result.imagine=x.imagine+y.imagine;
    return result;
}

complexNumber operator-(const complexNumber &x,const complexNumber &y)
{
    complexNumber result;
    result.real = x.real - y.real;
    result.imagine=x.imagine - y.imagine;
    return result;
}

complexNumber operator*(const complexNumber &x,const complexNumber &y)
{
    complexNumber result;
    mixednumber temp;
    result.real = x.real * y.real +((x.imagine * y.imagine)*-1);
    result.imagine = (x.real *y.imagine) + (y.real * x.imagine);
    return result;
}

complexNumber operator/(const complexNumber &x,const complexNumber &y)
{
     mixednumber denom,realp,imag;
     complexNumber result;

     denom = (y.real * y.real) + (y.imagine * y.imagine);
     realp = (x.real * y.real) + (x.imagine * y.imagine);
     imag =  (x.imagine * y.real) -(x.real * y.imagine);
     if(denom==0)
     {
         throw compzeroDenom;
     }
     result.real=realp/denom;
     result.imagine=imag/denom;
     return result;

}

complexNumber operator^(const complexNumber &x,const complexNumber &y)
{
    complexNumber result;
    double xreal,yreal,yima,xima;
    double darg,realanswer,imanwer,cons,temp;
    xreal=x.real.toDouble();
    xima = x.imagine.toDouble();
    yreal=y.real.toDouble();
    yima=y.imagine.toDouble();

   darg = x.arg(xreal,xima);
   temp=(yima*-1)*darg;
   cons = pow((pow(xreal,2.)+pow(xima,2.)),yreal/2.) * pow(M_E,temp);
   realanswer = cons*(cos((yreal * darg) + 0.5*yima * log(pow(xreal,2) + pow(xima,2))));
   if(abs(realanswer)<0.000001)
   {
       realanswer=0;
   }
   imanwer = cons * (sin((yreal * darg) + 0.5*yima * log(pow(xreal,2) + pow(xima,2))));
   if(abs(imanwer)<0.000001)
   {
       imanwer=0;
   }
   result.real=realanswer;
   result.imagine=imanwer;

    return result;
}
double complexNumber::arg(double x, double y) const
{
    if(x==0)
    {
        if(y<0)
        {
            return -M_PI_2;
        }
        else if(y>0)
        {

            return M_PI_2;
        }
        else
        {
            throw noARG;
        }
    }
    else
    {
        return atan(y/x);
    }
}




complexNumber operator~(const complexNumber &x)
{
    complexNumber result;
    result.imagine= -1*(x.imagine);
    result.real=x.real;
    return result;
}



bool operator ==(const complexNumber &x,const complexNumber &y)
{
    return (x.real==y.real && x.imagine == y.imagine);
}

bool operator !=(const complexNumber &x,const complexNumber &y)
{
    return !(x==y);
}


std::ostream&operator<<(std::ostream &out,const complexNumber &n)
{
    if(n.real!=0)
    {
        out<<n.real;
        if(n.imagine!= 0)
        {
            if(n.imagine>0)
            {
                out<<" + ";
            }
            out<<' '<<n.imagine<<"i";
        }
        else
        {
            out<<' ';
        }

    }
    else if(n.imagine!=0)
    {
        out<<n.imagine<<'i';
    }
    else
    {
        out<<"0";
    }
    return out;
}

std::istream&operator>>(std::istream &in, complexNumber& n)
{
    n=complexNumber();
    mixednumber Mreal,Mimag;
    char junk;

    in>>junk;
    if(junk=='i'||junk=='I'||(in.peek()=='i' && junk=='-')||(in.peek()=='I' && junk=='-'))
    {
        if(junk=='i'||junk=='I')
        {
            n.imagine=1;
        }
        else
            n.imagine=-1;
    }
    else if(isdigit(junk)||junk=='-'||junk=='.')
    {

        if(isdigit(junk)||isdigit(in.peek())||in.peek()=='.')
        {
            in.putback(junk);
            in>>Mreal;
            while(in.peek()==' ')
            {
                in.get(junk);
            }
            if(in.peek()=='i'||in.peek()=='I')
            {
                in>>junk;
                n.imagine=Mreal;
                while(in.peek()==' ')
                {
                    in.get(junk);
                }
                if(in.peek()=='+'||in.peek()=='-')
                {
                    in>>junk;
                    while(in.peek()==' ')
                    {
                        in.get(junk);
                    }
                    in>>Mimag;
                    if(junk=='-')
                    {
                       if(Mimag>0)
                       {
                           Mimag*=-1;
                       }
                    }
                    n.real=Mimag;
                }

            }
            else
            {
                n.real=Mreal;
                while(in.peek()==' ')
                {
                    in.get(junk);
                }
                if(in.peek()=='+'||in.peek()=='-')
                {
                    if(in.peek()=='+')
                    {
                        in>>junk;
                        if(in.peek()=='i'||in.peek()=='I')
                        {
                            in>>junk;
                            n.imagine=1;
                        }
                        else
                        {
                            in>>Mimag;
                            if(in.peek()=='i'||in.peek()=='I')
                            {
                                in>>junk;
                                n.imagine=Mimag;
                            }

                        }
                    }
                    else if(in.peek()=='-')
                    {
                        in>>junk;
                        while (in.peek()== ' ')
                        {
                            in.get(junk);
                        }
                        if(in.peek()=='i'||in.peek()=='I')
                        {
                            in>>junk;
                            n.imagine=-1;
                        }
                        else if(isdigit(in.peek()) || in.peek()== '.')
                        {

                            in.putback(junk);
                            in>>Mimag;
                            while(in.peek()==' ')
                            {
                                in.get(junk);
                            }
                            if(in.peek()=='i'||in.peek()=='I')
                            {
                                in>>junk;
                            }
                            if(Mimag>0)
                            {
                                Mimag*=-1;
                            }
                            n.imagine = Mimag ;
                        }
                    }
                }

            }
        }


    }
    return in;

}
