#ifndef POLYNOM_H
#define POLYNOM_H

#include <iostream>
#include <string>
#include <chrono>
#include <stdlib.h>

using namespace std;
using namespace chrono;

class Polynom {
public:
    int deg;
    short int* koef;
    bool* k;
    int degree;
    
    void reduce();


    explicit Polynom(const char* number);

    Polynom();

    Polynom(int new_deg, short int* new_koef);
    
    Polynom(int n, double* koef);
    
    Polynom(const Polynom& f);

    Polynom(bool a, int n);

    Polynom(int deg);
    
    


    void Creation();

    static int max(int a, int b);

    int getByIndex(const Polynom& a, int index);

    int getByIndexForMultiply(const Polynom& a, int index);

    void StringTo(std::string strkoef, int deg_);

    void StringTo();

    int module(int a);

    void Print();

    Polynom operator=(const Polynom& f);

    Polynom operator+(const Polynom& t);

    Polynom operator-(const Polynom& t);

    Polynom operator*(const Polynom& f);

    Polynom operator%(const Polynom& b) const;

    Polynom operator/(const Polynom& p) const;
    
    

    bool isZeroCoefficients() const;

    void zero();

    static Polynom extendedEuclidean(const Polynom& a, const Polynom& b, Polynom& x, Polynom& y);

    void PrintBezoutCoefficients();
    bool IsEmpty();

    void printBezoutCoefficients(Polynom& x, Polynom& y);

    static double measureExecutionTime(const std::function<void()>& func);

    
    Polynom get_x() const;
    Polynom get_y() const;
    
    Polynom div_x();
    Polynom mult_x();
    
    bool operator==(const Polynom& p);
    

    friend std::istream& operator>>(std::istream& is, Polynom& p);
    friend std::ostream& operator<<(std::ostream& os, Polynom p);

    Polynom gcd(Polynom& a, Polynom& b, Polynom& x, Polynom& y);


};

extern Polynom x;
extern Polynom y;

#endif
