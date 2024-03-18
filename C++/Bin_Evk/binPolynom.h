#ifndef BIN_POLYNOM_H
#define BIN_POLYNOM_H

#include <iostream>
#include <stdlib.h>
#include <chrono>

using namespace std;
using namespace chrono;

class binPolynom {
public:
    int degree;
    bool* k;
    
    void reduce();
    

    binPolynom();
    binPolynom(int n);
    binPolynom(int n, double* koef);
    binPolynom(bool a, int n);
    binPolynom(const binPolynom& p);
    ~binPolynom();

    binPolynom operator+(const binPolynom& p);
    binPolynom& operator=(const binPolynom& p);
    binPolynom operator-(const binPolynom& p);
    binPolynom operator*(const binPolynom& p);
    binPolynom div_x();
    binPolynom mult_x();
    bool operator==(const binPolynom& p);

    friend istream& operator>>(istream& is, binPolynom& p);
    friend ostream& operator<<(ostream& os, binPolynom p);

    binPolynom randbinPolynom(int degree);
    
    
    static binPolynom gcd(binPolynom a, binPolynom b, binPolynom& x, binPolynom& y);
    
    binPolynom get_x() const;
    binPolynom get_y() const;
};


#endif 
