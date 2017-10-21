#include "scanner.c"


int main(int argc, char *argv[]){
	printf("START\n");
	token *tok;
	tok= init_token();
	tok = get_token();
	printf("%d\n",tok->type );
	printf("END\n");
	return 0;
}