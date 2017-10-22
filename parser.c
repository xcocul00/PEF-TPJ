#include "scanner.c"


int main(int argc, char *argv[]){
	
	token *tok;
	read_file(argc,argv);
	printf("START\n");
		
	tok= init_token();

	tok = get_token();
	printf("token %d, \n",tok->type);
	ERROR(ERR_OK,"OK");
}