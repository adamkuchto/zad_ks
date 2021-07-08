#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void decode(char input)
{
    if ((int)input == 32)
    {
        cout << " ";
    }
    int kod = (int)input + 3;

    cout << (char)kod;
}

int main(int argc, char *argv[])
{
    char input;
    while (cin >> input)
    {
        if (input == 'x')
        {
            return 1;
        }
        else
        {
            decode(input);
        }
    }

    return 0;
}
