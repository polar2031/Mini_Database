#ifndef HEAD
#define HEAD "header.h"
#include HEAD
#endif

#include "FROM.c"
#include "WHERE.c"
#include "SELECT.c"

//將指令做初步的分割
int split_request(tablePtr tableEntry, char *inputLine){
	char *delin = " ";
	char tempLine[MAX_LINE_SIZE];
	char *pch;
	
	int selectStart = -1;
	int selectEnd = -1;;
	int fromStart = -1;
	int whereStart = -1;

	char selectArg[MAX_LINE_SIZE] = " ";
	char fromArg[MAX_LINE_SIZE] = " ";
	char whereArg[MAX_LINE_SIZE] = " ";

	strcpy(tempLine, inputLine);
	pch = strtok(tempLine, delin);
	//確定指令為SELECT
	if(pch != NULL){
		if(strcmp(pch, "SELECT") == 0){
			selectStart = pch - tempLine;
		}
		else{
			return ERROR;
		}
	}

	//分別找出FROM及WHERE
	//同時將屬於SELECT、FROM或WHERE的參數分別暫存在selectArg、fromArg、whereArg
	pch = strtok(NULL, delin);
	while(pch != NULL){
		//先遇到FROM
		if(strcmp(pch, "FROM") == 0){
			fromStart = pch - tempLine;
			pch = strtok(NULL, delin);
			while(pch != NULL){
				//遇到WHERE
				if(strcmp(pch, "WHERE") == 0){
					whereStart = pch - tempLine;
					pch = strtok(NULL, delin);
					//儲存WHERE的參數
					while(pch != NULL){
						strcat(whereArg, pch);
						strcat(whereArg, " ");
						pch = strtok(NULL, delin);
					}
					break;
				}
				//儲存FROM的參數
				else{
					strcat(fromArg, pch);
					strcat(fromArg, " ");
				}
				pch = strtok(NULL, delin);
			}
			break;
		}
		//先遇上WHERE
		else if(strcmp(pch, "WHERE") == 0){
			whereStart = pch - tempLine;
			pch = strtok(NULL, delin);
			//儲存WHERE的參數
			while(pch != NULL){
				strcat(whereArg, pch);
				strcat(whereArg, " ");
				pch = strtok(NULL, delin);
			}
			break;
		}
		//儲存SELECT的參數
		else{
			strcat(selectArg, pch);
			strcat(selectArg, " ");
		}
		pch = strtok(NULL, delin);
	}

	//printf("SELECT: %s\n", selectArg);
	//printf("FROM: %s\n", fromArg);
	//printf("WHERE: %s\n", whereArg);


	tablePtr tableNew;
	//FROM將指定的table join成新的table
	if(fromStart != -1){
		//FROM
		tableNew = FROM(tableEntry, fromArg);
	}
	else{
		//沒有FROM指令則視為FROM *
		tableNew = FROM(tableEntry, "*");
	}
	//WHERE篩選新的table
	if(whereStart != -1){
		WHERE(tableNew, whereArg);
	}
	//SELECT從篩選後的table選取需要的資料
	SELECT(tableNew, selectArg);
	return SUCCESS;
}
