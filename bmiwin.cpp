#include <windows.h>
#include <fstream>
using namespace std;
HWND przycisk, przycisk1;
HWND PoleTekstowe;

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_COMMAND:
	{
		if ((HWND)lParam == przycisk)
		{
			ofstream plik;
			plik.open("zapisane.txt");
			int dlugosc = GetWindowTextLength(PoleTekstowe);
			LPSTR tekst = (LPSTR)GlobalAlloc(GPTR, dlugosc + 1);
			GetWindowText(PoleTekstowe, tekst, dlugosc + 1);
			plik << tekst;
			plik.close();
		}
		else if ((HWND)lParam == przycisk1)
		{
			ifstream plik;
			plik.open("wczytane.txt");
			string calosc, linia;
			while (!plik.eof())
			{
				getline(plik, linia);
				calosc += linia;
			}
			plik.close();
			SetWindowText(PoleTekstowe, calosc.c_str());
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
	HWND hwnd;	   /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg;	   /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc, 0, sizeof(wc));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WndProc; /* This is where we will send messages to */
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	wc.lpszClassName = "WindowClass";
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);	  /* Load a standard icon */
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "WindowClass", "BMI", WS_VISIBLE | WS_OVERLAPPEDWINDOW,
						  CW_USEDEFAULT, /* x */
						  CW_USEDEFAULT, /* y */
						  640,			 /* width */
						  480,			 /* height */
						  NULL, NULL, hInstance, NULL);
	przycisk = CreateWindowEx(0, "BUTTON", "ZAPISZ", WS_CHILD | WS_VISIBLE, 0, 0, 640, 30, hwnd, NULL, hInstance, NULL);
	przycisk1 = CreateWindowEx(0, "BUTTON", "WCZYTAJ", WS_CHILD | WS_VISIBLE, 0, 35, 640, 30, hwnd, NULL, hInstance, NULL);
	PoleTekstowe = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL, 5, 70, 580, 395, hwnd, NULL, hInstance, NULL);

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
	{							/* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg);	/* Send it to WndProc */
	}
	return msg.wParam;
}
