#ifndef MEMORIES_H
#define MEMORIES_H
#include<iostream>
#include"complexNumber.h"

class memories
{
public:
    memories();
    ~memories();
    memories(const memories& x);


    complexNumber operator[](char ch) const;
    complexNumber &operator[](char ch);

    friend
    std::ostream&operator<<(std::ostream &out,const memories &n);
    friend
    std::istream&operator>>(std::istream &in, memories &n);

private:
    complexNumber list[26];
    void copy(const memories& x);



};

#endif // MEMORIES_H
