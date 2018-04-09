#ifndef HEAD
#define HEAD "header.h"
#include HEAD
#endif

tablePtr read_dbms_file()
{
	DIR *dir;
	struct dirent *entry;
	char dirStr[] = "data";
	char fileName[MAX_STRING_SIZE];
	FILE *fp;
	char ch;

	//檢查directory
	if(!(dir = opendir(dirStr))){
		printf("Directory not found.\n");
		return NULL;
	}
	if(!(entry = readdir(dir))){
		printf("Directory error.\n");
		return NULL;
	}

	tablePtr tableEntry = NULL;
	tablePtr tableTemp = NULL;
	
	do{
		//entry不為目錄
		if(entry->d_type != DT_DIR){
			//串接目錄與檔名
			strcpy(fileName, dirStr);
			strcat(fileName, "/");
			strcat(fileName, entry->d_name);
			fp = fopen(fileName, "r");
			//printf("%s\n", fileName);

			//檢查檔案
			if(fp == NULL){
				printf("Failed to read %s.\n", fileName);
			}
			else{
				//分配空間給新的table
				if(tableEntry == NULL){
					tableEntry = (tablePtr)malloc(sizeof(table));
					tableTemp = tableEntry;
				}
				else{
					tableTemp->nextTable = (tablePtr)malloc(sizeof(table));
					tableTemp = tableTemp->nextTable;
				}

				char nameTemp[MAX_STRING_SIZE];
				char *exten = ".";
				char *pch = NULL;
				
				//分離副檔名
				strcpy(nameTemp, entry->d_name);
				pch = strtok(nameTemp, exten);
				//複製table名字
				strcpy(tableTemp->tableName, pch);
				//printf("%s\n", tableTemp->tableName);

				
				//讀取column
				char tempLine[MAX_LINE_SIZE];
				char tempSplit[MAX_LINE_SIZE];
				char tempStr[MAX_STRING_SIZE];
				int colNumber = 0;
				int nowCol;
				char *delim = "\t";
				
				//讀取第一行(column數量及名稱)
				fgets(tempLine, MAX_LINE_SIZE, fp);
				if(tempLine[strlen(tempLine)-1] == '\n')
					tempLine[strlen(tempLine) - 2] = '\0';
				strcpy(tempSplit, tempLine);
				
				//以tab分割
				pch = strtok(tempSplit, delim);
				
				//計算column數量
				while(pch != NULL){
					//printf("%s\n",pch);
					pch = strtok(NULL, delim);
					colNumber++;
				}
				tableTemp->colNumber = colNumber;
				//printf("colNumber: %d\n", colNumber);
				
				//分配空間給colInfoList
				colInfoPtr *colInfoList = (colInfoPtr *)malloc(sizeof(colInfoPtr) * colNumber);
				nowCol = 0;

				//重新以tab分割
				pch = strtok(tempLine, delim);
				while(pch != NULL){
					//printf("%s1\n", pch);
					colInfoList[nowCol] = (colInfoPtr)malloc(sizeof(colInfo));
					strcpy(colInfoList[nowCol]->columnName, pch);
					//printf("%s\n", colInfoList[nowCol]->columnName);
					pch = strtok(NULL, delim);
					nowCol++;
				}

				//讀取第二行(column型別)
				fgets(tempLine, MAX_LINE_SIZE, fp);
				//printf("%s22",tempLine);
				if(tempLine[strlen(tempLine)-1] == '\n')
					tempLine[strlen(tempLine)-2] = '\0';
				nowCol = 0;
				//以tab分割
				pch = strtok(tempLine, delim);
				while(pch != NULL){
					if(strcmp(pch, "INT") == 0){
						colInfoList[nowCol]->type = 0;
					}
					else if(strcmp(pch, "FLOAT") == 0){
						colInfoList[nowCol]->type = 1;
					}
					else if(strcmp(pch, "STRING") == 0){
						colInfoList[nowCol]->type = 2;
					}
					else{
						colInfoList[nowCol]->type = -1;
					}
					nowCol++;
					pch = strtok(NULL, delim);
				}

				int rowNumber = 0;
				int nowRow;
				//計算資料行數
				while(fgets(tempLine, MAX_LINE_SIZE, fp)){
					rowNumber++;
				}
				//printf("%d\n", rowNumber);
				tableTemp->rowNumber = rowNumber;

				//分配空間給dataRowList
				dataRowPtr *dataRowList = (dataRowPtr *)malloc(sizeof(dataRowPtr) * rowNumber);

				//重新讀檔
				rewind(fp);
				//略過第一第二行
				fgets(tempLine, MAX_LINE_SIZE, fp);
				fgets(tempLine, MAX_LINE_SIZE, fp);
				
				nowCol = 0;
				nowRow = 0;
				//讀取一行
				while(fgets(tempLine, MAX_LINE_SIZE, fp)){
					if(tempLine[strlen(tempLine)-1] == '\n')
						tempLine[strlen(tempLine)-2] = '\0';
					//分配空間給datarow
					dataRowPtr dataRowTemp = (dataRowPtr)malloc(sizeof(dataRow));
					//分配空間給datarow->datalist
					dataPtr *dataList = (dataPtr *)malloc(sizeof(dataPtr) * colNumber);

					pch = strtok(tempLine, delim);
					while(pch != NULL){
						//分配空間給data
						dataPtr dataTemp = (dataPtr)malloc(sizeof(data));
						//複製資料至data
						strcpy(dataTemp->value, pch);
						//printf("%s\n", dataTemp->value);
						//指定data的屬性至colInfo
						dataTemp->attribute = colInfoList[nowCol];
						//將data加入dataRow
						dataList[nowCol] = dataTemp;
						nowCol++;
						pch = strtok(NULL, delim);
					}
					dataRowTemp->dataList = dataList;
					dataRowList[nowRow] = dataRowTemp;
					nowRow++;
					nowCol = 0;
				}
				
				tableTemp->colInfoList = colInfoList;
				tableTemp->dataRowList = dataRowList;
				tableTemp->activeDataRowList = NULL;
				tableTemp->nextTable = NULL;
			}
			fclose(fp);
		}
	}while(entry = readdir(dir));

	return tableEntry;
}
