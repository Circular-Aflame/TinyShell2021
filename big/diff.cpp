#include"Declarations.h"

char*out = gTerm.strout;/*简便输出指令*/
bool*cho=new bool[6]();/*命令记录*/
char*ii=nullptr;/*-I字符串记录*/
void help()/*显示帮助*/
{
	strcat(out,"输入格式：diff {-b}{-B}{-i}{-q}{-w}{-I[字符串]}[文件1][文件2]\n-b：不检查空格字符的不同\n-B：不检查空白行\n-i：不检查大小写的不同\n-q：仅显示有无差异。无差异时不显示，有差异时显示“File [文件1] and [文件2] differ”\n-w: 忽略全部的空格字符\n-I[字符串]：若两个文件在某几行有所不同，但这几行同时都包含了选项中指定字符串（空格不可忽略），则不显示为这两个文件的差异\n");
}
void modify(char*a,char* b);
void doDiff(int argc, char* argv[])/*diff指令处理*/
{
	if (argc<=2)/*单指令帮助*/
	{
		if (strcmp(argv[1],"--help")==0)/*显示帮助*/
		{
			help();
		}
		else/*单指令错误提示*/
		{
			strcat(out,argv[1]);
			strcat(out,": Command Wrong.Enter 'diff --help' for help.\n");
		}
	}
	else if(argc==3)/*基本功能*/
	{
		modify(argv[1],argv[2]);
	}
	else/*带命令diff实现*/
	{
		for (int i = 1; i < argc-2; i++)
		{
			switch(argv[i][1])
			{
				case 'b':
					cho[0]=1;/*不检查空格字符个数的不同*/
					break;
				case 'B':
					cho[1]=1;/*不检查空白行*/
					break;
				case 'i':
					cho[2]=1;/*不检查大小写不同*/
					break;
				case 'q':
					cho[3]=1;/*直接显示文件是否不同*/
					break;
				case 'w':
					cho[4]=1;/*忽略所有空格字符*/
					break;
				case 'I':
					cho[5]=1;/*忽略特定行差异*/
					ii=new char[20]();
					for(int o=0;argv[i][o+3]!=']';o++)
					{
						ii[o]=argv[i][o+3];
					}
					break;
				default:/*命令错误提示*/
					strcat(out,argv[i]);
					strcat(out,": Command Not Found.Enter 'diff --help' for help.\n");
					return;
			}
		}
		modify(argv[argc-2],argv[argc-1]);
		cho=new bool[6]();
		ii=NULL;
	}
}