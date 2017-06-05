
// �����߳�
//

#pragma once

/*
��һ�̣߳�
��������棬ͨ����Ϣ��������ʾ��Ϣ

�ڶ��̣߳�
����������Ϣ���ظ�
����ÿ���û����������߱༭ʱ��ά��һ����������
�ϴ���Ϣʱ������ͼÿ���û����²�������
�������ʱ�����Ͳ������в����
ע���ϴ��ֿ�����͹�ϵ������һ����λ������ȷ
Ҫ���ݴ��û��Ĵ����Ͳ������н��ж�λ����ת��

�����̣߳�
��ʱѭ������˼ά��ͼ
���û�ͬ��ʱ�䳬ʱ2s���������༭

����Ȩ���߼���
���û����߱༭ʱ��ȡ��Ȩ�ޣ�
���˼ά��ͼ�����Ӧ��
������û���������Ӧ��
�����û����ڱ༭״̬�������������
��������û�����״̬�ͱ༭��ͼָ��
�û��ٴ��������ʱ����û�в���������Ϊȡ��Ȩ��
��δ�ȵ��û�������¾��ּ���Ϊ�����û�
�ж�������״̬�ͱ༭��ͼָ�룬�����쳣�����������
ǿ���˳������������������ƥ��

�ֿ������߼���
���ֿ��������������û���Ϊ�û��༭����
û�������û�Ϊӵ�������ò��ɸ���
ӵ���߿��Ըı䲻�ɸ��ĵķֿ�
���ڿɸ��ķֿ飺
{
����ֿ�ʱ��������������û�
ͬʱ�ͷŸ��û���֮ǰ�����ֿ飨������ڣ�
�ͷ�ʱ�ͷŸ��û���֮ǰ�����ֿ�
}
���ڲ��ɸ��ķֿ飺
{
ֻ��ӵ���߿�������
����ʱ����¼�����û�
�ͷ�ʱ���������
}


*/


/****************************************************************/
/*************************������ͬ����ʼ*************************/
/****************************************************************/

#define SERVER_PORT "12345"


//tcp���ϼ�Э��
enum PacketType
{
	//��־λ
	defaultvalue,//ȱʡֵ
	error,//���Ӵ���
	success,//�ɹ�
	fail,//ʧ��
	nopermission,//û��Ȩ��
	clash,//��ͻ

	//�û���Ϣ����
	hello,//���ӷ�����
	login,//��¼
	regist,//ע��
	change,//�޸���Ϣ
	logout,//ע��
	getlist,//�����ȡ˼ά��ͼ�б�
	newmind,//�½�˼ά��ͼ
	selmind,//ѡ��˼ά��ͼ
	delmind,//ɾ��˼ά��ͼ
	editend,//�����༭

	//��ͼ�༭����
	changename,//��������
	addshare,//��ӹ����û�
	delshare,//ɾ�������û�
	lockblock,//��������������
	upmind,//�ϴ�˼ά��ͼ
	keepmind,//�޸ı�˼ά��ͼ
	downmind,//����˼ά��ͼ
	applyblock,//����༭�ֿ�
	finishblock,//��ɷֿ�༭
	blockaddroot,//��Ӹ��ֿ�
	blockdelwith,//�ֿ�ɾ�������ӷֿ�
	blockdelcombine,//�ֿ�ɾ���ϲ��ӷֿ�
	blockaddchild,//�ֿ�����ӷֿ�
	blockaddparent,//�ֿ���븸�ֿ�
	blocklineto,//�ֿ����ӵ��·ֿ�
	blockseparateroot,//�ֿ����Ϊ���ֿ�
	blockdelseparate,//�ֿ�ɾ�������ӷֿ�

};


//��֤���ճ��Ⱥ���
void CertainRecv(SOCKET sock, void *buf, int len);


//����CString
void SendCString(SOCKET sock, CString &string);


//����CString
void RecvCString(SOCKET sock, CString &string);

/****************************************************************/
/*************************������ͬ������*************************/
/****************************************************************/


//�����ʼ������
void ConnectInit();


//�����̻߳ص�����
UINT NetThreadFunc(LPVOID pParam);


//��Ӧhello
void RespondHello(SOCKET sock);


//��Ӧlogin
void RespondLogin(SOCKET sock);


//��Ӧregist
void RespondRegist(SOCKET sock);


//��Ӧchange
void RespondChange(SOCKET sock);


//��Ӧget
void RespondGetList(SOCKET sock);


//��Ӧnewmind
void RespondNewMind(SOCKET sock);


//��Ӧselmind
void RespondSelMind(SOCKET sock);


//��Ӧdelmind
void RespondDelMind(SOCKET sock);


//��Ӧeditend
void RespondEditEnd(SOCKET sock);


//��Ӧchangename
void RespondChangeName(SOCKET sock);


//��Ӧaddshare
void RespondAddShare(SOCKET sock);


//��Ӧdelshare
void RespondDelShare(SOCKET sock);


//��Ӧlockblock
void RespondLockBlock(SOCKET sock);


//��Ӧupmind
void RespondUpMind(SOCKET sock);


//��Ӧkeepmind
void RespondKeepMind(SOCKET sock);


//��Ӧdownmind
void RespondDownMind(SOCKET sock);


//��Ӧapplyblock
void RespondApplyBlock(SOCKET sock);


//��Ӧfinishblock
void RespondFinishBlock(SOCKET sock);


//��Ӧblockaddroot
void RespondBlockAddRoot(SOCKET sock);


//��Ӧblockdelwith
void RespondBlockDelWith(SOCKET sock);


//��Ӧblockdelcombine
void RespondBlockDelCombine(SOCKET sock);


//��Ӧblockaddchild
void RespondBlockAddChild(SOCKET sock);


//��Ӧblockaddparent
void RespondBlockAddParent(SOCKET sock);


//��Ӧblocklineto
void RespondBlockLineInto(SOCKET sock);


//��Ӧblockseparateroot
void RespondBlockSeparateRoot(SOCKET sock);


//��Ӧblockdelseparate
void RespondBlockDelSeparate(SOCKET sock);


//��ʾ��Ӧ�¼�
void ShowResiond(CString typestring, CString UserId, PacketType result);
