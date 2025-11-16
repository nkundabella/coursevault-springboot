#include <windows.h>
#include <string>
#include <sstream>
#include <cmath>   

#define IDC_EXPR    2000
#define IDC_DISPLAY 2001
#define BUTTON_BASE 3000


double currentResult = 0.0;
std::string currentInput = "";
char lastOp = '\0';
HWND hExpr, hDisplay;


std::string toStr(double val) {
    std::ostringstream ss;
    ss << val;
    return ss.str();
}

void UpdateDisplay(const std::string& expr, const std::string& result) {
    SetWindowTextA(hExpr, expr.c_str());
    SetWindowTextA(hDisplay, result.c_str());
}


void HandleButton(WPARAM wParam) {
    int id = LOWORD(wParam) - BUTTON_BASE;
    const char* labels[] = {
        "7","8","9","/",
        "4","5","6","*",
        "1","2","3","-",
        "0",".","%","+"
    };

    if (id < 0 || id > 16) return;

    
    if (id == 16) {  
        if (!currentInput.empty() && lastOp != '\0') {
            double n = std::stod(currentInput);
            switch (lastOp) {
                case '+': currentResult += n; break;
                case '-': currentResult -= n; break;
                case '*': currentResult *= n; break;
                case '/': if (n != 0) currentResult /= n; break;
                case '%': currentResult = fmod(currentResult, n); break;
            }
            std::string expr = toStr(currentResult);
            UpdateDisplay("", expr);
            currentInput = expr;
            lastOp = '\0';
        }
        return; 
    }

    std::string clicked = (id < 16) ? labels[id] : "";

    if (isdigit(clicked[0])) { 
        currentInput += clicked;
        UpdateDisplay("", currentInput);
    }
    else if (clicked == ".") { 
        if (currentInput.find('.') == std::string::npos) {
            currentInput += currentInput.empty() ? "0." : ".";
            UpdateDisplay("", currentInput);
        }
    }
    else { 
        if (!currentInput.empty()) {
            double n = std::stod(currentInput);
            if (lastOp != '\0') {
                switch (lastOp) {
                    case '+': currentResult += n; break;
                    case '-': currentResult -= n; break;
                    case '*': currentResult *= n; break;
                    case '/': if (n != 0) currentResult /= n; break;
                    case '%': currentResult = fmod(currentResult, n); break;
                }
            } else {
                currentResult = n;
            }
            std::string expr = toStr(currentResult) + " " + clicked;
            UpdateDisplay(expr, "");
            currentInput = "";
        }
        lastOp = clicked[0];
    }
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            
            hExpr = CreateWindowA("STATIC", "",
                WS_CHILD | WS_VISIBLE | SS_RIGHT,
                10, 10, 280, 25, hwnd, (HMENU)IDC_EXPR, NULL, NULL);

            
            hDisplay = CreateWindowA("STATIC", "0",
                WS_CHILD | WS_VISIBLE | SS_RIGHT,
                10, 40, 280, 35, hwnd, (HMENU)IDC_DISPLAY, NULL, NULL);

            
            const char* labels[] = {
                "7","8","9","/",
                "4","5","6","*",
                "1","2","3","-",
                "0",".","%","+"
            };

            int bw = 60, bh = 50, margin = 10;
            int startY = 90;

            for (int i = 0; i < 16; i++) {
                int row = i / 4;
                int col = i % 4;
                int x = margin + col * (bw + margin);
                int y = startY + row * (bh + margin);

                CreateWindowA("BUTTON", labels[i],
                    WS_CHILD | WS_VISIBLE | BS_FLAT,
                    x, y, bw, bh, hwnd, (HMENU)(BUTTON_BASE + i), NULL, NULL);
            }

            
            CreateWindowA("BUTTON", "=",
                WS_CHILD | WS_VISIBLE | BS_FLAT,
                margin, startY + 4 * (bh + margin),
                4 * bw + 3 * margin, bh,
                hwnd, (HMENU)(BUTTON_BASE + 16), NULL, NULL);

            break;
        }
        case WM_COMMAND:
            HandleButton(wParam);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nShow) {
    WNDCLASSA wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.lpszClassName = "CalcApp";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClassA(&wc);

    HWND hwnd = CreateWindowA("CalcApp", "Calculator",
        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 320, 480,
        NULL, NULL, hInst, NULL);

    ShowWindow(hwnd, nShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
