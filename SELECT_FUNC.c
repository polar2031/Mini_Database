#ifndef HEAD
#define HEAD "header.h"
#include HEAD
#endif

//計算資料筆數
void COUNT(tablePtr tableNew, char *arg){
	int i;
	int count = 0;
	if(strcmp(arg, "*") == 0){
		for(i = 0; i < tableNew->rowNumber; i++){
			if(tableNew->activeDataRowList[i] == 1){
				count++;
			}
		}
	}
	printf("COUNT = %d\n", count);
	return;
}

//計算最大值
void MAX(tablePtr tableNew, char *arg){
	int option;
	int col = find_col(tableNew, arg);
	int intMax;
	int intTemp;
	float floatMax;
	float floatTemp;
	int flag = 0;
	int i;
	int j;

	if(col >= 0){
		if(tableNew->colInfoList[col]->type == 0){
			for(i = 0; i < tableNew->rowNumber; i++){
				if(tableNew->activeDataRowList[i] == 1){
					intTemp = atoi(tableNew->dataRowList[i]->dataList[col]->value);
					if(flag){
						intMax = intMax > intTemp ? intMax : intTemp;
					}
					else{
						intMax = intTemp;
						flag = 1;
					}
				}
			}
			printf("MAX %s: %d\n", arg, intMax);
		}
		else if(tableNew->colInfoList[col]->type == 1){
			for(i = 0; i < tableNew->rowNumber; i++){
				if(tableNew->activeDataRowList[i] == 1){
					floatTemp = atof(tableNew->dataRowList[i]->dataList[col]->value);
					if(flag){
						floatMax = floatMax > floatTemp ? floatMax : floatTemp;
					}
					else{
						floatMax = floatTemp;
						flag = 1;
					}
				}
			}
			printf("MAX %s: %f\n", arg, floatMax);
		}
	}
}

//計算最小值
void MIN(tablePtr tableNew, char *arg){
	int option;
	int col = find_col(tableNew, arg);
	int intMin;
	int intTemp;
	float floatMin;
	float floatTemp;
	int flag = 0;
	int i;
	int j;

	if(col >= 0){
		if(tableNew->colInfoList[col]->type == 0){
			for(i = 0; i < tableNew->rowNumber; i++){
				if(tableNew->activeDataRowList[i] == 1){
					intTemp = atoi(tableNew->dataRowList[i]->dataList[col]->value);
					if(flag){
						intMin = intMin < intTemp ? intMin : intTemp;
					}
					else{
						intMin = intTemp;
						flag = 1;
					}
				}
			}
			printf("MIN %s: %d\n", arg, intMin);
		}
		else if(tableNew->colInfoList[col]->type == 1){
			for(i = 0; i < tableNew->rowNumber; i++){
				if(tableNew->activeDataRowList[i] == 1){
					floatTemp = atof(tableNew->dataRowList[i]->dataList[col]->value);
					if(flag){
						floatMin = floatMin > floatTemp ? floatMin : floatTemp;
					}
					else{
						floatMin = floatTemp;
						flag = 1;
					}
				}
			}
			printf("MIN %s: %f\n", arg, floatMin);
		}
	}
}

//計算總和
void SUM(tablePtr tableNew, char *arg){
	int option;
	int col = find_col(tableNew, arg);
	int intTemp;
	int intSum = 0;
	float floatTemp;
	float floatSum = 0.0;
	int i;

	if(col >= 0){
		if(tableNew->colInfoList[col]->type == 0){
			for(i = 0; i < tableNew->rowNumber; i++){
				if(tableNew->activeDataRowList[i] == 1){
					intTemp = atoi(tableNew->dataRowList[i]->dataList[col]->value);
					intSum += intTemp;
				}
			}
			printf("SUM %s: %d\n", arg, intSum);
		}
		else if(tableNew->colInfoList[col]->type == 1){
			for(i = 0; i < tableNew->rowNumber; i++){
				if(tableNew->activeDataRowList[i] == 1){
					floatTemp = atof(tableNew->dataRowList[i]->dataList[col]->value);
					floatSum += floatTemp;
				}
			}
			printf("SUM %s: %f\n", arg, floatSum);
		}
	}
}

//計算平均
void AVG(tablePtr tableNew, char *arg){
	int option;
	int col = find_col(tableNew, arg);
	int intTemp;
	int intSum = 0;
	float floatTemp;
	float floatSum = 0.0;
	int count = 0;
	int i;

	if(col >= 0){
		if(tableNew->colInfoList[col]->type == 0){
			for(i = 0; i < tableNew->rowNumber; i++){
				if(tableNew->activeDataRowList[i] == 1){
					intTemp = atoi(tableNew->dataRowList[i]->dataList[col]->value);
					intSum += intTemp;
					count++;
				}
			}
			printf("AVG %s: %f\n", arg, (float)intSum / (float)count);
		}
		else if(tableNew->colInfoList[col]->type == 1){
			for(i = 0; i < tableNew->rowNumber; i++){
				if(tableNew->activeDataRowList[i] == 1){
					floatTemp = atof(tableNew->dataRowList[i]->dataList[col]->value);
					floatSum += floatTemp;
					count++;
				}
			}
			printf("AVG %s: %f\n", arg, (float)floatSum / (float)count);
		}
	}
}

//輸出
void OUT(tablePtr tableNew, char *arg){
	char str[MAX_LINE_SIZE];
	char *delin = " ";
	char *pch;
	char *status;
	int count = 0;
	int *colList;
	int i;
	int j;
	int col;

	strcpy(str, arg);
	pch = strtok_r(str, delin, &status);
	//傳進來為*則輸出整個table
	if(strcmp(pch, "*") == 0){
		for(i = 0; i < tableNew->colNumber; i++){
			printf("%s\t", tableNew->colInfoList[i]->columnName);
			printf("%d\t", tableNew->colInfoList[i]->type);
		}
		printf("\n");
		for(i = 0; i < tableNew->rowNumber; i++){
			if(tableNew->activeDataRowList[i] == 1){
				for(j = 0; j < tableNew->colNumber; j++){
					printf("%s\t", tableNew->dataRowList[i]->dataList[j]->value);
				}
				printf("\n");
			}
		}
		return;
	}

	//計算最多可能的輸出欄位
	strcpy(str, arg);
	pch = strtok_r(str, delin, &status);
	while(pch != NULL){
		count++;
		pch = strtok_r(NULL, delin, &status);
	}
	
	//用於紀錄找到的欄位編號
	colList = (int *)malloc(sizeof(int) * count);

	strcpy(str, arg);
	pch = strtok_r(str, delin, &status);
	i = 0;
	while(pch != NULL){
		//依名稱尋找col編號
		col = find_col(tableNew, pch);
		//輸出column名稱
		if(col != -1){
			//紀錄下來
			colList[i] = col;
			i++;
			printf("%s\t", tableNew->colInfoList[col]->columnName);
		}
		pch = strtok_r(NULL, delin, &status);
	}
	printf("\n");
	//輸出指定column的資料
	for(i = 0; i < tableNew->rowNumber; i++){
		if(tableNew->activeDataRowList[i] == 1){
			for(j = 0; j < count; j++){
				printf("%s\t", tableNew->dataRowList[i]->dataList[colList[j]]->value);
			}
			printf("\n");
		}
	}
	return;
}

