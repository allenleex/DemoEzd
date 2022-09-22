// HostDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DemoEzd.h"
#include "HostDlg.h"
#include "CClientSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHostDlg dialog

CHostDlg::CHostDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHostDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHostDlg)
	m_strPort = _T("8888");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_hEzdDLL = NULL;
	lmc1_Initial = NULL;
	lmc1_Close = NULL;
	lmc1_LoadEzdFile = NULL;
	lmc1_Mark = NULL;
	lmc1_MarkEntity = NULL;
	lmc1_GetPrevBitmap = NULL;
	lmc1_ReadPort = NULL;
	lmc1_WritePort = NULL;

	lmc1_SetDevCfg = NULL;
	lmc1_SetHatchParam = NULL;
	lmc1_SetFontParam = NULL;
	lmc1_GetPenParam = NULL;
	lmc1_SetPenParam = NULL;
	lmc1_ClearEntLib = NULL;
	lmc1_AddTextToLib = NULL;
	lmc1_AddFileToLib = NULL;
	lmc1_AddBarCodeToLib = NULL;
	lmc1_ChangeTextByName = NULL;
	lmc1_MoveEnt = NULL;

	lmc1_AxisMoveTo = NULL;
	lmc1_AxisCorrectOrigin = NULL;
	lmc1_GetAxisCoor = NULL;
	lmc1_SaveEntLibToFile = NULL;
}

void CHostDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHostDlg)
	DDX_Text(pDX, IDC_PORT, m_strPort);
	DDX_Control(pDX, IDC_LOGLIST, m_logList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHostDlg, CDialog)
	//{{AFX_MSG_MAP(CHostDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDSTART, &CHostDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDSTOP2, &CHostDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDLOAD, &CHostDlg::OnBnClickedLoad)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHostDlg message handlers
void CHostDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here

	if (lmc1_Close != NULL)
	{
		lmc1_Close();
	}

	if (m_hEzdDLL != NULL)
	{
		FreeLibrary(m_hEzdDLL);//释放DLL句柄
		m_hEzdDLL = NULL;
	}
}

BOOL CHostDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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

	// 加载 MarkEzd.dll

	m_hEzdDLL = LoadLibrary(_T("MarkEzd.dll"));//加载动态连接库	
	if (m_hEzdDLL == NULL)
	{
		AfxMessageBox(_T("Can not find MarkEzd.dll!"));
	}
	else
	{
		lmc1_Initial = (LMC1_INITIAL)GetProcAddress(m_hEzdDLL, "lmc1_Initial");
		if (lmc1_Initial == NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_Initial in MarkEzd.dll!"));
		}

		lmc1_Close = (LMC1_CLOSE)GetProcAddress(m_hEzdDLL, "lmc1_Close");
		if (lmc1_Close == NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_Close in MarkEzd.dll!"));
		}

		lmc1_LoadEzdFile = (LMC1_LOADEZDFILE)GetProcAddress(m_hEzdDLL, "lmc1_LoadEzdFile");
		if (lmc1_LoadEzdFile == NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_LoadEzdFile in MarkEzd.dll!"));
		}

		lmc1_Mark = (LMC1_MARK)GetProcAddress(m_hEzdDLL, "lmc1_Mark");
		if (lmc1_Mark == NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_Mark in MarkEzd.dll!"));
		}

		lmc1_MarkEntity = (LMC1_MARKENTITY)GetProcAddress(m_hEzdDLL, "lmc1_MarkEntity");
		if (lmc1_MarkEntity == NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_MarkEntity in MarkEzd.dll!"));
		}

		lmc1_GetPrevBitmap = (LMC1_GETPREVBITMAP)GetProcAddress(m_hEzdDLL, "lmc1_GetPrevBitmap");
		if (lmc1_GetPrevBitmap == NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_GetPrevBitmap in MarkEzd.dll!"));
		}

		lmc1_ReadPort = (LMC1_READPORT)GetProcAddress(m_hEzdDLL, "lmc1_ReadPort");
		if (lmc1_ReadPort == NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_ReadPort in MarkEzd.dll!"));
		}

		lmc1_WritePort = (LMC1_WRITEPORT)GetProcAddress(m_hEzdDLL, "lmc1_WritePort");
		if (lmc1_WritePort == NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_WritePort in MarkEzd.dll!"));
		}

		lmc1_SetDevCfg = (LMC1_SETDEVCFG)GetProcAddress(m_hEzdDLL, "lmc1_SetDevCfg");
		if (lmc1_SetDevCfg == NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_SetDevCfg in MarkEzd.dll!"));
		}
		lmc1_SetHatchParam = (LMC1_SETHATCHPARAM)GetProcAddress(m_hEzdDLL, "lmc1_SetHatchParam");
		if (lmc1_SetHatchParam == NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_SetHatchParam in MarkEzd.dll!"));
		}
		lmc1_SetFontParam = (LMC1_SETFONTPARAM)GetProcAddress(m_hEzdDLL, "lmc1_SetFontParam");
		if (lmc1_SetFontParam == NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_SetFontParam in MarkEzd.dll!"));
		}
		lmc1_GetPenParam = (LMC1_GETPENPARAM)GetProcAddress(m_hEzdDLL, "lmc1_GetPenParam");
		if (lmc1_GetPenParam == NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_GetPenParam in MarkEzd.dll!"));
		}
		lmc1_SetPenParam = (LMC1_SETPENPARAM)GetProcAddress(m_hEzdDLL, "lmc1_SetPenParam");
		if (lmc1_SetPenParam == NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_SetPenParam in MarkEzd.dll!"));
		}

		lmc1_ClearEntLib = (LMC1_CLEARENTLIB)GetProcAddress(m_hEzdDLL, "lmc1_ClearEntLib");
		if (lmc1_ClearEntLib == NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_ClearEntLib in MarkEzd.dll!"));
		}
		lmc1_AddTextToLib = (LMC1_ADDTEXTTOLIB)GetProcAddress(m_hEzdDLL, "lmc1_AddTextToLib");
		if (lmc1_AddTextToLib == NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_AddTextToLib in MarkEzd.dll!"));
		}

		lmc1_AddFileToLib = (LMC1_ADDFILETOLIB)GetProcAddress(m_hEzdDLL, "lmc1_AddFileToLib");
		if (lmc1_AddFileToLib == NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_AddFileToLib in MarkEzd.dll!"));
		}

		lmc1_AddBarCodeToLib = (LMC1_ADDBARCODETOLIB)GetProcAddress(m_hEzdDLL, "lmc1_AddBarCodeToLib");
		if (lmc1_AddBarCodeToLib == NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_AddBarCodeToLib in MarkEzd.dll!"));
		}

		lmc1_ChangeTextByName = (LMC1_CHANGETEXTBYNAME)GetProcAddress(m_hEzdDLL, "lmc1_ChangeTextByName");
		if (lmc1_ChangeTextByName == NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_ChangeTextByName in MarkEzd.dll!"));
		}


		lmc1_AxisMoveTo = (LMC1_AXISMOVETO)GetProcAddress(m_hEzdDLL, "lmc1_AxisMoveTo");
		if (lmc1_AxisMoveTo == NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_AxisMoveTo in MarkEzd.dll!"));
		}
		lmc1_AxisCorrectOrigin = (LMC1_AXISCORRECTORIGIN)GetProcAddress(m_hEzdDLL, "lmc1_AxisCorrectOrigin");
		if (lmc1_AxisCorrectOrigin == NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_AxisCorrectOrigin in MarkEzd.dll!"));
		}
		lmc1_GetAxisCoor = (LMC1_GETAXISCOOR)GetProcAddress(m_hEzdDLL, "lmc1_GetAxisCoor");
		if (lmc1_GetAxisCoor == NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_GetAxisCoor in MarkEzd.dll!"));
		}

		lmc1_MoveEnt = (LMC1_MOVEENT)GetProcAddress(m_hEzdDLL, "lmc1_MoveEnt");
		if (lmc1_MoveEnt == NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_MoveEnt in MarkEzd.dll!"));
		}

		lmc1_SaveEntLibToFile = (LMC1_SAVEENTLIBTOFILE)GetProcAddress(m_hEzdDLL, "lmc1_SaveEntLibToFile");
		if (lmc1_SaveEntLibToFile == NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_SaveEntLibToFile in MarkEzd.dll!"));
		}

	}

	TCHAR path[_MAX_PATH];
	TCHAR drive[_MAX_DRIVE];
	TCHAR dir[_MAX_DIR];
	TCHAR fname[_MAX_FNAME];
	TCHAR ext[_MAX_EXT];
	GetModuleFileName(::AfxGetApp()->m_hInstance, path, _MAX_PATH);
	_wsplitpath(path, drive, dir, fname, ext);

	TCHAR strEzCadPath[256];

	_tcscpy(strEzCadPath, drive);
	_tcscat(strEzCadPath, dir);

	BOOL bTestMode = FALSE;

	int nErr = LMC1_ERR_SUCCESS;
	if (lmc1_Initial != NULL)
	{
		nErr = lmc1_Initial(strEzCadPath, bTestMode, GetSafeHwnd());
		if (nErr != LMC1_ERR_SUCCESS)
		{
			CString strErr;
			strErr.Format(_T("Initial lmc1 failed! ErrCode = %d"), nErr);
			AfxMessageBox(strErr);
		}
	}


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHostDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHostDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM)dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}


// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHostDlg::OnQueryDragIcon()
{
	return (HCURSOR)m_hIcon;
}

void CHostDlg::OnOK()
{
	// TODO: Add extra validation here

//	CDialog::OnOK();
}




void CHostDlg::OnBnClickedStart()
{
	// 打开TCP端口
	if (m_ListenSocket.Create(8888))
	{
		if (!m_ListenSocket.Listen())
		{
			AfxMessageBox(L"侦听端口失败");
		}
	}
	else
	{
		AfxMessageBox(L"创建网络服务失败");
	}
}


void CHostDlg::OnBnClickedStop()
{
	POSITION pos;
	pos = m_ListenSocket.m_ptrClientSocketList.GetHeadPosition();
	CClientSocket* pClient = NULL;

	while (pos != NULL)
	{
		pClient = (CClientSocket*)m_ListenSocket.m_ptrClientSocketList.GetNext(pos);

		if (pClient != NULL)
		{
			pClient->ShutDown();
			pClient->Close();

			delete pClient;
		}
	}

	m_ListenSocket.ShutDown();
	m_ListenSocket.Close();
}


void CHostDlg::OnBnClickedLoad()
{
	// TODO: 在此添加控件通知处理程序代码
}
