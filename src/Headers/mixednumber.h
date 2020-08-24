#ifndef MIXEDNUMBER_H
#define MIXEDNUMBER_H
#include"fraction.h"
#include<fstream>
class mixednumber : public fraction
{
    public:
        mixednumber();
        ~mixednumber();
        mixednumber(double decimal);
        mixednumber(fraction frac);
        mixednumber(int w,int n=0,int d =1);
        double toDouble() const;
        mixednumber(const mixednumber &other);
        mixednumber &operator = (const mixednumber &other);
        mixednumber &operator=(const fraction &other);
        mixednumber &operator=(const int &other);
        mixednumber &operator=(const double &other);


        void getValue(int &w, int &n, int &d);
        void setValue(int w, int n, int d);

        friend
        double mixTodouble(const mixednumber &x);

        friend
        std::ostream&operator<<(std::ostream &out,const mixednumber &n);
        friend
        std::istream&operator>>(std::istream &in, mixednumber &n);

    private:
        //int whole;
        void copy(const mixednumber &other);
        void nukeEveryone();
};

#endif // MIXEDNUMBER_H
