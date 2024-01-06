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
vector3::vector3(vector_n v):vector_n(v){
    if(v.size()!=3){
        throw "Type Mismatch";
    }
}
vector3::vector3():vector_n(3){}

valtype vector3::dot_product(vector3& v) {
    valtype dot_answer = operator[](0) * v[0] + operator[](1) * v[1] + operator[](2) * v[2];
    return dot_answer;
}

vector3 vector3::cross_product(vector3& v) {    //This vector cross v (note order of operations)
    vector3 cross_answer;
    cross_answer[0] = operator[](1) * v[2] - operator[](2) * v[1];
    cross_answer[1] = operator[](2) * v[0] - operator[](0) * v[2];
    cross_answer[2] = operator[](0) * v[1] - operator[](1) * v[0];
    return cross_answer;
}