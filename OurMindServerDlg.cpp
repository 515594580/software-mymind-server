
// OurMindServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OurMindServer.h"
#include "OurMindServerDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COurMindServerDlg �Ի���



COurMindServerDlg::COurMindServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COurMindServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COurMindServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COurMindServerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &COurMindServerDlg::OnBnClickedOk)
	ON_MESSAGE(WM_LAND_DEBUG, &COurMindServerDlg::OnLandDebug)
	ON_BN_CLICKED(IDCANCEL, &COurMindServerDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// COurMindServerDlg ��Ϣ�������

BOOL COurMindServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	
	//�����������̲߳�����
	pNetThread = AfxBeginThread(NetThreadFunc, this);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void COurMindServerDlg::OnPaint()
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
HCURSOR COurMindServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//ָ���ؼ���ӻ�ɾ����ʾ�ַ���
afx_msg LRESULT COurMindServerDlg::OnLandDebug(WPARAM wParam, LPARAM lParam)
{
	CString *pstring = (CString *)wParam;
	if(pstring==0)
		LandString = L"";
	else
	{
		LandString += *pstring;
		delete pstring;
	}

	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT_LANDDEBUG);
	int Tab[] = {65};
	pEdit->SetTabStops(1, Tab);
	SetDlgItemText(IDC_EDIT_LANDDEBUG, LandString);
	SendDlgItemMessage(IDC_EDIT_LANDDEBUG,WM_VSCROLL, SB_BOTTOM,0);

	return 0;
}




void COurMindServerDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}

void COurMindServerDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	//�����û�����
	DataSave();

	CDialogEx::OnCancel();
}
