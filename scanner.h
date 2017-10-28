#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#define KEY_COUNT 15

typedef enum {
	UNDEFINED,  //0
	END_OF_FILE,
	
	TYPE_DIV,	//2
	TYPE_SUB,
	TYPE_DOT,
	TYPE_COLON,
	TYPE_BLOCK_BEGIN,
	TYPE_BLOCK_END,
	TYPE_LEFT_BRACKET,
	TYPE_RIGHT_BRACKET,

	TYPE_NUMBER,		//10
	TYPE_WORD,

	TYPE_BANNER,		//12
	TYPE_MOTD,
	TYPE_LOGIN,
	TYPE_INT,
	TYPE_SHUTDOWN,
	TYPE_NO,
	TYPE_RIP,
	TYPE_RIPV2,
	TYPE_EIGRP,
	TYPE_OSPF,
	TYPE_SUMMARY,
	TYPE_CON,
	TYPE_AUX,
	TYPE_VTY,
	TYPE_PASSWORD,

} type_of_token;

typedef enum {
	ERR_OK,
	ERR_PARAM, //bad params
	ERR_FILE,  //file empty
}errors;



typedef struct {
	char *attribute;
	type_of_token type;
}token;

const char * const key_words[] = {
	"banner",
	"motd",
	"login",
	"int",
	"shutdown",
	"no",
	"RIP",
	"RIPv2",
	"EIGRP",
	"OSPF",
	"summary",
	"con",
	"aux",
	"vty",
	"password",
};



void help();
void ERROR(errors code, const char* message);
void read_file(int argc,char **argv);
char get_char();
token * init_token();
token * get_token();
bool is_number(char x);
