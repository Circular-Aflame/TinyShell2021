#include"Declarations.h"
#include "global.h"


int splitDir(char * inChar, char *arrChar[]){
    int len = strlen(inChar), templen = 0, argc = 0;
    for (int i = 0; i < len; i++){
        if (inChar[i] == '/'){
            arrChar[argc][templen] = '/';
            arrChar[argc][templen + 1] = '\0';
            argc++;
            templen = 0;
            continue;
        }
        arrChar[argc][templen] = inChar[i];
        templen++;
    }
    arrChar[argc][templen] = '\0';
    argc++;
    return argc;
}

void doCd(int argc, char * argv[]){
    if(strcmp(argv[1], "--help") == 0){
        strcpy(gTerm.strout, "Change the shell working directory.");
        return;
    }

    char fullDir[MAXLINE];
    char finDir[MAXLINE];
    char * arrDir[MAXARG];
    char * arrRedDir[MAXARG];
    int dirNo;
    int redDirNo = 0;

    memset(finDir, 0, sizeof(finDir));

    for (int i = 0; i < MAXARG; i++){
        arrDir[i] = new char[MAXLINE];
    }
    for (int i = 0; i < MAXARG; i++){
        arrRedDir[i] = new char[MAXLINE];
    }

    if (argv[1][0] == '/'){
        strcpy(fullDir, argv[1]); //输入为绝对路径
    }
    else {
        strcpy(fullDir, gTerm.wdir);
        if (strcmp(fullDir, "/") != 0){
            strcat(fullDir, "/");
        }
        strcat(fullDir, argv[1]);
    }

    dirNo = splitDir(fullDir, arrDir);
    for (int i = 0; i < dirNo; i++){
        if ((strcmp(arrDir[i], "../") == 0) || (strcmp(arrDir[i], "..") == 0)){
            if(redDirNo > 0){
                redDirNo--;
                continue;
            }
        }
        else {
            strcpy(arrRedDir[redDirNo], arrDir[i]);
            redDirNo++;
        }
    }

    for (int i = 0; i < redDirNo; i++){
        strcat(finDir, arrRedDir[i]);
    }
    if (strlen(finDir) == 0){
        strcpy(finDir, "/");
    }
    int len = strlen(finDir);
    if ((finDir[len - 1] == '/') && (len != 1)){
        finDir[len - 1] = '\0';
    }
    strcpy(gTerm.wdir, finDir);
    return;
}