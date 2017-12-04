#include "scanner.c"
#include "parser.h"
#include "structures.c"

token *tok;
//

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

void banner_block(router_elementPTR *router){
	//printf("%d\n", router->password_type);
	tok=get_token();
	if(tok->type==TYPE_MOTD){
		//PUSH TRUE INTO MODE
		//printf("BANNER MOTD\n");
	}
	else if(tok->type==TYPE_LOGIN){
		//PUSH FALSE INTO MODE
		//printf("BANNER LOGIN\n");
	}
	else
		ERROR(ERR_SYN,"Error after banner mode");
	tok=get_token();
	if(tok->type==TYPE_WORD){
		//printf("MESSAGE %s\n",tok->attribute);
		//PUSH MESSAGE INTO MESSAGE
	}
	else
		ERROR(ERR_SYN,"Error bad delimiter");
}

void password_block(){
	tok=get_token();
	if(tok->type==TYPE_CON){
		//printf("CON\n");
		//PUSH CON INTO TYPE
	}
	else if(tok->type==TYPE_AUX){
		//printf("AUX\n");
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
		//printf("VTY %d\n", result);
		//PUSH RESULT INTO NUM
	}
	else if(tok->type==TYPE_WORD){
		//printf("JUST PASSWORD %s\n",tok->attribute);
		//PUSH PASSWD INTO PASSWORD
		return;
	}
	else
		ERROR(ERR_SYN,"Error in password block");
	tok=get_token();
	if(tok->type==TYPE_WORD){
		//printf("PASSWORD %s\n",tok->attribute );
		//PUSH PASSWD INTO PASSWORD
	}
	else
		ERROR(ERR_SYN,"Error missing password");
}

char* check_ip(){
	char *string = (char *) malloc(sizeof(char) * 16);
	for(int i=0; i<=3; i++){
		int x = atoi(tok->attribute);
		if(x>=0 && x<=255){
			if(!i){
				strcpy(string,tok->attribute);
			}
			else
				strcat(string,tok->attribute);
		}
		else
			ERROR(ERR_SEM,"Error IP not from 0-255");
		if(i!=3){
			tok=get_token();
			if(tok->type!=TYPE_DOT){
				ERROR(ERR_SYN,"Error missing . symbol");
			}
			else
				strcat(string,".");
		}
		tok=get_token();
	}
	return string;
}

void interface_block(){
	bool ip=true;
	char address[15];
	tok=get_token();
	if(tok->type!=TYPE_WORD){
		ERROR(ERR_SEM,"Error missing interface name");
	}
	else{
		//PUSH eth NAME INTO NAME
		//printf("ETH : %s\n",tok->attribute );
		tok=get_token();
		if(tok->type==TYPE_LEFT_BRACKET){
			tok=get_token();
			while(tok->type!=TYPE_RIGHT_BRACKET && tok->type!=END_OF_FILE){
				if(tok->attribute==NULL){
					if(tok->type==TYPE_SHUTDOWN){
						// PUSH SHUTDOWN
						//printf("shutdown\n");
						tok=get_token();
					}
					else if(tok->type==TYPE_NO){
						//PUSH NO SHUTDOWN
						//printf("no shutdown\n");
						tok=get_token();
					}
					else
						ERROR(ERR_SYN,"Error in interface options");
				}
				else
				{
					if(atoi(tok->attribute)!=0){
						strcpy(address,check_ip());
					}
					else if (atoi(tok->attribute)==0 && !strcmp(tok->attribute,"0")){
						strcpy(address,check_ip());
					}
					else
						ERROR(ERR_SYN,"Error in interface options");
					if(ip){
						//printf("IP ADDR: %s\n", address);
					}
					else
						//printf("MASK ADDR: %s\n", address);
					ip=false;
				}
			}
		}
		else
			ERROR(ERR_SYN,"Error missing symbol (");
	}
}
char * protokol_type(int type){
	switch (type){
		case TYPE_RIP:
			return "RIP";
		case TYPE_RIPV2:
			return "RIPv2";
		case TYPE_EIGRP:
			return "EIGRP";
		case TYPE_OSPF:
			return "OSPF";
		default:
			return "ERR";
	}
}

void protokol_block(int x){
	char protokol_name[5];
	char address[150];
	bool flag = false;
	strcpy(protokol_name,protokol_type(x));
	//printf("PROTOKOL %s \n",protokol_name);
	//PUSH INTO PROTOKOL
	if(x==TYPE_EIGRP || x==TYPE_OSPF){
		tok=get_token();
		if(tok->attribute==NULL){
			ERROR(ERR_SYN,"Error missing area");
		}
		else{
			if(atoi(tok->attribute)!=0 || !strcmp(tok->attribute,"0")){
				//printf("AREA %s\n", tok->attribute);
			}
			else
				ERROR(ERR_SYN,"Error missing area");
		}
	}
	tok=get_token();
	if(tok->type==TYPE_LEFT_BRACKET){
		tok=get_token();
		while(tok->type!=TYPE_RIGHT_BRACKET && tok->type!=END_OF_FILE){
			if(tok->attribute==NULL){
				ERROR(ERR_SYN,"Error in protokol options");
			}
			else
			{
				if(atoi(tok->attribute)!=0){
					if(!flag)
						strcpy(address,check_ip());
					else{
						strcat(address,"\n");
						strcat(address,check_ip());
					}
				}
				else if (atoi(tok->attribute)==0 && !strcmp(tok->attribute,"0")){
					if(!flag)
						strcpy(address,check_ip());
					else{
						strcat(address,"\n");
						strcat(address,check_ip());
					}
				}
				else
					ERROR(ERR_SYN,"Error in protokol options");
				flag=true;
			}
		}
	}
	else
		ERROR(ERR_SYN,"Error missing symbol (");
	//printf("MASKS:\n%s\n", address);
}

void main_body(router_elementPTR *router){
	token *tok=init_token();
	tok=get_token();
	router->password_type=1;
	while(tok->type!=TYPE_BLOCK_END){
		if(tok->type==END_OF_FILE){
			break;
		}
		else if(tok->type==TYPE_BANNER){
			banner_block(router);
			tok=get_token();
		}
		else if(tok->type==TYPE_INT){
			//printf("interfaces %s\n",tok->attribute);
			//PUSH INT NAME
			interface_block();
			tok=get_token();

		}
		else if(tok->type==TYPE_PASSWORD){
			password_block();
			tok=get_token();
		}
		else
		{
			if(is_protocol(tok)){
				protokol_block(tok->type);
				tok=get_token();
			}
			else
				ERROR(ERR_SYN,"Error in main_body block");

		}
	}
}

int main(int argc, char *argv[]){
	
	read_file(argc,argv);
	//printf("START\n");
	router_elementPTR router;
	init_router_elem(&router);
	
	tok=init_token();
	tok->type=UNDEFINED;
	while(tok->type!=END_OF_FILE){


		tok = get_token();
		if(tok->type==TYPE_WORD)
		{
			////printf("Rname : %s\n",tok->attribute);
			//PUSH TO STRUCT
			router.name=tok->attribute;
			tok=get_token();
			if(tok->type==TYPE_BLOCK_BEGIN){
				main_body(&router);
			}
			else
				ERROR(ERR_SYN,"Symbol { missing after R-name");		
		}
		else if (tok->type==END_OF_FILE){
			break;
		}
		else
			ERROR(ERR_SYN,"No router name");
	}

	
	/*
	//printf("token %d, %s\n",tok->type,tok->attribute);
	
	while(tok->type!=END_OF_FILE)
	{
		////printf("token %d, %s\n",tok->type,tok->attribute);
		tok = get_token();
	}
	*/
	//protocol_elementPTR node;
	//node=init_protocol_elem();
	//interface_elementPTR node2;
	//node2=init_interface_elem();
	
	//print_protocol(node);
	/*
	//printf("%s\n",config_first_part );
	//printf("%s\n",config_second_part );
	//printf("%s\n",config_third_part );
	//printf("%s\n",config_fourth_part );*/
	print_routers(&router);
	free(tok);
	//free(router);
	close_file();
	ERROR(ERR_OK,"END");
}