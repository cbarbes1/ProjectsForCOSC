/* This bison-input file simply declares tokens for DJ programs
     (enumerated below on all the lines that begin with %token)
     and has a main funtion to repeatedly invoke the lexer.
*/

%code provides {
  #include "lex.yy.c"

  /* Function for printing generic syntax-error messages */
  void yyerror(const char *str) {
    printf("Syntax error on line %d at token %s\n",
           yylineno,yytext);
    printf("Halting compiler.\n");
    exit(-1);
  }
}


%token ENDFILE ERROR
%token IF THEN ELSE END REPEAT UNTIL READ WRITE
%token ID NUM
%token ASSIGN EQ LT PLUS MINUS TIMES OVER LPAREN RPAREN SEMI 


%start pgm

%%

pgm : 
    ;

%%

int main(int argc, char **argv) {
  if(argc!=2) {
    printf("Usage: tiny-lex  input-filename\n");
    exit(-1);
  }
  // open the input file
  yyin = fopen(argv[1],"r");
  if(yyin==NULL) {
    printf("ERROR: could not open file %s\n",argv[1]);
    exit(-1);
  }
  // tokenize the input file
  while(yylex()!=ENDFILE) { }
  return 0;
}

