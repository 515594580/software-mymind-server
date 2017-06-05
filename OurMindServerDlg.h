
// OurMindServerDlg.h : ͷ�ļ�
//

#pragma once


#define WM_LAND_DEBUG WM_USER+1


// COurMindServerDlg �Ի���
class COurMindServerDlg : public CDialogEx
{
// ����
public:
	COurMindServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_OURMINDSERVER_DIALOG };
	
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


	//����
private:
	CWinThread *pNetThread;//���繤�����߳�ָ��
	CString LandString;//LandDebug�ַ���


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
protected:
	afx_msg LRESULT OnLandDebug(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedCancel();
};
