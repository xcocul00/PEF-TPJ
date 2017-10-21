#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

typedef enum {
	UNDEFINED,  //0
	TEST,
} type_of_token;


typedef struct {
	char *attribute;
	type_of_token type;
}token;