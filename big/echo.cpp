#include <iostream>
#include <cstring>
#include"Declarations.h"
using namespace std;


void doEcho(int argc, char* argv[]) {
	char help[99] = "The instruction echo is used for outputting character string. ";
	char enter[2] = {'\n','\0'};//enter用于辅助回车。

	if (argc == 1) {//当只输入echo后面没有其它内容时，为防止指针指向空，直接输出“\n”
		
		strcat_s(gTerm.strout, enter);//加入回车的“/n”
	}
	else if (strcmp(argv[1], "--help") == 0) {
		strcat_s(help, enter);
		strcpy_s(gTerm.strout,9999, help);
	}//当用户输入--help的时候，输出帮助。
	else if (strcmp(argv[1], "-n") == 0) {//用户输入-n时的情况。
		
		for (int i = 2; i < argc; i++) {
			strcat_s(gTerm.strout, argv[i]);
			strcat_s(gTerm.strout, " ");
		}
	}
	else {
		for (int i = 1; i < argc; i++) {
			strcat_s(gTerm.strout, argv[i]);
			strcat_s(gTerm.strout, " ");
		}
		strcat_s(gTerm.strout, enter);//加入回车的“/n”
		
	}
}
