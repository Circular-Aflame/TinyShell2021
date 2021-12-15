#include"Declarations.h"
#include "global.h"

void doEcho(int argc, char * argv[]){
    if(strcmp(argv[1], "--help") == 0){
        cout << "this is placeholder text for echo --help" << endl;
        return;
    }
    if(strcmp(argv[1], "-n") == 0){
        strcat(gTerm.strout, argv[2]);
        for (int i = 3; i < argc; i++){
            strcat(gTerm.strout, " ");
            strcat(gTerm.strout, argv[i]);
        }
    }
    else{
        strcat(gTerm.strout, argv[1]);
        for (int i = 2; i < argc; i++){
            strcat(gTerm.strout, " ");
            strcat(gTerm.strout, argv[i]);
        }
        strcat(gTerm.strout, "\n");
    }
    return;
}