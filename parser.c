#include "scanner.c"
#include "parser.h"
#include "structures.c"

int bracket=0;
token *tok;

bool is_protocol(token *tok){
	switch (tok->type) {
		case TYPE_RIP:
			return true;
		case TYPE_RIPV2:
			return true;
		case TYPE_EIGRP:
			return true;
		case TYPE_OSPF:
			return true;
		default:
			return false;
	}
}

void banner_block(){
	tok=get_token();
	if(tok->type==TYPE_MOTD){
		//PUSH TRUE INTO MODE
		printf("MOTD\n");
	}
	else if(tok->type==TYPE_LOGIN){
		//PUSH FALSE INTO MODE
		printf("LOGIN\n");
	}
	else
		ERROR(ERR_SYN,"Error after banner mode");
	tok=get_token();
	if(tok->type==TYPE_WORD){
		printf("MESSAGE %s\n",tok->attribute);
		//PUSH MESSAGE INTO MESSAGE
	}
	else
		ERROR(ERR_SYN,"Error bad delimiter");
}

void main_body(){
	printf("MAIN BODY\n");
	token *tok=init_token();
	tok=get_token();
	while(tok->type!=TYPE_BLOCK_END){
		if(tok->type==END_OF_FILE){
			break;
		}
		else if(tok->type==TYPE_BANNER){
			printf("banner\n");
			banner_block();
			tok=get_token();
		}
		else if(tok->type==TYPE_INT){
			printf("interfaces\n");
		}
		else if(tok->type==TYPE_PASSWORD){
			printf("password\n");
		}
		else
		{
			if(is_protocol(tok)){
				printf("protokol\n");
			}
			else
				ERROR(ERR_SYN,"Error in main_body block");

		}
	}
	printf("KONIEC MAIN\n");
}

int main(int argc, char *argv[]){
	
	read_file(argc,argv);
	printf("START\n");
	tok=init_token();
	tok->type=UNDEFINED;
	while(tok->type!=END_OF_FILE){


		tok = get_token();
		if(tok->type==TYPE_WORD)
		{
			printf("Rname : %s\n",tok->attribute);
			//PUSH TO STRUCT
			tok=get_token();
			if(tok->type==TYPE_BLOCK_BEGIN){
				bracket++;
				main_body();
			}
			else
				ERROR(ERR_SYN,"Symbol { missing after R-name");		
		}
		else if (tok->type==END_OF_FILE){
			ERROR(ERR_OK,"END");
		}
		else
			ERROR(ERR_SYN,"No router name");
	}
	/*
	printf("token %d, %s\n",tok->type,tok->attribute);
	
	while(tok->type!=END_OF_FILE)
	{
		//printf("token %d, %s\n",tok->type,tok->attribute);
		tok = get_token();
	}
	*//*
	protocol_elementPTR node;
	node=init_protocol_elem();
	interface_elementPTR node2;
	node2=init_interface_elem();
	*/
	//print_protocols(node);
	/*
	printf("%s\n",config_first_part );
	printf("%s\n",config_second_part );
	printf("%s\n",config_third_part );
	printf("%s\n",config_fourth_part );*/
	close_file();
	ERROR(ERR_OK,"END");
}