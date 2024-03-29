#include "structures.c"

#define config_first_part "!\nversion 15.4\nservice timestamps debug datetime msec\nservice timestamps log datetime msec\nno service password-encryption\n!\n"
#define config_second_part "!\nboot-start-marker\nboot-end-marker\n!\n!\n!\nno aaa new-model\nmmi polling-interval 60\nno mmi auto-configure\nno mmi pvc\nmmi snmp-timeout 180\n!\n!\n!\nip cef\nno ipv6 cef\n!\nmultilink bundle-name authenticated\n!\n!\n!\nredudancy\n!\n!\n!\n"
#define config_third_part "!\nip forward-protocol nd\n!\n!\nno ip http server\nno ip http secure-server\n!\n!\n!\ncontrol-plane\n!\n!\n!\n"
#define config_fourth_part "transport input none\n!\n!\nend"


// prototypes
// helpfull functions
void print_file(char * name, char * text);
bool is_protocol(token *tok);

//syntax and semantic check
void banner_block(router_elementPTR *router);
void password_block(router_elementPTR *router);
char* check_ip();
void interface_block(interface_elementPTR *interfaces);
void protokol_block(int x, protocol_elementPTR *protocols);
void main_body(router_elementPTR *router);
