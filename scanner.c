#include "scanner.h"

#define BUFF_SIZE 101
static FILE* file;

char actual='\0';
char next='\0';


void read_file(int argc,char **argv){
	if(argc==3)
	{
		file = fopen(argv[1],"r");
		if(file==NULL){
			printf("prazdny\n");
		}
	}
	else
		ERROR(ERR_FAIL,"Bad params");
}

void close_file(){
	if(file!=NULL){
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

bool is_whitechar(char a){
	if(((int)a == (int)' ') || ((int)a == (int)'\n') || ((int)a == (int)'\r') || ((int)a == (int)'\t'))
		return true;
	else
		return false;
}

void skip_comments(){
	char a = get_char();
	bool stop_cykle=false; 
	if(a=='/'){
		while(actual!=EOF && actual!=10){
			actual=get_char();
		}
	}
	else if (a=='*'){
		while(actual!=EOF && !stop_cykle){
			actual=get_char();
			if(actual=='*'){
				next=get_char();
				if(next=='/')
					stop_cykle=true;
			}
		}
	}
	next='\0';
}

void skip_spaces(){
	while(actual!=EOF && (is_whitechar(actual) || actual=='/')){
		if(is_whitechar(actual))
			actual=get_char();
		else if(actual=='/')
		{
			skip_comments();
			actual=get_char();
		}
		
	}
}


token * get_token(){
	token *token;
	token=init_token();
	
	if(actual=='\0'){
		actual=get_char();
		skip_spaces();
	}
	if(is_whitechar(actual)){
		skip_spaces();
	}
	if(actual==EOF){
		token->type=END_OF_FILE;
		return token;
	}
	return token;
}

void ERROR(errors code, const char* message){
	fprintf(stderr,"ERR:%d, %s\n",code,message);
	exit(code);
}