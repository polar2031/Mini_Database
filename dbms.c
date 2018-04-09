#ifndef HEAD
#define HEAD 
#include "header.h"
#endif

#include "read_dbms_file.c"
#include "split_request.c"

int main(int argc, char *argv[])
{
	char inputLine[MAX_LINE_SIZE];
	char ch;
	int count;
	
	//讀取檔案	
	printf("Starting data base...\n");
	tablePtr tableEntry;
	tableEntry = read_dbms_file();
	//讀檔失敗
	if(tableEntry == NULL){
		printf("Failed to initial.\n");
		return 0;
	}

	//開始接收指令
	while(1){
		printf(">>");
		count = 0;
		while((ch = getchar()) != '\n'){
			if((count + 1) < MAX_LINE_SIZE){
				inputLine[count++] = ch;
			}
		}
		inputLine[count] = '\0';
		//收到exit便跳出
		if(strcmp(inputLine, "exit") == 0){
			break;
		}
		//將指令傳給split做處理
		if(split_request(tableEntry, inputLine) == ERROR){
			printf("\"%s\" is not an illegal request.\n", inputLine);
		}
	}

	return 0;
}
