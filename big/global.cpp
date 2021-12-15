#include"Declarations.h"
#include "global.h"


char* fullFileDir(char *fileName){
    char* fullDir =  new char[MAXLINE];
    strcpy(fullDir, gTerm.root);
    if (fileName[0] == '/'){ //带有绝对路径的fileName
        strcat(fullDir, fileName);
    }
    else{
        strcat(fullDir, gTerm.wdir);
        if (strcmp(gTerm.wdir, "/") != 0){ //非空的wdir是以文件夹名结尾的，因此在连接文件名之前需要加上/    
            strcat(fullDir, "/");
        }
        strcat(fullDir, fileName);
    }
    return fullDir;
}