#include"nead.h"

bool isNumber(char x)
{
    if (x >= '0' && x <= '9')
        return true;
    return false;
}

 LDouble chToNum(char x)
{
    return (int)(x - '0');
}

bool isInfixExperssion(char* infixExp)
{
    if (!infixExp) return false;
    if (checkBrackets(infixExp)) return true;
    return false;
}



bool checkBrackets(char* infixExp)   //brackets 圆括号
{
    stack<char> Sbra;
    int len = strlen(infixExp);
    for (int j = 0; j < len; ++j)
    {
        char i = infixExp[j];
        if (i == '(')
        {
            Sbra.push(i);
        }
        else if (i == ')')
        {
            if (!Sbra.empty())
            {
                Sbra.pop();
            }
            else
            {
                return false;
            }
        }
    }
    if (Sbra.empty())  return true;
    else  return false;
}


bool isOp(char i)
{
    if (i == '+' || i == '-' || i == '*' || i == '/') return true;
    return false;
}

bool isNegative(char* infixExp, int pos)
{
    if (infixExp[pos] == '-')
    {
        if (infixExp[pos - 1] == '(') return true; //被括号括起来的是负号
    }
    return false;
}