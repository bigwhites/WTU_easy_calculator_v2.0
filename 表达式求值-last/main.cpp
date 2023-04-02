#include"nead.h"
int main(void)
{
    showMenu();
    while (1)
    {
        static Variable var;
        char preInfixExp[400], command[50], c_strName[50];
        char* infixExp = nullptr, * suffixExp = nullptr;
        LDouble res;
        printf("\nInput command >>>");
        fflush(stdin);
        scanf("%s", command); //输入命令
        getchar();
        if (!strcmp("calc", command))   //计算表达式
        {
            gets_s(preInfixExp);  //得到带变量的准中缀表达式
            calc('c', var, preInfixExp, infixExp, suffixExp, res);
        }
        else if (!strcmp("new", command)) //新建变量
        {
            scanf("%s", c_strName);
            getchar();//吸收空格
            char ch = getchar(); //吸收等于号
            if (ch != '=')
            {
                printf("输入有误！\n");
                continue;
            }
            gets_s(preInfixExp);
            string name(c_strName);
            if (!correctName(name))
            {
                printf("变量名非法,只能为字母！\n");
                continue;
            }
            if (var.VarExist(name))
            {
                printf("该变量重定义！\n");
                continue;
            }
            if (!calc('a', var, preInfixExp, infixExp, suffixExp, res))
            {
                printf("表达式非法!\n");
                continue;
            }
            var.newVar(name, res);
        }
        else if (!strcmp("let", command))  //变量赋值
        {

            scanf("%s", c_strName);
            char ch = getchar(); //吸收空格
            char letOp[50]; //吸收赋值运算符
            scanf("%s", letOp);
            getchar(); //吸收空格
            gets_s(preInfixExp);//读入表达式
            string name = c_strName;
            if (!var.VarExist(name))
            {
                printf("该变量未定义！\n");
                continue;
            }
            if (!calc('a', var, preInfixExp, infixExp, suffixExp, res))
            {
                printf("表达式非法!\n");
                continue;
            }
            bool successLet = letMode(letOp, res, var.at(name));
            if (!successLet)
            {
                printf("输入错误！\n");
                continue;
            }
            var.at(name) = res;
        }
        else if (!strcmp("showvar", command))
        {
            if (var.size() == 0)
            {
                printf("还没有变量！\n");
                continue;
            }
            var.showAll();
        }
        else if (!strcmp("show", command)) //展示单个变量
        {
            char cstr_name[30];
            scanf("%s", cstr_name);
            getchar();
            string name = cstr_name;
            var.show(name);
        }
        else if (!strcmp("delete", command)) //删除变量
        {
            char c_strName[30];
            scanf("%s", c_strName);
            string name = c_strName;
            if (!var.VarExist(name))
            {
                printf("变量未定义或已经释放！\n");
                continue;
            }
            var.delVar(name);
        }
        else if (!strcmp("tree", command))
        {
            BiTree bt;
            gets_s(preInfixExp);//读入表达式
            varSubstitute(var, preInfixExp, infixExp);
            infixToSuffixExp(infixExp, suffixExp);
            bt.buildTree(suffixExp);
            bt.oreder("all");
            printf("\n遍历求值结果为 %.2llf\n", bt.calcTree());
        }
        else if (!strcmp("EXIT", command)) break;
        else if (!strcmp("cls", command))
        {
            system("cls");
            showMenu();
        }
        else printf("输入错误！\n");

    }
    return 0;
}
// (2+3)*60-9*(3+4)+3-50  == 190 


inline bool calc(char mode,Variable& var,char preInfixdExp[], char*& infixExp, char*& suffixExp,LDouble &res)//计算接口函数 mode=='c'展示计算过程
{                                                                                                            //传入带变量名的准中缀表达式计算
    if (!varSubstitute(var, preInfixdExp, infixExp) || !isInfixExperssion(infixExp))  //检测最后生成的中缀表达式的合法性
    {
        if (mode == 'c')
        {
            printf("表达式非法！\n");
        }
        delete[]infixExp;
        return false;
    }
    infixToSuffixExp(infixExp, suffixExp); //中缀转后缀
    if (mode == 'c')
    {
        printf("自动生成的后缀表达式为 ：%s\n", suffixExp);
        printf("结果为：%.2llf\n\n", calcSuffixExperssion(suffixExp)); //计算结果
    }
    res = calcSuffixExperssion(suffixExp);
    delete[]suffixExp; //回收内存
    delete[]infixExp;
    return true;
}

inline void showMenu(void)
{
    printf("\n\n");
    printf("\t\t======================--++++简易计算器++++--======================\n");
    printf("\t\t 可以随意输入空格或冗余括号提升可读性 计算结果保留两位小数\n");
    printf("\t\t 输入负数请用负号将其包裹\n");
    printf("\t\t 若输入的表达式有误会提示重新输入 若出现数学错误会终止程序\n");
    printf("\t\t 命令：1.calc (表达式)  2.new (变量)     3.delete(变量) 4.showvar\n");
    printf("\t\t       5.show (变量)    6.let (变量) (赋值号)(表达式)   7.cls 8.tree(表达式）\n");
    printf("\t\t======================================================================\n\n");
    printf("\n\n计算程序开始，输入 \"EXIT\" 结束计算。\n\n");
}