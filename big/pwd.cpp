#include"Declarations.h"
#include "global.h"

void doPwd(int argc, char * argv[]){
    if(argc >= 2){
        if(strcmp(argv[1], "--help") == 0){
            strcpy(gTerm.strout, "Print the name of the current working directory.\n");
            return;
        }
    }
    strcpy(gTerm.strout, gTerm.wdir);
    strcat(gTerm.strout, "\n");
    return;
}
