#define intf "interface "
#define ip_add "\n ip address "
#define space " "
#define line "\n"
#define end "\n!\n!\n"

//prototypes
char * protokol_type(int type);
char * parse_banner(char * string);
char * get_interface_string(interface_elementPTR *list);
char* get_protocol_string(protocol_elementPTR *list);
char* create_text(router_elementPTR *list);


