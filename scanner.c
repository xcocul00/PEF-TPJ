#include "scanner.h"

#define BUFF_SIZE 101
static FILE* file;

char actual='\0';
char next='\0';


void read_file(int argc,char **argv){
	if(argc==3)
	{
		
		file = fopen(argv[1],"r");
	}
	else
		ERROR(ERR_FAIL,"Bad params");
	if (file!=NULL){
		printf("sdfsdfsd\n");
		fclose(file);
	}
}

char get_char(){
	if(file!=NULL){
		return getc(file);}
	else{
		ERROR(ERR_FAIL,"Bad pdfarams");
		return 'f';
	}
}


token * init_token(){
	token *token = malloc (sizeof(token));
	token->attribute = NULL;
	token->type = UNDEFINED;
	return token;
}


token * get_token(){
	token *token;
	token=init_token();
	
	if(actual=='\0'){
		actual=get_char();
		token->type=9;
		//token->attribute="a";
	}
	return token;
}

void ERROR(errors code, const char* message){
	fprintf(stderr,"ERR:%d, %s\n",code,message);
	exit(code);
}