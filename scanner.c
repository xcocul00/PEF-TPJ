#include "scanner.h"

#define BUFF_SIZE 101
static FILE* file;

char actual='\0';
char next='\0';


void read_file(int argc,char **argv){
	if(argc==2)
	{
		if(!strcmp(argv[1],"--help"))
		{
			help();
		}
		file = fopen(argv[1],"r");
	}
	else
		ERROR(ERR_PARAM,"Bad params, try use --help");
}

void help(){
	printf("Using of CISCO parser :\n\t parser [input file]\n\t"
			" parser [--help]\n");
	ERROR(ERR_OK, " ");
}

void close_file(){
	if(file!=NULL){
		fclose(file);
	}
}

char get_char(){
	if(file!=NULL)
		return getc(file);

	ERROR(ERR_FILE,"Bad pdfarams");
	return 'f';
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

type_of_token char_type(char x){
	type_of_token type=UNDEFINED;
	switch (x) {
		case '/':
			type=TYPE_DIV;
			break;
		case '-':
			type=TYPE_SUB;
			break;
		case '.':
			type=TYPE_DOT;
			break;
		case ':':
			type=TYPE_COLON;
			break;
		case '{':
			type=TYPE_BLOCK_BEGIN;
			break;
		case '}':
			type=TYPE_BLOCK_END;
			break;
		case '(':
			type=TYPE_LEFT_BRACKET;
			break;
		case ')':
			type=TYPE_RIGHT_BRACKET;
			break;		
	}
	return type;
}

bool is_number(char x){
	if(((int)x >= (int)'0') && ((int)x <= (int)'9'))
		return true;
	else
		return false;
}

bool is_word(char x){
	if((((int)x >= (int)'A')&&((int)x <= (int)'Z')) || (((int)x >= (int)'a')&&((int)x <= (int)'z')))
		return true;
	else
		return false;
}

token * get_token(){
	token *token;
	token=init_token();
	int cnt=1;
	int lenght=1;
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
	else if(char_type(actual)!=UNDEFINED){
		token->type=char_type(actual);
		actual='\0';
		return token;
	}
	else if(is_word(actual) || actual=='#'){
		char buff[BUFF_SIZE];
		buff[0]=actual;
		actual=get_char();
		
		while((actual!=EOF) && (is_word(actual) || is_number(actual) || actual=='#')){
			buff[lenght]=actual;
			cnt++;
			lenght=cnt%BUFF_SIZE;
			actual=get_char();
		}
		buff[lenght]='\0';
		token->attribute=(char*)malloc(100);
		strncpy(token->attribute,buff,lenght);
		token->type=TYPE_WORD;

		for(int i=0; i<KEY_COUNT; i++){
			
			if(!strcmp(key_words[i],buff)){
				token->type=i+12;
				token->attribute=NULL;
			}
		}

	}
	else if(is_number(actual)){
		char buff[BUFF_SIZE];
		buff[0]=actual;
		actual=get_char();
		while((actual!=EOF) && (is_number(actual)) && (cnt<=BUFF_SIZE) ){
			buff[lenght]=actual;
			cnt++;
			lenght=cnt % BUFF_SIZE;
			actual=get_char();
		}
		buff[lenght]='\0';
		token->attribute=(char *)malloc(100);
		strncpy(token->attribute,buff,lenght);
		token->type=TYPE_NUMBER;
	}
	return token;
}

void ERROR(errors code, const char* message){
	fprintf(stderr,"ERR:%d, %s\n",code,message);
	exit(code);
}