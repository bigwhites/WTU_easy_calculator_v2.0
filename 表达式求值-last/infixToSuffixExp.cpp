#include"nead.h"
void infixToSuffixExp(char* infixExp, char*& suffixExp)
{
    int len = strlen(infixExp);
    suffixExp = new char[100 * len+200];
    int writeLoc = 0;
    stack<char> op;
    for (int i = 0; i < len; ++i)
    {
        if (infixExp[i] == ' ') continue; //过滤输入的表达式中的无用空格
        if (isNegative(infixExp, i))
        {
            suffixExp[writeLoc++]='-'; //把负号输出
            continue;
        }
        if (isNumber(infixExp[i])) //是数字
        {
            int j = i;
            while (isNumber(infixExp[j])||infixExp[j]=='.')  //把从该位置开始后面的数字全部输出
            {
                suffixExp[writeLoc++] = infixExp[j];
                ++j;
            }
            i = j - 1;
            suffixExp[writeLoc++] = ' '; //输出一个空格
        }

        else  //是运算符
        {
            char newOp = readOp(infixExp[i], infixExp, i); //识别新的运算符
            if (canPush(newOp,op)) //可以继续压栈
            {
                op.push(newOp);
            }
            else  //要出栈
            {
                if (infixExp[i] == ')')  //遇到左扩回就一直出栈直到遇到右括号
                {
                    char top = op.top();
                    op.pop();
                    while (top != '(')
                    {
                        suffixExp[writeLoc++] = top; //把（ ）间的运算符抛出
                        suffixExp[writeLoc++] = ' '; //输出一个空格
                        top = op.top();
                        op.pop();
                    }
                }
                else //栈顶运算符优先级大于等于新运算符 
                {
                    for (; !canPush(newOp, op); op.pop()) //抛出栈内运算符直到新的可以入栈
                    {
                        suffixExp[writeLoc++] = op.top();
                        suffixExp[writeLoc++] = ' '; //输出一个空格
                    }
                    op.push(infixExp[i]);
                }
            }
        }

    }
    for (; !op.empty(); op.pop())  //栈里还有运算符就抛出
    {
        suffixExp[writeLoc++] = op.top();
        suffixExp[writeLoc++] = ' ';
    }
    suffixExp[writeLoc] = '\0'; //结尾加上结束符
}


char readOp(char ch, char*& infixExp, int& loc)  //读取运算符
{
    char newOp = ch;
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%'||ch=='('||ch==')')
    {
        return newOp;
    }
    if (ch == '='||ch=='&'||ch=='|') //相同双字符的运算符
    {
        loc++;
        return ch;
    }
    switch (ch)
    {
    case'<':

        if (infixExp[loc + 1] == '=')
        {
            newOp = '['; //小于等于
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
    case '!':  //不等于
        if (infixExp[loc + 1] == '=')
        {
            newOp = '\\'; //不等于
            loc++;
        }
        else newOp = '!'; //非
        break;
    }
    return newOp;
}


bool canPush(char newOp, stack<char>& op) //判断能否继续压栈
{
    if (newOp == ')') return false; //左括号不能进栈
    if (op.empty()) return true; //栈空可入栈
    if (newOp == '('||op.top()=='(') return true;//右括号或栈顶为括号 无条件进栈
    if (priority(newOp) > priority(op.top()))  //优先级大于才能压栈
    {
        return true;
    }
    return false;
}

int priority(char op)  //运算符优先级
{
    if (op == '|') return 1;
    if (op == '&') return 2;
    if (op == '='|| op == '\\') return 3;   // \为不等于
    if (op=='<'||op=='>'||op==']'||op=='[') return 4;
    if (op == '+' || op == '-')  return 5;
    if (op == '*' || op == '/' || op == '%') return 6;
    if (op == '!') return 7;
}