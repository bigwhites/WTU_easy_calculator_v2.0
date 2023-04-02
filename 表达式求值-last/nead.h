#include<cstdio>
#include<stack>
#include<cstring>
#include<string>
#include<map>
#include<exception>
#include"iostream"
#include<string>
using namespace std;

typedef long double LDouble;
typedef long long int LInt;
#define OP 0
#define NUM 1

class Variable //������
{
protected:
	map<string, LDouble> varMap;  //keyΪ������ valueΪ��ֵ��map
public:
	void newVar(string name,LDouble firstVaule);  //�½�����
	void delVar(string name); //ɾ������
	LDouble& at(string name); //��ȡ����������
	int size(void); //��ȡ��������
	bool VarExist(string name);//�Ƿ���ڸñ���
	void showAll(void); //�鿴���б���
	void show(string name);  //�鿴��������
	string getValueStr(string name); //�õ�value�������ַ���
};

struct BiNode //�������ڵ�
{
    int status; //���������������������
	string n;   
	char op;
	BiNode* rchild;
	BiNode* lchild;
	BiNode(string _n)
	{
		n = _n;
		status = NUM;
		rchild = nullptr;
		lchild = nullptr;
	}
	BiNode(char _op)
	{
		op = _op;
		status = OP;
		rchild = nullptr;
		lchild = nullptr;
	}
};

class BiTree //������ʽ��
{
protected:
	BiNode* root; //���ڵ�
	void m_preOreder(BiNode* T); //�������
	void m_midOrder(BiNode* T);  //�������
	void m_lastOrder(BiNode* T); //�������
	void m_midOrder(BiNode* T, int deep); //����Ҫ���ŵĺ������
	LDouble m_calcTree(BiNode* T)
	{
		if (!T) return 0;
		if (!T->lchild && !T->rchild)
		{
			LDouble v = (LDouble)atof(T->n.c_str());
			return v;
		}
		else
		{
			LDouble lv = 0, rv = 0;
			lv = m_calcTree(T->lchild);
			rv = m_calcTree(T->rchild);
			return calc(T->op, rv, lv);
		}
	} //������ֵ
public:
	BiTree()
	{
		this->root = nullptr;
	}
	void buildTree(char* suffixExp); //���պ���������й������ʽ��
	void oreder(string mode); //����mode�������ʽ��
	void delTree(BiNode* T); //ɾ��������
	LDouble calcTree(void); //��������ֵ
	~BiTree() //����
	{
		delTree(this->root);
	}
};
inline void showMenu(void); //��ӡ�˵�
void infixToSuffixExp(char* infixExp, char*& suffixExp);  //��׺���ʽת��׺���ʽ
bool isNumber(char x); //������
LDouble chToNum(char x); //�ַ�ת��������
LDouble calc(char op, LDouble n, LDouble m); //��׺���ʽ�����׳������������
LDouble calcSuffixExperssion(char* lastExp); //�����׺���ʽ
bool isInfixExperssion(char* infixExp);  //�ж�������ʽ�Ƿ�Ϸ�
bool checkBrackets(char* infixExp); //��������Ƿ�ƥ��
bool isOp(char i); //��+ - * /�ĸ������������
inline bool calc(char mode, Variable& var, char preInfixdExp[], char*& infixExp, char*& suffixExp, LDouble& res);  //����ӿں��� mode='c'չʾ�������
bool isNegative(char* infixExp, int pos); //�ж��Ƿ��Ǹ���
bool varSubstitute(Variable& var, char* preInfixExp, char*& infixExp); //�������滻
bool isAlphabet(char ch);//����ĸ
string getValueStr(string name);//�õ�����ֵ���ַ���
bool letMode(char letOp[], LDouble& res, LDouble soucersValue); //���ո�ֵ��������и�ֵ
bool correctName(string name); //����Ƿ��ǺϷ��ı�����
char readOp(char ch, char*& infixExp, int& loc);  //��ȡ�����
int priority(char op);  //��������ȼ�
bool canPush(char newOp, stack<char>& op);//�ж��ܷ����ѹջ