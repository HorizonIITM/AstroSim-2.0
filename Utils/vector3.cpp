#include "vector3.h"
// class vector3 : public vector_n{
//     public:
//         vector3(std::vector<valtype> v);
//         vector3(const int n);
// };

vector3::vector3(std::vector<valtype> v):vector_n(v){
    if(v.size()!=3){
        throw "Type Mismatch";
    }
}
vector3::vector3(std::initializer_list<valtype> v):vector_n(v){
    if(v.size()!=3){
        throw "Type Mismatch";
    }
}
vector3::vector3():vector_n(3){}
