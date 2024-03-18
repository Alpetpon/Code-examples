#include "polynom.h"

using namespace std;


void Polynom::reduce(){
    while (degree > 0 && k[degree] == 0) {
        degree--;
    }
}

Polynom::Polynom(const char* number) {
    deg = (int)strlen(number) - 1;

    koef = new short int[deg + 1];

    for (int i = deg; i >= 0; i--) {
        koef[deg - i] = number[i] - '0';
    }
}

Polynom::Polynom() {
    deg = 0;
    koef = new short int[deg + 1];
    koef[0] = 0;
}

Polynom::Polynom(bool a, int n) {
    degree = n;
    k = new bool[n + 1]{a};
}



Polynom::Polynom(int new_deg, short int* new_koef) {
    deg = new_deg;
    koef = new short int[deg + 1];
    for (int i = 0; i <= deg; i++) {
        koef[i] = new_koef[i];
    }
}

Polynom::Polynom(int n, double* koef) {
    degree = n;
    k = new bool[n + 1]{0};
    for (int i = 0; i < n + 1; i++) {
        k[i] = koef[i];
    }
}

Polynom::Polynom(int degre) {
    deg = degre;
    koef = new short int[degre + 1];
    for (int i = 0; i <= degre; i++) {
        koef[i] = 0;
    }
}


Polynom::Polynom(const Polynom& f) {
    deg = f.deg;
    koef = new short int[deg + 1];
    for (int i = 0; i <= deg; i++) {
        koef[i] = f.koef[i];
    }
}


void Polynom::Creation() {
    cout << "Введите степень полинома: ";
    cin >> deg;

    while (deg < 0) {
        cout << "Степень полинома должна быть неотрицательной. Пожалуйста, введите снова: ";
        cin >> deg;
    }
    

    delete[] koef;
    koef = new short int[deg + 1];
    
    for (int i = 0; i <= deg; i++) {
        koef[i] = rand() % 2;
    }
}


int GetRandomNumber() {
    long min = -65536;
    long max = 65536;
    short int num = rand() % 2;
    return num;
}


void Polynom::StringTo(std::string strkoef, int deg_) {
    deg = deg_;
    koef = new short int[deg_ + 1];
    
    reverse(strkoef.begin(), strkoef.end());
    
    for (int i = 0; i <= deg_; i++) {
        if (i < strkoef.length()) {
            koef[i] = strkoef[i] - '0';
        } else {
            koef[i] = 0;
        }
    }
}

void Polynom::StringTo() {
    string strkoef;
    int deg;
    koef = new short int[deg + 1];
    for (int i = 0; i < strkoef.length(); i++) {
        koef[i] = strkoef[i] - '0';
    }
}




int Polynom::module(int a) {
    if (a < 0) return -a;
    else return a;
}

void Polynom::Print(){
    if (koef == nullptr) {
        cout << "0" << std::endl;
        return;
    }
    
    bool firstTerm = true;
    
    for (int i = deg; i >= 0; i--) {
        if (koef[i] != 0) {
            if (!firstTerm) {
                cout << (koef[i] > 0 ? " + " : " - ");
            } else {
                firstTerm = false;
                if (koef[i] < 0) {
                    cout << "-";
                }
            }
            
            cout << module(koef[i]);
            
            if (i != 0) {
                cout << "x^" << i;
            }
        }
    }
    
    cout << endl;
}


Polynom Polynom::operator=(const Polynom& f) {
    if (this != &f) {
        deg = f.deg;
        delete[] koef;
        koef = new short int[deg + 1];
        for (int i = 0; i <= deg; i++) {
            koef[i] = f.koef[i];
        }
    }
    return *this;
}

Polynom Polynom::operator+(const Polynom& t) {
    int maxDeg = deg > t.deg ? deg : t.deg;
    short int* resultKoef = new short int[maxDeg + 1];

    for (int i = maxDeg; i >= 0; i--) {
        long long int term1 = i <= deg ? koef[i] : 0;
        long long int term2 = (t.koef[i]);
        resultKoef[i] = term1 + term2;
    }
    Polynom result(maxDeg, resultKoef);
    delete[] resultKoef;
    return result;
}

Polynom Polynom::operator-(const Polynom& t) {
    int maxDeg = deg > t.deg ? deg : t.deg;
    short int* resultKoef = new short int[maxDeg + 1];
    for (int i = 0; i <= maxDeg; ++i) {
        long long int term1 = i <= deg ? koef[i] : 0;
        long long int term2 = i <= t.deg ? t.koef[i] : 0;
        resultKoef[i] = term1 - term2;
    }
    Polynom result(maxDeg, resultKoef);
    delete[] resultKoef;
    return result;
}

Polynom Polynom::operator*(const Polynom& f) {
    int resultDeg = deg + f.deg;
    short int* resultKoef = new short int[resultDeg + 1];
    
    for (int i = 0; i <= resultDeg; i++) {
        resultKoef[i] = 0;
        
        for (int j = max(0, i - f.deg); j <= min(i, deg); j++) {
            resultKoef[i] += koef[j] * f.koef[i - j];
        }
    }
    
    Polynom result(resultDeg, resultKoef);
    delete[] resultKoef;
    return result;
}

Polynom Polynom::operator%(const Polynom& b) const {
    Polynom aCopy = *this;
    Polynom bCopy = Polynom(b);
    int currentDegree = aCopy.deg - bCopy.deg;
    while (currentDegree >= 0) {
        int coef = aCopy.koef[aCopy.deg] / bCopy.koef[bCopy.deg];
        Polynom tempPoly(currentDegree);
        tempPoly.koef[currentDegree] = coef;
        aCopy = aCopy - (tempPoly * bCopy);
        aCopy.zero();
        if (currentDegree == aCopy.deg - bCopy.deg) {
            break;
        }
        currentDegree = aCopy.deg - bCopy.deg;
    }
    return aCopy;
}

Polynom Polynom::operator/(const Polynom& p) const {
    int quotientLength = deg - p.deg;
    short int* quotient = new short int[quotientLength + 1];
    short int* divided = new short int[deg + 1];
    
    for (int i = 0; i <= deg; i++) {
        divided[i] = koef[i];
    }
    
    for (int i = quotientLength; i >= 0; i--) {
        quotient[i] = divided[p.deg + i] / p.koef[p.deg];
        
        for (int j = 0; j <= p.deg; j++) {
            divided[i + j] = divided[i + j] - (quotient[i] * p.koef[j]);
        }
    }
    
    delete[] divided;
    
    return Polynom(quotientLength, quotient);
}


void Polynom::zero() {
    int newDeg = 0;
    for (int i = deg; i >= 0; i--) {
        if (koef[i] != 0) {
            newDeg = i;
            break;
        }
    }
    short int* koefNew = new short int[newDeg + 1];

    for (int i = 0; i <= newDeg; i++) {
        koefNew[i] = koef[i];
    }
    koef = koefNew;
    deg = newDeg;

}

bool Polynom::isZeroCoefficients() const {
    for (int i = 0; i <= deg; ++i) {
        if (koef[i] != 0) {
            return false;
        }
    }
    return true;
}





Polynom Polynom::extendedEuclidean(const Polynom& a, const Polynom& b, Polynom& x, Polynom& y) {
    if (b.deg == 0 && b.koef[0] == 0) {
        x = Polynom(1);
        y = Polynom(0);
        return a;
    }
    
    if (b.deg > a.deg) {
        return extendedEuclidean(a % b, a, y, x);
    }
    
    Polynom x1, y1;
    Polynom gcd = extendedEuclidean(b, a % b, x1, y1);
    
    x = y1;
    
    if (b.deg > 0 || !b.isZeroCoefficients()) {
        y = x1 - (a / b) * y1;
    } else {
        y = Polynom(5); 
    }


    
    return gcd;
}



void Polynom::PrintBezoutCoefficients(){
    if (koef == nullptr) {
        cout << "No coefficients" << endl;
        return;
    }
    
    for (int i = deg; i >= 0; i--) {
        if (i == deg) {
            cout << koef[i];
        } else {
            cout << module(koef[i]);
        }
        
        if (i != 0) {
            if (koef[i - 1] < 0) {
                cout << "x^" << i << " - ";
            } else {
                cout << "x^" << i << " + ";
            }
        }
    }
    cout << endl;
}

bool Polynom::IsEmpty(){
    return (koef == nullptr);
}

double Polynom::measureExecutionTime(const std::function<void()>& func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}


int Polynom::max(int a, int b) {
    if (a > b) return a;
    else return b;
}

int Polynom::getByIndex(const Polynom& a, int index) {
    if (index > a.deg) return 0;
    else return a.koef[index];
}

int Polynom::getByIndexForMultiply(const Polynom& a, int index) {
    if (index > a.deg) return 1;
    else return a.koef[index];
}


Polynom x(true, 1);
Polynom y(true, 1);


Polynom Polynom::get_x() const {
    return x;
}

Polynom Polynom::get_y() const {
    return y;
}

Polynom Polynom::div_x() {
    if (degree == 0) return *this;
    Polynom res(degree - 1);
    for (int i = 0; i < res.degree + 1; i++) {
        res.k[i] = k[i + 1];
    }
    return res;
}


Polynom Polynom::mult_x() {
    Polynom res(degree + 1);
    res.k[0] = 0;
    for (int i = 1; i < res.degree + 1; i++) {
        res.k[i] = k[i - 1];
    }
    return res;
}

bool Polynom::operator==(const Polynom& p) const{
    if (degree == p.degree) {
        for (int i = 0; i < degree + 1; i++) {
            if (k[i] != p.k[i]) return 0;
        }
        return 1;
    }
    return 0;
}



istream& operator>>(istream& is, Polynom& p) {
    is >> p.degree;
    p.k = new bool[p.degree + 1]{0};
    for (int i = 0; i < p.degree + 1; i++)
        is >> p.k[i];
    return is;
}

ostream& operator<<(ostream& os, Polynom p) {
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


Polynom Polynom::gcd(Polynom& a, Polynom& b, Polynom& x, Polynom& y) {
    if (a == Polynom()) {
        x = Polynom();
        y = Polynom(true, 1);
        return b;
    }
    
    if (b == Polynom()) {
        x = Polynom(true, 1);
        y = Polynom();
        return a;
    }
    
    Polynom g = gcd(b, a % b, x, y);
    Polynom temp = x;
    x = y;
    y = temp - (a / b) * y;
    
    return g;
}
