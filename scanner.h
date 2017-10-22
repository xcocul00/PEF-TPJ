#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#define KEY_COUNT 14

typedef enum {
	UNDEFINED,  //0
	END_OF_FILE,
	TEST,
} type_of_token;

typedef enum {
	ERR_OK,
	ERR_FAIL,
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
	"not_shutdown",
	"RIP",
	"RIPv2",
	"EIGRP",
	"OSPF",
	"no_auto_summary",
	"con",
	"aux",
	"vty",
};



void ERROR(errors code, const char* message);
void read_file(int argc,char **argv);
char get_char();
token * init_token();
token * get_token();
