#pragma once
#ifndef VECTOR3_H_
#define VECTOR3_H_

#include "vector_n.h"

class vector3 : public vector_n{
    public:
        vector3(const std::vector<valtype> v);
        vector3(const vector_n);
        vector3(std::initializer_list<valtype>);
        vector3();
};

#endif
