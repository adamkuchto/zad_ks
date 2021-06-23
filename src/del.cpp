#include <iostream>
#include <cmath>
#include <iomanip>
#include <conio.h>
#include <fstream>

using namespace std;
double a, b;

/**
 * funkcja pobierajaca dane do przetwazania
 * @param a - parametr a
 * @param b - parametr b
 * @return a, b;
 */
void dane(double, double)
{

    ifstream plik;
    plik.open("zapisane.txt");
    plik >> a >> b;
    plik.close();
}

int main()
{
    dane(a, b);
    cout << fixed << setprecision(2);
    cout << a + b << endl;
    cout << a - b << endl;
    cout << a * b << endl;
    cout << a / b << endl;

    return 0;
}
