#include"Declarations.h"
#include "global.h"

bool doLineno = false;
bool doBlankNo = false;
bool doReplaceBlank = false;
bool hasB = false;
bool doShowEnd = false;
bool isBlank = false;
bool isLastLineNonBlank = false;

int countDigit(int num){
    int count = 0;
    while (num != 0){
        num /= 10;
        count++;
    }
    return count;
}

void intToChar(int num, char * numStr){
    int digit = countDigit(num);
    char charDigit;
    numStr[digit] = '\0';
    while (num != 0){
        charDigit = '0' + num % 10;
        numStr[digit - 1] = charDigit;
        digit --;
        num /= 10;
    }
    return;
}

void outputLineNum(int linenum){
    int digit = countDigit(linenum);
    for(int j = 0; j < 6 - digit; j++){
        strcat(gTerm.strout, " ");
    }
    char numStr[20];
    intToChar(linenum, numStr);
    strcat(gTerm.strout, numStr);
    strcat(gTerm.strout, "  ");
    return;
}

int outputBlank(int linenum){
    if(doReplaceBlank){
        if(isBlank){
            return linenum;
        }
        else{
            isBlank = true;
        }
    }
    if(doBlankNo){
        outputLineNum(linenum);
        linenum++;
    }
    if(doShowEnd){
        strcat(gTerm.strout, "$");
    }
    strcat(gTerm.strout, "\n");
    return linenum;
}

int outputLine(char line[], int linenum){
    isBlank = false;
    if(doLineno){
        outputLineNum(linenum);
        linenum++;
    }
    strcat(gTerm.strout, line);
    if (doShowEnd){
        strcat(gTerm.strout, "$");
    }
    strcat(gTerm.strout, "\n");
    return linenum;
}

void doCat(int argc, char * argv[]){
    doLineno = false;
    doBlankNo = false;
    doReplaceBlank = false;
    hasB = false;
    doShowEnd = false;
    isBlank = false;
    
    int filenum = 0;
    char * arrFile[MAXARG];
    for (int i = 0; i < MAXARG; i++){
        arrFile[i] = new char[MAXLINE]; //initialize the 2D char array for storing file names
    }
    
    for(int i = 1; i < argc; i++){
        if (strcmp(argv[i], "--help") == 0){
            strcpy(gTerm.strout, "\
Usage: cat [OPTION]... [FILE]...\n\
Concatenate FILE(s) to standard output.\n\
\n\
With no file, or when FILE is -, read standard input.\n\
\n\
  -b, --number-nonblank    number nonempty output lines, overrides -n\n\
  -E, --show-ends          display $ at end of each line\n\
  -n, --number             number all output lines\n\
  -s, --squeeze-blank      suppress repeated empty output lines\n\
      --help     display this help and exit\n\
\n\
Examples:\n\
  cat f - g  Output f's contents, then standard input, then g's contents.");
            return;
        }
        else if ((strcmp(argv[i], "-n") == 0) || (strcmp(argv[i], "--number") == 0)){
            if (hasB){
                continue;
            }
            doLineno = true;
            doBlankNo = true;
        }
        else if ((strcmp(argv[i], "-b") == 0) || (strcmp(argv[i], "--number-nonblank") == 0)){
            hasB = true;
            doBlankNo = false;
            doLineno = true;
        }
        else if ((strcmp(argv[i], "-s") == 0) || (strcmp(argv[i], "--squeeze-blank") == 0)){
            doReplaceBlank = true;
        }
        else if ((strcmp(argv[i], "-E") == 0) || (strcmp(argv[i], "--show-ends") == 0)){
            doShowEnd = true;
        }
        else{
            strcpy(arrFile[filenum], argv[i]);
            filenum++;
        }
    }
    int linenum = 1;
    int digit = 0;
    for (int i = 0; i < filenum; i++){
        char line[MAXLINE];

        if ( (strcmp(arrFile[i], "-") == 0) || (filenum == 0) ){ //读入标准输入
            int strInLen = strlen(gTerm.strin);
            int totlinenum = 0;
            int templen = 0;
            char *arrline[MAXARG];
            for (int j = 0; j < MAXARG; j++){
                arrline[j] = new char[MAXLINE];
            }

            //用\n分割字符串
            for(int j = 0; j < strInLen; j++){
                if (gTerm.strin[j] == '\n'){
                    arrline[totlinenum][templen] = '\0';
                    totlinenum++;
                    templen = 0;
                    continue;
                }
                if (gTerm.strin[j] == '\n'){
                    templen++;
                    break;
                }
                arrline[totlinenum][templen] = gTerm.strin[j];
                templen++;
            }
            arrline[totlinenum][templen] = '\0';
            totlinenum++;

            //输出
            for (int j = 0; j < totlinenum; j++){
                if (strlen(arrline[j]) > 0){
                    linenum = outputLine(arrline[j], linenum);
                }
                else{
                    linenum = outputBlank(linenum);
                }
            }
        }

        //读入文件
        else{
            ifstream fin(fullFileDir(arrFile[i]));
            if (!fin){
                cerr << "cat: '" << arrFile[i] << "': No such file or directory" << endl;
                return;
            }
            else{
                while (fin.getline(line, MAXLINE)){
                    if (strlen(line) > 0){
                        linenum = outputLine(line, linenum);
                    }
                    else{
                        linenum = outputBlank(linenum);
                    }
                    if (fin.eof()){ //若文件的最后一行不是空行，需要做出标记
                        isLastLineNonBlank = true;
                        continue;
                    }
                }
                if(isLastLineNonBlank){
                    isLastLineNonBlank = false; //重设标记，进入下一次for循环，输出下一个文件
                    continue;
                }
                else{ //若文件的最后一行为空行，则fin.getline会返回false跳出while循环，因此需要再输出一个空行
                    linenum = outputBlank(linenum);
                }
            }
        }
    }
    return;
}