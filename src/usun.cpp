#include <windows.h>
#include <fstream>
#include <string>
#define bmi
using namespace std;
HWND PrzyciskPrzelicz;
HWND a;
HWND b;
HWND c;

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch (Message)
    {
    case WM_COMMAND:
    {
        if ((HWND)lParam == PrzyciskPrzelicz)
        {
            int dlugosc = GetWindowTextLength(a);
            LPSTR tekst = (LPSTR)GlobalAlloc(GPTR, dlugosc + 1);
            GetWindowText(a, tekst, dlugosc + 1);
            float c1 = atof(tekst);

            dlugosc = GetWindowTextLength(b);
            tekst = (LPSTR)GlobalAlloc(GPTR, dlugosc + 1);
            GetWindowText(b, tekst, dlugosc + 1);
            float c2 = atof(tekst);

            dlugosc = GetWindowTextLength(c);
            tekst = (LPSTR)GlobalAlloc(GPTR, dlugosc + 1);
            GetWindowText(c, tekst, dlugosc + 1);
            float c3 = atof(tekst);

            if (c3 == c1 * c2)
            {
                int bmi(double, double);
                MessageBox(hwnd, "ok", "wynik", MB_ICONINFORMATION);
            }
            else
            {
                MessageBox(hwnd, "blad", "wynik", MB_ICONINFORMATION);
            }
        }
        break;
    }
    /* Upon destruction, tell the main thread to stop */
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        break;
    }

    /* All other messages (a lot of them) are processed using default procedures */
    default:
        return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}
/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc; /* A properties struct of our window */
    HWND hwnd;     /* A 'HANDLE', hence the H, or a pointer to our window */
    MSG msg;       /* A temporary location for all messages */

    /* zero out the struct and set the stuff we want to modify */
    memset(&wc, 0, sizeof(wc));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WndProc; /* This is where we will send messages to */
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    /* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = "WindowClass";
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);   /* Load a standard icon */
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "WindowClass", "power judge", WS_VISIBLE | WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT, /* x */
                          CW_USEDEFAULT, /* y */
                          630,           /* width */
                          300,           /* height */
                          NULL, NULL, hInstance, NULL);
    PrzyciskPrzelicz = CreateWindowEx(0, "BUTTON", "Przelicz", WS_CHILD | WS_VISIBLE, 120, 10, 400, 100, hwnd, NULL, hInstance, NULL);
    a = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE, 10, 200, 190, 30, hwnd, NULL, hInstance, NULL);
    b = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE, 210, 200, 190, 30, hwnd, NULL, hInstance, NULL);
    c = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE, 410, 200, 190, 30, hwnd, NULL, hInstance, NULL);

    if (hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    /*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {                           /* If no error is received... */
        TranslateMessage(&msg); /* Translate key codes to chars if present */
        DispatchMessage(&msg);  /* Send it to WndProc */
    }
    return msg.wParam;
}
