#pragma once

#ifndef VECTORN_H_
#define VECTORN_H_

#include <vector>
#include <string>
#include "../defs.h"

class vector_n : protected std::vector<valtype>{
    protected:
        static bool equalsize(const vector&, const vector&);
    public:
        vector_n(const std::vector<valtype> v);
        vector_n(const int n);
        vector_n(std::initializer_list<valtype>);
        int size()const;
        valtype& operator [] (const int i);
        valtype operator [] (const int i)const;
        vector_n operator +(const vector_n&)const;
        vector_n operator -(const vector_n&)const;
        vector_n operator +()const;
        vector_n operator -()const;  
        vector_n operator +=(const vector_n&);   
        vector_n operator -=(const vector_n&); 
        vector_n operator *(const valtype)const;
        vector_n operator /(const valtype)const;
        vector_n operator *=(const valtype);
        vector_n operator /=(const valtype);
        valtype mag_square()const;
        valtype mag()const;
        std::string to_string(const std::string sep)const;
};

vector_n operator*(const valtype, const vector_n);

#endif