#include <windows.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <cstdio>

// Global variables
HINSTANCE g_hInst = nullptr;
  HWND g_hMainWnd = nullptr;
 HWND g_hDisplay = nullptr;

// Calculator state
std::wstring currentInput;
 double storedValue = 0.0;
wchar_t pendingOp = 0;
bool resetOnNextDigit = false;

// Control IDs
enum : int {
	IDC_DISPLAY = 100,
	IDC_BTN_0,
	IDC_BTN_1,
	IDC_BTN_2,
	IDC_BTN_3,
	IDC_BTN_4,
	IDC_BTN_5,
	IDC_BTN_6,
	IDC_BTN_7,
	IDC_BTN_8,
	IDC_BTN_9,
	IDC_BTN_DOT,
	IDC_BTN_ADD,
	IDC_BTN_SUB,
	IDC_BTN_MUL,
	IDC_BTN_DIV,
	IDC_BTN_EQ,
	IDC_BTN_CLR,
};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CreateCalculatorUI(HWND hwnd);
void OnButton(int id);
void UpdateDisplay(const std::wstring& text);
void AppendDigit(wchar_t ch);
void ApplyPending();
void SetOperation(wchar_t op);
void ClearAll();

// Forward declaration so MinGW WinMain wrapper can call it
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR, int nCmdShow);

#ifdef __MINGW32__
// MinGW (older) may not support -municode; provide ANSI entry that forwards to wWinMain
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
	return wWinMain(hInstance, nullptr, GetCommandLineW(), nCmdShow);
}
#endif

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR, int nCmdShow) {
	g_hInst = hInstance;

	const wchar_t CLASS_NAME[] = L"WinCalcMainWindow";

	WNDCLASSW wc = {};
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	RegisterClassW(&wc);

	g_hMainWnd = CreateWindowExW(
		0,
		CLASS_NAME,
		L"Calculator",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 260, 360,
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	if (!g_hMainWnd) return 0;

	ShowWindow(g_hMainWnd, nCmdShow);
	UpdateWindow(g_hMainWnd);

	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CREATE:
		CreateCalculatorUI(hwnd);
		ClearAll();
		return 0;
	case WM_COMMAND: {
		int id = LOWORD(wParam);
		OnButton(id);
		return 0;
	}
	case WM_GETMINMAXINFO: {
		MINMAXINFO* p = (MINMAXINFO*)lParam;
		p->ptMinTrackSize.x = 260;
		p->ptMinTrackSize.y = 360;
		return 0;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void CreateButton(HWND parent, int id, const wchar_t* text, int x, int y, int w, int h) {
	CreateWindowExW(
		0, L"BUTTON", text,
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		x, y, w, h,
		parent,
		(HMENU)(INT_PTR)id,
		g_hInst,
		nullptr);
}

void CreateCalculatorUI(HWND hwnd) {
	int margin = 10;
	int btnW = 50;
	int btnH = 40;
	int spacing = 10;

	// Display edit control (read-only)
	g_hDisplay = CreateWindowExW(
		WS_EX_CLIENTEDGE, L"EDIT", L"0",
		WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_AUTOHSCROLL | ES_READONLY,
		margin, margin, 210, 40,
		hwnd, (HMENU)(INT_PTR)IDC_DISPLAY, g_hInst, nullptr);

	int startX = margin;
	int startY = margin + 40 + spacing;

	// Row layout similar to standard calculator
	// Row 0: CLR, DIV
	CreateButton(hwnd, IDC_BTN_CLR, L"C", startX, startY, btnW*2 + spacing, btnH);
	CreateButton(hwnd, IDC_BTN_DIV, L"/", startX + (btnW*2 + spacing) + spacing, startY, btnW, btnH);

	// Row 1: 7 8 9 *
	startY += btnH + spacing;
	CreateButton(hwnd, IDC_BTN_7, L"7", startX, startY, btnW, btnH);
	CreateButton(hwnd, IDC_BTN_8, L"8", startX + btnW + spacing, startY, btnW, btnH);
	CreateButton(hwnd, IDC_BTN_9, L"9", startX + (btnW + spacing) * 2, startY, btnW, btnH);
	CreateButton(hwnd, IDC_BTN_MUL, L"*", startX + (btnW + spacing) * 3, startY, btnW, btnH);

	// Row 2: 4 5 6 -
	startY += btnH + spacing;
	CreateButton(hwnd, IDC_BTN_4, L"4", startX, startY, btnW, btnH);
	CreateButton(hwnd, IDC_BTN_5, L"5", startX + btnW + spacing, startY, btnW, btnH);
	CreateButton(hwnd, IDC_BTN_6, L"6", startX + (btnW + spacing) * 2, startY, btnW, btnH);
	CreateButton(hwnd, IDC_BTN_SUB, L"-", startX + (btnW + spacing) * 3, startY, btnW, btnH);

	// Row 3: 1 2 3 +
	startY += btnH + spacing;
	CreateButton(hwnd, IDC_BTN_1, L"1", startX, startY, btnW, btnH);
	CreateButton(hwnd, IDC_BTN_2, L"2", startX + btnW + spacing, startY, btnW, btnH);
	CreateButton(hwnd, IDC_BTN_3, L"3", startX + (btnW + spacing) * 2, startY, btnW, btnH);
	CreateButton(hwnd, IDC_BTN_ADD, L"+", startX + (btnW + spacing) * 3, startY, btnW, btnH);

	// Row 4: 0 . =
	startY += btnH + spacing;
	CreateButton(hwnd, IDC_BTN_0, L"0", startX, startY, btnW*2 + spacing, btnH);
	CreateButton(hwnd, IDC_BTN_DOT, L".", startX + (btnW*2 + spacing) + spacing, startY, btnW, btnH);
	CreateButton(hwnd, IDC_BTN_EQ, L"=", startX + (btnW + spacing) * 3, startY, btnW, btnH);
}

void UpdateDisplay(const std::wstring& text) {
	SetWindowTextW(g_hDisplay, text.c_str());
}

void NormalizeInput() {
	// Remove leading zeros, handle empty input
	if (currentInput.empty()) {
		currentInput = L"0";
		return;
	}
	// keep leading '0.' case
	if (currentInput.size() > 1 && currentInput[0] == L'0' && currentInput[1] != L'.') {
		// strip all leading zeros
		size_t pos = currentInput.find_first_not_of(L'0');
		if (pos == std::wstring::npos) {
			currentInput = L"0";
		} else {
			currentInput = currentInput.substr(pos);
		}
	}
}

void AppendDigit(wchar_t ch) {
	if (resetOnNextDigit) {
		currentInput.clear();
		resetOnNextDigit = false;
	}
	if (ch == L'.') {
		if (currentInput.find(L'.') == std::wstring::npos) {
			if (currentInput.empty()) currentInput = L"0";
			currentInput.push_back(L'.');
		}
	} else {
		currentInput.push_back(ch);
		NormalizeInput();
	}
	UpdateDisplay(currentInput);
}

double GetCurrentValue() {
	try {
		return std::stod(currentInput.empty() ? L"0" : currentInput);
	} catch (...) {
		return 0.0;
	}
}

void ClearAll() {
	currentInput = L"0";
	storedValue = 0.0;
	pendingOp = 0;
	resetOnNextDigit = false;
	UpdateDisplay(currentInput);
}

static std::wstring FormatDouble(double value) {
	wchar_t buf[64];
	// Use %.15g to avoid unnecessary trailing zeros while keeping precision
#if defined(_MSC_VER)
	_snwprintf(buf, sizeof(buf) / sizeof(buf[0]), L"%.15g", value);
#else
	swprintf(buf, L"%.15g", value);
#endif
	return std::wstring(buf);
}

void ApplyPending() {
	double rhs = GetCurrentValue();
	if (pendingOp == 0) {
		storedValue = rhs;
		return;
	}
	switch (pendingOp) {
	case L'+': storedValue = storedValue + rhs; break;
	case L'-': storedValue = storedValue - rhs; break;
	case L'*': storedValue = storedValue * rhs; break;
	case L'/':
		if (rhs == 0.0) {
			UpdateDisplay(L"Error");
			currentInput = L"0";
			storedValue = 0.0;
			pendingOp = 0;
			resetOnNextDigit = true;
			return;
		}
		storedValue = storedValue / rhs; break;
	}
	// display result
	std::wstring out = FormatDouble(storedValue);
	UpdateDisplay(out);
	currentInput = out;
}

void SetOperation(wchar_t op) {
	if (resetOnNextDigit) {
		resetOnNextDigit = false;
	}
	if (pendingOp == 0) {
		storedValue = GetCurrentValue();
	} else {
		ApplyPending();
	}
	pendingOp = op;
	resetOnNextDigit = true;
}

void OnButton(int id) {
	switch (id) {
	case IDC_BTN_0: AppendDigit(L'0'); break;
	case IDC_BTN_1: AppendDigit(L'1'); break;
	case IDC_BTN_2: AppendDigit(L'2'); break;
	case IDC_BTN_3: AppendDigit(L'3'); break;
	case IDC_BTN_4: AppendDigit(L'4'); break;
	case IDC_BTN_5: AppendDigit(L'5'); break;
	case IDC_BTN_6: AppendDigit(L'6'); break;
	case IDC_BTN_7: AppendDigit(L'7'); break;
	case IDC_BTN_8: AppendDigit(L'8'); break;
	case IDC_BTN_9: AppendDigit(L'9'); break;
	case IDC_BTN_DOT: AppendDigit(L'.'); break;
	case IDC_BTN_ADD: SetOperation(L'+'); break;
	case IDC_BTN_SUB: SetOperation(L'-'); break;
	case IDC_BTN_MUL: SetOperation(L'*'); break;
	case IDC_BTN_DIV: SetOperation(L'/'); break;
	case IDC_BTN_EQ:
		ApplyPending();
		pendingOp = 0;
		resetOnNextDigit = true;
		break;
	case IDC_BTN_CLR:
		ClearAll();
		break;
	default:
		break;
	}
}


