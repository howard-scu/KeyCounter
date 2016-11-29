
// KeyCounterDlg.cpp : 实现文件
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

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CKeyCounterDlg 对话框




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

// CKeyCounterDlg 消息处理程序

BOOL CKeyCounterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	if ( !SetHook ( TRUE ) )
	{
		szTooltip.Format( L"Key Counter初始化失败！" ) ;
		OnDestroy();
	}
	else
		szTooltip.Format(L"Key Counter初始化成功！");

	m_notify.cbSize=sizeof NOTIFYICONDATA;  
	m_notify.hWnd=this->m_hWnd;    
	m_notify.uID=IDI_ICON2;  
	m_notify.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON2));  
	m_notify.uCallbackMessage=WM_SHOWTASK;  
	m_notify.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP; //OK,下面就是托盘产生了.
	//szTooltip.Format(L"Key Counter\n");
	wcscpy(m_notify.szTip,szTooltip);
	Shell_NotifyIcon(NIM_ADD,&m_notify);


	// 启动时采用SW_HIDE无效
	// ShowWindow(SW_HIDE);

	SetTimer(1 , 1000/*ms*/ , NULL);
	count = 0;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CKeyCounterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CKeyCounterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CKeyCounterDlg::OnBnClickedAddHook()
{
	if ( !SetHook ( TRUE ) )
		this->MessageBox ( L"安装键盘钩子失败！" ) ;

}

void CKeyCounterDlg::OnBnClickedRemoveHook()
{
	if ( !SetHook ( FALSE ) )
		this->MessageBox ( L"卸载键盘钩子失败！" ) ;
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
	case WM_RBUTTONUP:                                 // 右键起来时弹出菜单
		{
			LPPOINT lpoint = new tagPOINT;
			::GetCursorPos(lpoint);                    // 得到鼠标位置
			CMenu menu;
			menu.CreatePopupMenu();                    // 声明一个弹出式菜单
			menu.AppendMenu(MF_STRING, WM_DESTROY, L"关闭");
			menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x ,lpoint->y, this);
			HMENU hmenu = menu.Detach();
			menu.DestroyMenu();
			delete lpoint;
		}
		break;
	case WM_LBUTTONDBLCLK:                           // 双击左键的处理
		{
			this->ShowWindow(SW_SHOWNORMAL);         // 显示主窗口
			// TODO: 创建对话框
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
		ShowWindow(SW_HIDE); // 当最小化市，隐藏主窗口              
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
   //    KillTimer(1);		// 这个貌似应该有DeleteTimer之类的。。不过我没找到。。
   //    ShowWindow(SW_HIDE);  // 隐掉它。。
   //}
}

void CKeyCounterDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CDialogEx::OnWindowPosChanging(lpwndpos);
	lpwndpos->flags &=~SWP_SHOWWINDOW;
	CDialog::OnWindowPosChanging(lpwndpos);
}
