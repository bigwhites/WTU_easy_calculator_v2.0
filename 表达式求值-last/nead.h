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

class Variable //变量类
{
protected:
	map<string, LDouble> varMap;  //key为变量名 value为数值的map
public:
	void newVar(string name,LDouble firstVaule);  //新建变量
	void delVar(string name); //删除变量
	LDouble& at(string name); //获取变量的引用
	int size(void); //获取变量个数
	bool VarExist(string name);//是否存在该变量
	void showAll(void); //查看所有变量
	void show(string name);  //查看单个变量
	string getValueStr(string name); //得到value的数字字符串
};

struct BiNode //二叉树节点
{
    int status; //表明是运算符还是运算数
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

class BiTree //二叉表达式树
{
protected:
	BiNode* root; //根节点
	void m_preOreder(BiNode* T); //先序遍历
	void m_midOrder(BiNode* T);  //中序遍历
	void m_lastOrder(BiNode* T); //后序遍历
	void m_midOrder(BiNode* T, int deep); //带必要括号的后序遍历
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
	} //遍历求值
public:
	BiTree()
	{
		this->root = nullptr;
	}
	void buildTree(char* suffixExp); //按照后序遍历序列构建表达式树
	void oreder(string mode); //按照mode遍历表达式树
	void delTree(BiNode* T); //删除二叉树
	LDouble calcTree(void); //二叉树求值
	~BiTree() //析构
	{
		delTree(this->root);
	}
};
inline void showMenu(void); //打印菜单
void infixToSuffixExp(char* infixExp, char*& suffixExp);  //中缀表达式转后缀表达式
bool isNumber(char x); //是数字
LDouble chToNum(char x); //字符转换成数字
LDouble calc(char op, LDouble n, LDouble m); //后缀表达式计算抛出的最基本运算
LDouble calcSuffixExperssion(char* lastExp); //计算后缀表达式
bool isInfixExperssion(char* infixExp);  //判断输入表达式是否合法
bool checkBrackets(char* infixExp); //检查括号是否匹配
bool isOp(char i); //是+ - * /四个基本运算符号
inline bool calc(char mode, Variable& var, char preInfixdExp[], char*& infixExp, char*& suffixExp, LDouble& res);  //计算接口函数 mode='c'展示计算过程
bool isNegative(char* infixExp, int pos); //判断是否是负号
bool varSubstitute(Variable& var, char* preInfixExp, char*& infixExp); //变量的替换
bool isAlphabet(char ch);//是字母
string getValueStr(string name);//得到变量值的字符串
bool letMode(char letOp[], LDouble& res, LDouble soucersValue); //按照赋值运算符进行赋值
bool correctName(string name); //检查是否是合法的变量名
char readOp(char ch, char*& infixExp, int& loc);  //读取运算符
int priority(char op);  //运算符优先级
bool canPush(char newOp, stack<char>& op);//判断能否继续压栈