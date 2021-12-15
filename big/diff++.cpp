#include"Declarations.h"

extern bool*cho;
extern char*ii;
extern char*out;/*便于输出*/
bool*conta,*contb;/*-I比较数组*/
char name[2][20]={"newtmpfile1.txt","newtmpfile2.txt"};
void remove()/*清除临时文件*/
{
	remove(name[0]);
	remove(name[1]);
}
bool linecheck(FILE*at,int a,int*rowa)/*检查是否为空白行*/
{
	fseek(at,rowa[a],0);
	char f=fgetc(at);
	if(f=='\n')
	{
		return false;
	}
	return true;
}
bool sea(char*w,int p,int k,int n)/*w中是否含有目标字符串*/
{
	if(k-p<n)
	{
		return false;
	}
	char*o=new char[n]();
	for(int i=0;i<n-1;i++)
	{
		o[i]=w[p+i];
	}
	if(strcmp(o,ii)==0)
	{
		return true;
	}
	return sea(w,p+1,k,n);
}
bool cont(FILE*at,int a,int*rowa)/*判断是否都含忽略差异数组*/
{
	int k=rowa[a]-rowa[a-1];
	char*w=new char[rowa[a]-rowa[a-1]]();
	fseek(at,rowa[a-1],0);
	for(int i=0;i<k;i++)
	{
		w[i]=fgetc(at);
	}
	int n=0;
	while(ii[n]!='\0'){n++;}
	return sea(w,0,k,n+1);
}
void contrast(FILE*at,bool*contan,int an,int*rowa)/*记录字符串比对情况*/
{
	for(int i=0;i<an;i++)
	{
		contan[i]=cont(at,i+1,rowa);
	}
}
char ali(char x)/*统一为小写字母*/
{
	if((x>='A')&&(x<='Z'))
	{
		return x+32;
	}
	return x;
}
void numoutm(int k)/*输出行数*/
{
	int t=1;
	for(int i=10;k>=i;i*=10)
	{
		t++;
	}
	char*num=new char[t];
	for(int i=0;i<t;i++)
	{
		num[t-i-1]=k%10+'0';
		k/=10;
	}
	strcat(out,num);
	delete[] num;
}
void newfilem(FILE*&at,int j)/*打开临时文件*/
{
	at=fopen(name[j],"w+");
	gets(gTerm.strin);
	for(int i=0;gTerm.strin[i]!='\0';i++)
	{
		if(gTerm.strin[i]=='\\'&&gTerm.strin[i+1]=='n')
		{
			fputc('\n',at);
			i++;
		}
		else
		{
			fputc(gTerm.strin[i],at);
		}
	}
	fclose(at);
	at=fopen(name[j],"r");
}
bool checkm(FILE*&at,char*ar)/*检查并打开文件*/
{
	char*a=new char[50];
	if(ar[0]=='\\')
	{
		strcpy(a,ar);
	}
	else
	{
		strcpy(a, gTerm.wdir);
		strcat(a, "\\");
		strcat(a, ar);
	}/*合成文件路径*/
	if ((at = fopen(a, "r")) == NULL)
	{
		strcat(out, "diff: ");
		strcat(out, ar);
		strcat(out, ": No such file or directory.\n");
		delete[] a;
		return true;
	}
	delete[] a;
	return false;
}
int lengthm(FILE*d)/*获取文件行数*/
{
	int i=1;
	char f='f';
	while(f!=EOF)
	{
		f=fgetc(d);
		if(f=='\n')
		{
			i++;
		}
	}
	return i;
}
void rowm(FILE*at,int*rowa)/*获取行节点*/
{
	rowa[0]=0;
	int i=1;
	char t='t';
	rewind(at);
	while(t!=EOF)
	{
		t=fgetc(at);
		if(t=='\n')
		{
			rowa[i]=ftell(at);
			i++;
		}
	}
	rowa[i]=ftell(at)+1;
}
bool parem(FILE*at,int a,int*rowa,FILE*bt,int b,int*rowb)/*比较两行是否相同*/
{
	int i=rowa[a-1];
	int j=rowb[b-1];
	fseek(at,i,0);
	fseek(bt,j,0);
	char f=fgetc(at);
	char l=fgetc(bt);
	if(cho[0])/*判断是否检查空格不同*/
	{
		if((f==' ')&&(l==' '))
		{
			while(f==' '){f=fgetc(at);}
			while(l==' '){l=fgetc(bt);}
		}
	}
	if(cho[4])/*判断是否忽略空格*/
	{
		while(f==' '){f=fgetc(at);}
		while(l==' '){l=fgetc(bt);}
	}
	while((f!='\n')&&(l!='\n')&&(f!=EOF)&&(l!=EOF))
	{
		if(cho[0])/*判断是否检查空格不同*/
		{
			if((f==' ')&&(l==' '))
			{
				while(f==' '){f=fgetc(at);}
				while(l==' '){l=fgetc(bt);}
			}
		}
		if(cho[4])/*判断是否忽略空格*/
		{
			while(f==' '){f=fgetc(at);}
			while(l==' '){l=fgetc(bt);}
		}
		if(cho[2])/*判断是否检查大小写*/
		{
			f=ali(f);
			l=ali(l);
		}
		if(f!=l)
		{
			return false;
		}
		f=fgetc(at);
		l=fgetc(bt);
	}
	if((f=='\n')||(f==EOF))
	{
		if((l=='\n')||(l==EOF))
		{
			return true;
		}
	}
	return false;
}
char lcsm(int i,int j,int p,char**se,char*re)/*录出最长子列*/
{
	if(p==-1)
	{
		return se[i][j];
	}
	switch(se[i][j])
	{
		case 'e':
			re[p]=lcsm(i-1,j-1,p-1,se,re);
			break;
		case 'd':
			re[p]=lcsm(i-1,j,p-1,se,re);
			break;
		case 'a':
			re[p]=lcsm(i,j-1,p-1,se,re);
			break;
	}
	return se[i][j];
}
void addm(int b,int*rowb,FILE*bt)/*添加行操作*/
{
	char*fen=new char[rowb[b]-rowb[b-1]+3]();
	fseek(bt,rowb[b-1],0);
	fen[0]='>';
	int i=0;
	while((fen[i]!='\n')&&(fen[i]!=EOF))
	{
		i++;
		fen[i]=fgetc(bt);
	}
	if(fen[i]!='\n')
	{
		fen[i]='\n';
	}
	strcat(out,fen);
	delete[] fen;
}
void delem(int a,int*rowa,FILE*at)/*删除行操作*/
{
	char*fen=new char[rowa[a]-rowa[a-1]+3]();
	fseek(at,rowa[a-1],0);
	fen[0]='<';
	int i=0;
	while((fen[i]!='\n')&&(fen[i]!=EOF))
	{
		i++;
		fen[i]=fgetc(at);
	}
	if(fen[i]!='\n')
	{
		fen[i]='\n';
	}
	strcat(out,fen);
	delete[] fen;
}
void replacem(int a,int b,int p,char*re,FILE*at,FILE*bt,int*rowa,int*rowb,int fix)/*输出更改方案*/
{
	if(p==fix)
	{
		return;
	}
	switch(re[p])
	{
		case 'e':
			replacem(a+1,b+1,p+1,re,at,bt,rowa,rowb,fix);
			break;
		case 'a':
			numoutm(a);
			strcat(out,"a");
			numoutm(b+1);
			strcat(out,"\n");
			addm(b+1,rowb,bt);
			int k;
			for(k=1;(re[p+k]!='e')&&(p+k!=fix);k++)
			{
				addm(b+1+k,rowb,bt);
			}
			if(p+k!=fix)
			{
				replacem(a+1,b+1+k,p+k+1,re,at,bt,rowa,rowb,fix);
			}
			break;
		case 'd':
			bool e=true;
			for(int k=1;(re[p+k]!='e')&&(p+k!=fix);k++)
			{
				if(re[p+k]=='a')
				{
					e=false;
					break;
				}
			}
			if(e)
			{
				numoutm(a+1);
				strcat(out,"d");
				numoutm(b);
				strcat(out,"\n");
				delem(a+1,rowa,at);
				int k;
				for(k=1;(re[p+k]!='e')&&(p+k!=fix);k++)
				{
					delem(a+1+k,rowa,at);
				}
				if(p+k!=fix)
				{
					replacem(a+1+k,b+a,p+k+1,re,at,bt,rowa,rowb,fix);
				}
				break;
			}
			else
			{
				numoutm(a+1);
				strcat(out,"c");
				numoutm(b+1);
				strcat(out,"\n");
				delem(a+1,rowa,at);
				int k;
				for(k=1;re[p+k]!='a';k++)
				{
					delem(a+1+k,rowa,at);
				}
				strcat(out,"---\n");
				addm(b+1,rowb,bt);
				int m;
				for(m=1;(re[p+k+m]!='e')&&(p+k+m!=fix);m++)
				{
					addm(b+1+m,rowb,bt);
				}
				if(p+k+m!=fix)
				{
					replacem(a+1+k,b+m+1,p+k+m+1,re,at,bt,rowa,rowb,fix);
				}
				break;
			}
			break;
	}
}
bool stringjudge(int a,int b,int p,char*re,int*rowa,int*rowb,int fix)/*-I判断*/
{
	if(p==fix)
	{
		return true;
	}
	switch(re[p])
	{
		case 'e':
			return stringjudge(a+1,b+1,p+1,re,rowa,rowb,fix);
			break;
		case 'a':
			if(contb[b]==0)
			{
				return false;
			}
			int k;
			for(k=1;(re[p+k]!='e')&&(p+k!=fix);k++)
			{
				if(contb[b+k]==0)
				{
					return false;
				}
			}
			if(p+k!=fix)
			{
				return stringjudge(a+1,b+1+k,p+k+1,re,rowa,rowb,fix);
			}
			else
			{
				return true;
			}
			break;
		case 'd':
			bool e=true;
			for(int k=1;(re[p+k]!='e')&&(p+k!=fix);k++)
			{
				if(re[p+k]=='a')
				{
					e=false;
					break;
				}
			}
			if(e)
			{
				if(conta[a]==0)
				{
					return false;
				}
				int k;
				for(k=1;(re[p+k]!='e')&&(p+k!=fix);k++)
				{
					if(conta[a+k]==0)
					{
						return false;
					}
				}
				if(p+k!=fix)
				{
					return stringjudge(a+1+k,b+a,p+k+1,re,rowa,rowb,fix);
				}
				else
				{
					return true;
				}
				break;
			}
			else
			{
				if(conta[a]==0)
				{
					return false;
				}
				int k;
				for(k=1;re[p+k]!='a';k++)
				{
					if(conta[a+k]==0)
					{
						return false;
					}
				}
				if(contb[b]==0)
				{
					return false;
				}
				int m;
				for(m=1;(re[p+k+m]!='e')&&(p+k+m!=fix);m++)
				{
					if(contb[b+m]==0)
					{
						return false;
					}
				}
				if(p+k+m!=fix)
				{
					return stringjudge(a+1+k,b+m+1,p+k+m+1,re,rowa,rowb,fix);
				}
				else
				{
					return true;
				}
				break;
			}
			break;
	}
	return false;
}
bool linejudge(int a,int b,int p,char*re,FILE*at,FILE*bt,int*rowa,int*rowb,int fix)/*-I判断*/
{
	if(p==fix)
	{
		return true;
	}
	switch(re[p])
	{
		case 'e':
			return linejudge(a+1,b+1,p+1,re,at,bt,rowa,rowb,fix);
			break;
		case 'a':
			if(linecheck(bt,b,rowb))
			{
				return false;
			}
			int k;
			for(k=1;(re[p+k]!='e')&&(p+k!=fix);k++)
			{
				if(linecheck(bt,b+k,rowb))
				{
					return false;
				}
			}
			if(p+k!=fix)
			{
				return linejudge(a+1,b+1+k,p+k+1,re,at,bt,rowa,rowb,fix);
			}
			else{return true;}
			break;
		case 'd':
			bool e=true;
			for(int k=1;(re[p+k]!='e')&&(p+k!=fix);k++)
			{
				if(re[p+k]=='a')
				{
					e=false;
					break;
				}
			}
			if(e)
			{
				if(linecheck(at,a,rowa))
				{
					return false;
				}
				int k;
				for(k=1;(re[p+k]!='e')&&(p+k!=fix);k++)
				{
					if(linecheck(at,a+k,rowa))
					{
						return false;
					}
				}
				if(p+k!=fix)
				{
					return linejudge(a+1+k,b+a,p+k+1,re,at,bt,rowa,rowb,fix);
				}
				else{return true;}
				break;
			}
			else
			{
				if(linecheck(at,a,rowa))
				{
					return false;
				}
				int k;
				for(k=1;re[p+k]!='a';k++)
				{
					if(linecheck(at,a+k,rowa))
					{
						return false;
					}
				}
				if(linecheck(bt,b,rowb))
				{
					return false;
				}
				int m;
				for(m=1;(re[p+k+m]!='e')&&(p+k+m!=fix);m++)
				{
					if(linecheck(bt,b+m,rowb))
					{
						return false;
					}
				}
				if(p+k+m!=fix)
				{
					return linejudge(a+1+k,b+m+1,p+k+m+1,re,at,bt,rowa,rowb,fix);
				}
				else{return true;}
				break;
			}
			break;
	}
	return false;
}
void modify(char*ar,char* br)
{
	FILE*at,*bt;
	if(ar[0]=='-')
	{
		newfilem(at,0);
	}
	else
	{
		if (checkm(at,ar)){return;}
	}
	if(br[0]=='-')
	{
		newfilem(bt,1);
	}
	else
	{
		if (checkm(bt,br)){return;}
	}/*打开文件并检验是否成功*/
	int an=lengthm(at);
	int bn=lengthm(bt);/*获取两个文本行数*/
	int*rowa=new int[an+1];
	int*rowb=new int[bn+1];
	rowm(at,rowa);
	rowm(bt,rowb);/*获取每行指针*/
	char**se=new char*[an+1];
	for(int i=0;i<=an;i++)
	{
		se[i]=new char[bn+1];
	}/*存储最长公共子列的递归符*/
	int**com=new int*[an+1];/*记录子列长度*/
	for(int i=0;i<=an;i++)/*记录子列路径*/
	{
		com[i]=new int[bn+1];
		for(int j=0;j<=bn;j++)
		{
			if(j==0)
			{
				com[i][j]=0;
				se[i][j]='d';
			}
			else if(i==0)
			{
				com[i][j]=0;
				se[i][j]='a';
			}
			else
			{
				if(parem(at,i,rowa,bt,j,rowb))
				{
					com[i][j]=com[i-1][j-1]+1;
					se[i][j]='e';
				}
				else
				{
					if(com[i-1][j]<=com[i][j-1])
					{
						com[i][j]=com[i][j-1];
						se[i][j]='a';
					}
					else
					{
						com[i][j]=com[i-1][j];
						se[i][j]='d';
					}
				}
			}
		}
	}
	int fix=an+bn-com[an][bn];
	char*re=new char[fix];
	int p=fix-1;
	re[p]=lcsm(an,bn,p-1,se,re);
	if(cho[5])/*共有字符串判断*/
	{
		conta=new bool[an];
		contrast(at,conta,an,rowa);
		contb=new bool[bn];
		contrast(bt,contb,bn,rowb);
		if(stringjudge(0,0,0,re,rowa,rowb,fix))
		{
			remove();
			delete[] conta;
			delete[] contb;
			return;
		}
	}
	if(cho[1])/*不检查空白行*/
	{
		if(linejudge(0,0,0,re,at,bt,rowa,rowb,fix))
		{
			remove();
			return;
		}
	}
	if(cho[3])/*-q指令判断*/
	{
		if((com[an][bn]==an)&&(an==bn))
		{
			remove();
			return;
		}
		else
		{
			strcat(out,"File ");
			strcat(out,ar);
			strcat(out," and ");
			strcat(out,br);
			strcat(out," differ\n");
			remove();
			return;
		}
	}
	replacem(0,0,0,re,at,bt,rowa,rowb,fix);
	delete[] com;
	delete[] se;
	delete[] rowa;
	delete[] rowb;
	delete[] re;
	fclose(at);
	fclose(bt);/*扫除*/
	remove();
}