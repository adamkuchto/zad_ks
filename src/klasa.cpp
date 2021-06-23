#include <iostream>
#include <string>
using namespace std;

class samochod
{
public:
    string nazwa;
    int x;
    int y;
    samochod(string n, int poz_x, int poz_y)
    {
        nazwa = n;
        x = poz_x;
        y = poz_y;
    }
    void przesun(string kierunek, int step)
    {
        if (kierunek == "prawa")
        {
            x = x + 1;
        }
        else if (kierunek == "lewa")
        {
            x = x - 1;
        }
        else if (kierunek == "gora")
        {
            y = y - 1;
        }
        else if (kierunek == "dol")
        {
            y = y + step;
        }
        cout << "pozycja " << nazwa << " x: " << x << " y: " << y << endl;
    }
    void lokalizacja()
    {
        cout << nazwa << " is on position " << x << y << endl;
    }
};

int main()
{
    int ile;
    cout << "ile? ";
    cin >> ile;
    samochod *s1 = new samochod("maly", 20, 20);
    samochod *s2 = new samochod("duzy", 50, 70);

    // s2->przesun("dol", ile);
    s1->lokalizacja();
    s2->lokalizacja();

    return 0;
}