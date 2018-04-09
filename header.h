#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <limits.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fnmatch.h>


#define SUCCESS 1
#define ERROR 0

#define MAX_STRING_SIZE 64
#define MAX_LINE_SIZE 512

#define COMMEND_NUMBER 3

typedef struct colInfo *colInfoPtr;
typedef struct colInfo{
	int type;
	char columnName[MAX_STRING_SIZE];
}colInfo;

typedef struct data *dataPtr;
typedef struct data{
	char value[MAX_STRING_SIZE];
	colInfoPtr attribute;
}data;

typedef struct dataRow *dataRowPtr;
typedef struct dataRow{
	dataPtr *dataList;
}dataRow;

typedef struct table *tablePtr;
typedef struct table{
	int colNumber;
	int rowNumber;
	char tableName[MAX_STRING_SIZE];
	colInfoPtr *colInfoList;
	dataRowPtr *dataRowList;
	int *activeDataRowList;
	tablePtr nextTable;
}table;

#include "find_col.c"
