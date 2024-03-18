#include "application.h"
#include <iostream>
#include "polynom.h"
#include <chrono>
#include <ctime>
#include <fstream>

using namespace std;
using namespace std::chrono;

Application::Application() {}

int Application::exec() {
    int ch, k;
    int deg1 = 0, deg2 = 0, deg3 = 0;
    string koeff1, koeff2;
    

    auto start = chrono::steady_clock::now();
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    int values = 0;

    Polynom p1(deg1), p2(deg2), p3(deg3);

    srand(time(NULL));

    while (true) {
        ch = menu();

        switch (ch) {
        case 1:
            cout << "Выберите: из строки (1) или случайные (2):" << endl << ">";
            cin >> k;

            if (k == 2) {
                p1.Creation();
                cout << "Полином 1:" << endl;
                p1.Print();
                p2.Creation();
                cout << "Полином 2:" << endl;
                p2.Print();
                cout << endl;
                p3 = p1 + p2;
                cout << "Результат:" << endl;
                p3.Print();
            }

            if (k == 1) {
                cout << "Введите степень первого полинома: ";
                cin >> deg1;
                cout << endl;
                cout << "Введите коэффициенты первого полинома: ";
                cin >> koeff1;
                p1.StringTo(koeff1, deg1);
                cout << "Полином 1:" << endl;
                p1.Print();
                cout << endl;
                cout << "Введите степень второго полинома: ";
                cin >> deg2;
                cout << endl;
                cout << "Введите коэффициенты второго полинома: ";
                cin >> koeff2;
                p2.StringTo(koeff2, deg2);
                cout << "Полином 2:" << endl;
                p1.Print();
                cout << endl;
                p3 = p1 + p2;
                cout << "Результат:" << endl;
                p3.Print();
            }
            break;

        case 2:
            cout << "Выберите: из строки (1) или случайные (2):" << endl << ">";
            cin >> k;

            if (k == 2) {
                p1.Creation();
                cout << "Полином 1:" << endl;
                p1.Print();
                p2.Creation();
                cout << "Полином 2:" << endl;
                p2.Print();
                cout << endl;
                p3 = p1 - p2;
                cout << "Результат:" << endl;
                p3.Print();
            }

            if (k == 1) {
                cout << "Введите степень первого полинома: ";
                cin >> deg1;
                cout << endl;
                cout << "Введите коэффициенты первого полинома: ";
                cin >> koeff1;
                p1.StringTo(koeff1, deg1);
                cout << "Полином 1:" << endl;
                p1.Print();
                cout << endl;
                cout << "Введите степень второго полинома: ";
                cin >> deg2;
                cout << endl;
                cout << "Введите коэффициенты второго полинома: ";
                cin >> koeff2;
                p2.StringTo(koeff2, deg2);
                cout << "Полином 2:" << endl;
                p1.Print();
                cout << endl;
                p3 = p1 - p2;
                cout << "Результат:" << endl;
                p3.Print();
            }
            break;

        case 3:
            cout << "Выберите: из строки (1) или случайные (2):" << endl << ">";
            cin >> k;

            if (k == 2) {
                p1.Creation();
                cout << "Полином 1:" << endl;
                p1.Print();
                p2.Creation();
                cout << "Полином 2:" << endl;
                p2.Print();
                cout << endl;
                p3 = p1 * p2;
                cout << "Результат:" << endl;
                p3.Print();
            }

            if (k == 1) {
                cout << "Введите степень первого полинома: ";
                cin >> deg1;
                cout << endl;
                cout << "Введите коэффициенты первого полинома: ";
                cin >> koeff1;
                p1.StringTo(koeff1, deg1);
                cout << "Полином 1:" << endl;
                p1.Print();
                cout << endl;
                cout << "Введите степень второго полинома: ";
                cin >> deg2;
                cout << endl;
                cout << "Введите коэффициенты второго полинома: ";
                cin >> koeff2;
                p2.StringTo(koeff2, deg2);
                cout << "Полином 2:" << endl;
                p2.Print();
                cout << endl;
                p3 = p1 * p2;
                cout << "Результат:" << endl;
                p3.Print();
            }
            break;

        case 4:
            cout << "Выберите: из строки (1) или случайные (2):" << endl << ">";
            cin >> k;

            if (k == 2) {
                p1.Creation();
                cout << "Полином 1:" << endl;
                p1.Print();
                p2.Creation();
                cout << "Полином 2:" << endl;
                p2.Print();
                cout << endl;
                p3 = p1 / p2;
                cout << "Результат:" << endl;
                p3.Print();
            }

            if (k == 1) {
                cout << "Введите степень первого полинома: ";
                cin >> deg1;
                cout << endl;
                cout << "Введите коэффициенты первого полинома: ";
                cin >> koeff1;
                p1.StringTo(koeff1, deg1);
                cout << "Полином 1:" << endl;
                p1.Print();
                cout << endl;
                cout << "Введите степень второго полинома: ";
                cin >> deg2;
                cout << endl;
                cout << "Введите коэффициенты второго полинома: ";
                cin >> koeff2;
                p2.StringTo(koeff2, deg2);
                cout << "Полином 2:" << endl;
                p2.Print();
                cout << endl;
                p3 = p1 / p2;
                cout << "Результат:" << endl;
                p3.Print();
            }
            break;

        case 5:
            cout << "Выберите: из строки (1) или случайные (2):" << endl << ">";
            cin >> k;

            if (k == 2) {
                p1.Creation();
                cout << "Полином 1:" << endl;
                p1.Print();
                p2.Creation();
                cout << "Полином 2:" << endl;
                p2.Print();
                cout << endl;
                p3 = p1 % p2;
                cout << "Результат:" << endl;
                p3.Print();
            }

            if (k == 1) {
                cout << "Введите степень первого полинома: ";
                cin >> deg1;
                cout << endl;
                cout << "Введите коэффициенты первого полинома: ";
                cin >> koeff1;
                p1.StringTo(koeff1, deg1);
                cout << "Полином 1:" << endl;
                p1.Print();
                cout << endl;
                cout << "Введите степень второго полинома: ";
                cin >> deg2;
                cout << endl;
                cout << "Введите коэффициенты второго полинома: ";
                cin >> koeff2;
                p2.StringTo(koeff2, deg2);
                cout << "Полином 2:" << endl;
                p2.Print();
                cout << endl;
                p3 = p1 % p2;
                cout << "Результат:" << endl;
                p3.Print();
            }
            break;
            case 6:
                srand(time(NULL));
                int deg1, deg2;
                double koeff1, koeff2;
                cout << "Выберите: из строки (1) или случайные (2):" << endl << ">";
                cin >> k;
                
                if (k == 2) {
                    Polynom p1, p2, x, y;
                    cout << "Введите степень первого полинома" << endl;
                    cin >> deg1;
                    p1.Creation();
                    
                    p2.Creation();
                    
                    cout << "Полином 1:" << endl;
                    p1.Print();
                    cout << "Полином 2:" << endl;
                    p2.Print();
                    
                    auto start = chrono::steady_clock::now();
                    Polynom gcd_result = p1.gcd(p1, p2, x, y);
                    auto end = chrono::steady_clock::now();

        
                    cout << "Результат расширенного алгоритма Евклида:" << endl;
                    cout << "GCD(a, b): " << gcd_result << endl;
                    cout << "Коэффициенты Безу для a: " << gcd_result.get_x() << endl;
                    cout << "Коэффициенты Безу для b: " << gcd_result.get_y() << endl;
                    
                    auto diff = end - start;
                    cout << "Время исполнения:" << duration_cast<nanoseconds>(diff).count() << "наносекунд" << endl;
                }
                
                if (k == 1) {
                    int deg1, deg2;
                    string koeff1, koeff2;
                    cout << "Введите степень первого полинома: ";
                    cin >> deg1;
                    cout << endl;
                    cout << "Введите коэффициент первого полинома: ";
                    cin >> koeff1;
                    
                    Polynom p1(true, deg1);
                    p1 = Polynom(true, deg1);
                    cout << "Полином 1:" << endl;
                    cout << p1 << endl;
                    
                    cout << "Введите степень второго полинома: ";
                    cin >> deg2;
                    cout << endl;
                    cout << "Введите коэффициент второго полинома: ";
                    cin >> koeff2;
                    
                    Polynom p2(true, deg2);
                    p2 = Polynom(true, deg2);
                    cout << "Полином 2:" << endl;
                    cout << p2 << endl;
                    
                    Polynom x, y;
                    auto start = chrono::steady_clock::now();
                    Polynom gcd_result = p1.gcd(p1, p2, x, y);
                    auto end = chrono::steady_clock::now();
                    
                    cout << "Результат расширенного алгоритма Евклида:" << endl;
                    cout << "GCD(a, b): " << gcd_result << endl;
                    cout << "Коэффициенты Безу для a: " << x << endl;
                    cout << "Коэффициенты Безу для b: " << y << endl;
                    
                    auto diff = end - start;
                    cout << "Время исполнения:" << duration_cast<nanoseconds>(diff).count() << "наносекунд" << endl;
                }
                break;


        case 0:
            return 0;

        default:
            break;
        }
    }

    return 0;
}

int Application::menu() {
    int ch;
    cout << "Меню по тестированию" << endl;
    cout << "1 - +" << endl;
    cout << "2 - -" << endl;
    cout << "3 - * на одночлен" << endl;
    cout << "4 - / на одночлен" << endl;
    cout << "5 - % на одночлен" << endl;
    cout << "6 - Алгоритм Евклида" << endl;
    cout << "0 - выход" << endl << ">";
    cin >> ch;
    return ch;
}
