#ifndef HEAD
#define HEAD "header.h"
#include HEAD
#endif

tablePtr JOIN(tablePtr table1, tablePtr table2)
{
	tablePtr tableNew;
	int colNum1;
	int colNum2;
	int rowNum1;
	int rowNum2;
	int row1;
	int row2;
	int i;
	int j;


	tableNew = (tablePtr)malloc(sizeof(table));
	//table2為NULL表示複製table1即可
	if(table2 == NULL){
		tableNew->nextTable = NULL;
		tableNew->tableName[0] = '\0';
		tableNew->colNumber = table1->colNumber;
		tableNew->rowNumber = table1->rowNumber;
		tableNew->dataRowList = (dataRowPtr *)malloc(sizeof(dataRowPtr) * tableNew->rowNumber);
		for(i = 0; i < tableNew->rowNumber; i++){
			tableNew->dataRowList[i] = (dataRowPtr)malloc(sizeof(dataRow));
			tableNew->dataRowList[i]->dataList = (dataPtr *)malloc(sizeof(dataPtr) * tableNew->colNumber);
			for(j = 0; j < tableNew->colNumber; j++){
				tableNew->dataRowList[i]->dataList[j] = table1->dataRowList[i]->dataList[j];
			}
		}
		tableNew->colInfoList = (colInfoPtr *)malloc(sizeof(colInfoPtr) * tableNew->colNumber);
		for(i = 0; i < tableNew->colNumber; i++){
			tableNew->colInfoList[i] = table1->colInfoList[i];
		}
		tableNew->activeDataRowList = (int *)malloc(sizeof(int) * tableNew->rowNumber);
		for(i = 0; i < tableNew->rowNumber; i++){
			tableNew->activeDataRowList[i] = 1;
		}
		
	}
	//join table1 & table2
	else{
		tableNew->nextTable = NULL;
		tableNew->tableName[0] = '\0';
		tableNew->colNumber = table1->colNumber + table2->colNumber;
		tableNew->rowNumber = table1->rowNumber * table2->rowNumber;
		tableNew->dataRowList = (dataRowPtr *)malloc(sizeof(dataRowPtr) * tableNew->rowNumber);
		for(i = 0; i < tableNew->rowNumber; i++){
			tableNew->dataRowList[i] = (dataRowPtr)malloc(sizeof(dataRow));
			tableNew->dataRowList[i]->dataList = (dataPtr *)malloc(sizeof(dataPtr) * tableNew->colNumber);
			row1 = i / table2->rowNumber;
			row2 = i % table2->rowNumber;
			for(j = 0; j < table1->colNumber; j++){
				tableNew->dataRowList[i]->dataList[j] = table1->dataRowList[row1]->dataList[j];
			}
			for(j = 0; j < table2->colNumber; j++){
				tableNew->dataRowList[i]->dataList[j + table1->colNumber] = table2->dataRowList[row2]->dataList[j];
			}
		}
		tableNew->colInfoList = (colInfoPtr *)malloc(sizeof(colInfoPtr) * tableNew->colNumber);
		for(i = 0; i < table1->colNumber; i++){
			tableNew->colInfoList[i] = table1->colInfoList[i];
		}
		for(i = 0; i < table2->colNumber; i++){
			tableNew->colInfoList[i + table1->colNumber] = table2->colInfoList[i];
		}
		tableNew->activeDataRowList = (int *)malloc(sizeof(int) * tableNew->rowNumber);
		for(i = 0; i < tableNew->rowNumber; i++){
			tableNew->activeDataRowList[i] = 1;
		}
	}	
	return tableNew;
}
