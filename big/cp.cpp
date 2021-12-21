#include"Declarations.h"
#include "global.h"

bool fileExists(char *fileName) //检测文件是否存在
{
    ifstream infile(fileName);
    return infile.good();
}

bool fileCopy(char *input, char *output){ //复制文件
    ifstream fin;
    ofstream fout;

    char line[MAXLINE];
    fin.open(input);
    if (!fin){
        cerr << "cp: " << input << ": No such file" << endl;
        fin.close();
        return false;
    }
    else{
        fout.open(output);
        if (!fout){
            cerr << "cp: " << output << ": Failed to open file" << endl;
            fin.close();
            fout.close();
            return false;
        }
        while (fin.getline(line, MAXLINE)){
            fout << line;
            if(!fin.eof()){
                fout << endl;
            }
        }
    }
    fin.close();
    fout.close();
    return true;
}

void doCp(int argc, char * argv[]){
    char * arrFile[MAXARG];
    bool doOverwrt = true;
    bool doInteract = false;
    bool doBackup = false;
    bool doVerbose = false;
    int filenum = 0;

    for (int i = 0; i < MAXARG; i++){
        arrFile[i] = new char[MAXLINE]; //initialize the 2D char array for storing file names
    }
    
    for(int i = 1; i < argc; i++){
        if (strcmp(argv[i], "--help") == 0){
            strcpy(gTerm.strout, "Usage: cp [OPTION]... SOURCE DEST\n\
Copy SOURCE to DEST, or multiple SOURCE(s) to DIRECTORY.\n\
\n\
  -b                           make a backup of existing destination file with backup suffix of '~'\n\
  -i, --interactive            prompt before overwrite (overrides a previous -n option)\n\
  -n, --no-clobber             do not overwrite an existing file (overrides a previous -i option)\n\
  -v, --verbose                explain what is being done\n\
      --help     display this help and exit");
            return;
        }
        
        else if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--interactive") == 0){
            doOverwrt = false;
            doInteract = false;
        }
        else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--no-clobber") == 0){
            doOverwrt = false;
            doInteract = true;
        }
        else if (strcmp(argv[i], "-b") == 0){
            doBackup = true;
        }
        else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 00){
            doVerbose = true;
        }
        else{
            strcpy(arrFile[filenum], argv[i]);
            filenum++;
        }
    }

    if (!doOverwrt){
        if (fileExists(fullFileDir(arrFile[1]))){
            if (doInteract){
                cout << "cp: Overwrite '" << arrFile[1] << "'? (y/n) ";
                char response[10];
                cin.getline(response, MAXLINE);
                if (strcmp(response, "y") != 0){
                    cerr << "cp: Command aborted" << endl;
                    return;
                }
            }
            else{
                cerr << "cp: File '" << arrFile[1] << "' already exists, command aborted" << endl;
                return;
            }
        }
    }

    if (doBackup){
        if (fileExists(fullFileDir(arrFile[1]))){
            char backupFile[MAXLINE];
            strcpy(backupFile, arrFile[1]);
            strcat(backupFile, "~");
            if (!fileCopy(fullFileDir(arrFile[1]), fullFileDir(backupFile))){
                cerr << "cp: Failed to create backup file for" << arrFile[1] << endl;
                return;
            }
        }
    }

    if (!fileCopy(fullFileDir(arrFile[0]), fullFileDir(arrFile[1]))){
        return;
    }

    if (doVerbose){
        strcat(gTerm.strout, "'");
        strcat(gTerm.strout, arrFile[0]);
        strcat(gTerm.strout, "' -> '");
        strcat(gTerm.strout, arrFile[1]);
        strcat(gTerm.strout, "'");
        strcat(gTerm.strout, "\n");
    }

    /*if (strcmp(arrFile[0], "-") == 0){ //input from standard input
        if (strcmp(arrFile[1], "-") == 0){ //output to standard output
            strcpy(gTerm.strout, gTerm.strin);
        }
        else{
            ofstream fout;
            fout.open(fullFileDir(arrFile[1]));
            if (!fout){
                cerr << "cp: " << arrFile[1] << ": No such file or directory" << endl;
                return;
            }
            fout << gTerm.strin;
            fout.close();
        }
    }
    else{
        if (strcmp(arrFile[1], "-") == 0){ //output to standard output
            ifstream fin(fullFileDir(arrFile[1]));
            if (!fin){
                cerr << "cp: " << arrFile[1] << ": No such file or directory" << endl;
                return;
            }
            else{
                char line[MAXLINE];
                while (fin.getline(line, MAXLINE)){
                    strcat(gTerm.strout, line);
                    strcat(gTerm.strout, "\n");
                }
            }
        }
        else{
            fileCopy(fullFileDir(arrFile[0]), fullFileDir(arrFile[1]), doOverwrt);
        }
    }*/

    return;
}