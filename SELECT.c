#ifndef HEAD
#define HEAD "header.h"
#include HEAD
#endif

#include "SELECT_FUNC.c"

void SELECT(tablePtr tableNew, char *arg){
	char *delin1 = ",";
	char *delin2 = " ";
	char *delin3 = "(";
	char *delin4 = ")";
	char *pch1;
	char *pch2;
	char *pch3;
	char *pch4;
	char *status1;
	char *status2;
	char *status3;
	char *status4;
	char str1[MAX_STRING_SIZE];
	char str2[MAX_STRING_SIZE];
	char str3[MAX_STRING_SIZE];
	char outputList[MAX_LINE_SIZE];
	int flag = 0;
	outputList[0] = '\0';

	//分解SELECT的參數
	pch1 = strtok_r(arg, delin1, &status1);
	while(pch1 != NULL){
		strcpy(str1, pch1);
		pch2 = strtok_r(str1, delin2, &status2);
		while(pch2 != NULL){
			strcpy(str2, pch2);
			pch3 = strtok_r(str2, delin3, &status3);
			//若為Aggregate functions 可直接拆掉之後誇號傳給負責的函式
			if(strcmp(pch3, "COUNT") == 0){
				pch3 = strtok_r(NULL, delin3, &status3);
				if(pch3 != NULL){
					strcpy(str3, pch3);
					pch4 = strtok_r(str3, delin4, &status4);
					COUNT(tableNew, pch4);
				}
			}
			else if(strcmp(pch3, "SUM") == 0){
				pch3 = strtok_r(NULL, delin3, &status3);
				if(pch3 != NULL){
					strcpy(str3, pch3);
					pch4 = strtok_r(str3, delin4, &status4);
					SUM(tableNew, pch4);
				}
			}
			else if(strcmp(pch3, "MAX") == 0){
				pch3 = strtok_r(NULL, delin3, &status3);
				if(pch3 != NULL){
					strcpy(str3, pch3);
					pch4 = strtok_r(str3, delin4, &status4);
					MAX(tableNew, pch4);
				}
			}
			else if(strcmp(pch3, "MIN") == 0){
				pch3 = strtok_r(NULL, delin3, &status3);
				if(pch3 != NULL){
					strcpy(str3, pch3);
					pch4 = strtok_r(str3, delin4, &status4);
					MIN(tableNew, pch4);
				}
			}
			else if(strcmp(pch3, "AVG") == 0){
				pch3 = strtok_r(NULL, delin3, &status3);
				if(pch3 != NULL){
					strcpy(str3, pch3);
					pch4 = strtok_r(str3, delin4, &status4);
					AVG(tableNew, pch4);
				}
			}
			//非 Aggregate functions 則先記錄下來
			else{
				flag = 1;
				strcat(outputList, " ");
				strcat(outputList, pch3);
			}
			pch2 = strtok_r(NULL, delin2, &status2);
		}
		pch1 = strtok_r(NULL, delin1, &status1);
	}
	if(flag == 1){
		//將記錄下來的非 Aggregate functions 交給 OUT
		OUT(tableNew, outputList);
	}
}
