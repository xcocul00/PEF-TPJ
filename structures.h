
//PROTOCOLS
/*
* structure contains information about protocols
* it's part of router structure
*/
typedef struct protocol_element {
	int name;
	int system;
	char *networks;	
}protocol_elementPTR;

//INTERFACES
/*
* structure contains information about interfaces
* it's part of router structure
*/
typedef struct interface_element {
	char *name;
	char *IP;
	char *MASK;
	bool state;	
}interface_elementPTR;

//ROUTERS
/*
* structure contains information about router configuration
*/
typedef struct router_element{
	char *name;
	bool banner_mode;
	char *banner_message;
	char *password;
	int password_type; //0-en 1-con 2-aux 3-vty
	int vty_num;
	char *interface_list;
}router_elementPTR;

//prototypes
void init_protocol_elem(protocol_elementPTR *element);
void init_interface_elem(interface_elementPTR *element);
void init_router_elem(router_elementPTR *element);
void free_router(router_elementPTR *element);

