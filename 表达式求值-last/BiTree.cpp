#include"nead.h"

void BiTree::oreder(string mode)
{
	if (!this->root) return;
	if (mode=="all" || mode == "pre")
	{
		printf("先序遍历结果为：");
		m_preOreder(this->root);
		printf("\n");
	}
	if (mode=="all" || mode == "mid")
	{
		printf("中序遍历结果为：");
		m_midOrder(this->root,1);
		printf("\n");
	}
	if(mode=="all"||mode=="last")
	{
		printf("后序遍历结果为：");
		m_lastOrder(this->root);
		printf("\n");
	}
}

void  BiTree::m_preOreder(BiNode* T)
{
	if (!T) return;
	if (T->status == OP)
	{
		printf("%c ", T->op);
	}
	else
	{
		printf("%s ", T->n.c_str());
	}
	m_preOreder(T->lchild);
	m_preOreder(T->rchild);
}

void BiTree::m_midOrder(BiNode* T)
{
	if (!T) return;
	else
	{
		printf("( ");
		m_midOrder(T->lchild);
		if (T->status == OP)
		{
			printf("%c ", T->op);
		}
		else
		{
			printf("%s ", T->n.c_str());
		}
		m_midOrder(T->rchild);
		printf(") ");
	}
}

void BiTree::m_lastOrder(BiNode* T)
{
	if (!T) return;
	else
	{
		m_lastOrder(T->lchild);
		m_lastOrder(T->rchild);
		if (T->status == OP)
		{
			printf("%c ", T->op);
		}
		else
		{
			printf("%s ", T->n.c_str());
		}
	}
}

void BiTree::m_midOrder(BiNode* T, int deep)
{
	if (!T)
	{
		return;
	}
	else if (!T->lchild && !T->rchild)  //为叶子节点一定是操作数
	{
		printf("%s", T->n.c_str());
	}
	else
	{
		if (deep > 1)
		{
			printf("（"); //还有子表达式
		}
		m_midOrder(T->lchild, deep + 1);
		printf("%c", T->op);
		m_midOrder(T->rchild, deep + 1);
		if (deep > 1)
		{
			printf(")");
		}
	}

}

void BiTree::buildTree(char* suffixExp)
{
	stack<BiNode*> s;
	int len = strlen(suffixExp);
	for (int i = 0; i < len; ++i)
	{
		if (suffixExp[i] == ' ')
		{
			continue;
		}
		if (suffixExp[i] == '-' && isNumber(suffixExp[i + 1]) || isNumber(suffixExp[i])) //是数字
		{
			string num;
			num.push_back(suffixExp[i]);
			int j = i + 1;
			while (suffixExp[j] != ' ')
			{
				num.push_back(suffixExp[j]);
				j++;
			}
			i = j; //i指针无需回退，因为数字后面必为空格
			auto newNode = new BiNode(num); 
			s.push(newNode);
		}
		else //是运算符
		{
			auto newNode = new BiNode(suffixExp[i]);
			newNode->rchild = s.top();
			s.pop();
			newNode->lchild = s.top();
			s.pop();
			s.push(newNode);
		}
	
	}
	this->root = s.top();
}


void BiTree::delTree(BiNode* T)
{
	if (!T) return;
	delTree(T->lchild);
	delTree(T->rchild);
	delete T;
	T = nullptr;
}


LDouble BiTree::calcTree(void)
{
	if (!this->root)
	{
		return 0;
	}
	else
	{
		return m_calcTree(this->root);
	}
}

