#include <iostream>
#include <cstring>
#include"Declarations.h"
using namespace std;


void doEcho(int argc, char* argv[]) {
	char help[99] = "The instruction echo is used for outputting character string. ";
	char enter[2] = {'\n','\0'};//enter���ڸ����س���

	if (argc == 1) {//��ֻ����echo����û����������ʱ��Ϊ��ָֹ��ָ��գ�ֱ�������\n��
		
		strcat_s(gTerm.strout, enter);//����س��ġ�/n��
	}
	else if (strcmp(argv[1], "--help") == 0) {
		strcat_s(help, enter);
		strcpy_s(gTerm.strout,9999, help);
	}//���û�����--help��ʱ�����������
	else if (strcmp(argv[1], "-n") == 0) {//�û�����-nʱ�������
		
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
		strcat_s(gTerm.strout, enter);//����س��ġ�/n��
		
	}
}
