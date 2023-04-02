#include"nead.h"



bool Variable::VarExist(string name)
{
	if (this->varMap.count(name)) return true;
	return false;
}

void Variable::newVar(string name,LDouble firstValue)
{
	if (varMap.count(name))  return; //如果有相同直接返回
	this->varMap.insert(pair<string, LDouble>(name, firstValue));
	
}

void Variable::delVar(string name)
{
	if (!this->varMap.count(name)) return; //不存在直接返回
	this->varMap.erase(name);
}

int Variable::size(void)
{
	return varMap.size();
}

LDouble& Variable::at(string name)
{
	return varMap[name];
}

void Variable::showAll(void)
{
	printf("\n全部变量如下:\n");
	for (auto i : varMap)
	{
		printf("VAR %s = %llf\n",i.first.c_str(),i.second);
	}
	printf("\n\n");
}

void Variable::show(string name)  //查看单个变量
{
	if (!this->varMap.count(name))
	{
		printf("变量未定义！\n");
	}
	else
	{
		printf("VAR %s = %llf\n", name.c_str(), varMap[name]);
	}
}

string Variable::getValueStr(string name) //得到变量值的字符串
{
	string result;
	char c_result[80];
	sprintf(c_result, "%.3llf", varMap[name]);
	result = c_result;
	return result;
}

bool isAlphabet(char ch)  //是字母
{
	if (ch >= 'a' && ch <= 'z') return true;
	if (ch >= 'A' && ch <= 'Z') return true;
	return false;
}


bool varSubstitute(Variable& var, char* preInfixExp,char*& infixExp) //变量替换
{
	int len = strlen(preInfixExp);
	infixExp = new char[3 * len+300];
	int writeLoc = 0;
	for (int i = 0; i < len; ++i)
	{
		if (!isAlphabet(preInfixExp[i])) //不是字母无需处理
		{
			infixExp[writeLoc++] = preInfixExp[i];
		}
		else //变量替换为数字
		{
			int j = i;
			string name;
			string valueStr;
			int negativeLogo = 0; //代表表示负数的"次数"
			while (isAlphabet(preInfixExp[j]))
			{
				if (j >= 2 && preInfixExp[j - 1] == '-' && preInfixExp[j - 2] == '(')
				{
					++negativeLogo; //引用变量时取反
				}
				name.push_back(preInfixExp[j]);
				++j;
			}
			i = j - 1; //更新遍历指针到最后一个字母
			if (!var.VarExist(name))
			{
				return false;
			}
			infixExp[writeLoc++] = '(';
			valueStr = var.getValueStr(name); //得到数字的字符串
			for(auto ch: valueStr)
			{
				if (ch == '-')
				{
					++negativeLogo;
					if (negativeLogo == 2) continue;  //负负得正 一个负号的情况把负号输出
				}
				infixExp[writeLoc++] = ch; //数字替换
			}
			infixExp[writeLoc++] = ')';
		}
	}
	infixExp[writeLoc++] = '\0';
	return true;
}

bool letMode(char letOp[], LDouble& res,LDouble soucersValue) //按照赋值运算符进行赋值
{
	if (!strcmp(letOp, "="))
	{
		res = res; //普通赋值
	}
	else if (!strcmp(letOp, "+="))
	{
		res = soucersValue + res;
	}
	else if (!strcmp(letOp, "-="))
	{
		res = soucersValue - res;
	}
	else if (!strcmp(letOp, "*="))
	{
		res = soucersValue * res;
	}
	else if (!strcmp(letOp, "/="))
	{
		if (res == 0)
		{
			return false;
		}
		res = soucersValue / res;
	}
	else
	{
		return false;
	}
	return true;
}

bool correctName(string name) //检查是否是合法的变量名
{
	for (auto i : name)
	{
		if (!isAlphabet(i)) return false;
	}
	return true;
}