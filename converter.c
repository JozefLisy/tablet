#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 33

void BinDec(char *buffer);

void main(){
	char buffer[BUFFER_SIZE];
	int num = 0, n_condition = 1, n_size = 0, i = 0;
	while(n_condition){
		printf("1 -> BIN-DEC\t2 -> BIN-HEX\t3 -> DEC-HEX\t4 -> HEX-DEC\t0 -> EXIT\nChoose an option: >"):
		fgets(buffer, BUFFER_SIZE, stdin);
		num = atoi(buffer);
		memset(buffer);

		switch num{
			case 1:
				BinDec(&buffer);
				break;
			case 2:
				
				break;
			case 3:
				
				break;
			case 4:
				
				break;
			case 0:
				n_condition = 0;
				printf("Exiting!\n");
				break;
			default:
				printf("Please, enter to valid value!\n");
				break;
		}
	}

	printf("bey!");
	return 0;
}

void BinDec(char *p_buffer, int *num, int *p_size, int *p_i){
	printf("Binary number >");
	fgets(p_buffer, BUFFER_SIZE, stdin);

	&num = atoi(p_buffer);
	int tester = 255;
	
	while(1){
		if(&num 
		
	}
}




