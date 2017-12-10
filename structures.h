
//PROTOCOLS
typedef struct protocol_element {
	struct protocol_element *next;
	int name;
	int system;
	char *networks;	
}*protocol_elementPTR;

//INTERFACES
typedef struct interface_element {
	//struct interface_element *next;
	char *name;
	char *IP;
	char *MASK;
	bool state;	
}interface_elementPTR;


//ROUTERS
typedef struct router_element{
	char *name;
	bool banner_mode;
	char *banner_message;
	char *password;
	int password_type; //0-en 1-con 2-aux 3-vty
	int vty_num;
	char *interface_list;
}router_elementPTR;

typedef struct {
	router_elementPTR actual;
	router_elementPTR first;
}routers_list;



