#include<iostream>
#include<string.h>
#include<stack> 
#include<sstream>
#include<map>
#include<vector>
using namespace std;
char infix[100];          //��׺���ʽ 
char suffix[100];         //��׺���ʽ 
char letter[50];          //�������������ĸ 
map<char,int> m;          //ӳ�� ����ĸ��0��1��Ӧ 


void handle()             //��->ת��Ϊ- <=>ת��Ϊ=�������� 
{
	int i=0,j;
	while(infix[i]!='\0')
	{
		if(infix[i]=='-')    //����->ת��Ϊ-�������� 
		{
			j=i;
			while(infix[j]!='\0')
			{
				infix[j+1]=infix[j+2];
				j++;
			}
		}
		else if(infix[i]=='=') //����<=>ת��Ϊ=�������� 
		{
			j=i;
			while(infix[j]!='\0')
			{
				infix[j+1]=infix[j+2];
				j++;
			}
			j=i-1;
			while(infix[j]!='\0')
			{
				infix[j]=infix[j+1];
				j++;
			}
		}
	i++;
	}
}


int isp(char a)            //�������ȼ� 
{
	if(a=='#') return 0;
	if(a=='(') return 1;
	if(a=='!') return 6;
	if(a=='&') return 5;
	if(a=='|') return 4;
	if(a=='-') return 3;
	if(a=='=') return 2;
}


void change()            //����׺ת��Ϊ��׺ 
{
	int i=0,j=0;
	stack<char> s;
	s.push('#');
	char ch;
	while(infix[i]!='#')
	{
		if((infix[i]>='a'&&infix[i]<='z')||(infix[i]>='A'&&infix[i]<='Z'))
		{
			suffix[j++]=infix[i];
		}
		else if(infix[i]=='(')
		{
			s.push('(');
		}
		else if(infix[i]==')')
		{
			for(ch=s.top(),s.pop();ch!='(';ch=s.top(),s.pop())
			{
				suffix[j++]=ch;
			}
		}
		else
		{
			if(isp(infix[i])<=isp(s.top()))
			{
				suffix[j++]=s.top();
				s.pop();
			}
			
			s.push(infix[i]);
		}
		i++;
	}
	while(!s.empty())
	{
		ch=s.top();
		s.pop();
		suffix[j++]=ch;
	}
}

int cal()           //�Ժ�׺���ʽ��������
{
	stack<char> s;
	s.push('#');
	int i=0;
	int t1,t2;
	while(suffix[i]!='#')
	{
		if(suffix[i]>='a'&&suffix[i]<'z'||suffix[i]>='A'&&suffix[i]<='Z')
			s.push(m[suffix[i]]);
		else
		{
			if(suffix[i]=='!')
			{
				if(s.top()=='#')
					cout<<"���ݴ���"<<endl; 
				else
				{
					t1=s.top();
					s.pop();
					s.push(!t1);
				}
			}
			if(suffix[i]=='&')
			{
				t1=s.top();
				s.pop();
				t2=s.top();
				s.pop();
				if(t1==1&&t2==1)
				{
					s.push(1);
				}
				else
				{
					s.push(0);
				}
			}
			if(suffix[i]=='|')
			{
				t1=s.top();
				s.pop();
				t2=s.top();
				s.pop();
				if(t1==1||t2==1)
				{
					s.push(1);
				}
				else
				{
					s.push(0);
				}
			}
			if(suffix[i]=='-')
			{
				t1=s.top();
				s.pop();
				t2=s.top();
				s.pop();
				if(t1==0&&t2==1)
				{
					s.push(0);
				}
				else
				{
					s.push(1);
				}
			}
			if(suffix[i]=='=')
			{
				t1=s.top();
				s.pop();
				t2=s.top();
				s.pop();
				if(t1==1&&t2==1||t1==0&&t2==0)
				{
					s.push(1);
				}
				else
				{
					s.push(0);
				}
			}
		}
		i++;
	}
	return (s.top());
	
} 

void dfs(int c)       //�ݹ�ö��ÿһ����� 
{
	if(c==strlen(letter))
	{
		int result=cal(),i=0;
		for(i=0;i<strlen(letter);i++)
		{
			cout<<m[letter[i]]<<"\t";
		}
		if(result==1)
		{
			cout<<result<<endl;
		}
		else
		{
			cout<<result<<endl;
		}
	return; 
	}
	
	m[letter[c]]=0;
	dfs(c+1);
	m[letter[c]]=1;
	dfs(c+1);
}




int main()
{
	cout<<"\t\t"<<"==========================================================="<<endl;
	cout<<"\t\t"<<"�ã���ʾ��,��->��ʾ�̺�,��<=>��ʾ˫�̺�,��&��ʾ��,��|��ʾ��"<<endl;
	 cout<<"\t\t\t\t\t"<<"����#�˳�"<<endl;
	cout<<"\t\t"<<"==========================================================="<<endl;
	while(1)
	{
		cout<<"��������ʽ��"<<endl;
		cin>>infix;        //������ʽ 
		if(infix[0]=='#')
			break;
		else{

			int i,j=0;        //�����ʽ����ĸ��ȡ���� 
			for(i=0;i<strlen(infix);i++) 
		{
			if(infix[i]>='a'&&infix[i]<='z'||infix[i]>='A'&&infix[i]<='Z')
			{ 
				letter[j++]=infix[i];
			}
		}
		int len=strlen(letter);
		for(i=0;i<len;i++)
		{
			int k=i+1;
			for(j=i+1;j<len;j++)
			{
				if(letter[j]!=letter[i])	
					letter[k++]=letter[j];
			}
			letter[k]='\0';
		}
		i=0;
		while(letter[i]!='\0')
		{
			cout<<letter[i++]<<"\t";
		}
		cout<<"result"; 
		cout<<endl;
	
		char a[]="#";      //����׺���ʽ���һ����ʶ�� 
		strcat(infix,a);

		handle();	      //��->ת��Ϊ- <=>ת��Ϊ=�������� 

		change();         //����׺ת��Ϊ��׺ 
	
		dfs(0);           //�ݹ�ö��ÿһ����� 
		 }
	}


	return 0;
} 
