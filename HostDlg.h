// DemoEzdDlg.h : header file
//

#if !defined(AFX_HOSTDLG_H__D5C35BA8_57CF_4D71_B01B_C281D4F2E537__INCLUDED_)
#define AFX_HOSTDLG_H__D5C35BA8_57CF_4D71_B01B_C281D4F2E537__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHostDlg dialog
#include "resource.h"
#include "MarkEzdDll.h"
#include "ListenSocket.h"

class CHostDlg : public CDialog
{
// Construction
public:
	CHostDlg(CWnd* pParent = NULL);	// standard constructor

	HINSTANCE m_hEzdDLL;//DLL调用句柄

	LMC1_INITIAL       lmc1_Initial;
	LMC1_CLOSE         lmc1_Close;
	LMC1_LOADEZDFILE   lmc1_LoadEzdFile;
	LMC1_MARK          lmc1_Mark;
	LMC1_MARKENTITY    lmc1_MarkEntity;
	LMC1_GETPREVBITMAP lmc1_GetPrevBitmap;

	LMC1_READPORT  lmc1_ReadPort;
	LMC1_WRITEPORT lmc1_WritePort;

	LMC1_SETDEVCFG     lmc1_SetDevCfg;
	LMC1_SETHATCHPARAM lmc1_SetHatchParam;
	LMC1_SETFONTPARAM  lmc1_SetFontParam;
	LMC1_GETPENPARAM   lmc1_GetPenParam;
	LMC1_SETPENPARAM   lmc1_SetPenParam;
	LMC1_CLEARENTLIB   lmc1_ClearEntLib;
	LMC1_ADDTEXTTOLIB  lmc1_AddTextToLib;
	LMC1_ADDFILETOLIB  lmc1_AddFileToLib;
	LMC1_ADDBARCODETOLIB   lmc1_AddBarCodeToLib;
	LMC1_CHANGETEXTBYNAME  lmc1_ChangeTextByName;
	LMC1_AXISMOVETO        lmc1_AxisMoveTo;
	LMC1_AXISCORRECTORIGIN lmc1_AxisCorrectOrigin;
	LMC1_GETAXISCOOR       lmc1_GetAxisCoor;
	LMC1_SAVEENTLIBTOFILE  lmc1_SaveEntLibToFile;

	LMC1_MOVEENT lmc1_MoveEnt;



	// Dialog Data
		//{{AFX_DATA(CHostDlg)
	enum { IDD = IDD_HOST_DIALOG };
	CString	m_strPort;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHostDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHostDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedLoad();
public:
	CListBox m_logList;
	CListenSocket m_ListenSocket;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOSTDLG_H__D5C35BA8_57CF_4D71_B01B_C281D4F2E537__INCLUDED_)
