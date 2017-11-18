
//PROTOCOLS
typedef struct protocol_element {
	struct protocol_element *next;
	int name;
	int system;
	char *networks;	
}*protocol_elementPTR;

typedef struct {
	protocol_elementPTR actual;
	protocol_elementPTR first;
}protocol_list;

//INTERFACES
typedef struct interface_element {
	struct interface_element *next;
	char *name;
	char *IP;
	char *MASK;
	bool state;	
}*interface_elementPTR;

typedef struct {
	interface_elementPTR actual;
	interface_elementPTR first;
}interface_list;

//ROUTERS
typedef struct router_element{
	struct router_element *next;
	bool banner_mode;
	char *banner_message;
	char *password;
	int password_type; // 1-con 2-aux 3-vty
	int vty_num;
	// doplnit listy	
}*router_elementPTR;

typedef struct {
	router_elementPTR actual;
	router_elementPTR first;
}routers_list;



//PROTOTYPES
void Init_protocolList (protocol_list *);
protocol_elementPTR init_protocol_elem();