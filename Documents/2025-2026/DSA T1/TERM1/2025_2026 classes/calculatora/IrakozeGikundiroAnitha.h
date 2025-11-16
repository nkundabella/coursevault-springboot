
// MFCApplication1Dlg.h : header file
//

#pragma once


// CMFCApplication1Dlg dialog
class CMFCApplication1Dlg : public CDialogEx
{
// Construction
public:
	CMFCApplication1Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString Edit_result;
	bool Flag;
	int opera;
	float number1, number2,number0;
	CString str1, str2;
	afx_msg void OnBnClickedB0();
	afx_msg void OnBnClickedB2();
	afx_msg void OnBnClickedB3();
	afx_msg void OnBnClickedB6();
	afx_msg void OnBnClickedB5();
	afx_msg void OnBnClickedB4();
	afx_msg void OnBnClickedB8();
	afx_msg void OnBnClickedB9();
	afx_msg void OnBnClickedB7();
	afx_msg void OnBnClickedB1();
	afx_msg void OnBnClickedBPlus();
	afx_msg void OnBnClickedBSub();
	afx_msg void OnBnClickedBMul();
	afx_msg void OnBnClickedBDiv();
	afx_msg void OnBnClickedBEqual();
	afx_msg void OnBnClickedBPoint();
	afx_msg void OnBnClickedBSign();
	afx_msg void OnBnClickedBClear();
};
