#include"Declarations.h"
#include "global.h"

void doPwd(int argc, char * argv[]){
    if(strcmp(argv[1], "--help") == 0){
        strcpy(gTerm.strout, "Print the name of the current working directory.");
        return;
    }
    strcpy(gTerm.strout, gTerm.wdir);
    strcat(gTerm.strout, "\n");
    return;
}