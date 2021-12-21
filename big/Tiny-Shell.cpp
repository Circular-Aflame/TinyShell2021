#include"Declarations.h"

Terminal gTerm;

char table[9999];//table数组负备份strin。

int main() {
    cout << "Machine Name:";
    cin >> gTerm.mach;
    cout << "Root Directory:";
    cin >> gTerm.root;
    cout << "Login:";
    cin >> gTerm.user; //以上为输入机器名称、根目录、以及用户名。
    cin.ignore();//如果没有这条语句，第一次循环的cin.getline会被跳过，造成连续输出两次用户名等内容。

    for (int p = 0;; p++) {
        strcpy(gTerm.wdir,"/");
        cout << "\033[92;1m" << gTerm.user 
            << "\033[92; 1m@" 
            << "\033[92;1m" << gTerm.mach 
            << "\033[0m:" 
            << "\033[94;1m" << gTerm.wdir 
            << "\033[0m$ ";//以上为输出彩色的用户名等提示信息。

        int argc = 0;//argc为记录字符串数量的变量。

        cin.getline(gTerm.strin, 9999);
        strcat(gTerm.strin," ");//用户输入指令到strin。程序自动在输入末尾补一个空格。 

        bool blank = 1;//blank负责辅助判断输入字符串是否为空字符串。
        for (int i = 0; i < strlen(gTerm.strin); i++) {
            if (gTerm.strin[i] != 32) {
                blank = 0;
            }
        }
        if (blank == 1) {
            continue;
        }//当输入字符串为空字符串时，直接跳过此次循环。

        for (int i = 0; i < strlen(gTerm.strin); i++) {
            if (gTerm.strin[i] != 32) {
                strncpy(gTerm.strin, gTerm.strin + i, strlen(gTerm.strin) );
                break;
            }
        }//去掉输入正式指令前的空格
        


        int num = 0;//num为记录“|”个数的变量。
        for (int i = 1; i < strlen(gTerm.strin); i++) {//循环从1开始，防止一开始就出现了复合指令。
            if (gTerm.strin[i] == 124&& gTerm.strin[i-1]==32) {//仅当“|”前为空格时，将“|”识别为复合指令。
                num++;
            }//124为“|”的ASCII码
        }
        if (num == 0) {//没有复合指令时
            strcpy(table, gTerm.strin);//table用作数据隔离，防止后续操作影响gTerm.strin
            for (int i = 0; i < strlen(gTerm.strin); i++) {
                if (gTerm.strin[i] == 32&& gTerm.strin[i+1]!=32) {//"32"为空格的ASCII码,仅当空格后面不为空格时argc++。
                    argc++;
                }
            }

            char** argv = new char* [argc + 1];//加1是为了保证在strin中没有空格时argv可以被创建出来。
            for (int i = 0; i < argc; i++) {
                if (i == 0) {
                    argv[i] = strtok(table, " ");
                }
                else {
                    argv[i] = strtok(NULL, " ");
                }//如果strin中出现空格，则将strin分割,并将字符串分别存在argv[x]里面。

            };

            char name[8][8] = { "diff" ,"cat","cd","cp","grep","echo","tee","pwd" };
            void(*pointer[8])(int, char* []) = { doDiff,doCat,doCd,doCp,doGrep,doEcho,doTee,doPwd };
            bool notfound=1;//notfound用于辅助判断输入指令是否合法。
            for (int i = 0; i < 8; i++) {
                if (strcmp(argv[0], name[i]) == 0) {
                    pointer[i](argc, argv);
                    notfound = 0;
                }
            }
            if (notfound) {
                cerr << "command '" << argv[0] << "'not found" << endl;
                continue;
            }//如果没有相应指令，用cerr提示。

            cout << gTerm.strout;
            for (int i = 0; i < strlen(gTerm.strout); i++) {
                gTerm.strout[i] = '\0';//清空输出
            }
            delete[]argv;//删除动态二位数组argv。
        }
        else {
            for (int i = 0; i < strlen(table); i++) {
                table[i] = '\0';//清空
            }
            strcpy(table, gTerm.strin);//table用作数据隔离，防止后续操作影响gTerm.strin
            char** strin = new char* [num+1];//二维数组strin负责记录以“|”为标志拆分的字符串。
            strcat_s(table, "|");//用户输入指令到strin。程序自动在输入末尾补一个"|",以便让strtok识别最后一段字符串。
            for (int i = 0; i < num+1; i++) {
                if (i == 0) {
                    strin[i] = strtok(table, "|");
                }
                else {
                    strin[i] = strtok(NULL, "|");
                }//如果gTerm.strin中出现“|”，则将其分割,并将字符串分别存在strin[x]里面。
            }

            for (int i1 = 0; i1 < num+1; i1++) {
                
                bool blank1 = 1;//blank1负责辅助判断输入字符串是否为空字符串。
                for (int i = 0; i < strlen(strin[i1]); i++) {
                    if (strin[i1][i] != 32) {
                        blank1 = 0;
                    }
                }
                if (blank1 == 1) {
                    cerr << "command ' 'not found" << endl;
                    break;
                }//当某一段复合指令字符串为空字符串时，直接报错。

                for (int i = 0; i < strlen(strin[i1]); i++) {
                    if (strin[i1][i] != 32) {
                        strncpy(strin[i1], strin[i1] + i, strlen(strin[i1]));
                        break;
                    }
                }//去掉输入正式指令前的空格
                
                int argc = 0;
                for (int i = 0; i < strlen(strin[i1]); i++) {
                    if (strin[i1][i] == 32&& strin[i1][i + 1] != 32) {
                        argc++;
                    }
                }//"32"为空格的ASCII码,仅当空格后面不为空格时argc++。
                

                char** argv = new char* [argc + 1];//加1是为了保证在strin中没有空格时argv可以被创建出来。
                for (int i = 0; i < argc; i++) {
                    if (i == 0) {
                        argv[i] = strtok(strin[i1], " ");
                    }
                    else {
                        argv[i] = strtok(NULL, " ");
                    }//如果strin[i1]中出现空格，则将strin[i1]分割,并将字符串分别存在argv[x]里面。

                }
               

                char name[8][8] = {"diff" ,"cat","cd","cp","grep","echo","tee","pwd"};
                bool notfound=1;//notfound用于辅助判断输入指令是否合法。
                void(*pointer[8])(int, char* []) = { doDiff,doCat,doCd,doCp,doGrep,doEcho,doTee,doPwd };

                for (int i = 0; i < 8; i++) {
                    if (strcmp(argv[0], name[i]) == 0) {
                        pointer[i](argc, argv);
                        notfound=0;
                    }
                }
                if (notfound) {
                    cerr << "command '" << argv[0] << "'not found" << endl;
                    continue;
                }//如果没有相应指令，用cerr提示。

                if (i1 == num ) {
                    cout << gTerm.strout;
                }
                else { 
                    strcpy(gTerm.strin,gTerm.strout); 
                }//这一次的结果作为下一条指令的输入。

                for (int i = 0; i < strlen(gTerm.strout); i++) {
                    gTerm.strout[i] = '\0';//清空输出
                }
                
                delete[]argv;//删除动态二位数组argv。
            }
            
            delete[]strin;//删除动态二位数组strin。

        }
    }
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
