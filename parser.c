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
		printf("BANNER MOTD\n");
	}
	else if(tok->type==TYPE_LOGIN){
		//PUSH FALSE INTO MODE
		printf("BANNER LOGIN\n");
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

void password_block(){
	tok=get_token();
	if(tok->type==TYPE_CON){
		printf("CON\n");
		//PUSH CON INTO TYPE
	}
	else if(tok->type==TYPE_AUX){
		printf("AUX\n");
		//PUSH AUX INTO TYPE
	}
	else if(tok->type==TYPE_VTY){
		int first,second,result;
		//PUSH VTY INTO TYPE
		tok=get_token();
		if(tok->type!=TYPE_NUMBER){
			ERROR(ERR_SYN,"Error in number vty consoles");
		}
		else
			first=atoi(tok->attribute);
		tok=get_token();
		if(tok->type!=TYPE_SUB)
			ERROR(ERR_SYN,"Error in number vty consoles");
		tok=get_token();
		if(tok->type!=TYPE_NUMBER){
			ERROR(ERR_SYN,"Error in number vty consoles");
		}
		else
			second=atoi(tok->attribute);
		result=second-first;
		if(result<=0 || second>=10){
			ERROR(ERR_SEM,"Error bad vty nums");
		}
		printf("VTY %d\n", result);
		//PUSH RESULT INTO NUM
	}
	else if(tok->type==TYPE_WORD){
		printf("JUST PASSWORD %s\n",tok->attribute);
		//PUSH PASSWD INTO PASSWORD
		return;
	}
	else
		ERROR(ERR_SYN,"Error in password block");
	tok=get_token();
	if(tok->type==TYPE_WORD){
		printf("PASSWORD %s\n",tok->attribute );
		//PUSH PASSWD INTO PASSWORD
	}
	else
		ERROR(ERR_SYN,"Error missing password");
}

void interface_block(){
	tok=get_token();
	if(tok->type!=TYPE_WORD){
		ERROR(ERR_SEM,"Error missing interface name");
	}
	else{
		//PUSH eth NAME INTO NAME
		printf("ETH : %s\n",tok->attribute );
		tok=get_token();
		if(tok->type==TYPE_LEFT_BRACKET){
			tok=get_token();
			while(tok->type!=TYPE_RIGHT_BRACKET && tok->type!=END_OF_FILE){
				int a=atoi("cd");
				printf("%d\n",a);
				tok=get_token();
				printf("%d a %s\n",tok->type, tok->attribute );
			}
		}
		else
			ERROR(ERR_SYN,"Error missing symbol (");
	}

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
			banner_block();
			tok=get_token();
		}
		else if(tok->type==TYPE_INT){
			printf("interfaces\n");
			interface_block();
		}
		else if(tok->type==TYPE_PASSWORD){
			password_block();
			tok=get_token();
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