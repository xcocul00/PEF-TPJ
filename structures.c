#include "structures.h"

void Init_protocolList(protocol_list *L){
	L->actual=NULL;
	L->first=NULL;
}

void Init_interfacesList(interface_list *L){
	L->actual=NULL;
	L->first=NULL;
}

void Init_routersList(routers_list *L){
	L->actual=NULL;
	L->first=NULL;
}

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

router_elementPTR init_router_elem(){
	router_elementPTR element=malloc(sizeof(router_elementPTR));
	element->banner_mode=false;
	element->banner_message=NULL;
	element->password=NULL;
	element->password_type=0;
	element->vty_num=0;
	return element;
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

