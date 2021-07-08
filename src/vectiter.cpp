#include <iostream>
#include <ctime>
#include <string>
#include <vector>
using namespace std;

int main()
{
    vector<int> allnr{2, 2, 34, 5, 4, 21, 3};
    vector<int>::iterator it = allnr.begin();
    cout << *it << endl;
    it += 4;
    cout << *it << endl;
    vector<string> slowo{"janusz", "jadwiga", "baba", "jaga"};
    vector<string>::iterator st;
    st = slowo.begin();
    // cout << *st << endl;
    // st = slowo.begin();
    for (int i = 0; i <= 4; ++i)
    {
        st += i;
        cout << *st << endl;
    }

    cout << slowo[2] << endl;
    cout << slowo[2] << endl;
    return 0;
}
