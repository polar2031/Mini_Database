#ifndef HEAD
#define HEAD "header.h"
#include HEAD
#endif

#include "findTable.c"
#include "JOIN.c"

tablePtr FROM(tablePtr tableEntry, char* arg)
{
	char *delin1 = " ";
	char *delin2 = ",";
	char *pch1;
	char *pch2;
	char *status1;
	char *status2;
	char str1[MAX_STRING_SIZE];
	tablePtr tableNew = NULL;
	tablePtr tableTemp = NULL;
	//傳入的參數為*join所有table
	if(strcmp(arg, "*") == 0){
		while(tableEntry != NULL){
			//第一個加入的table
			if(tableNew == NULL){
				tableNew = JOIN(tableEntry, NULL);
			}
			//JOIN新的table
			else{
				tableNew = JOIN(tableNew, tableEntry);
			}
			tableEntry = tableEntry->nextTable;
		}
		return tableNew;
	}

	//分解傳進的參數為table名稱
	pch1 = strtok_r(arg, delin1, &status1);
	while(pch1 != NULL){
		strcpy(str1, pch1);
		pch2 = strtok_r(str1, delin2, &status2);
		while(pch2 != NULL){
			//依名稱尋找table
			tableTemp = findTable(tableEntry, pch2);
			//找不到該名稱的table
			if(tableTemp == NULL){
				printf("Table: %s not found.\n", pch2);
				return NULL;
			}
			//第一個加入的table
			if(tableNew == NULL){
				tableNew = JOIN(tableTemp, NULL);
			}
			//JOIN新的table
			else{
				tableNew = JOIN(tableNew, tableTemp);
			}
			pch2 = strtok_r(NULL ,delin2, &status2);
		}
		pch1 = strtok_r(NULL, delin1, &status1);
	}
	return tableNew;
}
