
// KeyCounterDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KeyCounter.h"
#include "KeyCounterDlg.h"
#include "afxdialogex.h"
#include "../KeyboardHook/keyboard.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define WM_SHOWTASK (WM_USER+100)

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CKeyCounterDlg �Ի���




CKeyCounterDlg::CKeyCounterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CKeyCounterDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON2);
}

void CKeyCounterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CKeyCounterDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD_HOOK, &CKeyCounterDlg::OnBnClickedAddHook)
	ON_BN_CLICKED(IDC_REMOVE_HOOK, &CKeyCounterDlg::OnBnClickedRemoveHook)
	ON_BN_CLICKED(IDC_BTN, &CKeyCounterDlg::OnBnClickedBtn)
	ON_MESSAGE(WM_SHOWTASK,OnShowTask)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()

#include <Strsafe.h>

// CKeyCounterDlg ��Ϣ�������

BOOL CKeyCounterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	if ( !SetHook ( TRUE ) )
	{
		szTooltip.Format( L"Key Counter��ʼ��ʧ�ܣ�" ) ;
		OnDestroy();
	}
	else
		szTooltip.Format(L"Key Counter��ʼ���ɹ���");

	m_notify.cbSize=sizeof NOTIFYICONDATA;  
	m_notify.hWnd=this->m_hWnd;    
	m_notify.uID=IDI_ICON2;  
	m_notify.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON2));  
	m_notify.uCallbackMessage=WM_SHOWTASK;  
	m_notify.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP; //OK,����������̲�����.
	//szTooltip.Format(L"Key Counter\n");
	wcscpy(m_notify.szTip,szTooltip);
	Shell_NotifyIcon(NIM_ADD,&m_notify);


	// ����ʱ����SW_HIDE��Ч
	// ShowWindow(SW_HIDE);

	SetTimer(1 , 1000/*ms*/ , NULL);
	count = 0;
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CKeyCounterDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CKeyCounterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CKeyCounterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CKeyCounterDlg::OnBnClickedAddHook()
{
	if ( !SetHook ( TRUE ) )
		this->MessageBox ( L"��װ���̹���ʧ�ܣ�" ) ;

}

void CKeyCounterDlg::OnBnClickedRemoveHook()
{
	if ( !SetHook ( FALSE ) )
		this->MessageBox ( L"ж�ؼ��̹���ʧ�ܣ�" ) ;
}

void CKeyCounterDlg::OnBnClickedBtn()
{
	CString str;
	str.Format(L"%d", GetKeyCount());
	::MessageBox ( NULL, str,L"" ,MB_OK );
}


LRESULT CKeyCounterDlg::OnShowTask(WPARAM wParam, LPARAM lParam)
{
	if(wParam != IDI_ICON2)
		return 1;
	switch(lParam)
	{
	case WM_RBUTTONUP:                                 // �Ҽ�����ʱ�����˵�
		{
			LPPOINT lpoint = new tagPOINT;
			::GetCursorPos(lpoint);                    // �õ����λ��
			CMenu menu;
			menu.CreatePopupMenu();                    // ����һ������ʽ�˵�
			menu.AppendMenu(MF_STRING, WM_DESTROY, L"�ر�");
			menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x ,lpoint->y, this);
			HMENU hmenu = menu.Detach();
			menu.DestroyMenu();
			delete lpoint;
		}
		break;
	case WM_LBUTTONDBLCLK:                           // ˫������Ĵ���
		{
			this->ShowWindow(SW_SHOWNORMAL);         // ��ʾ������
			// TODO: �����Ի���
		}
		break;
	}
	return 0;
}

void CKeyCounterDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if(nType == SIZE_MINIMIZED)  
	{  
		ShowWindow(SW_HIDE); // ����С���У�����������              
	}  
}


void CKeyCounterDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	Shell_NotifyIcon(NIM_DELETE,&m_notify);
}

void CKeyCounterDlg::OnTimer(UINT nIDEvent)  
{
	szTooltip.Format(L"Key Press Counts: %d\n",GetKeyCount());
	wcscpy(m_notify.szTip,szTooltip);
	Shell_NotifyIcon(NIM_MODIFY,&m_notify);

	//count++;
	//CString  str;
	//str.Format(L"%d",count);
	//TRACE(str);
   //if (nIDEvent == 1)
   //{
   //    KillTimer(1);		// ���ò��Ӧ����DeleteTimer֮��ġ���������û�ҵ�����
   //    ShowWindow(SW_HIDE);  // ����������
   //}
}

void CKeyCounterDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CDialogEx::OnWindowPosChanging(lpwndpos);
	lpwndpos->flags &=~SWP_SHOWWINDOW;
	CDialog::OnWindowPosChanging(lpwndpos);
}
