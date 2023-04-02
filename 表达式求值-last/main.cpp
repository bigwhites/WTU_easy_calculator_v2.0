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
        scanf("%s", command); //��������
        getchar();
        if (!strcmp("calc", command))   //������ʽ
        {
            gets_s(preInfixExp);  //�õ���������׼��׺���ʽ
            calc('c', var, preInfixExp, infixExp, suffixExp, res);
        }
        else if (!strcmp("new", command)) //�½�����
        {
            scanf("%s", c_strName);
            getchar();//���տո�
            char ch = getchar(); //���յ��ں�
            if (ch != '=')
            {
                printf("��������\n");
                continue;
            }
            gets_s(preInfixExp);
            string name(c_strName);
            if (!correctName(name))
            {
                printf("�������Ƿ�,ֻ��Ϊ��ĸ��\n");
                continue;
            }
            if (var.VarExist(name))
            {
                printf("�ñ����ض��壡\n");
                continue;
            }
            if (!calc('a', var, preInfixExp, infixExp, suffixExp, res))
            {
                printf("���ʽ�Ƿ�!\n");
                continue;
            }
            var.newVar(name, res);
        }
        else if (!strcmp("let", command))  //������ֵ
        {

            scanf("%s", c_strName);
            char ch = getchar(); //���տո�
            char letOp[50]; //���ո�ֵ�����
            scanf("%s", letOp);
            getchar(); //���տո�
            gets_s(preInfixExp);//������ʽ
            string name = c_strName;
            if (!var.VarExist(name))
            {
                printf("�ñ���δ���壡\n");
                continue;
            }
            if (!calc('a', var, preInfixExp, infixExp, suffixExp, res))
            {
                printf("���ʽ�Ƿ�!\n");
                continue;
            }
            bool successLet = letMode(letOp, res, var.at(name));
            if (!successLet)
            {
                printf("�������\n");
                continue;
            }
            var.at(name) = res;
        }
        else if (!strcmp("showvar", command))
        {
            if (var.size() == 0)
            {
                printf("��û�б�����\n");
                continue;
            }
            var.showAll();
        }
        else if (!strcmp("show", command)) //չʾ��������
        {
            char cstr_name[30];
            scanf("%s", cstr_name);
            getchar();
            string name = cstr_name;
            var.show(name);
        }
        else if (!strcmp("delete", command)) //ɾ������
        {
            char c_strName[30];
            scanf("%s", c_strName);
            string name = c_strName;
            if (!var.VarExist(name))
            {
                printf("����δ������Ѿ��ͷţ�\n");
                continue;
            }
            var.delVar(name);
        }
        else if (!strcmp("tree", command))
        {
            BiTree bt;
            gets_s(preInfixExp);//������ʽ
            varSubstitute(var, preInfixExp, infixExp);
            infixToSuffixExp(infixExp, suffixExp);
            bt.buildTree(suffixExp);
            bt.oreder("all");
            printf("\n������ֵ���Ϊ %.2llf\n", bt.calcTree());
        }
        else if (!strcmp("EXIT", command)) break;
        else if (!strcmp("cls", command))
        {
            system("cls");
            showMenu();
        }
        else printf("�������\n");

    }
    return 0;
}
// (2+3)*60-9*(3+4)+3-50  == 190 


inline bool calc(char mode,Variable& var,char preInfixdExp[], char*& infixExp, char*& suffixExp,LDouble &res)//����ӿں��� mode=='c'չʾ�������
{                                                                                                            //�������������׼��׺���ʽ����
    if (!varSubstitute(var, preInfixdExp, infixExp) || !isInfixExperssion(infixExp))  //���������ɵ���׺���ʽ�ĺϷ���
    {
        if (mode == 'c')
        {
            printf("���ʽ�Ƿ���\n");
        }
        delete[]infixExp;
        return false;
    }
    infixToSuffixExp(infixExp, suffixExp); //��׺ת��׺
    if (mode == 'c')
    {
        printf("�Զ����ɵĺ�׺���ʽΪ ��%s\n", suffixExp);
        printf("���Ϊ��%.2llf\n\n", calcSuffixExperssion(suffixExp)); //������
    }
    res = calcSuffixExperssion(suffixExp);
    delete[]suffixExp; //�����ڴ�
    delete[]infixExp;
    return true;
}

inline void showMenu(void)
{
    printf("\n\n");
    printf("\t\t======================--++++���׼�����++++--======================\n");
    printf("\t\t ������������ո���������������ɶ��� ������������λС��\n");
    printf("\t\t ���븺�����ø��Ž������\n");
    printf("\t\t ������ı��ʽ�������ʾ�������� ��������ѧ�������ֹ����\n");
    printf("\t\t ���1.calc (���ʽ)  2.new (����)     3.delete(����) 4.showvar\n");
    printf("\t\t       5.show (����)    6.let (����) (��ֵ��)(���ʽ)   7.cls 8.tree(���ʽ��\n");
    printf("\t\t======================================================================\n\n");
    printf("\n\n�������ʼ������ \"EXIT\" �������㡣\n\n");
}