#include "structures.h"

void init_protocol_elem(protocol_elementPTR *element){
	element->networks=malloc(sizeof(char *)*100);
	element->name=0;
	element->system=0;
}

void init_interface_elem(interface_elementPTR *element){
	element->name=malloc(sizeof(char *)*8);
	element->IP=malloc(sizeof(char *)*20);
	element->MASK=malloc(sizeof(char *)*20);
	element->state=false;
}


void init_router_elem(router_elementPTR *element){
	element->name=malloc(sizeof(char *)*10);
	element->banner_mode=false;
	element->banner_message=malloc(sizeof(char *)*32);
	element->password=malloc(sizeof(char *)*30);
	element->password_type=0;
	element->vty_num=0;
	element->interface_list=malloc(sizeof(char *)*100);
	element->protocol_list=malloc(sizeof(char *)*100);
}

void print_protocol(protocol_elementPTR *node){
	printf("*****\nPRINT PROTOKOL %d\n",node->name);
	printf("AS/ID/AREA %d\n",node->system);
	printf("networks:\n%s\n",node->networks);
}

void print_interfaces(interface_elementPTR *node){
	printf("*****\nPRINT INT %s **********\n",node->name);
	printf("IP %s\n",node->IP);
	printf("MASK %s\n",node->MASK);
	printf("STATE %s\n",node->state?"true":"false");
}

void print_routers(router_elementPTR *element){
	printf("********ROUTER************\nROUTER: %s\n",element->name);
	printf("BANNER MODE: %s\n", element->banner_mode?"true":"false" );
	printf("MESSAGE: %s\n", element->banner_message);
	printf("PASSWORD: %s\n",element->password );
	printf("PASSWD TYPE: %d\n",element->password_type);
	printf("VTY: %d\n", element->vty_num );
	printf("INTERFACES:\n%s\n",element->interface_list);
	//printf("PROTOCOLS:\n%s\n",element->protocol_list);
	printf("************END ROUTER**********\n");
}


void free_router(router_elementPTR *element){
	free(element->name);
	free(element->banner_message);
	free(element->password);
}

