
// ���ݿ�
//

#pragma once

#define USER_NUM 1000


//�ļ��洢�ṹ��
/*
�ļ�Ŀ¼��
{
UserData.dat
MindData.dat
(���MindNum��)<UserName>_<MindName>.mind
}

�ļ��ڲ��ṹ�洢��
UserData.dat��
{
(int)UserNum
(UserNum��)(tUserData)UserData
}

MindData.dat��
{
(int)UserNum
(UserNum��)(ListTemplet<class BlockNode>)MindList
}


<UserName>_<MindName>.mind


���к󣬶�ȡ UserData.dat��MindData.dat �ļ�
<UserName>_<MindName>.mind �ļ��õ�ʱ�ٶ�ȡ


/****************************************************************/
/*************************������ͬ����ʼ*************************/
/****************************************************************/
/*
���ļ������ݽṹ
CString��
{
(int)Length
(Length��)(wchar_t)ch
}
����Ľṹ�������䶨��
*/

//�������
#define LIST_GO(list, p) ((list) = (list)->p)
#define LIST_FORCE(list, p, type) ((list) = (type)((list)->p))

#define MAX_SHARE 100//˼ά��ͼ���������
#define MAX_JOIN 100//������˼ά��ͼ��

#define MAX_BLOCK_DEEP 200//˼ά��ͼ������

#define DEFAULT_LENGTH 550//Ĭ�ϵ�ͼ��
#define DEFAULT_WIDTH 450//Ĭ�ϵ�ͼ��

#define DEFAULT_BLOCK_LENGTH 70//Ĭ�Ϸֿ鳤
#define DEFAULT_BLOCK_WIDTH 40//Ĭ�Ϸֿ��

#define MIN_LENGTH 110//��С��ͼ��
#define MIN_WIDTH 90//��С��ͼ��

#define MIN_BLOCK_LENGTH 14//��С�ֿ鳤
#define MIN_BLOCK_WIDTH 8//��С�ֿ��


//����ģ��
//�ļ������ݽṹ
/*
(int)num
(num��)(TYPE)Node
*/
template <typename TYPE>
class ListTemplet
{
	//����
public:

	TYPE * const qnode;
	TYPE *pnode;
	TYPE *ptail;
	int num;

	//����
public:
	ListTemplet(): qnode(new TYPE)
	{
		pnode = ptail = qnode;
		num = 0;
	};
	~ListTemplet()
	{
		pnode = qnode;
		while(pnode->pt)
		{
			//LIST_FORCE(pnode, pt, TYPE*);
			LIST_GO(pnode, pt);
			delete pnode->qt;
		}
		delete pnode;
	};
	void Add();//��pnode�������ڵ㣬pnodeָ���½ڵ�
	void Del();//ɾ��pnode����Ľڵ㣬pnode����
	TYPE *Cut();//����pnode����Ľڵ㣬pnode����
	void Paste(TYPE *p);//��pnode����ճ���ڵ㣬pnodeָ���½ڵ�
	void Clear();//���������
	void ReadFile(FILE *fp);//���ļ���ȡ
	void WriteFile(FILE *fp);//д���ļ�
	void Send(SOCKET sock);//�����緢��
	void Recv(SOCKET sock);//���������
};
//����ڵ����
//�ļ������ݽṹ
/*
����TYPE�����麯������
*/
template <typename TYPE>
class NodeBase
{
	//����
public:
	TYPE *pt, *qt;

	//����
public:
	NodeBase()
	{
		pt = qt = 0;
	};
	virtual void ReadFile(FILE *fp){};//���ļ���ȡ
	virtual void WriteFile(FILE *fp){};//д���ļ�
	virtual void Send(SOCKET sock){};//�����緢��
	virtual void Recv(SOCKET sock){};//���������
};


//��ģ��
//�ļ������ݽṹ
//���ڵ�ݹ�Ķ��壬��ʼΪ���ڵ�ĵ�һ���ӽڵ�
/*
(��ǰ�ڵ㼰���ֵܽڵ������)
{
(bool)true
(�ݹ�洢)(��һ���ӽڵ�)
(TYPE)Node
}
(bool)false
*/
template <typename TYPE>
class TreeTemplet
{
	//����
public:
	TYPE * const qnode;
	TYPE *pnode;

	//����
public:
	TreeTemplet(): qnode(new TYPE)
	{
		pnode = qnode;
	};
	~TreeTemplet()
	{
		while(qnode->pch)
		{
			pnode = qnode->pch;
			Del();
		}
		delete qnode;
	};
	void Add();//��pnode��������½ڵ���Ϊ��һ���ӽڵ㣬pnodeָ���½ڵ�
	int Del();//ɾ��pnode�ڵ㣬���ӽڵ��Ϊ�丸�ڵ�ĵ�һ���ӽڵ㣬��������ţ�pnodeָ���丸�ڵ㣬�����ӽڵ����
	TYPE *Cut();//����pnode�ڵ㣬pnodeָ���丸�ڵ�
	void Paste(TYPE *p);//���ڵ����ӵ�pnode����
	int GetLocal(int string[]);//λ��ת��Ϊ����
	bool SetLocal(int string[], int num);//����������λ�ã��ɹ�����true
	void ReadFile(FILE *fp);//���ļ���ȡ
	void PartReadFile(FILE *fp, TYPE *p);//�ݹ���ļ���ȡ����
	void WriteFile(FILE *fp);//д���ļ�
	void PartWriteFile(FILE *fp, TYPE *p);//�ݹ�д���ļ�����
	void Send(SOCKET sock);//�����緢��
	void PartSend(SOCKET sock, TYPE *p);//�ݹ�����緢�Ͳ���
	void Recv(SOCKET sock);//���������
	void PartRecv(SOCKET sock, TYPE *p);//�ݹ��������ղ���
};
//���ڵ����
//�ļ������ݽṹ
/*
����TYPE�����麯������
*/
template <typename TYPE>
class TreeNodeBase
{
	//����
public:
	TYPE *pt, *qt;
	TYPE *pch, *ppr;

	//����
public:
	TreeNodeBase()
	{
		pt = qt = pch = ppr = 0;
	};
	virtual void ReadFile(FILE *fp){};//���ļ���ȡ
	virtual void WriteFile(FILE *fp){};//д���ļ�
	virtual void Send(SOCKET sock){};//�����緢��
	virtual void Recv(SOCKET sock){};//���������
};


//�û����ݽṹ��
//�ļ������ݽṹ
/*
(CString)UserId
(CString)Password
*/
struct tUserData
{
	//����
public:

	//������
	CString UserId;//�û���
	CString Password;//����
	int JoinNum;//����˼ά��ͼ��
	CString JoinUser[MAX_JOIN];//˼ά��ͼӵ��������
	CString JoinMind[MAX_JOIN];//˼ά��ͼ����

	//�ڴ����
	bool Online;//����״̬
	SYSTEMTIME LastTime;//�ϴ�keepʱ��
	class MindNode *pEditMind;//�༭��˼ά��ͼ
	class BlockNode *pLockBlock;//�����ķֿ�
	ListTemplet<class OperateNode> OperateList;//��������

	//���Ᵽ�����
	ListTemplet<class MindNode> MindList;//ӵ��˼ά��ͼ

	//����
public:
	tUserData();
	void ReadFile(FILE *fp);//���ļ���ȡ��Ϣ
	void WriteFile(FILE *fp);//����Ϣд���ļ�
};


//˼ά��ͼ�ڵ���
//�ļ������ݽṹ
/*
(CString)UserId
(CString)MindName
(int)Length
(int)Width
(bool)ReadOnly
(int)ShareNum
(ShareNum��)(CString)ShareUser
(CString)EditTime
*/
class MindNode: public NodeBase<MindNode>
{
	//����
public:

	//������
	CString UserId;//�û���
	CString MindName;//˼ά��ͼ����
	int Length; //��
	int Width;//��
	int Pos_X;//���ֿ�λ��x
	int Pos_Y;//���ֿ�λ��x
	bool ReadOnly; //�Ƿ�ֻ��
	int ShareNum;//�����û�����
	CString ShareUser[MAX_SHARE];//�����û���
	CString EditTime;//�༭ʱ��

	//�ڴ����
	int EditNum;//��ǰ�༭����
	bool EditStatus;//ӵ���߱༭״̬
	bool UserStatus[MAX_SHARE];//�û��༭״̬

	//���Ᵽ�����
	TreeTemplet<class BlockNode> BlockTree;//˼ά��ͼ�ֿ���

	//����
public:
	MindNode();
	void Copy(const MindNode &Node);//��������
	void ReadFile(FILE *fp);//���ļ���ȡ
	void WriteFile(FILE *fp);//д���ļ�
	void Send(SOCKET sock);//�����緢��
	void Recv(SOCKET sock);//���������
};


//��״ö��
enum enumShape 
{
	rect, //������
	rore, //Բ�Ǿ���
	round, //Բ��
	eche, //����
	diamond, //����
	para, //ƽ���ı���
	octa, //�˱���
};


//����ö��
enum enumDir 
{
	dirup,
	dirdown,
	dirleft,
	dirright,
};


//˼ά��ͼ�ֿ�ڵ���
class BlockNode: public TreeNodeBase<BlockNode>
{
	//����
public:

	//������
	int PosX;//λ��x
	int PosY;//λ��y
	enumShape Shape;//��״
	enumDir Dir;//���߷���
	int Color;//��ɫ
	int Length;//��
	int Width;//��
	CString Text;//����
	bool Lock;//�Ƿ�����

	//�ڴ����
	CString LockUser;//�����ߣ�Ϊ��˵���ǽ�ֹ�����û��޸�

	//����
public:
	BlockNode();
	void Copy(const BlockNode &Node);//��������
	void ReadFile(FILE *fp);//���ļ���ȡ
	void WriteFile(FILE *fp);//д���ļ�
	void Send(SOCKET sock);//�����緢��
	void Recv(SOCKET sock);//���������
};


//����������ö��
enum enumOperate
{
	updatamind,//���µ�ͼ��Ϣ
	updatablock,//���·ֿ���Ϣ
	updatarelation,//���·ֿ��ϵ
};
//�ֿ��ϵ����ö��
enum enumRelation
{
	addroot,//�ֿ���Ӹ��ֿ�
	delwith,//�ֿ�ɾ�������ӷֿ�
	delcombine,//�ֿ�ɾ���ϲ��ӷֿ�
	addchild,//�ֿ�����ӷֿ�
	addparent,//�ֿ���븸�ֿ�
	lineto,//�ֿ����ӵ��·ֿ�
	separateroot,//�ֿ����Ϊ���ֿ�
	delseparate,//�ֿ�ɾ�������ӷֿ�
};


//�ֿ���Ϣ��������
struct BlockOperateData
{
	//����
public:
	int Deep;
	int Local[MAX_BLOCK_DEEP];
	BlockNode Block;
	bool SetWith;

	//����
public:
	void Copy(const BlockOperateData &Data);
	void Send(SOCKET sock);
	void Recv(SOCKET sock);
};


//�ֿ��ϵ��������
struct RelationOperateData
{
	//����
public:
	enumRelation Relation;
	int Deep1;
	int Deep2;
	int Local1[MAX_BLOCK_DEEP];
	int Local2[MAX_BLOCK_DEEP];
	int Message;

	//����
public:
	void Copy(const RelationOperateData &Data);
	void Send(SOCKET sock);
	void Recv(SOCKET sock);
};


//����������ڵ���
class OperateNode: public NodeBase<OperateNode>
{
	//����
public:
	enumOperate Operate;//��������
	MindNode MindData;//��ͼ��Ϣ��������
	struct BlockOperateData BlockData;//�ֿ���Ϣ��������
	struct RelationOperateData RelationData;//�ֿ��ϵ��������

	//����
public:
	void Copy(const OperateNode &Node);//��������
	void Send(SOCKET sock);//�����緢��
	void Recv(SOCKET sock);//���������
};


//���ļ�����CString
void ReadFileCString(FILE* fp, CString &string);


//CString����д���ļ�
void WriteFileCString(FILE* fp, CString &string);


//���ֲ��ң��Ҳ�������ǰһ����
//CString
bool BinarySearch(const CString string[], const CString &target, int start, int end, int &result);
//CString��CString
bool BinarySearch(const CString string[], const CString string2[], const CString &target, 
				  const CString &target2, int start, int end, int &result);
//tUserData
bool BinarySearch(tUserData * const string[], const CString &target, int start, int end, int &result);


//��˼ά��ͼ���в���
bool OperateData(MindNode &TheMind, ListTemplet<class OperateNode> &OperateList);


//��˼ά��ͼ���й�ϵ����
int OperateRelation(TreeTemplet<class BlockNode> &BlockTree, enumRelation Relation, int Local[], int Deep);


//�ݹ����÷ֿ���������
void LockBlockWith(BlockNode *pBlock, bool IsLock);

/****************************************************************/
/*************************������ͬ������*************************/
/****************************************************************/


//��ʱ����м���
int MinusTime(const SYSTEMTIME &time1, const SYSTEMTIME &time2);


//ʱ��ת���ַ���
void GetTime(const SYSTEMTIME &time, CString &string);


//ʱ��ת����ϸ�ַ���
void GetAllTime(const SYSTEMTIME &time, CString &string);


//�û��ڴ�����ȫ�ֱ���
extern tUserData *g_pUserData[USER_NUM];
extern int g_UserNum;


//���ݿ��ʼ��
void DataInit();


//���ݿⱣ��
void DataSave();


//����û�
bool AddUser(CString &UserId, CString &Password);


//�˶��û�
bool TestUser(CString &UserId, CString &Password);


//�޸��û���Ϣ
bool ChangeUser(CString &UserId, CString &Password, CString &Password2);


//�ҵ��û�ӵ��˼ά��ͼ����
ListTemplet<MindNode> *GetOwnMindList(CString &UserId);


//�����û�����˼ά��ͼ����
ListTemplet<MindNode> *BuildJoinMindList(CString &UserId);


//�½�˼ά��ͼ
MindNode *NewMind(CString &UserId);


//ѡ��˼ά��ͼ
MindNode *SelMind(CString &UserId, CString &MindUserId, CString &MindName);


//ɾ��˼ά��ͼ
bool DelMind(CString &UserId, CString &MindName);


//�����༭
enum PacketType EditEnd(CString &UserId);


//����˼ά��ͼ����
enum PacketType ChangeName(CString &UserId, CString &MindName);


//��ӹ����û�
enum PacketType AddShare(CString &UserId, CString &ShareUserId);


//ɾ�������û�
enum PacketType DelShare(CString &UserId, CString &ShareUserId);


//���÷ֿ���������
enum PacketType LockBlock(CString &UserId, int Deep, int Local[], ListTemplet<OperateNode> * &pReOperateList, 
						  bool IsLock, bool SetWith);


//�ϴ�˼ά��ͼ
enum PacketType UpMind(CString &UserId, MindNode &TheMind, ListTemplet<OperateNode> * &pReOperateList);


//����˼ά��ͼ
enum PacketType KeepMind(CString &UserId, ListTemplet<OperateNode> * &pReOperateList);


//����˼ά��ͼ
enum PacketType DownMind(CString &UserId, ListTemplet<OperateNode> * &pReOperateList);


//����ֿ�
enum PacketType ApplyBlock(CString &UserId, int Local[], int Deep, ListTemplet<OperateNode> * &pReOperateList);


//�ͷŷֿ�
enum PacketType FinishBlock(CString &UserId, BlockNode &NewBlock, ListTemplet<OperateNode> * &pReOperateList);


//��Ӹ��ֿ�
enum PacketType BlockAddRoot(CString &UserId, int x, int y, ListTemplet<OperateNode> * &pReOperateList);


//ɾ�������ӷֿ�
enum PacketType BlockDelWith(CString &UserId, BlockNode &NewBlock, ListTemplet<OperateNode> * &pReOperateList);


//ɾ�������ӷֿ�
enum PacketType BlockDelCombine(CString &UserId, BlockNode &NewBlock, ListTemplet<OperateNode> * &pReOperateList);


//����ӷֿ�
enum PacketType BlockAddChild(CString &UserId, BlockNode &NewBlock, ListTemplet<OperateNode> * &pReOperateList, 
							  int x, int y);


//���븸�ֿ�
enum PacketType BlockAddParent(CString &UserId, BlockNode &NewBlock, ListTemplet<OperateNode> * &pReOperateList, 
							   int x, int y);


//���ӵ����зֿ�
enum PacketType BlockLineInto(CString &UserId, BlockNode &NewBlock, ListTemplet<OperateNode> * &pReOperateList, 
							  int Deep, int Local[]);


//����Ϊ���ֿ�
enum PacketType BlockSeparateRoot(CString &UserId, BlockNode &NewBlock, ListTemplet<OperateNode> * &pReOperateList);


//ɾ�������ӷֿ�
enum PacketType BlockDelSeparate(CString &UserId, BlockNode &NewBlock, ListTemplet<OperateNode> * &pReOperateList);


//���²��������޸ĵ�ͼ�༭ʱ��
//mind����
void RefreshOperateList(MindNode &TheMind, SYSTEMTIME *ptime, bool OwnUser);
//Bolck����
void RefreshOperateList(MindNode &TheMind, SYSTEMTIME *ptime, int Deep, int Local[], bool SetWith);
//Relation����
void RefreshOperateList(MindNode &TheMind, SYSTEMTIME *ptime, enumRelation Relation,  
						int Deep1, int Local1[], int Deep2, int Local2[], int Message);


//ˢ�¶�λ��Ϣ
void RefreshBlockLocal(int Local[], int &Deep, ListTemplet<OperateNode> &OperateList);


//�ݹ�ˢ�·ֿ�λ�����ֵ
void RefreshMaxPos(BlockNode *pBlock, int &Pos_X, int &Pos_Y);


//�ݹ��ж��Ƿ�����
bool JudgeBlockLock(BlockNode *pBlock, bool Own);

