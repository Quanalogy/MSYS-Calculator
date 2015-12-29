// Win32Project1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "MSYS_Calculator.h"
#include <iostream>
#include <string>
#include <atlstr.h>
#include <Windows.h>

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
		CreateWindow(TEXT("STATIC"), TEXT("MSYS Calculator"), // Static er tekst, det næste er beskeden
			WS_VISIBLE | WS_CHILD,                            //
			0, 0, 200, 25,                                  //x,y, width height
			hWnd, (HMENU) NULL, NULL, NULL);

		maxForTimerBox = CreateWindow(TEXT("EDIT"), TEXT("Write your Max for the timer"), //textBoxX kaldes et handle
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
			0, 100, 200, 25,
			hWnd, (HMENU) maxForTimerID, NULL, NULL);

		cpuFreqBox = CreateWindow(TEXT("EDIT"), TEXT("Write your CpuFreq"),
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
			0, 130, 200, 25,
			hWnd, (HMENU) cpuFreqID, NULL, NULL);

		delayPrescalerBox = CreateWindow(TEXT("EDIT"), TEXT("Write your Prescaler delay"),
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 
			0, 160, 200, 25,
			hWnd, (HMENU) delayPrescalerID, NULL, NULL);

		delayBox = CreateWindow(TEXT("EDIT"), TEXT("Write your delay"),
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
			0, 190, 200, 25,
			hWnd, (HMENU) delayID, NULL, NULL);

		CreateWindow(TEXT("BUTTON"), TEXT("Klik her for at få resultatet"),
			WS_VISIBLE | WS_CHILD,
			200, 100, 200, 25, 
			hWnd, (HMENU) resultButtonID, NULL, NULL);
	
		outputBox = CreateWindow(TEXT("EDIT"), TEXT("OUTPUT"),
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			450, 100, 200, 25,
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

		case resultButtonID: //hvis der er trykket på knappen
			{
				bool bSuccess;
				int maxForTimer, cpuFreq, delayPrescaler, delay;
				wchar_t theCalculatedNumber;

				maxForTimer = GetDlgItemInt(hWnd, maxForTimerID, NULL, true);
				cpuFreq = GetDlgItemInt(hWnd, cpuFreqID, NULL, true);
				delayPrescaler = GetDlgItemInt(hWnd, delayPrescalerID, NULL, true);
				delay = GetDlgItemInt(hWnd, delayID, NULL, true);

				int resX = (maxForTimer + 1) - (cpuFreq*delay) / delayPrescaler;

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
