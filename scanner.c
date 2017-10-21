#include "scanner.h"

#define BUFF_SIZE 101


token * init_token(){
	token *token = malloc (sizeof(token));
	token->attribute = NULL;
	token->type = UNDEFINED;
	return token;
}


//char get_token()

token * get_token(){
	token *token;
	token=init_token();
	token->type=TEST;
	return token;
}