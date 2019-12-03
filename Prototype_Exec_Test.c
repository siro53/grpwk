//
// Created by udemegane on 2019/12/02.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Udemegane_Prototype.h"
#include "PB.h"
#include "Udemegane_Debug.h"



void FuncA(void){
    ConstructDLL("RororinaFlyxell",0);
    ConstructDLL("TotooriaHelmold",1);
    ConstructDLL("MerurulinceRedeArls",2);
    ConstructDLL("ElmeruliaFlyxell",3);

    DebugPrint_All();
    ConstructSMatrix(4);
    DebugPrint_ShowSMatrix(4);
}

void FuncB(void){
    char T[] = "abcdabxxxxxcxcdxxxaabacddcxxxadcb";
    ImportT(T);

    DebugPrint_ShowBGTable(T);
}

void FuncC(void){
    char T[] = "abcdabxxxxxcxcdxxxaabacddcxxxadcb";
    ImportT(T);

    ConstructDLL("abcdab",0);
    ConstructDLL("bab",1);
    ConstructDLL("bbcdcdab",2);
    ConstructDLL("baab",3);
    ConstructDLL("a",4);
    ConstructDLL("cddcabcadcb",5);
    ConstructSMatrix(5);

    DebugPrint_ShowBGTable(T);
    DebugPrint_ShowSMatrix(5);


    IndexSearch(5);

}

int main(void) {

    int n = 2;


    switch(n){
        case 0:
            FuncA();
            break;

        case 1:
            FuncB();
            break;

        case 2:
            FuncC();
            break;

        default:
            FuncA();

    }

    Endfunc();
    return (0);
}
