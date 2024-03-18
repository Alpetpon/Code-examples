#include "binPolynom.h"

void binPolynom::reduce(){
    while (degree > 0 && k[degree] == 0) {
        degree--;
    }
}

binPolynom::binPolynom() {
    degree = 0;
    k = new bool[1]{0};
}

binPolynom::binPolynom(int n) {
    degree = n;
    k = new bool[n + 1]{0};
}

binPolynom::binPolynom(int n, double* koef) {
    degree = n;
    k = new bool[n + 1]{0};
    for (int i = 0; i < n + 1; i++) {
        k[i] = koef[i];
    }
}

binPolynom::binPolynom(bool a, int n) {
    degree = n;
    k = new bool[n + 1]{a};
}

binPolynom::binPolynom(const binPolynom& p) {
    degree = p.degree;
    k = new bool[degree + 1]{0};
    for (int i = 0; i < degree + 1; i++) {
        k[i] = p.k[i];
    }
}

binPolynom::~binPolynom() {
    delete[] k;
    k = nullptr;
}

binPolynom binPolynom::operator+(const binPolynom& p) {
    int resdegree = (degree > p.degree ? degree : p.degree);
    binPolynom res(resdegree);
    for (int i = 0; i < degree + 1; i++)
        res.k[i] = k[i];
    int mn = (res.degree < p.degree ? res.degree : p.degree);
    for (int i = 0; i < mn + 1; i++)
        res.k[i] ^= p.k[i];
    res.reduce();
    return res;
}

binPolynom& binPolynom::operator=(const binPolynom& p) {
    if (this != &p) {
        delete[] k;
        degree = p.degree;
        k = new bool[degree + 1]{0};
        for (int i = 0; i < degree + 1; i++) {
            k[i] = p.k[i];
        }
    }
    return *this;
}

binPolynom binPolynom::operator-(const binPolynom& p) {
    return *this + p;
}

binPolynom binPolynom::operator*(const binPolynom& p) {
    int resdegree = degree + p.degree;
    binPolynom res(resdegree);
    for (int i = 0; i < degree; i++) {
        for (int j = 0; j < p.degree; j++) {
            res.k[i] ^= (k[i] && p.k[i]);
        }
    }
    res.reduce();
    return res;
}

binPolynom binPolynom::div_x() {
    if (degree == 0) return *this;
    binPolynom res(degree - 1);
    for (int i = 0; i < res.degree + 1; i++) {
        res.k[i] = k[i + 1];
    }
    return res;
}

binPolynom binPolynom::mult_x() {
    binPolynom res(degree + 1);
    res.k[0] = 0;
    for (int i = 1; i < res.degree + 1; i++) {
        res.k[i] = k[i - 1];
    }
    return res;
}

bool binPolynom::operator==(const binPolynom& p) {
    if (degree == p.degree) {
        for (int i = 0; i < degree + 1; i++) {
            if (k[i] != p.k[i]) return 0;
        }
        return 1;
    }
    return 0;
}

istream& operator>>(istream& is, binPolynom& p) {
    p.~binPolynom();
    is >> p.degree;
    p.k = new bool[p.degree + 1]{0};
    for (int i = 0; i < p.degree + 1; i++)
        is >> p.k[i];
    return is;
}

ostream& operator<<(ostream& os, binPolynom p) {
    for (int i = p.degree; i >= 0; i--) {
        if (p.k[i] > 0)
            os << "+";
        else if (p.k[i] == 0)
            continue;
        os << p.k[i];
        if (i == 1)
            os << "x";
        else if (i == 0)
            continue;
        else
            os << "x^" << i;
    }
    return os;
}

Polynom Polynom::randbinPolynom(int degree) {
    binPolynom res(degree);
    res.k[degree] = 1;
    for (int i = 0; i < degree; i++) {
        res.k[i] = rand() % 2;
    }
    return res;
}


binPolynom x(true, 1);
binPolynom y(true, 1);


binPolynom binPolynom::get_x() const {
    return x;
}

binPolynom binPolynom::get_y() const {
    return y;
}

binPolynom binPolynom::gcd(binPolynom a, binPolynom b, binPolynom& x, binPolynom& y) {
    binPolynom g;
    if (a == binPolynom()) return b;
    if (b == binPolynom()) return a;
    if (a.k[0] == 0 && b.k[0] == 0) {
        g = gcd(a.div_x(), b.div_x(), x, y).mult_x();
        return g;
    }
    else if (a.k[0] == 0) {
        g = gcd(a.div_x(), b, x, y);
        if (x.k[0] == 0) { 
            x = x.div_x();
            return g;
        }
        else {
            x = (x - b).div_x();
            y = y + a.div_x();
            return g;
        }
    }
    else if (b.k[0] == 0) {
        g = gcd(a, b.div_x(), x, y);
        if (y.k[0] == 0) {
            y = y.div_x();
            return g;
        }
        else {
            x = x + b.div_x();
            y = y - a.div_x();
            return g;
        }
    }
    else if (b.degree > a.degree) {
        g = gcd(a, b - a, x, y);
        x = x - y;
        return g;
    }
    else {
        g = gcd(a - b, b, x, y);
        y = y - x;
        return g;
    }
}