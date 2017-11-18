#include "scanner.c"
#include "parser.h"
#include "structures.c"


int main(int argc, char *argv[]){
	
	read_file(argc,argv);
	token *tok;
	
	printf("START\n");
		
	tok= init_token();
	tok = get_token();
	printf("token %d, %s\n",tok->type,tok->attribute);
	
	while(tok->type!=END_OF_FILE)
	{
		//printf("token %d, %s\n",tok->type,tok->attribute);
		tok = get_token();
	}
	protocol_elementPTR node;
	node=init_protocol_elem();
	interface_elementPTR node2;
	node2=init_interface_elem();
	print_protocol(node);
	print_interfaces(node2);


	//print_protocols(node);
	/*
	printf("%s\n",config_first_part );
	printf("%s\n",config_second_part );
	printf("%s\n",config_third_part );
	printf("%s\n",config_fourth_part );*/
	close_file();
	ERROR(ERR_OK,"END");
}