#include"nead.h"



bool Variable::VarExist(string name)
{
	if (this->varMap.count(name)) return true;
	return false;
}

void Variable::newVar(string name,LDouble firstValue)
{
	if (varMap.count(name))  return; //�������ֱͬ�ӷ���
	this->varMap.insert(pair<string, LDouble>(name, firstValue));
	
}

void Variable::delVar(string name)
{
	if (!this->varMap.count(name)) return; //������ֱ�ӷ���
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
	printf("\nȫ����������:\n");
	for (auto i : varMap)
	{
		printf("VAR %s = %llf\n",i.first.c_str(),i.second);
	}
	printf("\n\n");
}

void Variable::show(string name)  //�鿴��������
{
	if (!this->varMap.count(name))
	{
		printf("����δ���壡\n");
	}
	else
	{
		printf("VAR %s = %llf\n", name.c_str(), varMap[name]);
	}
}

string Variable::getValueStr(string name) //�õ�����ֵ���ַ���
{
	string result;
	char c_result[80];
	sprintf(c_result, "%.3llf", varMap[name]);
	result = c_result;
	return result;
}

bool isAlphabet(char ch)  //����ĸ
{
	if (ch >= 'a' && ch <= 'z') return true;
	if (ch >= 'A' && ch <= 'Z') return true;
	return false;
}


bool varSubstitute(Variable& var, char* preInfixExp,char*& infixExp) //�����滻
{
	int len = strlen(preInfixExp);
	infixExp = new char[3 * len+300];
	int writeLoc = 0;
	for (int i = 0; i < len; ++i)
	{
		if (!isAlphabet(preInfixExp[i])) //������ĸ���账��
		{
			infixExp[writeLoc++] = preInfixExp[i];
		}
		else //�����滻Ϊ����
		{
			int j = i;
			string name;
			string valueStr;
			int negativeLogo = 0; //�����ʾ������"����"
			while (isAlphabet(preInfixExp[j]))
			{
				if (j >= 2 && preInfixExp[j - 1] == '-' && preInfixExp[j - 2] == '(')
				{
					++negativeLogo; //���ñ���ʱȡ��
				}
				name.push_back(preInfixExp[j]);
				++j;
			}
			i = j - 1; //���±���ָ�뵽���һ����ĸ
			if (!var.VarExist(name))
			{
				return false;
			}
			infixExp[writeLoc++] = '(';
			valueStr = var.getValueStr(name); //�õ����ֵ��ַ���
			for(auto ch: valueStr)
			{
				if (ch == '-')
				{
					++negativeLogo;
					if (negativeLogo == 2) continue;  //�������� һ�����ŵ�����Ѹ������
				}
				infixExp[writeLoc++] = ch; //�����滻
			}
			infixExp[writeLoc++] = ')';
		}
	}
	infixExp[writeLoc++] = '\0';
	return true;
}

bool letMode(char letOp[], LDouble& res,LDouble soucersValue) //���ո�ֵ��������и�ֵ
{
	if (!strcmp(letOp, "="))
	{
		res = res; //��ͨ��ֵ
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

bool correctName(string name) //����Ƿ��ǺϷ��ı�����
{
	for (auto i : name)
	{
		if (!isAlphabet(i)) return false;
	}
	return true;
}