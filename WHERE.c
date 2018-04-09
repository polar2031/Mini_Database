#ifndef HEAD
#define HEAD "header.h"
#include HEAD
#endif

#include "WHERE_FUNC.c"

void WHERE(tablePtr tableNew, char* arg){
	char *delin1 = " ";
	char *pch1;
	char *status1;
	int flag = 0;
	char op[MAX_STRING_SIZE];
	char leftStr[MAX_STRING_SIZE];
	char rightStr[MAX_STRING_SIZE];

	pch1 = strtok_r(arg, delin1, &status1);
	//將傳進的參數分解
	while(pch1 != NULL){
		//左邊參數
		strcpy(leftStr, pch1);
		pch1 = strtok_r(NULL, delin1, &status1);
		if(pch1 != NULL){
			//算符
			strcpy(op, pch1);
		}
		pch1 = strtok_r(NULL, delin1, &status1);
		if(pch1 != NULL){
			//右邊參數
			strcpy(rightStr, pch1);
		}
		//篩選
		sieve(tableNew, leftStr, rightStr, op);
		pch1 = strtok_r(NULL, delin1, &status1);
		if(pch1 != NULL){
			if(strcmp(pch1, "AND") != 0){
				break;
			}
		}
		else{
			break;
		}
		pch1 = strtok_r(NULL, delin1, &status1);
	}
	return;
}
