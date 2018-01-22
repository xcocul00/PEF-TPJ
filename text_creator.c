#include "text_creator.h"

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

char * parse_banner(char * string){
	string++;
	string[strlen(string)-1] = 0;
	return string;
}

char * get_interface_string(interface_elementPTR *list){
	char *string = (char *) malloc(sizeof(char) * 100);
	strcpy(string,intf);
	strcat(string,list->name);
	strcat(string,ip_add);
	strcat(string,list->IP);
	strcat(string,space);
	strcat(string,list->MASK);
	if(list->state){
		strcat(string,line);
		strcat(string," no shutdown");
	}
	else{
		strcat(string,line);
		strcat(string," shutdown");
	}
	strcat(string,end);
	return string;
}

char* get_protocol_string(protocol_elementPTR *list){
	char *string = (char *) malloc(sizeof(char) * 100);
	strcpy(string,"router ");
	strcat(string,protokol_type(list->name));
	if(list->name==20 || list->name==21){
		char buff [3];
		strcat(string," ");
		sprintf(buff,"%d",list->system);
		strcat(string,buff);
	}
	strcat(string,"\n");
	strcat(string,space);
	strcat(string,list->networks);
	strcat(string,end);
	return string;
}

char* create_text(router_elementPTR *list){
	char *string = (char *) malloc(sizeof(char) * 2000);
	strcpy(string,config_first_part);
	strcat(string,"hostname ");
	strcat(string,list->name);
	strcat(string,line);
	if(list->password_type==0){
		strcat(string,"!\n!\n!\nenable password ");
		strcat(string,list->password);
		strcat(string,end);
	}
	strcat(string,config_second_part);
	strcat(string,list->interface_list);
	strcat(string,config_third_part);
	if(strlen(list->banner_message)!=0){
		if(list->banner_mode){
			strcat(string,"banner motd ");
		}
		else{
			strcat(string,"banner login ");
		}
		//strcat(string,list->banner_message);
		strcat(string,parse_banner(list->banner_message));
		strcat(string,end);
	}
	strcat(string,"line con 0\n");
	if(list->password_type==1){
		strcat(string," password ");
		strcat(string,list->password);
		strcat(string,line);
	}
	strcat(string," logging synchronous\n");
	strcat(string,"line aux 0\n");
	if(list->password_type==2){
		strcat(string," password ");
		strcat(string,list->password);
		strcat(string,line);
	}	
	strcat(string,"line vty 0 ");
	char tmp[2];
	sprintf(tmp,"%d",list->vty_num);
	strcat(string,tmp);
	strcat(string,line);
	if(list->password_type==3){
		strcat(string," password ");
		strcat(string,list->password);
		strcat(string,line);
	}
	strcat(string," login\n!\n");
	strcat(string,config_fourth_part);	
	//hesla atd
	return string;

}