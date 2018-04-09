#ifndef HEAD
#define HEAD "header.h"
#include HEAD
#endif

//依名稱尋找table
tablePtr findTable(tablePtr tableEntry, char *tableName)
{
	while(tableEntry != NULL){
		if(strcmp(tableEntry->tableName, tableName) == 0){
			return tableEntry;
		}
		else{
			tableEntry = tableEntry->nextTable;
		}
	}
	return NULL;
}
