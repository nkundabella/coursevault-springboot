#include <windows.h>
#include <string>
#include <sstream>

HWND hDisplay;
std::wstring currentExpression = L"";

// Function to evaluate simple 2-number expressions
double evaluateExpression(const std::wstring& expr, bool& isValid) {
    double num1 = 0, num2 = 0;
    wchar_t op = L' ';
    isValid = true;

    // Validate expression format
    if (swscanf(expr.c_str(), L"%lf%1[-+*/]%lf", &num1, &op, &num2) != 3) {
        isValid = false;
        return 0;
    }

    switch (op) {
    case L'+': return num1 + num2;
    case L'-': return num1 - num2;
    case L'*': return num1 * num2;
    case L'/':
        if (num2 == 0) {
            isValid = false;
            return 0;
        }
        return num1 / num2;
    default:
        isValid = false;
        return 0;
    }
}

// Window Procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_COMMAND: {
        int id = LOWORD(wParam);

        // Digit buttons (IDs 100-109)
        if (id >= 100 && id <= 109) {
            currentExpression += std::to_wstring(id - 100);
            SetWindowTextW(hDisplay, currentExpression.c_str());
        }
        // Operator buttons
        else if (id >= 110 && id <= 113) {
            wchar_t op = L"+-*/"[id - 110];
            currentExpression += op;
            SetWindowTextW(hDisplay, currentExpression.c_str());
        }
        // Clear
        else if (id == 114) {
            currentExpression = L"";
            SetWindowTextW(hDisplay, currentExpression.c_str());
        }
        // Equals
        else if (id == 115) {
            bool isValid;
            double result = evaluateExpression(currentExpression, isValid);
            if (isValid) {
                std::wostringstream ss;
                ss << result;
                currentExpression = ss.str();
            }
            else {
                currentExpression = L"Error";
            }
            SetWindowTextW(hDisplay, currentExpression.c_str());
        }
        // Decimal point
        else if (id == 116) {
            currentExpression += L".";
            SetWindowTextW(hDisplay, currentExpression.c_str());
        }
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

// WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    // Register window class
    WNDCLASSW wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"Calculator";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassW(&wc)) {
        MessageBoxW(NULL, L"Failed to register window class!", L"Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    // Create main window
    HWND hwnd = CreateWindowExW(
        0,
        L"Calculator",
        L"C++ Calculator",
        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME, // Disable maximize and resize
        CW_USEDEFAULT, CW_USEDEFAULT, 300, 400,
        NULL, NULL, hInstance, NULL
    );

    if (!hwnd) {
        MessageBoxW(NULL, L"Failed to create window!", L"Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    // Display textbox
    hDisplay = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT,
        20, 20, 240, 30, hwnd, NULL, hInstance, NULL);

    // Digit buttons 1-9
    int x = 20, y = 70;
    for (int i = 1; i <= 9; i++) {
        std::wstring num = std::to_wstring(i);
        CreateWindowW(L"BUTTON", num.c_str(),
            WS_CHILD | WS_VISIBLE | BS_CENTER,
            x, y, 50, 50, hwnd, (HMENU)(100 + i), hInstance, NULL);
        x += 60;
        if (i % 3 == 0) { x = 20; y += 60; }
    }
    // Digit 0
    CreateWindowW(L"BUTTON", L"0", WS_CHILD | WS_VISIBLE | BS_CENTER,
        20, y, 50, 50, hwnd, (HMENU)100, hInstance, NULL);

    // Decimal point
    CreateWindowW(L"BUTTON", L".", WS_CHILD | WS_VISIBLE | BS_CENTER,
        80, y, 50, 50, hwnd, (HMENU)116, hInstance, NULL);

    // Operator buttons (+, -, *, /, C)
    const wchar_t* ops[5] = { L"+", L"-", L"*", L"/", L"C" };
    for (int i = 0; i < 5; i++) {
        CreateWindowW(L"BUTTON", ops[i], WS_CHILD | WS_VISIBLE | BS_CENTER,
            140, 70 + i * 60, 50, 50, hwnd, (HMENU)(110 + i), hInstance, NULL);
    }

    // Equals button
    CreateWindowW(L"BUTTON", L"=", WS_CHILD | WS_VISIBLE | BS_CENTER,
        200, 70, 50, 230, hwnd, (HMENU)115, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Message loop
    MSG msg = {};
    while (GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return 0;
}