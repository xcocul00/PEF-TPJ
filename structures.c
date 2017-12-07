#include "structures.h"

void Init_protocolList(protocol_list *L){
	L->actual=NULL;
	L->first=NULL;
}

void Init_interfacesList(interface_list *L){
	L->actual=NULL;
	L->first=NULL;
}
/*
void Init_routersList(routers_list *L){
	L->actual=NULL;
	L->first=NULL;
}
*/
protocol_elementPTR init_protocol_elem(){
	protocol_elementPTR element=malloc(sizeof(protocol_elementPTR));
	element->name=0;
	element->system=0;
	element->networks=NULL;
	element->next=NULL;
	return element;
}

interface_elementPTR init_interface_elem(){
	interface_elementPTR element=malloc(sizeof(interface_elementPTR));
	element->name=NULL;
	element->IP=NULL;
	element->MASK=NULL;
	element->next=NULL;
	element->state=false;
	return element;
}

void init_router_elem(router_elementPTR *element){
	element->name=malloc(sizeof(char *)*10);
	element->banner_mode=false;
	element->banner_message=malloc(sizeof(char *)*32);
	element->password=malloc(sizeof(char *)*30);
	element->password_type=0;
	element->vty_num=0;
}

void print_protocol(protocol_elementPTR node){
	printf("*****\nPRINT PROTOKOL %d\n",node->name);
	printf("AS/ID/AREA %d\n",node->system);
	printf("networks %s\n",node->networks);
	if(node->next!=NULL){
		printf("NOT LAST\n******\n");
	}
	else
		printf("LAST\n******\n");
}

void print_interfaces(interface_elementPTR node){
	printf("*****\nPRINT INT %s\n",node->name);
	printf("IP %s\n",node->IP);
	printf("MASK %s\n",node->MASK);
	printf("STATE %s\n",node->state?"true":"false");
	if(node->next!=NULL){
		printf("NOT LAST\n******\n");
	}
	else
		printf("LAST\n******\n");
}

void print_routers(router_elementPTR *element){
	printf("********ROUTER************\nROUTER: %s\n",element->name);
	printf("BANNER MODE: %s\n", element->banner_mode?"true":"false" );
	printf("MESSAGE: %s\n", element->banner_message);
	printf("PASSWORD: %s\n",element->password );
	printf("PASSWD TYPE: %d\n",element->password_type);
	printf("VTY: %d\n", element->vty_num );
	printf("************END ROUTER**********\n");
}


void free_router(router_elementPTR *element){
	free(element->name);
	free(element->banner_message);
	free(element->password);
}

