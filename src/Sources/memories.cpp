#include "memories.h"
#include<sstream>
#include<iostream>
using namespace std;
memories::memories()
{
    for(int i =0; i<26; ++i)
    {
        list[i]=0;

    }
}
memories::~memories()
{
    for(int i =0; i<26; ++i)
    {
        list[i]=0;
    }
}
memories::memories(const memories& x)
{
    copy(x);
}



complexNumber memories::operator[](char ch) const
{
        return(list[int(ch-65)]);

}
complexNumber &memories::operator [](char ch)
{
      return(list[ch-65]);
}

void memories::copy(const memories &x)
{
    for(int i =0; i<26;++i)
    {
        list[i]=x.list[i];
    }
}

std::ostream&operator<<(std::ostream &out,const memories &n)
{
    for(int i =0; i<26;++i)
    {
        out<<char(65+i)<<" = "<<n.list[i]<<endl;
    }
    return out;
}

std::istream&operator>>(std::istream &in, memories &n)
{
    stringstream ss;
    string line,chomp,piece;
    complexNumber num;
    char junk,ch;
    getline(in,line);
    ss<<line;
    while( ss>>piece)
    {
       chomp=chomp+piece+' ';
    }
    ss=stringstream();
    ss<<chomp;
    getline(ss,line,'=');
    ch=line[0];
    if(ss.peek()=='=')
    {
        ss>>junk;
    }
    ss>>num;
    for(int i =0;i<26;++i)
    {
        if((65+i)==toupper(ch))
        {
            n.list[i]=num;
        }
    }

return in;

}
