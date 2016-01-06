// Win32Project1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "MSYS_Calculator.h"
#include <iostream>
#include <string>
#include <atlstr.h>
#include <Windows.h>
#include <sstream>
#include <vector>

using namespace std;

#define MAX_LOADSTRING 100
#define maxForTimerID 1000
#define cpuFreqID 1001
#define delayPrescalerID 1002
#define delayID 1003
#define resultButtonID 1004
#define outputID 1005
#define BAUDID 1006
#define FOSCID 1007
#define UBRRID 1008
#define UBRRLID 1009
#define UBRRHID 1010
#define BAUDResultButtonID 1011

char szClassName[] = "TextEntry";
wchar_t textSaved[20];
HWND maxForTimerBox, cpuFreqBox, delayPrescalerBox, delayBox, outputBox, BAUDBox, FOSCBox, UBRRBox, UBRRLBox, UBRRHBox;
// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

using namespace std;

//strings
#define buttonText "Klik For Resultat"
#define resultText "Resultatet"


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_WIN32PROJECT1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent, width, height;
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;

	switch (message)
	{
	case WM_CREATE:{

		if (GetWindowRect(hWnd, &rect)){
			width = rect.right - rect.left;
			height = rect.bottom - rect.top;
		}

		//titel
		CreateWindow(TEXT("STATIC"), TEXT("MSYS Calculator"), // Static er tekst, det næste er beskeden
			WS_VISIBLE | WS_CHILD | SS_CENTER,                            //
			0, 0, width, 25,                                  //x,y, width height
			hWnd, (HMENU)NULL, NULL, NULL);


		maxForTimerBox = CreateWindow(TEXT("EDIT"), TEXT(""), //textBoxX kaldes et handle
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
			100, 100, 130, 25,
			hWnd, (HMENU)maxForTimerID, NULL, NULL);
		// sæt 1
		CreateWindow(TEXT("STATIC"), TEXT("CpuFrek (int)"),
			WS_VISIBLE | WS_CHILD | SS_CENTER,
			0, 70, 100, 25,
			hWnd, (HMENU)NULL, NULL, NULL);

		cpuFreqBox = CreateWindow(TEXT("EDIT"), TEXT("Skriv CpuFrek"),
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
			0, 100, 100, 25,
			hWnd, (HMENU)cpuFreqID, NULL, NULL);

		// sæt 2
		CreateWindow(TEXT("STATIC"), TEXT("Max timer (int)"),
			WS_VISIBLE | WS_CHILD | SS_CENTER,
			100, 70, 130, 25,
			hWnd, (HMENU)NULL, NULL, NULL);


		delayPrescalerBox = CreateWindow(TEXT("EDIT"), TEXT(""),
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
			230, 100, 150, 25,
			hWnd, (HMENU)delayPrescalerID, NULL, NULL);

		//sæt 3
		CreateWindow(TEXT("STATIC"), TEXT("Prescaler delay (int)"),
			WS_VISIBLE | WS_CHILD | SS_CENTER,
			230, 70, 150, 25,
			hWnd, (HMENU)NULL, NULL, NULL);

		CreateWindow(TEXT("BUTTON"), TEXT(buttonText),
			WS_VISIBLE | WS_CHILD,
			510, 70, 150, 55,
			hWnd, (HMENU)resultButtonID, NULL, NULL);


		//sæt 4
		CreateWindow(TEXT("STATIC"), TEXT("Delay (Skrives kun nævner)"),
			WS_VISIBLE | WS_CHILD | SS_CENTER,
			380, 70, 80, 25,
			hWnd, (HMENU)NULL, NULL, NULL);

		delayBox = CreateWindow(TEXT("EDIT"), TEXT("Skriv delay"),
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
			380, 100, 80, 25,
			hWnd, (HMENU)delayID, NULL, NULL);


		// knap, har ingen titel.
		CreateWindow(TEXT("BUTTON"), TEXT(buttonText),
			WS_VISIBLE | WS_CHILD,
			460 + 50, 70, 150, 55,
			hWnd, (HMENU)resultButtonID, NULL, NULL);

		outputBox = CreateWindow(TEXT("EDIT"), TEXT(""),
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
			810, 85, 70, 25,
			hWnd, (HMENU)outputID, NULL, NULL);

		// resultatblok.
		CreateWindow(TEXT("STATIC"), TEXT("Resultat (int)"),
			WS_VISIBLE | WS_CHILD,
			610 + 200, 0, 690, 1000,
			hWnd, (HMENU)NULL, NULL, NULL);


		outputBox = CreateWindow(TEXT("EDIT"), TEXT(resultText),
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			610 + 200, 85, 120, 25,
			hWnd, (HMENU)outputID, NULL, NULL);


//start på udregning af baud rate
		CreateWindow(TEXT("static"), TEXT("Udregning af BAUD rate"),
			WS_VISIBLE | WS_CHILD | SS_CENTER,
			0, 160, 200, 25,
			hWnd, (HMENU) NULL, NULL, NULL);
		
		//cpu freq
		CreateWindow(TEXT("static"), TEXT("Frekvens for CPU"),
			WS_VISIBLE | WS_CHILD | SS_CENTER,
			0, 200, 150, 25,
			hWnd, (HMENU)NULL, NULL, NULL);

		FOSCBox = CreateWindow(TEXT("edit"), TEXT(""),
			WS_VISIBLE | WS_BORDER | WS_CHILD | ES_NUMBER,
			0, 230, 150, 25,
			hWnd, (HMENU)FOSCID, NULL, NULL);

		//ubrr
		CreateWindow(TEXT("static"), TEXT("UBRR"),
			WS_VISIBLE | WS_CHILD | SS_CENTER,
			150, 200, 100, 25,
			hWnd, (HMENU)NULL, NULL, NULL);

		UBRRBox = CreateWindow(TEXT("edit"), TEXT(""),
			WS_VISIBLE | WS_BORDER | WS_CHILD | ES_NUMBER,
			150, 230, 100, 25,
			hWnd, (HMENU)UBRRID, NULL, NULL);




		//ubrrl
		CreateWindow(TEXT("static"), TEXT("UBRRL"),
			WS_VISIBLE | WS_CHILD | SS_CENTER,
			250, 200, 100, 25,
			hWnd, (HMENU)NULL, NULL, NULL);

		UBRRLBox = CreateWindow(TEXT("edit"), TEXT(""),
			WS_VISIBLE | WS_BORDER | WS_CHILD | ES_NUMBER,
			250, 230, 100, 25,
			hWnd, (HMENU)UBRRLID, NULL, NULL);

		//ubrrh
		CreateWindow(TEXT("static"), TEXT("UBRRH"),
			WS_VISIBLE | WS_CHILD | SS_CENTER,
			350, 200, 100, 25,
			hWnd, (HMENU)NULL, NULL, NULL);

		UBRRHBox = CreateWindow(TEXT("edit"), TEXT(""),
			WS_VISIBLE | WS_BORDER | WS_CHILD | ES_NUMBER,
			350, 230, 100, 25,
			hWnd, (HMENU)UBRRHID, NULL, NULL);

		//button no text
		CreateWindow(TEXT("BUTTON"), TEXT(buttonText),
			WS_VISIBLE | WS_CHILD,
			510, 230, 150, 55,
			hWnd, (HMENU)BAUDResultButtonID, NULL, NULL);

		//result is already there
		BAUDBox = CreateWindow(TEXT("edit"), TEXT(resultText),
			WS_VISIBLE | WS_BORDER | WS_CHILD | ES_NUMBER,
			810, 230, 100, 25,
			hWnd, (HMENU)BAUDID, NULL, NULL);



		break;
	}

	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);


		switch (LOWORD(wParam))
		{
		case maxForTimerID:
			if (wmEvent == 256)
				SetDlgItemText(hWnd, maxForTimerID, L"");
			break;
		case cpuFreqID:
			if (wmEvent == 256)
				SetDlgItemText(hWnd, cpuFreqID, L"");
			break;

		case delayPrescalerID:
			if (wmEvent == 256)
				SetDlgItemText(hWnd, delayPrescalerID, L"");
			break;

		case delayID:
			if (wmEvent == 256)
				SetDlgItemText(hWnd, delayID, L"");
			break;

		case resultButtonID: //hvis der er trykket på knappen
		{

			int maxForTimer, cpuFreq, delayPrescaler, delay, maxForTimerLength, cpuFreqLength, delayPrescalerLength, delayLength;

			//Get an int to represent how many characters inserted in the box, used later for checking if empty
			maxForTimerLength = SendMessage(maxForTimerBox, WM_GETTEXTLENGTH, 0,0);
			cpuFreqLength = SendMessage(cpuFreqBox, WM_GETTEXTLENGTH, 0, 0);
			delayPrescalerLength = SendMessage(delayPrescalerBox, WM_GETTEXTLENGTH, 0, 0);
			delayLength = SendMessage(delayBox, WM_GETTEXTLENGTH, 0, 0);

			//check if boxes is empty before calculating
			if (maxForTimerLength == 0 || cpuFreqLength == 0 || delayPrescalerLength == 0 || delayLength == 0){
				MessageBox(0, L"Du mangler at indtaste en af de fire parametre!", 0, 0);
				break;
			}

			maxForTimer = GetDlgItemInt(hWnd, maxForTimerID, NULL, true);
			cpuFreq = GetDlgItemInt(hWnd, cpuFreqID, NULL, true);
			delayPrescaler = GetDlgItemInt(hWnd, delayPrescalerID, NULL, true);
			delay = GetDlgItemInt(hWnd, delayID, NULL, true);

			float delayFloat = (float)1/delay;
			
			float resXPart1 = (float)maxForTimer + 1;
			long float resXPart2 = (float)(cpuFreq*delayFloat) / delayPrescaler;
			float resX = (float)resXPart1 - resXPart2;


			std::wostringstream woss;

			woss << resX;
			std::wstring ws = woss.str();
			const wchar_t* outputFl = ws.c_str();
			std::vector<wchar_t> buf(outputFl, outputFl + (ws.size() + 1));
			wchar_t *outputFloat = &buf[0];



			SetDlgItemText(hWnd, outputID, outputFloat);
			//SetDlgItemInt(hWnd, outputID, resX, true);

			break;
		}
		case BAUDResultButtonID:
		{
			int FOSC, UBRR, UBRRL, UBRRH, UBRRLLength, UBRRHLength, FOSCLength;
			float BAUD;

			FOSC = GetDlgItemInt(hWnd, FOSCID, NULL, true);

			// Get the length of the editboxes to see if they are empty
			UBRRHLength = SendMessage(UBRRHBox, WM_GETTEXTLENGTH, 0, 0);
			UBRRLLength = SendMessage(UBRRLBox, WM_GETTEXTLENGTH, 0, 0);
			FOSCLength = SendMessage(FOSCBox, WM_GETTEXTLENGTH, 0, 0);


			//are they empty ?
			if (UBRRHLength == 0 || UBRRLLength == 0){
				MessageBox(0,L"Indtast UBRRH og UBRRL eller værdien for UBRR",0,0);
				break;
			} 
			// continued
			if (FOSCLength == 0){
				MessageBox(0, L"Indtast frekvensen!", 0, 0);
				break;
			}

			UBRRH = GetDlgItemInt(hWnd, UBRRHID, NULL, true);
			UBRRL = GetDlgItemInt(hWnd, UBRRLID, NULL, true);
			UBRR = (256 * UBRRH) + UBRRL;
			SetDlgItemInt(hWnd, UBRRID, UBRR, true);

			BAUD = (float)((FOSC) / (16 * (UBRR + 1)));

			std::wostringstream woss;
			woss << BAUD;
			std::wstring ws = woss.str();
			const wchar_t* outputFl = ws.c_str();
			std::vector<wchar_t> buf(outputFl, outputFl + (ws.size() + 1));
			wchar_t *outputFloat = &buf[0];

			SetDlgItemText(hWnd, BAUDID, outputFloat);

			break;
		}
		break;
		}

		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
