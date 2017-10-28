#include "scanner.c"


int main(int argc, char *argv[]){
	
	read_file(argc,argv);
	token *tok;
	
	printf("START TESTU\n");
		
	tok= init_token();
	tok = get_token();
	
	while(tok->type!=END_OF_FILE)
	{
		printf("token %d, %s\n",tok->type,tok->attribute);
		tok = get_token();
	}

	close_file();
	ERROR(ERR_OK," ");
}