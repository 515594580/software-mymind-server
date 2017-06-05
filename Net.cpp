
// �����߳�
//

#include "stdafx.h"
#include "OurMindServer.h"
#include "OurMindServerDlg.h"



SOCKET g_WelcomeSocket;//������socket���

static int g_IntBuf[10000];//���λ�������



/****************************************************************/
/*************************������ͬ����ʼ*************************/
/****************************************************************/
//��֤���ճ��Ⱥ���
void CertainRecv(SOCKET sock, void *buf, int len)
{
	static char buf2[100000];
	int num = 0;
	int temp;
	while(num<len)
	{
		temp = recv(sock, buf2+num, len-num, 0);
		if(temp>0)
			num += temp;
	}
	memcpy(buf, buf2, len);
}


//����CString
void SendCString(SOCKET sock, CString &string)
{
	int len = string.GetLength()+1;
	send(sock, (char *)&len, sizeof(int), 0);
	send(sock, (char *)(LPCWSTR)string, sizeof(wchar_t)*len, 0);//�û���
}


//����CString
void RecvCString(SOCKET sock, CString &string)
{
	static wchar_t buf[100000] = {0};
	int len;
	CertainRecv(sock, &len, sizeof(int));
	CertainRecv(sock, buf, sizeof(wchar_t)*len);
	string = buf;
}
/****************************************************************/
/*************************������ͬ������*************************/
/****************************************************************/


//�����ʼ������
void ConnectInit()
{
    WSADATA wsaData;
    int iResult = WSAStartup( MAKEWORD(2,2), &wsaData );
    if ( iResult != NO_ERROR )
        assert(0);

    //create server's socket��socket����һ�����
    g_WelcomeSocket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

    if ( g_WelcomeSocket == INVALID_SOCKET ) {
        //printf( "Error at socket(): %ld\n", WSAGetLastError() );
		assert(0);
        WSACleanup();
    }

    //bind server socket with the port and ip address�����Լ���ip�˿ڣ�������socket
    sockaddr_in service;


    service.sin_family = AF_INET;
    service.sin_addr.s_addr = INADDR_ANY;
    service.sin_port = htons(atoi(SERVER_PORT));

    if(bind(g_WelcomeSocket, (SOCKADDR*)&service, sizeof(service))==SOCKET_ERROR)
	{
        //printf( "bind() failed.\n" );
		assert(0);
        closesocket(g_WelcomeSocket);
        return;
    }

    //listening socket binded with port׼��������������������
    if ( listen( g_WelcomeSocket, 10 ) == SOCKET_ERROR )
        //printf( "Error listening on socket.\n");
		assert(0);
}


//�����̻߳ص�����
UINT NetThreadFunc(LPVOID pParam)
{
	//��ʼ�����ݿ�
	DataInit();

	//��ʼ������
	ConnectInit();

	while(1)//ѭ���������ӶϿ�����
	{
		SOCKET ConnectSocket=SOCKET_ERROR;

		while (ConnectSocket==SOCKET_ERROR) //�ȴ�����
		{
			ConnectSocket = accept(g_WelcomeSocket, NULL, NULL);//�������ӣ��ҵ�socket��������ضԷ�socket���
		}

		//�������ݰ�
		PacketType type;
		CertainRecv(ConnectSocket, &type, sizeof(type));
		//�ж����ݰ�����
		switch(type)
		{
			//�û���Ϣ����
		case hello:
			RespondHello(ConnectSocket);
			break;
		case login:
			RespondLogin(ConnectSocket);
			break;
		case regist:
			RespondRegist(ConnectSocket);
			break;
		case change:
			RespondChange(ConnectSocket);
			break;
		case getlist:
			RespondGetList(ConnectSocket);
			break;
		case newmind:
			RespondNewMind(ConnectSocket);
			break;
		case selmind:
			RespondSelMind(ConnectSocket);
			break;
		case delmind:
			RespondDelMind(ConnectSocket);
			break;
		case editend:
			RespondEditEnd(ConnectSocket);
			break;

			//��ͼ�༭����
		case changename:
			RespondChangeName(ConnectSocket);
			break;
		case upmind:
			RespondUpMind(ConnectSocket);
			break;
		case keepmind:
			RespondKeepMind(ConnectSocket);
			break;
		case downmind:
			RespondDownMind(ConnectSocket);
			break;
		case addshare:
			RespondAddShare(ConnectSocket);
			break;
		case delshare:
			RespondDelShare(ConnectSocket);
			break;
		case lockblock:
			RespondLockBlock(ConnectSocket);
			break;
		case applyblock:
			RespondApplyBlock(ConnectSocket);
			break;
		case finishblock:
			RespondFinishBlock(ConnectSocket);
			break;
		case blockaddroot:
			RespondBlockAddRoot(ConnectSocket);
			break;
		case blockdelwith:
			RespondBlockDelWith(ConnectSocket);
			break;
		case blockdelcombine:
			RespondBlockDelCombine(ConnectSocket);
			break;
		case blockaddchild:
			RespondBlockAddChild(ConnectSocket);
			break;
		case blockaddparent:
			RespondBlockAddParent(ConnectSocket);
			break;
		case blocklineto:
			RespondBlockLineInto(ConnectSocket);
			break;
		case blockseparateroot:
			RespondBlockSeparateRoot(ConnectSocket);
			break;
		case blockdelseparate:
			RespondBlockDelSeparate(ConnectSocket);
			break;

		default:
			assert(0);
			break;
		}
		//�Ͽ�����
		closesocket(ConnectSocket);
	}

	return 0;
}


//��Ӧhello
void RespondHello(SOCKET sock)
{
	//����
	PacketType type;
	type = success;
	send(sock, (char *)&type, sizeof(type), 0);//��־
	//������Ϣ
	ShowResiond(L"hello", L"", defaultvalue);
}


//��Ӧlogin
void RespondLogin(SOCKET sock)
{
	//����
	CString UserId, Password;
	RecvCString(sock, UserId);//�û���
	RecvCString(sock, Password);//����
	//����
	PacketType type;
	if(TestUser(UserId, Password))
		type = success;
	else
		type = fail;
	//����
	send(sock, (char *)&type, sizeof(type), 0);//��־
	//������Ϣ
	ShowResiond(L"login", UserId, type);
}


//��Ӧregist
void RespondRegist(SOCKET sock)
{
	//����
	CString UserId, Password;
	RecvCString(sock, UserId);//�û���
	RecvCString(sock, Password);//����
	//����
	PacketType type;
	if(AddUser(UserId, Password))
		type = success;
	else
		type = fail;
	//����
	send(sock, (char *)&type, sizeof(type), 0);//��־
	//������Ϣ
	ShowResiond(L"regist", UserId, type);
}


//��Ӧchange
void RespondChange(SOCKET sock)
{
	//����
	CString UserId, Password, Password2;
	RecvCString(sock, UserId);//�û���
	RecvCString(sock, Password);//����
	RecvCString(sock, Password2);//������
	//����
	PacketType type;
	if(ChangeUser(UserId, Password, Password2))
		type = success;
	else
		type = fail;
	//����
	send(sock, (char *)&type, sizeof(type), 0);//��־
	//������Ϣ
	ShowResiond(L"change", UserId, type);
}


//��Ӧgetlist
void RespondGetList(SOCKET sock)
{
	//����
	CString UserId;
	RecvCString(sock, UserId);//�û���
	//����EditEnd
	PacketType type;
	type = EditEnd(UserId);
	//������Ϣ
	ShowResiond(L"(editend)", UserId, type);
	//��������getlist
	//����
	ListTemplet<MindNode> *pMindList;
	pMindList = GetOwnMindList(UserId);
	//����
	pMindList->Send(sock);//ӵ��˼ά��ͼ
	//����
	pMindList = BuildJoinMindList(UserId);
	//����
	pMindList->Send(sock);//����˼ά��ͼ
	delete pMindList;
	//������Ϣ
	ShowResiond(L"getlist", UserId, defaultvalue);
}


//��Ӧnewmind
void RespondNewMind(SOCKET sock)
{
	//����
	CString UserId;
	RecvCString(sock, UserId);//�û���
	//����
	MindNode *pTheMind = NewMind(UserId);
	//����
	pTheMind->Send(sock);//��˼ά��ͼ
	pTheMind->BlockTree.Send(sock);//��˼ά��ͼ�ֿ���
	//������Ϣ
	ShowResiond(L"newmind", UserId, defaultvalue);
}


//��Ӧselmind
void RespondSelMind(SOCKET sock)
{
	//����
	CString UserId, MindUserId, MindName;
	RecvCString(sock, UserId);//�û���
	RecvCString(sock, MindUserId);//˼ά��ͼӵ����
	RecvCString(sock, MindName);//˼ά��ͼ����
	//����
	MindNode *pTheMind = SelMind(UserId, MindUserId, MindName);
	PacketType type;
	if(pTheMind)
	{
		//����
		type = success;
		send(sock, (char *)&type, sizeof(type), 0);//��־
		pTheMind->Send(sock);//˼ά��ͼ
		pTheMind->BlockTree.Send(sock);//˼ά��ͼ�ֿ���
	}
	else
	{
		//����
		send(sock, (char *)&type, sizeof(type), 0);//��־
		type = fail;
	}
	//������Ϣ
	ShowResiond(L"selmind", UserId, defaultvalue);
}


//��Ӧdelmind
void RespondDelMind(SOCKET sock)
{
	//����
	CString UserId, MindName;
	RecvCString(sock, UserId);//�û���
	RecvCString(sock, MindName);//˼ά��ͼ����
	//����
	PacketType type;
	if(DelMind(UserId, MindName))
		type = defaultvalue;
	else
		type = fail;
	//������Ϣ
	ShowResiond(L"delmind", UserId, type);
}


//��Ӧeditend
void RespondEditEnd(SOCKET sock)
{
	//����
	CString UserId;
	RecvCString(sock, UserId);//�û���
	//����
	PacketType type;
	type = EditEnd(UserId);
	//������Ϣ
	ShowResiond(L"editend", UserId, type);
}


//��Ӧchangename
void RespondChangeName(SOCKET sock)
{
	//����
	CString UserId, MindName;
	RecvCString(sock, UserId);//�û���
	RecvCString(sock, MindName);//˼ά��ͼ������
	//����
	PacketType type = ChangeName(UserId, MindName);
	//����
	send(sock, (char *)&type, sizeof(type), 0);//��־
	//������Ϣ
	ShowResiond(L"changename", UserId, type);
}


//��Ӧaddshare
void RespondAddShare(SOCKET sock)
{
	//����
	CString UserId, ShareUserId;
	RecvCString(sock, UserId);//�û���
	RecvCString(sock, ShareUserId);//�����û�����
	//����
	PacketType type = AddShare(UserId, ShareUserId);
	//����
	send(sock, (char *)&type, sizeof(type), 0);//��־
	//������Ϣ
	ShowResiond(L"addshare", UserId, type);
}


//��Ӧdelshare
void RespondDelShare(SOCKET sock)
{
	//����
	CString UserId, ShareUserId;
	RecvCString(sock, UserId);//�û���
	RecvCString(sock, ShareUserId);//�����û�����
	//����
	PacketType type = DelShare(UserId, ShareUserId);
	//����
	send(sock, (char *)&type, sizeof(type), 0);//��־
	//������Ϣ
	ShowResiond(L"delshare", UserId, type);
}


//��Ӧlockblock
void RespondLockBlock(SOCKET sock)
{
	//����
	CString UserId;
	int deep;
	bool IsLock, SetWith;
	RecvCString(sock, UserId);//�û���
	CertainRecv(sock, &deep, sizeof(deep));//��λ����
	CertainRecv(sock, g_IntBuf, sizeof(int)*deep);//��λ����
	CertainRecv(sock, &IsLock, sizeof(IsLock));//�Ƿ�����
	CertainRecv(sock, &SetWith, sizeof(SetWith));//��������
	//����
	ListTemplet<OperateNode> *pOperateList;
	PacketType type = LockBlock(UserId, deep, g_IntBuf, pOperateList, IsLock, SetWith);
	//����
	send(sock, (char *)&type, sizeof(type), 0);//��־
	if(type==success)
	{
		pOperateList->Send(sock);//��������
		pOperateList->Clear();//��ղ�������
	}
	//������Ϣ
	ShowResiond(L"lockblock", UserId, type);
}


//��Ӧupmind
void RespondUpMind(SOCKET sock)
{
	//����
	CString UserId;
	MindNode TheMind;
	RecvCString(sock, UserId);//�û���
	TheMind.Recv(sock);//˼ά��ͼ
	//����
	ListTemplet<OperateNode> *pOperateList;
	PacketType type = UpMind(UserId, TheMind, pOperateList);
	//����
	send(sock, (char *)&type, sizeof(type), 0);//��־
	if(type==success)
	{
		pOperateList->Send(sock);//��������
		//������Ϣ
		if(pOperateList->num>0)
			ShowResiond(L"upmind", UserId, type);
		else
		{
			//��ע��
			ShowResiond(L"upmind", UserId, defaultvalue);
		}
		pOperateList->Clear();//��ղ�������
	}
	else
	{
		//������Ϣ
		ShowResiond(L"upmind", UserId, type);
	}
}


//��Ӧkeepmind
void RespondKeepMind(SOCKET sock)
{
	//����
	CString UserId;
	RecvCString(sock, UserId);//�û���
	//����
	ListTemplet<OperateNode> *pOperateList;
	PacketType type = KeepMind(UserId, pOperateList);
	//����
	send(sock, (char *)&type, sizeof(type), 0);//��־
	if(type==success)
	{
		pOperateList->Send(sock);//��������
		//������Ϣ
		if(pOperateList->num>0)
			ShowResiond(L"keepmind", UserId, type);
		else
		{
			//��ע��
			ShowResiond(L"keepmind", UserId, defaultvalue);
		}
		pOperateList->Clear();//��ղ�������
	}
	else
	{
		//������Ϣ
		ShowResiond(L"keepmind", UserId, type);
	}
}


//��Ӧdownmind
void RespondDownMind(SOCKET sock)
{
	//����
	CString UserId;
	RecvCString(sock, UserId);//�û���
	//����
	ListTemplet<OperateNode> *pOperateList;
	PacketType type = DownMind(UserId, pOperateList);
	//����
	send(sock, (char *)&type, sizeof(type), 0);//��־
	if(type==success || type==fail)
	{
		pOperateList->Send(sock);//��������
		//������Ϣ
		if(pOperateList->num>0)
			ShowResiond(L"downmind", UserId, type);
		else
		{
			//��ע��
			ShowResiond(L"downmind", UserId, defaultvalue);
		}
		pOperateList->Clear();//��ղ�������
	}
	else
	{
		//������Ϣ
		ShowResiond(L"downmind", UserId, type);
	}
}


//��Ӧapplyblock
void RespondApplyBlock(SOCKET sock)
{
	//����
	CString UserId;
	int Deep;
	RecvCString(sock, UserId);//�û���
	CertainRecv(sock, &Deep, sizeof(Deep));//���
	CertainRecv(sock, g_IntBuf, sizeof(int)*Deep);//��λ����
	//����
	ListTemplet<OperateNode> *pOperateList;
	PacketType type = ApplyBlock(UserId, g_IntBuf, Deep, pOperateList);
	//����
	send(sock, (char *)&type, sizeof(type), 0);//��־
	if(type==success)
	{
		pOperateList->Send(sock);//��������
		//������Ϣ
		ShowResiond(L"applyblock", UserId, type);
		pOperateList->Clear();//��ղ�������
	}
	else
	{
		//������Ϣ
		ShowResiond(L"applyblock", UserId, type);
	}
}


//��Ӧfinishblock
void RespondFinishBlock(SOCKET sock)
{
	//����
	CString UserId;
	BlockNode TheBlock;
	RecvCString(sock, UserId);//�û���
	TheBlock.Recv(sock);//�ֿ�����
	//����
	ListTemplet<OperateNode> *pOperateList;
	PacketType type = FinishBlock(UserId, TheBlock, pOperateList);
	//����
	send(sock, (char *)&type, sizeof(type), 0);//��־
	if(type==success)
	{
		pOperateList->Send(sock);//��������
		//������Ϣ
		ShowResiond(L"finishblock", UserId, type);
		pOperateList->Clear();//��ղ�������
	}
	else if(type==fail)
	{
		TheBlock.Send(sock);//�ֿ�����
		ShowResiond(L"finishblock", UserId, type);
	}
	else
	{
		//������Ϣ
		ShowResiond(L"finishblock", UserId, type);
	}
}


//��Ӧblockaddroot
void RespondBlockAddRoot(SOCKET sock)
{
	//����
	CString UserId;
	int x, y;
	RecvCString(sock, UserId);//�û���
	CertainRecv(sock, &x, sizeof(x));//����x
	CertainRecv(sock, &y, sizeof(y));//����y
	//����
	ListTemplet<OperateNode> *pOperateList;
	PacketType type = BlockAddRoot(UserId, x, y, pOperateList);
	//����
	send(sock, (char *)&type, sizeof(type), 0);//��־
	if(type==success || type==fail)
	{
		pOperateList->Send(sock);//��������
		//������Ϣ
		ShowResiond(L"blockaddroot", UserId, type);
		pOperateList->Clear();//��ղ�������
	}
	else
	{
		//������Ϣ
		ShowResiond(L"blockaddroot", UserId, type);
	}
}


//��Ӧblockdelwith
void RespondBlockDelWith(SOCKET sock)
{
	//����
	CString UserId;
	BlockNode TheBlock;
	RecvCString(sock, UserId);//�û���
	//����
	ListTemplet<OperateNode> *pOperateList;
	PacketType type = BlockDelWith(UserId, TheBlock, pOperateList);
	//����
	send(sock, (char *)&type, sizeof(type), 0);//��־
	if(type==success)
	{
		pOperateList->Send(sock);//��������
		pOperateList->Clear();//��ղ�������
	}
	else if(type==fail)
	{
		TheBlock.Send(sock);//�ֿ�����
	}
	//������Ϣ
	ShowResiond(L"blockdelwith", UserId, type);
}


//��Ӧblockdelcombine
void RespondBlockDelCombine(SOCKET sock)
{
	//����
	CString UserId;
	BlockNode TheBlock;
	RecvCString(sock, UserId);//�û���
	//����
	ListTemplet<OperateNode> *pOperateList;
	PacketType type = BlockDelCombine(UserId, TheBlock, pOperateList);
	//����
	send(sock, (char *)&type, sizeof(type), 0);//��־
	if(type==success)
	{
		pOperateList->Send(sock);//��������
		pOperateList->Clear();//��ղ�������
	}
	else if(type==fail)
	{
		TheBlock.Send(sock);//�ֿ�����
	}
	//������Ϣ
	ShowResiond(L"blockdelcombine", UserId, type);
}


//��Ӧblockaddchild
void RespondBlockAddChild(SOCKET sock)
{
	//����
	CString UserId;
	BlockNode TheBlock;
	int x, y;
	RecvCString(sock, UserId);//�û���
	CertainRecv(sock, &x, sizeof(x));//����x
	CertainRecv(sock, &y, sizeof(y));//����y
	//����
	ListTemplet<OperateNode> *pOperateList;
	PacketType type = BlockAddChild(UserId, TheBlock, pOperateList, x, y);
	//����
	send(sock, (char *)&type, sizeof(type), 0);//��־
	if(type==success)
	{
		pOperateList->Send(sock);//��������
		pOperateList->Clear();//��ղ�������
	}
	else if(type==fail)
	{
		TheBlock.Send(sock);//�ֿ�����
	}
	//������Ϣ
	ShowResiond(L"blockaddchild", UserId, type);
}


//��Ӧblockaddparent
void RespondBlockAddParent(SOCKET sock)
{
	//����
	CString UserId;
	BlockNode TheBlock;
	int x, y;
	RecvCString(sock, UserId);//�û���
	CertainRecv(sock, &x, sizeof(x));//����x
	CertainRecv(sock, &y, sizeof(y));//����y
	//����
	ListTemplet<OperateNode> *pOperateList;
	PacketType type = BlockAddParent(UserId, TheBlock, pOperateList, x, y);
	//����
	send(sock, (char *)&type, sizeof(type), 0);//��־
	if(type==success)
	{
		pOperateList->Send(sock);//��������
		pOperateList->Clear();//��ղ�������
	}
	else if(type==fail)
	{
		TheBlock.Send(sock);//�ֿ�����
	}
	//������Ϣ
	ShowResiond(L"blockaddparent", UserId, type);
}


//��Ӧblocklineto
void RespondBlockLineInto(SOCKET sock)
{
	//����
	CString UserId;
	BlockNode TheBlock;
	RecvCString(sock, UserId);//�û���
	int deep;
	//����
	ListTemplet<OperateNode> *pOperateList;
	CertainRecv(sock, &deep, sizeof(deep));//��λ����
	CertainRecv(sock, g_IntBuf, sizeof(int)*deep);//��λ����
	PacketType type = BlockLineInto(UserId, TheBlock, pOperateList, deep, g_IntBuf);
	//����
	send(sock, (char *)&type, sizeof(type), 0);//��־
	if(type==success)
	{
		pOperateList->Send(sock);//��������
		pOperateList->Clear();//��ղ�������
	}
	else if(type==fail)
	{
		TheBlock.Send(sock);//�ֿ�����
	}
	//������Ϣ
	ShowResiond(L"blocklineto", UserId, type);
}


//��Ӧblockseparateroot
void RespondBlockSeparateRoot(SOCKET sock)
{
	//����
	CString UserId;
	BlockNode TheBlock;
	RecvCString(sock, UserId);//�û���
	//����
	ListTemplet<OperateNode> *pOperateList;
	PacketType type = BlockSeparateRoot(UserId, TheBlock, pOperateList);
	//����
	send(sock, (char *)&type, sizeof(type), 0);//��־
	if(type==success)
	{
		pOperateList->Send(sock);//��������
		pOperateList->Clear();//��ղ�������
	}
	else if(type==fail)
	{
		TheBlock.Send(sock);//�ֿ�����
	}
	//������Ϣ
	ShowResiond(L"blockseparateroot", UserId, type);
}


//��Ӧblockdelseparate
void RespondBlockDelSeparate(SOCKET sock)
{
	//����
	CString UserId;
	BlockNode TheBlock;
	RecvCString(sock, UserId);//�û���
	//����
	ListTemplet<OperateNode> *pOperateList;
	PacketType type = BlockDelSeparate(UserId, TheBlock, pOperateList);
	//����
	send(sock, (char *)&type, sizeof(type), 0);//��־
	if(type==success)
	{
		pOperateList->Send(sock);//��������
		pOperateList->Clear();//��ղ�������
	}
	else if(type==fail)
	{
		TheBlock.Send(sock);//�ֿ�����
	}
	//������Ϣ
	ShowResiond(L"blockdelseparate", UserId, type);
}


//��ʾ��Ӧ�¼�
void ShowResiond(CString typestring, CString UserId, PacketType result)
{
	SYSTEMTIME time;
	GetLocalTime(&time);
	CString *pstring = new CString;
	GetTime(time, *pstring);
	*pstring += L":\t"+typestring;
	*pstring += L",\t"+UserId;
	*pstring += L",\t";
	switch(result)
	{
	case error:
		*pstring += L"error";
		break;
	case success:
		*pstring += L"success";
		break;
	case fail:
		*pstring += L"fail";
		break;
	case nopermission:
		*pstring += L"nopermission";
		break;
	case clash:
		*pstring += L"clash";
		break;
	}
	*pstring += "\r\n";

	static HWND hWnd;//����Ϣ���½���
	if(hWnd = AfxGetMainWnd()->m_hWnd)
		::SendMessage(hWnd, WM_LAND_DEBUG, (WPARAM)pstring, 0);
}
