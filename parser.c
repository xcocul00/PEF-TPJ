#include "scanner.c"
#include "parser.h"
#include "structures.c"
#include "text_creator.c"

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
	tok=get_token();
	if(tok->type==TYPE_MOTD){
		router->banner_mode=true;
	}
	else if(tok->type==TYPE_LOGIN){
		router->banner_mode=false;
	}
	else
		ERROR(ERR_SYN,"Error after banner mode");
	tok=get_token();
	if(tok->type==TYPE_WORD){
		router->banner_message=tok->attribute;
	}
	else
		ERROR(ERR_SYN,"Error bad delimiter");
}

void password_block(router_elementPTR *router){
	tok=get_token();
	if(tok->type==TYPE_CON){
		router->password_type=1;
	}
	else if(tok->type==TYPE_AUX){
		router->password_type=2;
	}
	else if(tok->type==TYPE_VTY){
		int first,second,result;
		router->password_type=3;
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
		router->vty_num=result;
	}
	else if(tok->type==TYPE_WORD){
		router->password=tok->attribute;
		return;
	}
	else
		ERROR(ERR_SYN,"Error in password block");
	tok=get_token();
	if(tok->type==TYPE_WORD){
		router->password=tok->attribute;
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

void interface_block(interface_elementPTR *interfaces){
	bool ip=true;
	char address[15];

	tok=get_token();
	if(tok->type!=TYPE_WORD){
		ERROR(ERR_SEM,"Error missing interface name");
	}
	else{
		interfaces->name=tok->attribute;
		tok=get_token();
		if(tok->type==TYPE_LEFT_BRACKET){
			tok=get_token();
			while(tok->type!=TYPE_RIGHT_BRACKET && tok->type!=END_OF_FILE){
				
				if(tok->attribute==NULL){
					if(tok->type==TYPE_SHUTDOWN){
						interfaces->state=false;
						tok=get_token();
					}
					else if(tok->type==TYPE_NO){
						interfaces->state=true;
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
						strcpy(interfaces->IP,address);

					}
					else{
						strcpy(interfaces->MASK,address);
					}
					ip=false;
				}
			}
		}
		else
			ERROR(ERR_SYN,"Error missing symbol (");
	}
}

void protokol_block(int x, protocol_elementPTR *protocols){
	char protokol_name[5];
	char address[150];
	bool flag = false;
	strcpy(protokol_name,protokol_type(x));
	//printf("protocols: %d\n",protocols->name);
	//printf("PROTOKOL %s \n",protokol_name);
	protocols->name=x;
	if(x==TYPE_EIGRP || x==TYPE_OSPF){
		tok=get_token();
		if(tok->attribute==NULL){
			ERROR(ERR_SYN,"Error missing area");
		}
		else{
			if(atoi(tok->attribute)!=0 || !strcmp(tok->attribute,"0")){
				//printf("AREA %s\n", tok->attribute);
				protocols->system=atoi(tok->attribute);
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
						strcat(address,"\n ");
						strcat(address,check_ip());
					}
				}
				else if (atoi(tok->attribute)==0 && !strcmp(tok->attribute,"0")){
					if(!flag)
						strcpy(address,check_ip());
					else{
						strcat(address,"\n ");
						strcat(address,check_ip());
					}
				}
				else
					ERROR(ERR_SYN,"Error in protokol options");
				flag=true;
			}
		}
		strcpy(protocols->networks, address);
		//printf("%s\n", address);
	}
	else
		ERROR(ERR_SYN,"Error missing symbol (");
}

void main_body(router_elementPTR *router){
	char *tmp=(char *) malloc(sizeof(char) * 100);
	char *tmp2=(char *) malloc(sizeof(char) * 100);
	strcpy(tmp,"!\n!\n");
	token *tok=init_token();
	tok=get_token();
	while(tok->type!=TYPE_BLOCK_END){
		if(tok->type==END_OF_FILE){
			break;
		}
		else if(tok->type==TYPE_BANNER){
			banner_block(router);
			tok=get_token();
		}
		else if(tok->type==TYPE_INT){
			interface_elementPTR interfaces;
			init_interface_elem(&interfaces);
			interface_block(&interfaces);
			strcat(tmp,get_interface_string(&interfaces));
			tok=get_token();

		}
		else if(tok->type==TYPE_PASSWORD){
			password_block(router);
			tok=get_token();
		}
		else
		{
			if(is_protocol(tok)){
				protocol_elementPTR protocols;
				init_protocol_elem(&protocols);
				protokol_block(tok->type,&protocols);
				get_protocol_string(&protocols);
				strcat(tmp2,get_protocol_string(&protocols));
				tok=get_token();
			}
			else
				ERROR(ERR_SYN,"Error in main_body block");

		}
	
	}
	strcpy(router->interface_list,tmp);
	//strcat(router->interface_list,tmp2);
	//printf("TMP2:%s\n", tmp2);
	//strcpy(router->protocol_list,tmp2);
}

int main(int argc, char *argv[]){
	
	read_file(argc,argv);
	router_elementPTR router;
	init_router_elem(&router);
	char *text=(char *) malloc(sizeof(char) * 3000);

	tok=init_token();
	tok->type=UNDEFINED;
	while(tok->type!=END_OF_FILE){


		tok = get_token();
		if(tok->type==TYPE_WORD)
		{
			router.name=tok->attribute;
			tok=get_token();
			if(tok->type==TYPE_BLOCK_BEGIN){
				main_body(&router);
				strcpy(text,create_text(&router));
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
	printf("%s\n", text);
	//print_routers(&router);
	//free(tok);
	//free_router(&router);
	close_file();
	ERROR(ERR_OK,"END");
}