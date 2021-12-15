#include"Declarations.h"
#include "global.h"

void doTee(int argc, char * argv[]){
    bool doOverwrt = true;
    char * arrFile[MAXARG];
    int filenum = 0;
    for (int i = 0; i < MAXARG; i++){
        arrFile[i] = new char[MAXLINE]; //初始化存储文件名的字符串数组
    }

    for (int i = 1; i < argc; i++){
        if (strcmp(argv[1], "--help") == 0) {
        strcpy(gTerm.strout, "Usage: tee [OPTION]... [FILE]...\n\
Copy standard input to each FILE, and also to standard output.\n\
\n\
  -a, --append              append to the given FILEs, do not overwrite\n\
      --help     display this help and exit");
        return;
        }
        else if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--append") == 0) {
            doOverwrt = false;
        }
        else{
            strcpy(arrFile[filenum], argv[i]);
            filenum ++; //存储文件名和文件数量
        }
    }

    strcpy(gTerm.strout, gTerm.strin);

    if(gTerm.strin[strlen(gTerm.strin) - 1] == '\n'){
        gTerm.strin[strlen(gTerm.strin) - 1] = '\0';
    }

    for (int i = 0; i < filenum; i++){
        ofstream fout;
        if (doOverwrt){
            fout.open(fullFileDir(arrFile[i]));
        }
        else{
            fout.open(fullFileDir(arrFile[i]), ios_base::app);
        }
        if (!fout){
            cerr << "tee: '" << arrFile[i] << "': No such file or directory" << endl;
            continue;
        }
        fout << gTerm.strin;
        fout.close();
    }
    return;
}