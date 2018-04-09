#ifndef HEAD
#define HEAD "header.h"
#include HEAD
#endif

//依名稱尋找column編號
int find_col(tablePtr tableNew, char *arg){
	int i;
	for(i = 0; i < tableNew->colNumber; i++){
		if(strcmp(tableNew->colInfoList[i]->columnName, arg) == 0){
			return i;
		}
	}
	return -1;
}
