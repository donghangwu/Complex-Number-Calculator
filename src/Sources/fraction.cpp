#include "fraction.h"
/*
 * The default constructor makes an "empty"
 * object, and is required ALL the time!
 */
using namespace std;
fraction::fraction()
{
    num = 0;
    denom = 1;
}
/*
 * Two item constructor that will pass a numerator
 * and a denominator to the new fraction
 */
fraction::fraction(int n, int d)
{
   setValue(n,d);

}
/*
 * How do you destroy a fraction?
 * By the destructor!
 */
fraction::~fraction()
{
    num = denom = 0;
}
/*
 * The copy constructor is fired whenever
 * 1. You pass by value
 * 2. You use a return statement that
 *    does not got back to a reference
 */
fraction::fraction(const fraction &frac)
{
    num = frac.num;
    denom = frac.denom;
}


fraction::fraction( double other)
{

    bool neg=false;
    std::stringstream ss;
    ss<<other;
    if(other<0)
    {
     neg =true;
    }
    std::string FracSTR;
    ss>>FracSTR;
    stringToFract(FracSTR,neg);

    reduce();
}

void fraction::stringToFract(string STRfract,bool neg)
{
     std::string wholePart, fractionPart;
         std::stringstream ss;
         ss<<STRfract;
    std::getline(ss,wholePart,'.');
    std::getline(ss,fractionPart);
    int numDigits = fractionPart.size();
    if(numDigits>=5)
    {
        fractionPart=fractionPart.substr(0,3);
        numDigits=3;
    }
     if(numDigits > 0)
    {
        if(!neg)
        {
            denom = makeDenom(numDigits, allDecimalsTheSame(fractionPart));
            num = denom * std::stoi(wholePart) + std::stoi(fractionPart);
        }
        else
        {
            denom = makeDenom(numDigits, allDecimalsTheSame(fractionPart));
            num = (denom * std::stoi(wholePart)) - std::stoi(fractionPart);
        }
    }
    else
    {
        denom =1;
         num = denom * std::stoi(wholePart) ;
    }
}


bool fraction::allDecimalsTheSame(const std::string &fracPart)
{
    bool yes = true;
    for(int i = 1; yes && i < fracPart.size(); ++i)
    {
        yes = (fracPart[0] == fracPart[i]);

    }
    if(fracPart.size() < 3)
    {
        yes = false;
    }
    return yes;
}

int fraction::makeDenom(int digits, bool same)
{
    std::string result("1");

    for(int i = 0; i < digits; ++i)
        result += "0";
    return std::stoi(result) - (int)same * 1;
}

/*
 * The assignment operator needs to be
 * returned by reference so that you can
 * "chain" operators.
 * e.g.
 * x = y = z;
 */
fraction& fraction::operator=(const fraction &frac)
{
    if(this != &frac)
    {
        num = frac.num;
        denom = frac.denom;
    }
    return *this;
}

fraction& fraction::operator+=(const fraction &other)
{
    *this = *this + other;
    return *this;
}

fraction& fraction::operator-=(const fraction &other)
{
    *this = *this - other;
    return *this;
}

fraction& fraction::operator*=(const fraction &other)
{
    *this = *this * other;
    return *this;
}

fraction& fraction::operator/=(const fraction &other)
{
    *this = *this / other;
    return *this;
}




int fraction::getNum() const //accessor function for numerator
{
    return num;
}

int fraction::getDenom() const//accessor function for denominator
{
    return denom;
}

void fraction::setValue(int n, int d) //mutator function
{
    num = n;
    denom = d;
    reduce();
}

void fraction::display()
{
    std::cout<<" "<<num;
    if(denom != 1)
       std::cout<<"/"<<denom<<" ";
}


void fraction::getInput()
{
    char junk;
    std::cin>>num>>junk>>denom;
    reduce();
}


void fraction::reduce()
{
    bool neg = num < 0 || denom < 0,
         both = num < 0 && denom < 0;
    int divisor = gcd(abs(num), abs(denom));
    num = abs(num) / divisor;
    denom = abs(denom) / divisor;
    if(!both) //Asking is both == false
        if(neg)
            num *= -1;
}

int fraction::gcd(int p, int q)
{
   return !q ? p : gcd(q, p%q);  //!q is the same as asking q == 0;
}

/*
 *  Remainder Theorem
 *
 *  P = nQ + R;
 *
 * 36 = (1)(24) + 12  Question, is 12 == 0?
 * 24 = (2)(12) + 0   If no, move Q into P, and R into Q and continue
 *                    until R == 0;
 * If R== 0, that means Q is the GCD of the original numbers provided
 *
 */


