
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <iostream>
#define ID_EDIT 1
#define IDM_EDUNDO       10101
#define IDM_EDCUT        10102
#define IDM_EDCOPY       10103
#define IDM_EDPASTE      10104
#define IDM_EDDEL        10105
#define WM_KEYDOWN                      0x0100

using namespace std;

static TCHAR szWindowClass[] = _T("DesktopApp");

static TCHAR szTitle[] = _T("Sticky Notes");

HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_QUESTION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(255, 235, 135)));
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_QUESTION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Sticky Notes"),
            NULL);

        return 1;
    }

    // Store instance handle in our global variable
    hInst = hInstance;

    HWND hWnd = CreateWindow(
        szWindowClass,
        NULL,
        WS_SYSMENU&~WS_CAPTION,
        CW_USEDEFAULT, CW_USEDEFAULT,
        250, 250,
        NULL,
        NULL,
        hInstance,
        NULL
    );
    SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    
    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Sticky Notes"),
            NULL);

        return 1;
    }

    ShowWindow(hWnd,
        nCmdShow);
    UpdateWindow(hWnd);


    // Main message loop:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
    WPARAM wParam, LPARAM lParam) {

    static HWND hwndEdit;
    static HWND toolBar;
    static HBRUSH brush;
    
    switch (msg) {
        case WM_CHAR:
            OutputDebugString(L"WM_KEYDOWN:");
            break;


        case WM_CREATE:

            hwndEdit = CreateWindow(L"Edit", NULL,
                WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
                10, 10, 210, 190, hwnd, (HMENU)ID_EDIT,
                NULL, NULL);

            break;

        case WM_CTLCOLOREDIT:
        {
            HDC hdc = (HDC)wParam;
            SetTextColor(hdc, RGB(75, 65, 0));
            SetBkColor(hdc, RGB(255, 235, 135));

            if (brush == NULL)
            {
                brush = CreateSolidBrush(RGB(255, 235, 135));
            }
            OutputDebugString(L"Testing\n");
            return (LRESULT)brush;
        }

        case WM_DESTROY:
            PostQuitMessage(0);
            DeleteObject(brush);
            break;
        }

        return DefWindowProcW(hwnd, msg, wParam, lParam);
}

LRESULT CALLBACK EditProc(HWND hwnd, UINT msg,
    WPARAM wParam, LPARAM lParam) {


    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

