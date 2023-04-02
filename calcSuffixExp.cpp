#include"nead.h"

LDouble calcSuffixExperssion(char* suffixExp)
{
        int len = strlen(suffixExp);
        char buff;
        stack<LDouble> num;
        for (int i = 0; i < len; ++i)
        {
            buff = suffixExp[i];
            if (buff == '-' && isNumber(suffixExp[i + 1])) //�Ǹ��� ֱ������
            {
               continue;
            }
            if (isNumber(buff))
            {
                int j = i;
                LDouble n = 0;
                LDouble lastNum = 0;
                stack<char> x;
                int flag = 1;
                if ((i != 0) && suffixExp[i - 1] == '-') flag = -1;
                while (isNumber(suffixExp[j]))
                {
                    x.push(suffixExp[j]);
                    ++j;
                }
                while (!x.empty())
                {
                    lastNum += chToNum(x.top()) * pow(10, n);
                    ++n;
                    x.pop();
                }
                LDouble m = 1;
                if (suffixExp[j] == '.')
                {
                    ++j;
                    while (isNumber(suffixExp[j]))
                    {
                        m *= 0.1;
                        lastNum += m * (chToNum(suffixExp[j]));
                        ++j;
                    }
                }
                num.push(lastNum * flag);
                i = j - 1;
            }
            else  //�������
            {
                if (buff=='!')  //��Ŀ�����
                {
                    if (!(int)num.top())
                    {
                        num.pop();
                        num.push(1);
                    }
                    else
                    {
                        num.pop();
                        num.push(0);
                    }
                }
                else 
                {
                    LDouble n = num.top();
                    num.pop();
                    LDouble m = num.top();
                    num.pop();
                    num.push(calc(buff, n, m));
                }
            }
            if (suffixExp[i + 1] == ' ')  ++i;
        }
        return num.top();
    
}

LDouble calc(char op, LDouble n, LDouble m)
{
    switch (op)
    {
    case '+':
        return m + n;
        break;
    case '-':
        return m - n;
        break;
    case '*':
        return m * n;
        break;
    case '/': 
        return m / n;
    case '%':
        return (int)m % (int)n;
    case '&':
        return (int)m && (int)n;
    case '|':
        return (int)m || (int)n;
    case '<':
        return (m < n);
    case '>':
        return (m > n);
    case '[':
        return (m < n) || ((int)m == (int)n);
    case ']':
        return (m > n) || ((int)m == (int)n);
    case '\\':
        return ((int)m != (int)n);
    case '=':
        return((int)m == (int)n);
    }
}
