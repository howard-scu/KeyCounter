
// KeyCounterDlg.h : 头文件
//

#pragma once


// CKeyCounterDlg 对话框
class CKeyCounterDlg : public CDialogEx
{
// 构造
public:
	CKeyCounterDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_KEYCOUNTER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAddHook();
	afx_msg void OnBnClickedRemoveHook();
	afx_msg void OnBnClickedRemoveHook2();
	afx_msg void OnBnClickedBtn();
	LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);
	NOTIFYICONDATA m_notify;  
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent); 
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
};
