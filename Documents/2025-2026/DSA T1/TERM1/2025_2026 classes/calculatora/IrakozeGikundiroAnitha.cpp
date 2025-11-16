
// MFCApplication1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg dialog



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
	, Edit_result(_T(""))
{
	 number1 = number2 = number0= 0;
	 str1 = _T("");
	 str2 = _T("");
	 Flag =  true;
	 opera = 0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Edit_result);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_BN_CLICKED(IDC_B0, &CMFCApplication1Dlg::OnBnClickedB0)
	ON_BN_CLICKED(IDC_B2, &CMFCApplication1Dlg::OnBnClickedB2)
	ON_BN_CLICKED(IDC_B3, &CMFCApplication1Dlg::OnBnClickedB3)
	ON_BN_CLICKED(IDC_B6, &CMFCApplication1Dlg::OnBnClickedB6)
	ON_BN_CLICKED(IDC_B5, &CMFCApplication1Dlg::OnBnClickedB5)
	ON_BN_CLICKED(IDC_B4, &CMFCApplication1Dlg::OnBnClickedB4)
	ON_BN_CLICKED(IDC_B8, &CMFCApplication1Dlg::OnBnClickedB8)
	ON_BN_CLICKED(IDC_B9, &CMFCApplication1Dlg::OnBnClickedB9)
	ON_BN_CLICKED(IDC_B7, &CMFCApplication1Dlg::OnBnClickedB7)
	ON_BN_CLICKED(IDC_B1, &CMFCApplication1Dlg::OnBnClickedB1)
	ON_BN_CLICKED(IDC_B_PLUS, &CMFCApplication1Dlg::OnBnClickedBPlus)
	ON_BN_CLICKED(IDC_B_SUB, &CMFCApplication1Dlg::OnBnClickedBSub)
	ON_BN_CLICKED(IDC_B_MUL, &CMFCApplication1Dlg::OnBnClickedBMul)
	ON_BN_CLICKED(IDC_B_DIV, &CMFCApplication1Dlg::OnBnClickedBDiv)
	ON_BN_CLICKED(IDC_B_EQUAL, &CMFCApplication1Dlg::OnBnClickedBEqual)
	ON_BN_CLICKED(IDC_B_POINT, &CMFCApplication1Dlg::OnBnClickedBPoint)
	ON_BN_CLICKED(IDC_B_SIGN, &CMFCApplication1Dlg::OnBnClickedBSign)	
	ON_BN_CLICKED(IDC_B_CLEAR, &CMFCApplication1Dlg::OnBnClickedBClear)
END_MESSAGE_MAP()


// CMFCApplication1Dlg message handlers

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedB0()
{
	if (Flag == true) {


		str1 += _T("0");
		Edit_result = str1;
	}
	else {
		str2 += _T("0");
		Edit_result = str2;
	}
	UpdateData(FALSE);
}


void CMFCApplication1Dlg::OnBnClickedB1()
{
	if (Flag == true) {


		str1 += _T("1");
		Edit_result = str1;
	}
	else {
		str2 += _T("1");
		Edit_result = str2;
	}
	UpdateData(FALSE);
}


void CMFCApplication1Dlg::OnBnClickedB2()
{
	if (Flag == true) {


		str1 += _T("2");
		Edit_result = str1;
	}
	else {
		str2 += _T("2");
		Edit_result = str2;
	}
	UpdateData(FALSE);
}


void CMFCApplication1Dlg::OnBnClickedB3()
{
	
	if (Flag == true) {


		str1 += _T("3");
		Edit_result = str1;
	}
	else {
		str2 += _T("3");
		Edit_result = str2;
	}
	UpdateData(FALSE);
}


void CMFCApplication1Dlg::OnBnClickedB6()
{

	if (Flag == true) {


		str1 += _T("6");
		Edit_result = str1;
	}
	else {
		str2 += _T("6");
		Edit_result = str2;
	}
	UpdateData(FALSE);
}


void CMFCApplication1Dlg::OnBnClickedB5()
{

	if (Flag == true) {


		str1 += _T("5");
		Edit_result = str1;
	}
	else {
		str2 += _T("5");
		Edit_result = str2;
	}
	UpdateData(FALSE);
}


void CMFCApplication1Dlg::OnBnClickedB4()
{

	if (Flag == true) {


		str1 += _T("4");
		Edit_result = str1;
	}
	else {
		str2 += _T("4");
		Edit_result = str2;
	}
	UpdateData(FALSE);
}


void CMFCApplication1Dlg::OnBnClickedB8()
{

	if (Flag == true) {


		str1 += _T("8");
		Edit_result = str1;
	}
	else {
		str2 += _T("8");
		Edit_result = str2;
	}
	UpdateData(FALSE);
}

void CMFCApplication1Dlg::OnBnClickedB9()
{

	if (Flag == true) {


		str1 += _T("9");
		Edit_result = str1;
	}
	else {
		str2 += _T("9");
		Edit_result = str2;
	}
	UpdateData(FALSE);
}


void CMFCApplication1Dlg::OnBnClickedB7()
{
	if (Flag == true) {


		str1 += _T("7");
		Edit_result = str1;
	}
	else {
		str2 += _T("7");
		Edit_result = str2;
	}
	UpdateData(FALSE);
}





void CMFCApplication1Dlg::OnBnClickedBPlus()
{

	if (Edit_result != _T("")) {
		number1 = _ttof(Edit_result);
		Flag = !Flag;
		Edit_result = _T("");
		opera = 1;
	}

	
}

void CMFCApplication1Dlg::OnBnClickedBSub()
{
	if (Edit_result != _T("")) {
		number1 = _ttof(Edit_result);
		Flag = !Flag;
		Edit_result = _T("");
		opera = 2;
	}
}

void CMFCApplication1Dlg::OnBnClickedBMul()
{
	if (Edit_result != _T("")) {
		number1 = _ttof(Edit_result);
		Flag = !Flag;
		Edit_result = _T("");
		opera = 3;
	}
}

void CMFCApplication1Dlg::OnBnClickedBDiv()
{
	if (Edit_result != _T("")) {
		number1 = _ttof(Edit_result);
		Flag = !Flag;
		Edit_result = _T("");
		opera = 4;
	}
}

void CMFCApplication1Dlg::OnBnClickedBEqual()
{
	if (Edit_result != _T("")) {
		number2 = _ttof(Edit_result);
		Flag = !Flag;
		Edit_result = _T("");
	}
	 
	if (opera == 1) {
		number0 = number1 + number2;
	}
	if (opera == 2) {
		number0 = number1 - number2;
	}
	if (opera == 3) {
		number0 = number1 * number2;
	}
	if (opera == 4) {
		number0 = number1 / number2;
	}
	Edit_result.Format(_T("%.3f"), number0);
	UpdateData(FALSE);
	str1 = _T("");
	str2 = _T("");
	Flag = true;
}

void CMFCApplication1Dlg::OnBnClickedBPoint()
{
	if (Flag == true) {
		if (str1.Find(_T(".")) == -1) {   
			str1 += _T(".");
			Edit_result = str1;
		}
	}
	else {
		if (str2.Find(_T(".")) == -1) {  
			str2 += _T(".");
			Edit_result = str2;
		}
	}
	UpdateData(FALSE);
}



void CMFCApplication1Dlg::OnBnClickedBSign()
{
	if (Flag == true) {
		if (!str1.IsEmpty()) {
			if (str1[0] == _T('-'))
				str1.Delete(0, 1);   
			else
				str1 = _T("-") + str1;  
			Edit_result = str1;
		}
	}
	else {
		if (!str2.IsEmpty()) {
			if (str2[0] == _T('-'))
				str2.Delete(0, 1);
			else
				str2 = _T("-") + str2;
			Edit_result = str2;
		}
	}
	UpdateData(FALSE);
}







void CMFCApplication1Dlg::OnBnClickedBClear()
{
	str1 = _T("");
	str2 = _T("");
	number1 = number2 = number0 = 0;
	opera = 0;
	Flag = true;
	Edit_result = _T("0");
	SetDlgItemText(IDC_EDIT1, Edit_result);
	UpdateData(FALSE);
}

