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
	strcat(string,config_second_part);
	//INTERFACE PROTOKOL
	strcat(string,config_third_part);
	//hesla atd
	return string;

}