#include "text_creator.h"

 char * get_interface_string(interface_elementPTR *list){
	char *string = (char *) malloc(sizeof(char) * 200);
	strcpy(string,intf);
	strcat(string,list->name);
	strcat(string,ip_add);
	strcat(string,list->IP);
	strcat(string,space);
	strcat(string,list->MASK);
	strcat(string,end);
	return string;
}