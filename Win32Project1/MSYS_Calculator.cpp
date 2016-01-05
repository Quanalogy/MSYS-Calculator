// Win32Project1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "MSYS_Calculator.h"
#include <iostream>
#include <string>
#include <atlstr.h>
#include <Windows.h>

using namespace std;

#define MAX_LOADSTRING 100
#define maxForTimerID 1000
#define cpuFreqID 1001
#define delayPrescalerID 1002
#define delayID 1003
#define resultButtonID 1004
#define outputID 1005

char szClassName[] = "TextEntry";
wchar_t textSaved[20];
HWND maxForTimerBox, cpuFreqBox, delayPrescalerBox, delayBox;
HWND outputBox;
// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

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
	if (!InitInstance (hInstance, nCmdShow))
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

	return (int) msg.wParam;
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

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WIN32PROJECT1);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:{

		//titel
		CreateWindow(TEXT("STATIC"), TEXT("MSYS Calculator"), // Static er tekst, det n�ste er beskeden
			WS_VISIBLE | WS_CHILD,                            //
			0, 0, 200, 25,                                  //x,y, width height
			hWnd, (HMENU) NULL, NULL, NULL);

		// s�t 1
		CreateWindow(TEXT("STATIC"), TEXT("CpuFrek (int)"),
			WS_VISIBLE | WS_CHILD,
			0, 70, 100, 25,
			hWnd, (HMENU)NULL, NULL, NULL);

		cpuFreqBox = CreateWindow(TEXT("EDIT"), TEXT("Skriv CpuFrek"),
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
			0, 100, 100, 25,
			hWnd, (HMENU)cpuFreqID, NULL, NULL);

		// s�t 2
		CreateWindow(TEXT("STATIC"), TEXT("Max timer (int)"), 
			WS_VISIBLE | WS_CHILD,                            
			100, 70, 130, 25,                                 
			hWnd, (HMENU)NULL, NULL, NULL);

		maxForTimerBox = CreateWindow(TEXT("EDIT"), TEXT("Skriv Max for timer"), //textBoxX kaldes et handle
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
			100, 100, 130, 25,
			hWnd, (HMENU) maxForTimerID, NULL, NULL);

		//s�t 3
		CreateWindow(TEXT("STATIC"), TEXT("Prescaler delay (int)"),
			WS_VISIBLE | WS_CHILD,
			230, 70, 150, 25,
			hWnd, (HMENU)NULL, NULL, NULL);

		delayPrescalerBox = CreateWindow(TEXT("EDIT"), TEXT("Skriv Prescaler delay"),
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 
			230, 100, 150, 25,
			hWnd, (HMENU) delayPrescalerID, NULL, NULL);


		//s�t 4
		CreateWindow(TEXT("STATIC"), TEXT("Delay (float)"),
			WS_VISIBLE | WS_CHILD,
			380, 70, 80, 25,
			hWnd, (HMENU)NULL, NULL, NULL);

		delayBox = CreateWindow(TEXT("EDIT"), TEXT("Skriv delay"),
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			380, 100, 80, 25,
			hWnd, (HMENU) delayID, NULL, NULL);

		
		// knap, har ingen titel.
		CreateWindow(TEXT("BUTTON"), TEXT("Klik for resultat"),
			WS_VISIBLE | WS_CHILD,
			460+50, 70, 150, 55, 
			hWnd, (HMENU) resultButtonID, NULL, NULL);

		// resultatblok.
		CreateWindow(TEXT("STATIC"), TEXT("Resultat (int)"),
			WS_VISIBLE | WS_CHILD,
			610 + 200, 0, 690, 1000,
			hWnd, (HMENU)NULL, NULL, NULL);


		outputBox = CreateWindow(TEXT("EDIT"), TEXT(" Resultat"),
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			610+200, 85, 70, 25,
			hWnd, (HMENU) outputID, NULL, NULL);

		break;
	}

	case WM_COMMAND:
		wmId    = LOWORD(wParam);
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

		case resultButtonID: //hvis der er trykket p� knappen
			{
				bool bSuccess;
				int maxForTimer, cpuFreq, delayPrescaler;
				string delayInput;
				wchar_t theCalculatedNumber;

				maxForTimer = GetDlgItemInt(hWnd, maxForTimerID, NULL, true);
				cpuFreq = GetDlgItemInt(hWnd, cpuFreqID, NULL, true);
				delayPrescaler = GetDlgItemInt(hWnd, delayPrescalerID, NULL, true);
				delayInput =  GetDlgItemInt(hWnd, delayID, NULL, true);

				float delay = stof(delayInput,NULL);

				int resX = (int) ceil((maxForTimer + 1) - (cpuFreq*delay) / (int)delayPrescaler);

				SetDlgItemInt(hWnd, outputID, resX, true);


				
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
