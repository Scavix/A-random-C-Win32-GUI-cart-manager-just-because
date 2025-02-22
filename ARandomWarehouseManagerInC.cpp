// ARandomWarehouseManagerInC.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "ARandomWarehouseManagerInC.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_LOADSTRING 100

// New control IDs
#define IDC_LIST_PRODUCTS   101
#define IDC_LIST_CART       102
#define IDC_BUTTON_ADD      103
#define IDC_STATIC_TOTAL    105
#define IDC_BUTTON_PRINTT   106

//(104) is skipped cause error

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Global handles for new controls and total price
HWND hListProducts = NULL, hListCart = NULL, hButtonAdd = NULL, hButtonPrint = NULL, hStaticTotal = NULL;
double totalPrice = 0.0;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
void                LoadProducts(HWND hListProducts);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ARANDOMWAREHOUSEMANAGERINC, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ARANDOMWAREHOUSEMANAGERINC));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
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
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ARANDOMWAREHOUSEMANAGERINC));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_ARANDOMWAREHOUSEMANAGERINC);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//  FUNCTION: InitInstance(HINSTANCE, int)
//  PURPOSE: Saves instance handle and creates main window
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 400, 500, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  FUNCTION: LoadProducts(HWND)
//  PURPOSE: Reads a list of items and prices from products.txt and adds them to the products list box.
//
void LoadProducts(HWND hListProducts)
{
    FILE* f;
    errno_t err = fopen_s(&f, "products.txt", "r");
    if (err != 0 || !f)
    {
        MessageBox(NULL, L"Could not open products.txt", L"Error", MB_OK | MB_ICONERROR);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), f))
    {
        // Remove newline
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';

        // ANSI to Unicode
        wchar_t wLine[256];
        MultiByteToWideChar(CP_ACP, 0, line, -1, wLine, 256);

        SendMessage(hListProducts, LB_ADDSTRING, 0, (LPARAM)wLine);
    }
    fclose(f);
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//  PURPOSE: Processes messages for the main window.
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        // Products list box
        hListProducts = CreateWindowEx(WS_EX_CLIENTEDGE, L"LISTBOX", NULL,
            WS_CHILD | WS_VISIBLE | LBS_STANDARD,
            10, 10, 200, 200,
            hWnd, (HMENU)IDC_LIST_PRODUCTS, hInst, NULL);

        // Add cart button
        hButtonAdd = CreateWindow(L"BUTTON", L"Add to Cart",
            WS_CHILD | WS_VISIBLE,
            220, 10, 120, 30,
            hWnd, (HMENU)IDC_BUTTON_ADD, hInst, NULL);

        // Cart list box
        hListCart = CreateWindowEx(WS_EX_CLIENTEDGE, L"LISTBOX", NULL,
            WS_CHILD | WS_VISIBLE | LBS_STANDARD,
            10, 220, 200, 200,
            hWnd, (HMENU)IDC_LIST_CART, hInst, NULL);

        // Print button
        hButtonPrint = CreateWindow(L"BUTTON", L"Print Receipt",
            WS_CHILD | WS_VISIBLE,
            220, 50, 120, 30,
            hWnd, (HMENU)IDC_BUTTON_PRINTT, hInst, NULL);

        // Total price text
        hStaticTotal = CreateWindow(L"STATIC", L"Total: $0.00",
            WS_CHILD | WS_VISIBLE,
            220, 90, 150, 30,
            hWnd, (HMENU)IDC_STATIC_TOTAL, hInst, NULL);

        LoadProducts(hListProducts);
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case IDC_BUTTON_ADD:
        {
            // Get selected product
            int index = (int)SendMessage(hListProducts, LB_GETCURSEL, 0, 0);
            if (index != LB_ERR)
            {
                wchar_t buffer[256];
                SendMessage(hListProducts, LB_GETTEXT, index, (LPARAM)buffer);

                // Buffer has to be terminated by null char
                buffer[255] = L'\0';

                SendMessage(hListCart, LB_ADDSTRING, 0, (LPARAM)buffer);

                // Parse the price
                wchar_t* token = wcschr(buffer, L' ');
                if (token != NULL)
                {
                    double price = _wtof(token + 1);
                    totalPrice += price;

                    wchar_t totalText[100];
                    swprintf(totalText, 100, L"Total: $%.2f", totalPrice);
                    SetWindowText(hStaticTotal, totalText);
                }
            }
        }
        break;
        case IDC_BUTTON_PRINTT:
        {
            FILE* f;
            errno_t err = fopen_s(&f, "receipt.txt", "w");
            if (err == 0 && f)
            {
                int count = (int)SendMessage(hListCart, LB_GETCOUNT, 0, 0);
                wchar_t buffer[256];
                for (int i = 0; i < count; i++)
                {
                    SendMessage(hListCart, LB_GETTEXT, i, (LPARAM)buffer);
                    char line[256];
                    WideCharToMultiByte(CP_ACP, 0, buffer, -1, line, sizeof(line), NULL, NULL);
                    fprintf(f, "%s\n", line);
                }
                fprintf(f, "Total: $%.2f\n", totalPrice);
                fclose(f);
                MessageBox(hWnd, L"Receipt printed to receipt.txt", L"Receipt", MB_OK);
            }
            else
            {
                MessageBox(hWnd, L"Error printing receipt", L"Error", MB_OK | MB_ICONERROR);
            }
        }
        break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // You can add custom painting code here if needed.
        EndPaint(hWnd, &ps);
    }
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