#include "scanner.c"


int main(int argc, char *argv[]){
	
	read_file(argc,argv);
	token *tok;
	
	printf("START\n");
		
	tok= init_token();

	tok = get_token();
	printf("token %d, \n",tok->type);
	close_file();
	ERROR(ERR_OK,"OK");
}