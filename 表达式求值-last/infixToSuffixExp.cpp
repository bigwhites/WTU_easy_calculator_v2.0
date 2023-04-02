#include"nead.h"
void infixToSuffixExp(char* infixExp, char*& suffixExp)
{
    int len = strlen(infixExp);
    suffixExp = new char[100 * len+200];
    int writeLoc = 0;
    stack<char> op;
    for (int i = 0; i < len; ++i)
    {
        if (infixExp[i] == ' ') continue; //��������ı��ʽ�е����ÿո�
        if (isNegative(infixExp, i))
        {
            suffixExp[writeLoc++]='-'; //�Ѹ������
            continue;
        }
        if (isNumber(infixExp[i])) //������
        {
            int j = i;
            while (isNumber(infixExp[j])||infixExp[j]=='.')  //�ѴӸ�λ�ÿ�ʼ���������ȫ�����
            {
                suffixExp[writeLoc++] = infixExp[j];
                ++j;
            }
            i = j - 1;
            suffixExp[writeLoc++] = ' '; //���һ���ո�
        }

        else  //�������
        {
            char newOp = readOp(infixExp[i], infixExp, i); //ʶ���µ������
            if (canPush(newOp,op)) //���Լ���ѹջ
            {
                op.push(newOp);
            }
            else  //Ҫ��ջ
            {
                if (infixExp[i] == ')')  //���������ؾ�һֱ��ջֱ������������
                {
                    char top = op.top();
                    op.pop();
                    while (top != '(')
                    {
                        suffixExp[writeLoc++] = top; //�ѣ� �����������׳�
                        suffixExp[writeLoc++] = ' '; //���һ���ո�
                        top = op.top();
                        op.pop();
                    }
                }
                else //ջ����������ȼ����ڵ���������� 
                {
                    for (; !canPush(newOp, op); op.pop()) //�׳�ջ�������ֱ���µĿ�����ջ
                    {
                        suffixExp[writeLoc++] = op.top();
                        suffixExp[writeLoc++] = ' '; //���һ���ո�
                    }
                    op.push(infixExp[i]);
                }
            }
        }

    }
    for (; !op.empty(); op.pop())  //ջ�ﻹ����������׳�
    {
        suffixExp[writeLoc++] = op.top();
        suffixExp[writeLoc++] = ' ';
    }
    suffixExp[writeLoc] = '\0'; //��β���Ͻ�����
}


char readOp(char ch, char*& infixExp, int& loc)  //��ȡ�����
{
    char newOp = ch;
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%'||ch=='('||ch==')')
    {
        return newOp;
    }
    if (ch == '='||ch=='&'||ch=='|') //��ͬ˫�ַ��������
    {
        loc++;
        return ch;
    }
    switch (ch)
    {
    case'<':

        if (infixExp[loc + 1] == '=')
        {
            newOp = '['; //С�ڵ���
            loc++;
        }
        break;
    case '>':
        if (infixExp[loc + 1] == '=')
        {
            newOp = ']';
            loc++;
        }
        break;
    case '!':  //������
        if (infixExp[loc + 1] == '=')
        {
            newOp = '\\'; //������
            loc++;
        }
        else newOp = '!'; //��
        break;
    }
    return newOp;
}


bool canPush(char newOp, stack<char>& op) //�ж��ܷ����ѹջ
{
    if (newOp == ')') return false; //�����Ų��ܽ�ջ
    if (op.empty()) return true; //ջ�տ���ջ
    if (newOp == '('||op.top()=='(') return true;//�����Ż�ջ��Ϊ���� ��������ջ
    if (priority(newOp) > priority(op.top()))  //���ȼ����ڲ���ѹջ
    {
        return true;
    }
    return false;
}

int priority(char op)  //��������ȼ�
{
    if (op == '|') return 1;
    if (op == '&') return 2;
    if (op == '='|| op == '\\') return 3;   // \Ϊ������
    if (op=='<'||op=='>'||op==']'||op=='[') return 4;
    if (op == '+' || op == '-')  return 5;
    if (op == '*' || op == '/' || op == '%') return 6;
    if (op == '!') return 7;
}