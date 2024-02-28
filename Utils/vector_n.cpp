#include "vector_n.h"
#include "utils.h"

// class vector_n : protected std::vector<valtype>{
//     protected:
//         static bool equalsize(const vector&, const vector&);
//     public:
//         vector_n(const std::vector<valtype> v);
//         vector_n(const int n);
//         vector_n(std::initializer_list<valtype>);
//         int size()const;
//         valtype& operator [] (const int i);
//         valtype operator [] (const int i)const;
//         vector_n operator +(const vector_n&)const;
//         vector_n operator -(const vector_n&)const;
//         vector_n operator +()const;
//         vector_n operator -()const;  
//         vector_n operator +=(const vector_n&);   
//         vector_n operator -=(const vector_n&); 
//         vector_n operator *(const valtype&)const;
//         vector_n operator /(const valtype&)const;
//         vector_n operator *=(const valtype&);
//         vector_n operator /=(const valtype&);
//         //copy and move??
// };


bool vector_n::equalsize(const vector& v1, const vector& v2){
    return v1.size()==v2.size();
}

vector_n::vector_n(std::vector<valtype> v):vector<valtype>(v){}
vector_n::vector_n(const int n):vector<valtype>(n,0){}
vector_n::vector_n(std::initializer_list<valtype>v):vector<valtype>(v){}
int vector_n::size()const{
    return vector<valtype>::size();
}
valtype& vector_n::operator [] (const int i){
    return vector<valtype>::operator[](i);
}
valtype vector_n::operator [] (const int i)const{
    return vector<valtype>::operator[](i);
}

vector_n vector_n::operator+(const vector_n& v)const {
    if(!equalsize(*this, v)){
        throw "Type Mismatch"; 
    }
    vector_n sum = vector_n(size());
    for(int i=0;i<size();i++){
        sum[i] = operator[](i) + v[i];
    }
    return sum;
}
vector_n vector_n::operator-(const vector_n& v)const{
    return operator+(-v);
};


vector_n vector_n::operator+()const{
    return *this;
}
vector_n vector_n::operator-()const{
    vector_n neg = vector_n(size());
    for(int i=0;i<size();i++){
        neg[i] = -operator[](i);
    }
    return neg;
}

vector_n vector_n::operator+=(const vector_n& v){
    if(!equalsize(*this, v)){
        throw "Type Mismatch"; 
    }
    for(int i=0;i<size();i++){
        operator[](i) = operator[](i) + v[i];
    }
    return *this;
}

vector_n vector_n::operator-=(const vector_n& v){
    return operator+=(-v);
}

vector_n vector_n::operator *(const valtype v)const{
    vector_n prod = vector_n(size());
    for(int i=0;i<size();i++){
        prod[i] = operator[](i)*v;
    }
    return prod;
}
vector_n vector_n::operator /(const valtype v)const{
    vector_n div = vector_n(size());
    for(int i=0;i<size();i++){
        div[i] = operator[](i)/v;
    }
    return div;
}

vector_n vector_n::operator *=(const valtype v){
    for(int i=0;i<size();i++){
        operator[](i) = operator[](i)*v;
    }
    return *this;
}
vector_n vector_n::operator /=(const valtype v){
    for(int i=0;i<size();i++){
        operator[](i) = operator[](i)/v;
    }
    return *this;
}

valtype vector_n::mag_square()const{
    valtype m = 0;
    for(int i=0;i<size();i++){
        valtype c = operator[](i);
        m+= c*c;
    }
    return m;
}
valtype vector_n::mag()const{
    return sqrt(mag_square());
}


vector_n operator*(const valtype x, const vector_n v){
    return v*x;
}

std::string vector_n::to_string(const std::string sep)const{
    std::string s = "";
    for(int i=0;i<size()-1;i++){
        s+= std::to_string(operator[](i));
        s+=sep;
    }
    s+=std::to_string(operator[](size()-1));
    return s;
}


bool vector_n::operator ==(const vector_n& v)const{
    if(!equalsize(*this, v)){
        throw "Type Mismatch"; 
    }
    for(int i=0;i<size();i++){
        if (operator[](i) != operator[](i))
            return false;
    }
    return true;
}
bool vector_n::operator !=(const vector_n& v)const{
    return ! operator==(v);
}