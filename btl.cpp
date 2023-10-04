#include <windows.h>
#include <tchar.h>
#include<stdio.h>

#define snprintf _snprintf

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HWND hEdit1, hEdit2, hResult, number1, number2;
    switch (uMsg)
    {
    case WM_CREATE:
        
        CreateWindow("STATIC", "Number1:", WS_CHILD | WS_VISIBLE, 10, 10, 70, 30,hwnd, NULL, NULL, NULL);
        CreateWindow("STATIC", "Number2:", WS_CHILD | WS_VISIBLE,10, 50, 70, 30, hwnd, NULL, NULL, NULL);
        
        hEdit1 = CreateWindow(_T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER, 75, 10, 160, 30, hwnd, NULL, NULL, NULL);
        hEdit2 = CreateWindow(_T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER, 75, 50, 160, 30, hwnd, NULL, NULL, NULL);
        CreateWindow(_T("BUTTON"), _T("+"), WS_CHILD | WS_VISIBLE, 250, 10, 80, 30, hwnd, (HMENU)1, NULL, NULL);
        CreateWindow(_T("BUTTON"), _T("-"), WS_CHILD | WS_VISIBLE, 250, 50, 80, 30, hwnd, (HMENU)2, NULL, NULL);
        CreateWindow(_T("BUTTON"), _T("*"), WS_CHILD | WS_VISIBLE, 350, 10, 80, 30, hwnd, (HMENU)3, NULL, NULL);
        CreateWindow(_T("BUTTON"), _T("/"), WS_CHILD | WS_VISIBLE, 350, 50, 80, 30, hwnd, (HMENU)4, NULL, NULL);
        
        hResult = CreateWindow(_T("STATIC"), _T(""), WS_CHILD | WS_VISIBLE | SS_CENTER, 10, 90, 450, 30, hwnd, NULL, NULL, NULL);
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            if (wmId >= 1 && wmId <= 4)
            {
                TCHAR szNum1[256], szNum2[256];
                GetWindowText(hEdit1, szNum1, 256);
                GetWindowText(hEdit2, szNum2, 256);
                double num1 = atof(szNum1);
                double num2 = atof(szNum2);
                double result = 0.0;
                if (wmId == 1)
                    result = num1 + num2;
                else if (wmId == 2)
                    result = num1 - num2;
                else if (wmId == 3)
                    result = num1 * num2;
                else if (wmId == 4)
	                if(num2 == 0){
	                		MessageBox(NULL, "No can divide zeros!", "ERROR SHOW!", MB_OK);
					}else{
						result = num1 / num2;
					}
                    
                
                TCHAR szResult[256];

				_snprintf(szResult, _countof(szResult), _T("Result: %.2f"), result);
                SetWindowText(hResult, szResult);
            }
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

    WNDCLASSEX	 wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WindowProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("CalculatorApp"), NULL };
    RegisterClassEx(&wc);


    HWND hwnd = CreateWindow(wc.lpszClassName, _T("Calculator"), WS_OVERLAPPEDWINDOW, 500, 200, 450, 180, NULL, NULL, wc.hInstance, NULL);


    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnregisterClass(wc.lpszClassName, wc.hInstance);
    return 0;
}
