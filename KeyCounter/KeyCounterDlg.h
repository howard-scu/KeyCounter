
// KeyCounterDlg.h : ͷ�ļ�
//

#pragma once


// CKeyCounterDlg �Ի���
class CKeyCounterDlg : public CDialogEx
{
// ����
public:
	CKeyCounterDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_KEYCOUNTER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
