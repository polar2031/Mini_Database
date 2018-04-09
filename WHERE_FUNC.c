#ifndef HEAD
#define HEAD "header.h"
#include HEAD
#endif

//將算符轉為其代表的數字
int op2opCode(char *op){
	if(strcmp(op, "=") == 0){
		return 0;
	}
	else if(strcmp(op, "<") == 0){
		return 1;
	}
	else if(strcmp(op, "<=") == 0){
		return 2;
	}
	else if(strcmp(op, ">") == 0){
		return 3;
	}
	else if(strcmp(op, ">=") == 0){
		return 4;
	}
	else if(strcmp(op, "!=") == 0){
		return 5;
	}
	else{
		return -1;
	}
}

//比較INT型別
int compareI(int i1, int i2, int opCode){
	if(opCode == 0){
		return i1 == i2 ? 1 : 0;
	}
	else if(opCode == 1){
		return i1 < i2 ? 1 : 0;
	}
	else if(opCode == 2){
		return i1 <= i2 ? 1 : 0;
	}
	else if(opCode == 3){
		return i1 > i2 ? 1 : 0;
	}
	else if(opCode == 4){
		return i1 >= i2 ? 1 : 0;
	}
	else if(opCode == 5){
		return i1 == i2 ? 0 : 1;
	}
	return 1;
}

//比較FLOAT型別
int compareF(int f1, int f2, int opCode){
	if(opCode == 0){
		return f1 == f2 ? 1 : 0;
	}
	else if(opCode == 1){
		return f1 < f2 ? 1 : 0;
	}
	else if(opCode == 2){
		return f1 <= f2 ? 1 : 0;
	}
	else if(opCode == 3){
		return f1 > f2 ? 1 : 0;
	}
	else if(opCode == 4){
		return f1 >= f2 ? 1 : 0;
	}
	else if(opCode == 5){
		return f1 == f2 ? 0 : 1;
	}
	return 1;
}

//比較STRING型別
int compareS(char *s1, char *s2, int opCode){
	int r = strcmp(s1, s2);
	if(opCode == 0){
		return  r == 0? 1 : 0;
	}
	else if(opCode == 1){
		return r < 0 ? 1 : 0;
	}
	else if(opCode == 2){
		return r <= 0 ? 1 : 0;
	}
	else if(opCode == 3){
		return r > 0 ? 1 : 0;
	}
	else if(opCode == 4){
		return r >= 0 ? 1 : 0;
	}
	else if(opCode == 5){
		return r == 0 ? 0 : 1;
	}
	return 1;
}


void compare(tablePtr tableNew, int col1, int col2, char *arg, int opCode, int type){
	int i;
	int i1;
	int i2;
	int f1;
	int f2;
	char *s1;
	char *s2;
	//左邊參數為自行輸入
	if(col2 != -1){
		//INT
		if(type == 0){
			for(i = 0; i < tableNew->rowNumber; i++){
				if(tableNew->activeDataRowList[i] == 1){
					i1 = atoi(tableNew->dataRowList[i]->dataList[col1]->value);
					i2 = atoi(tableNew->dataRowList[i]->dataList[col2]->value);
					tableNew->activeDataRowList[i] = compareI(i1, i2, opCode);
				}
			}
		}
		//FLOAT
		else if(type == 1){
			for(i = 0; i < tableNew->rowNumber; i++){
				if(tableNew->activeDataRowList[i] == 1){
					f1 = atof(tableNew->dataRowList[i]->dataList[col1]->value);
					f2 = atof(tableNew->dataRowList[i]->dataList[col2]->value);
					tableNew->activeDataRowList[i] = compareF(f1, f2, opCode);
				}
			}
		}
		//STRING
		else if(type == 2){
			for(i = 0; i < tableNew->rowNumber; i++){
				if(tableNew->activeDataRowList[i] == 1){
					s1 = tableNew->dataRowList[i]->dataList[col1]->value;
					s2 = tableNew->dataRowList[i]->dataList[col2]->value;
					tableNew->activeDataRowList[i] = compareS(s1, s2, opCode);
				}
			}
		}
	}
	//左邊參數為column
	else{
		//INT
		if(type == 0){
			i2 = atoi(arg);
			for(i = 0; i < tableNew->rowNumber; i++){
				if(tableNew->activeDataRowList[i] == 1){
					i1 = atoi(tableNew->dataRowList[i]->dataList[col1]->value);
					tableNew->activeDataRowList[i] = compareI(i1, i2, opCode);
				}
			}
		}
		//FLOAT
		else if(type == 1){
			f2 = atof(arg);
			for(i = 0; i < tableNew->rowNumber; i++){
				if(tableNew->activeDataRowList[i] == 1){
					f1 = atof(tableNew->dataRowList[i]->dataList[col1]->value);
					tableNew->activeDataRowList[i] = compareF(f1, f2, opCode);
				}
			}
		}
		//STRING
		else if(type == 2){
			s2 = arg;
			for(i = 0; i < tableNew->rowNumber; i++){
				if(tableNew->activeDataRowList[i] == 1){
					s1 = tableNew->dataRowList[i]->dataList[col1]->value;
					tableNew->activeDataRowList[i] = compareS(s1, s2, opCode);
				}
			}
		}
	}
	return;
}


void sieve(tablePtr tableNew, char *leftStr, char *rightStr, char *op){
	char *delin1 = "\'";
	char *pch;
	int col1;
	int col2;
	int opCode;

	col1 = find_col(tableNew, leftStr);
	col2 = find_col(tableNew, rightStr);
	opCode = op2opCode(op);
	//左參數和右參數皆為column名稱
	if(col1 != -1 && col2 != -1){
		if(tableNew->colInfoList[col1]->type == tableNew->colInfoList[col2]->type){
			compare(tableNew, col1, col2, NULL, opCode, tableNew->colInfoList[col1]->type);
		}
	}
	//右參數為數字或字串
	else if(col1 != -1){
		//依據左參數型別決定如何處理右邊參數
		if(tableNew->colInfoList[col1]->type != 2){
			compare(tableNew, col1, col2, rightStr, opCode, tableNew->colInfoList[col1]->type);
		}
		else{
			pch = strtok(rightStr, delin1);
			compare(tableNew, col1, col2, pch, opCode, tableNew->colInfoList[col1]->type);
		}
	}
}


