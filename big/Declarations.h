#include <iostream>
#include <fstream>
#include <string.h>
#include <cstring>
using namespace std;

void doDiff(int argc, char* argv[]);
void doGrep(int argc, char* argv[]);
void doTee(int argc, char* argv[]);
void doCat(int argc, char* argv[]);
void doCp(int argc, char* argv[]);
void doCd(int argc, char* argv[]);
void doPwd(int argc, char* argv[]);
void doEcho(int argc, char* argv[]);
struct Terminal {
    char user[9999]; // 用户名
    char mach[9999]; // 计算机名
    char root[9999]; // 根目录
    char wdir[9999]; // 工作目录
    char strin[9999]; // 重定向标准输入
    char strout[9999]; // 重定向标准输出
};
extern Terminal gTerm;
