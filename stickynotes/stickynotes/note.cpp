
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#define ID_EDIT 1

static TCHAR szWindowClass[] = _T("DesktopApp");

static TCHAR szTitle[] = _T("Sticky Notes");

HINSTANCE hInst;

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
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);



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
        WS_OVERLAPPEDWINDOW^WS_THICKFRAME^WS_MAXIMIZEBOX^WS_BORDER,
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
    static HBRUSH brush;

    switch (msg) {

    case WM_CREATE:

        hwndEdit = CreateWindow(L"Edit", NULL,
            WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
            0, 0, 250, 250, hwnd, (HMENU)ID_EDIT,
            NULL, NULL);
        brush = CreateSolidBrush(RGB(255, 235, 135));
        break;

    case WM_CTLCOLOREDIT:
    {
        HDC hdc = (HDC)hwndEdit;
        SendMessage(hwndEdit, WM_ERASEBKGND, wParam, 0);
        SetBkMode((HDC)wParam, TRANSPARENT);
        SetTextColor(hdc, RGB(60, 60, 60));
        SetBkColor(hdc, RGB(255, 0, 0)); 
        return (LRESULT)((HBRUSH)brush);
    //}

    }
    break;

    case WM_COMMAND:
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        DeleteObject(brush);
        break;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}